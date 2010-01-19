#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
	public:
		Texture();
		~Texture();
		void bind() const;
		void hasTransparency(bool value) { _has_transparency = value; }
		bool hasTransparency() const { return _has_transparency; }
	private:
		GLuint _id;
		bool _has_transparency;
};

#endif

