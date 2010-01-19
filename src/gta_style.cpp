#include "common.hpp"

GtaStyle::GtaStyle(std::string filename)
{
	std::cout << "opening map: " << filename << std::endl;
	std::ifstream f(filename.c_str());

	f.seekg(0, std::ios::end);
	int size = f.tellg();
	f.seekg(0, std::ios::beg);

	std::cout << "allocating " << size << " bytes for map" << std::endl;
	_data = new char[size];
	f.read(_data, size);

	f.close();

	char* offset = _data;

	FileHeader* file_header = reinterpret_cast<FileHeader*>(offset);

	std::string hdr(file_header->name, 0, 4);
	if(hdr != "GBST")
		throw std::runtime_error("wrong header: \"" + hdr + "\"");
	if(file_header->version != 700)
		throw std::runtime_error("wrong version: " + boost::lexical_cast<std::string>(file_header->version));

	offset += sizeof(FileHeader);

	while(offset < _data + size)
	{
		ChunkHeader* chunk_header = reinterpret_cast<ChunkHeader*>(offset);
		offset += sizeof(ChunkHeader);
		std::string chunk_hdr(chunk_header->type, 0, 4);
		std::cout << "Found: " << chunk_hdr << " at " << offset - _data << ", size: " << chunk_header->size <<  std::endl;

		if(chunk_hdr == "PALX") // palette index
		{
			_palette_index.phys_palette = reinterpret_cast<uint16_t*>(offset);
			offset += chunk_header->size;
		}
		else if(chunk_hdr == "PPAL") // physical palettes
		{
			_palette_data = reinterpret_cast<uint32_t*>(offset);
			offset += chunk_header->size;
		}
		else if(chunk_hdr == "PALB") // palette base
		{
			_palette_base = reinterpret_cast<PaletteBase*>(offset);
			offset += sizeof(PaletteBase);
		}
		else if(chunk_hdr == "TILE")
		{
			_tiles = reinterpret_cast<uint8_t*>(offset);
			offset += chunk_header->size;
		}
		else
		{
			std::cout << "skipping " << chunk_header->size << " bytes on \"" << chunk_hdr << "\" offset: " << (int)(offset - _data) << std::endl;
			offset += chunk_header->size;
		}
	}

	_textures.reserve(992);
	const int page_size = 256 * 256;
	for(int page_num = 0; page_num < 62; page_num++)
	{
		uint8_t* page = _tiles + page_size * page_num;

		for(int y = 0; y < 4; y++)
		{
			for(int x = 0; x < 4; x++)
			{
				uint32_t tile[64*64];
				const int tile_index = page_num * 16 + y * 4 + x;
				int palette_index = _palette_index.phys_palette[tile_index];

				bool has_transparency = false;

				for(int tile_y = 0; tile_y < 64; tile_y++)
				{
					for(int tile_x = 0; tile_x < 64; tile_x++)
					{
						uint8_t c = page[(y * 64 + tile_y) * 256 + x * 64 + tile_x];
						if(c == 0)
						{
							has_transparency = true;
							tile[tile_y * 64 + tile_x] = 0x00000000;
						}
						else
						{
							tile[tile_y * 64 + tile_x] = getPaletteValue(palette_index, c) | 0xff000000;
						}
					}
				}

				boost::shared_ptr<Texture> texture(new Texture);
				texture->hasTransparency(has_transparency);
				texture->bind();
				glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 64, 64, GL_BGRA, GL_UNSIGNED_BYTE, tile);
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_BGRA, GL_UNSIGNED_BYTE, tile);
				_textures.push_back(texture);
			}
		}
	}
}

GtaStyle::~GtaStyle()
{
	delete[] _data;
}

boost::shared_ptr<Texture>
GtaStyle::getTexture(unsigned int index)
{
	if(index > _textures.size())
		throw std::runtime_error( boost::str(boost::format("index %d out of bounds") % index).c_str() );
	return _textures[index];
}

uint32_t
GtaStyle::getPaletteValue(int palette_index, uint8_t color_index)
{
	int page_start = (palette_index / 64) * 64 * 256 * 4;
	uint32_t* page = _palette_data + page_start;
	return page[(palette_index % 64) + color_index * 64];
}

