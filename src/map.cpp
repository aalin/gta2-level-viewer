#include "common.hpp"

Map::Map(Engine& engine, std::string filename)
	: _engine(engine), _style(filename + ".sty"), _part_size(16)
{
	std::ifstream f((filename + ".gmp").c_str());

	f.seekg(0, std::ios::end);
	int size = f.tellg();
	f.seekg(0, std::ios::beg);

	_map_data = new char[size];
	f.read(_map_data, size);

	f.close();

	char* offset = _map_data;

	FileHeader* file_header = reinterpret_cast<FileHeader*>(offset);

	std::string hdr(file_header->name, 0, 4);
	if(hdr != "GBMP")
		throw std::runtime_error("wrong header: \"" + hdr + "\"");
	if(file_header->version != 500)
		throw std::runtime_error("wrong version");

	std::cout << "GBMP Version: " << file_header->version << std::endl;

	offset += sizeof(FileHeader);

	while(offset < _map_data + size)
	{
		ChunkHeader* chunk_header = reinterpret_cast<ChunkHeader*>(offset);
		offset += sizeof(ChunkHeader);
		std::string chunk_hdr(chunk_header->type, 0, 4);
		std::cout << "found: " << chunk_hdr << " at " << offset - _map_data << std::endl;

		if(chunk_hdr == "DMAP")
		{
			_compressed_map.base = reinterpret_cast<uint32_t*>(offset);
			offset += 256 * 256 * sizeof(uint32_t);

			_compressed_map.column_words = *reinterpret_cast<uint32_t*>(offset);
			offset += sizeof(uint32_t);

			_compressed_map.columns = reinterpret_cast<uint32_t*>(offset);
			offset += _compressed_map.column_words * sizeof(uint32_t);

			_compressed_map.num_blocks = *reinterpret_cast<uint32_t*>(offset);
			offset += sizeof(uint32_t);

			_compressed_map.blocks = reinterpret_cast<BlockInfo*>(offset);
			offset += _compressed_map.num_blocks * sizeof(BlockInfo);
		}
		else
		{
			std::cout << "skipping " << chunk_header->size << " bytes on \"" << chunk_hdr << "\" offset: " << (int)(offset - _map_data) << std::endl;
			offset += chunk_header->size;
		}
	}

	_parts.reserve(_part_size * _part_size);
	for(int i = 0; i < 256 / _part_size; i++)
	{
		for(int j = 0; j < 256 / _part_size; j++)
		{
			Part part;
			
			for(int z = 8; z >= 0; z--)
			{
				for(int y = 0; y < _part_size; y++)
				{
					for(int x = 0; x < _part_size; x++)
					{
						const uint32_t offset = _compressed_map.base[(y + i * _part_size) * 256 + x + j * _part_size];
						ColInfo* column = reinterpret_cast<ColInfo*>(_compressed_map.columns + offset);

						if(z < column->height - column->offset)
						{
							uint32_t block = column->blockd[z];
							Vector3 block_offset(x, -y, z + column->offset);
							addBlock(getBlock(block), block_offset, part);
						}

						/*
						for(int z = 0; z < column->height - column->offset; z++)
						{
							uint32_t block = column->blockd[z];
							Vector3 block_offset(x, -y, z + column->offset);
							addBlock(getBlock(block), block_offset, part);
						}*/
					}
				}
			}

			_parts.push_back(part);
		}
	}
}

Map::~Map()
{
	delete[] _map_data;
}

void
Map::draw()
{
	//for(int part_y = 0; part_y < 256 / _part_size; part_y++)
	for(int part_y = 0; part_y < 8; part_y++)
	{
		//for(int part_x = 0; part_x < 256 / _part_size; part_x++)
		for(int part_x = 0; part_x < 8; part_x++)
		{
			glPushMatrix();
				glTranslatef(part_x * _part_size, -part_y * _part_size, 0);
				Part& part = _parts[part_y * _part_size + part_x];
				for(Part::iterator it = part.begin(); it != part.end(); it++)
				{
					if(it->first < 992)
					{
						_style.getTexture(it->first)->bind();
						it->second.draw();
					}
				}
			glPopMatrix();
		}
	}
}

