#include "common.hpp"

VBO::VBO()
{
	glGenBuffers(1, &_buffer_id);
}

VBO::~VBO()
{
	glDeleteBuffersARB(1, &_buffer_id);
}

void
VBO::bind()
{
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, _buffer_id);
}

