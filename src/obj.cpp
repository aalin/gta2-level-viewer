#include "common.hpp"

struct Face {
	std::vector<int> vectors;
	std::vector<int> tex_choords;
	std::vector<int> normals;
};



std::vector<std::string>
splitString(const std::string& str, char delimiter = '/')
{
	std::string::size_type last_pos  = str.find_first_not_of(delimiter, 0);
	std::string::size_type pos = str.find_first_of(delimiter, last_pos);

	std::vector<std::string> result;
	while(pos != std::string::npos || last_pos != std::string::npos)
	{
		result.push_back(str.substr(last_pos, pos - last_pos));
		last_pos = str.find_first_not_of(delimiter, pos);
		pos = str.find_first_of(delimiter, last_pos);
	}
	return result;
}

Obj::Obj(Engine& engine, std::string filename)
	: _engine(engine)
{
	std::cout << "OBJ(" << filename << ")" << std::endl;
	std::ifstream f(filename.c_str());
	if(!f.good())
		throw std::runtime_error("omg");

	std::vector<Vector3> vectors;
	std::vector<Face> faces;

	while(f.good())
	{
		std::string line;
		getline(f, line);

		std::stringstream ss;
		ss << line;

		std::string cmd;
		ss >> cmd;

		if(cmd == "v")
		{
			double x, y, z;
			ss >> x >> y >> z;
			Vector3 v(x, y, z);

			vectors.push_back(v);
		}
		else if(cmd == "f")
		{
			std::string rest;
			getline(ss, rest);
			std::vector<std::string> cols = splitString(rest, ' ');

			Face face;

			for(std::vector<std::string>::iterator it = cols.begin(); it != cols.end(); it++)
			{
				std::vector<std::string> v_t_n = splitString(*it, '/');
				if(v_t_n.size() > 0)
					face.vectors.push_back(boost::lexical_cast<int>(v_t_n[0]));
				else
					throw "No vertice specified";
			}

			faces.push_back(face);
		}
	}

	_list = glGenLists(1);
	glNewList(_list, GL_COMPILE);
	glColor3f(1.0, 1.0, 1.0);
	for(std::vector<Face>::iterator face_it = faces.begin(); face_it != faces.end(); face_it++)
	{
		switch(face_it->vectors.size())
		{
			case 3:
				glBegin(GL_TRIANGLES);
				break;
			case 4:
				glBegin(GL_QUADS);
				break;
			default:
				glBegin(GL_POLYGON);
				break;
		}

		for(std::vector<int>::iterator vector_it = face_it->vectors.begin(); vector_it != face_it->vectors.end(); vector_it++)
		{
			Vector3& v = vectors[*vector_it - 1];
			glVertex3f( v.x, v.y, v.z );
		}
	}
	glEnd();
	glEndList();
}

Obj::~Obj()
{
	glDeleteLists(_list, 1);
}

	void
Obj::update()
{ }

	void
Obj::draw()
{
	/*
	   glTranslatef(_matrix(0).getX(), _matrix(0).getY(), _matrix(0).getZ());
	   glRotatef(1, _matrix(1).getX(), _matrix(1).getY(), _matrix(0).getZ());
	   glScalef(    _matrix(2).getX(), _matrix(2).getY(), _matrix(0).getZ());*/

/*
	std::cout << _matrix(2).getX() << std::endl;
	std::cout << _matrix(2).getY() << std::endl;
	std::cout << _matrix(2).getZ() << std::endl;
	std::cout << std::endl;
*/
	glCallList(_list);
}
