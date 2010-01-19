#ifndef TEST_STATE_HPP
#define TEST_STATE_HPP

class TestState : public AbstractState {
	public:
		TestState(Engine&);
		void update();
		void draw();
	private:
		Camera _camera;
		Vector3 _pointzor;
		Vector3 _veczor;
};

#endif

