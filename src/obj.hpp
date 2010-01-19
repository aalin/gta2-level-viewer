#ifndef OBJ_HPP
#define OBJ_HPP

	class Obj {
		public:
			Obj(Engine&, std::string);
			~Obj();
			void update();
			void draw();
		private:
			GLuint _list;
			Engine& _engine;
	};

#endif

