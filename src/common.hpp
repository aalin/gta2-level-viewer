#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <map>
#include <vector>
#include <cmath>

#include <boost/shared_ptr.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/operators.hpp>
#include <boost/format.hpp>

#include <SDL/SDL.h>

#define GL_GLEXT_PROTOTYPES

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#endif

#include "texture.hpp"

#include "math.hpp"
#include "angle.hpp"
#include "range.hpp"

#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "vertex.hpp"

#include "matrix3x3.hpp"
#include "matrix4x4.hpp"

#include "quad.hpp"
#include "triangle.hpp"

#include "camera.hpp"

#include "engine.hpp"

#include "vbo.hpp"
#include "geometry.hpp"

#include "obj.hpp"
#include "gta_style.hpp"
#include "map.hpp"

#include "objects/abstract_object.hpp"

#include "states/abstract_state.hpp"
#include "states/play_state.hpp"
#include "states/test_state.hpp"

#endif

