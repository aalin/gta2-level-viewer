#ifndef GTA_STYLE_HPP
#define GTA_STYLE_HPP

class GtaStyle {
	struct FileHeader {
		char name[4];
		uint16_t version;
	};

	struct ChunkHeader {
		char type[4];
		uint32_t size;
	};

	struct PaletteBase {
		uint16_t tile;
		uint16_t sprite;
		uint16_t car_remap;
		uint16_t ped_remap;
		uint16_t code_obj_remap;
		uint16_t map_obj_remap;
		uint16_t user_remap;
		uint16_t font_remap;
	};

	struct PaletteIndex {
		uint16_t* phys_palette;
	};

	public:
		GtaStyle(std::string);
		~GtaStyle();
		boost::shared_ptr<Texture> getTexture(unsigned int);
	private:
		char* _data;
		PaletteIndex _palette_index;
		PaletteBase* _palette_base;
		uint32_t* _palette_data;
		uint8_t* _tiles;
		std::vector<boost::shared_ptr<Texture> > _textures;
		uint32_t getPaletteValue(int, uint8_t);
};

#endif

