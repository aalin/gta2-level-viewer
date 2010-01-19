#include "../common.hpp"

namespace Objects {

	AbstractObject::AbstractObject(Engine& engine)
		: _engine(engine)
	{ }

	AbstractObject::~AbstractObject()
	{ }

}

