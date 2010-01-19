#include "common.hpp"

Texture::Texture()
	: _has_transparency(false)
{
	glGenTextures(1, &_id);
}

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
}

void
Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

