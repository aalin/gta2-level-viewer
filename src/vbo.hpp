#ifndef VBO_HPP
#define VBO_HPP

class VBO {
	public:
		enum Usage
		{
			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY
		};
		VBO();
		~VBO();
		template<typename T> void updateData(const std::vector<T>&, Usage);

		void bind();
	private:
		GLuint _buffer_id;
};

template<typename T>
void
VBO::updateData(const std::vector<T>& data, Usage usage)
{
	const GLsizeiptr byte_size = sizeof(T) * data.size();
	glBindBuffer(GL_ARRAY_BUFFER, _buffer_id);
	glBufferData(GL_ARRAY_BUFFER, byte_size, &data[0], usage);
}

#endif