std::vector<Vector3>
Map::constructLid(int slope, int num_levels)
{
	std::vector<Vector3> lid;
	lid.reserve(4);
	
	if(slope == 0)
	{
		lid.push_back(Vector3(0, 0, 0));
		lid.push_back(Vector3(1, 0, 0));
		lid.push_back(Vector3(1, 1, 0));
		lid.push_back(Vector3(0, 1, 0));
		return lid;
	}

	float height = 1.0 / num_levels;
	int level = slope % num_levels;
	float low = height * level - height * num_levels;

	lid.push_back(Vector3(0, 0, low));
	lid.push_back(Vector3(1, 0, low));
	lid.push_back(Vector3(1, 1, low));
	lid.push_back(Vector3(0, 1, low));

	// this is weird, everything seems to be mirrored and upside down... :/
	switch(slope / num_levels)
	{
		case 0: // up
			lid[2] += Vector3(0, 0, height);
			lid[3] += Vector3(0, 0, height);
			break;
		case 1: // down
			lid[0] += Vector3(0, 0, height);
			lid[1] += Vector3(0, 0, height);
			break;
		case 2: // right
			lid[0] += Vector3(0, 0, height);
			lid[3] += Vector3(0, 0, height);
			break;
		case 3: // left
			lid[1] += Vector3(0, 0, height);
			lid[2] += Vector3(0, 0, height);
			break;
	}

	return lid;
}

void
Map::addBlock(const BlockInfo& block, const Vector3& offset, Part& part)
{
	int slope_type = block.slope_type >> 2;
	std::vector<Vector3> lid(4);
	int rotation = 0;

	if(Range<int>(1, 8).include(slope_type))
		lid = constructLid(slope_type - 1, 2);
	else if(Range<int>(9, 40).include(slope_type))
		lid = constructLid(slope_type - 9, 8);
	else if(Range<int>(41, 44).include(slope_type))
		lid = constructLid(slope_type - 41, 1);
	else
		lid = constructLid(0, 0);

	Quad<Vector3> lid_face = {
		lid[0],
		lid[1],
		lid[2],
		lid[3]
	};

	Quad<Vector3> bottom_face = {
		Vector3(0, 0, -1),
		Vector3(1, 0, -1),
		lid[1],
		lid[0]
	};

	Quad<Vector3> top_face = {
		Vector3(0, 1, -1),
		Vector3(1, 1, -1),
		lid[2],
		lid[3]
	};

	Quad<Vector3> left_face = {
		Vector3(0, 0, -1),
		Vector3(0, 1, -1),
		lid[3],
		lid[0]
	};

	Quad<Vector3> right_face = {
		Vector3(1, 1, -1),
		Vector3(1, 0, -1),
		lid[1],
		lid[2]
	};

	addFace(block.lid,    Map::LidFace,    lid_face,    offset, part);
	addFace(block.bottom, Map::BottomFace, bottom_face, offset, part);
	addFace(block.top,    Map::TopFace,    top_face,    offset, part);
	addFace(block.left,   Map::LeftFace,   left_face,   offset, part);
	addFace(block.right,  Map::RightFace,  right_face,  offset, part);
}

void
Map::addFace(const uint16_t& face, Map::FaceType face_type, const Quad<Vector3>& face_quad, const Vector3& offset, Part& part)
{
	if(unsigned int texture = face & 0x3ff)
	{
		std::vector<Vertex> vertices(4);
		vertices[0].position = face_quad.tl;
		vertices[1].position = face_quad.tr;
		vertices[2].position = face_quad.bl;
		vertices[3].position = face_quad.br;

		vertices[0].texcoord = Vector2(0, 0);
		vertices[1].texcoord = Vector2(1, 0);
		vertices[2].texcoord = Vector2(1, 1);
		vertices[3].texcoord = Vector2(0, 1);

		bool flip = face & 0x2000;
		if(flip)
			for(std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
				it->texcoord = Matrix4x4::scale(Vector3(-1, 1, 1)) * it->texcoord;

		for(std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
			it->texcoord = Matrix4x4::scale(Vector3(1,-1, 1)) * it->texcoord;

		unsigned int rotation = (face >> 14) * 90;
		for(std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
		{
			it->texcoord = Matrix4x4::translation(Vector3(-0.5, -0.5, 0)) * it->texcoord;
			it->texcoord = Matrix4x4::rotationZ(Degrees(360 - rotation)) * it->texcoord;
			it->texcoord = Matrix4x4::translation(Vector3(0.5, 0.5, 0)) * it->texcoord;
		}

		for(std::vector<Vertex>::iterator it = vertices.begin(); it != vertices.end(); it++)
			it->position += offset;

		part[texture].pushVertex(vertices[0]);
		part[texture].pushVertex(vertices[1]);
		part[texture].pushVertex(vertices[2]);
		part[texture].pushVertex(vertices[0]);
		part[texture].pushVertex(vertices[2]);
		part[texture].pushVertex(vertices[3]);
	}
}

const Map::BlockInfo&
Map::getBlock(uint32_t index) const
{
	if(index < _compressed_map.num_blocks)
		return _compressed_map.blocks[index];
	throw "Map::getBlock: index out of bounds";
}

