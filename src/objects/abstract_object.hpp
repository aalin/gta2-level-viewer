#ifndef ABSTRACT_OBJECT_HPP
#define ABSTRACT_OBJECT_HPP

namespace Objects {
	class AbstractObject {
		public:
			AbstractObject(Engine&);
			virtual ~AbstractObject();
			virtual void update() = 0;
			virtual void draw() = 0;
		protected:
			Engine& _engine;
	};
}

#endif

