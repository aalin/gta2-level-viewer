#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

class Geometry {
	public:
		Geometry();
		void draw();
		void pushVertex(const Vertex&);
	private:
		void readyBuffers();
		void drawBuffers();
		std::vector<Vector3> _positions;
		std::vector<Vector3> _normals;
		std::vector<Vector2> _texcoords;
		boost::shared_ptr<VBO> _position_buffer;
		boost::shared_ptr<VBO> _normal_buffer;
		boost::shared_ptr<VBO> _texcoord_buffer;
};

#endif

