#ifndef MAP_HPP
#define MAP_HPP

class Map {
	typedef std::map<unsigned int, Geometry> Part;

	enum FaceType {
		LidFace,
		TopFace,
		RightFace,
		BottomFace,
		LeftFace
	};

	struct FileHeader {
		char name[4];
		uint16_t version;
	};

	struct ChunkHeader {
		char type[4];
		uint32_t size;
	};

	struct BlockInfo {
		uint16_t left, right, top, bottom, lid;
		uint8_t arrows; 
		uint8_t slope_type;
	};

	struct CompressedMap {
		uint32_t* base;
		uint32_t column_words;
		uint32_t* columns;
		uint32_t num_blocks;
		BlockInfo* blocks;
	};

	struct ColInfo {
		uint8_t height;
		uint8_t offset;
		uint16_t pad;
		uint32_t blockd[8];
	};

	public:
		Map(Engine&, std::string filename);
		~Map();
		void draw();
	private:
		Engine& _engine;
		char* _map_data;
		CompressedMap _compressed_map;
		GtaStyle _style;
		const BlockInfo& getBlock(uint32_t) const;
		void loadTextures();
		void drawBlock(const BlockInfo& block);
		void drawFace(const uint16_t&, bool, const Vector3&, const Vector3&, const Vector3&, const Vector3&);
		const int _part_size;
		std::vector<Part> _parts;

		void addBlock(const BlockInfo&, const Vector3&, Part&);
		void addFace(const uint16_t&, Map::FaceType, const Quad<Vector3>&, const Vector3&, Part&);
		std::vector<Vector3> constructLid(int, int);
};

#endif

