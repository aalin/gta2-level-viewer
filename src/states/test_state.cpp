#include "../common.hpp"

TestState::TestState(Engine& engine)
	: AbstractState(engine), _pointzor(Vector3(0.5, 0.5, 0.5)), _veczor(Vector3(-1.0,-1.0,-1.0))
{
	glFogf(GL_FOG_START, 10.0);
	glFogf(GL_FOG_END, 20.0);
	_camera.set(
		Vector3(3.5, 3.5, 3.5),
		Vector3(0.0, 0.0, 0.0),
		Vector3(0.0, 1.0, 0.0)
	);
}

void
TestState::update()
{
	Uint8* keys = SDL_GetKeyState(NULL);
	/*
	if(keys[SDLK_LEFT])
		_camera.rotateY(Degrees(1));
	if(keys[SDLK_RIGHT])
		_camera.rotateY(Degrees(-1));
	if(keys[SDLK_UP])
		_camera.rotateX(Degrees(1));
	if(keys[SDLK_DOWN])
		_camera.rotateX(Degrees(-1));
	if(keys[SDLK_q])
		_camera.rotateZ(Degrees(1));
	if(keys[SDLK_e])
		_camera.rotateZ(Degrees(-1));*/

	if(keys[SDLK_DOWN]) _pointzor = Matrix4x4::rotationX(Degrees(1)) * _pointzor;
	if(keys[SDLK_UP]) _pointzor = Matrix4x4::rotationX(Degrees(-1)) * _pointzor;
	if(keys[SDLK_LEFT]) _pointzor = Matrix4x4::rotationY(Degrees(1)) * _pointzor;
	if(keys[SDLK_RIGHT]) _pointzor = Matrix4x4::rotationY(Degrees(-1)) * _pointzor;
	if(keys[SDLK_q]) _pointzor = Matrix4x4::rotationZ(Degrees(-1)) * _pointzor;
	if(keys[SDLK_e]) _pointzor = Matrix4x4::rotationZ(Degrees(1)) * _pointzor;
}

void
TestState::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 800/600.0, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	_camera.draw();

	/*
	glPushMatrix();
		glBegin(GL_QUADS);
			glColor3f(0.0f,1.0f,0.0f);			// Set The Color To Green
			glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Top)
			glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Top)
			glVertex3f(-1.0f, 1.0f, 1.0f);			// Bottom Left Of The Quad (Top)
			glVertex3f( 1.0f, 1.0f, 1.0f);			// Bottom Right Of The Quad (Top)
			glColor3f(1.0f,0.5f,0.0f);			// Set The Color To Orange
			glVertex3f( 1.0f,-1.0f, 1.0f);			// Top Right Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f, 1.0f);			// Top Left Of The Quad (Bottom)
			glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Bottom)
			glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Bottom)
			glColor3f(1.0f,0.0f,0.0f);			// Set The Color To Red
			glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Front)
			glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Front)
			glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Front)
			glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Front)
			glColor3f(1.0f,1.0f,0.0f);			// Set The Color To Yellow
			glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Back)
			glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Back)
			glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Back)
			glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Back)
			glColor3f(0.0f,0.0f,1.0f);			// Set The Color To Blue
			glVertex3f(-1.0f, 1.0f, 1.0f);			// Top Right Of The Quad (Left)
			glVertex3f(-1.0f, 1.0f,-1.0f);			// Top Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f,-1.0f);			// Bottom Left Of The Quad (Left)
			glVertex3f(-1.0f,-1.0f, 1.0f);			// Bottom Right Of The Quad (Left)
			glColor3f(1.0f,0.0f,1.0f);			// Set The Color To Violet
			glVertex3f( 1.0f, 1.0f,-1.0f);			// Top Right Of The Quad (Right)
			glVertex3f( 1.0f, 1.0f, 1.0f);			// Top Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f, 1.0f);			// Bottom Left Of The Quad (Right)
			glVertex3f( 1.0f,-1.0f,-1.0f);			// Bottom Right Of The Quad (Right)
		glEnd();

	glPopMatrix();
*/
	glPushMatrix();
		glBegin(GL_LINES);
			glColor3f(1.0f,0.0f,0.0f);
			glVertex3f(-10.0,  0.0,  0.0);
			glVertex3f( 10.0,  0.0,  0.0);
			glColor3f(0.0f,1.0f,0.0f);
			glVertex3f(  0.0, 10.0,  0.0);
			glVertex3f(  0.0,-10.0,  0.0);
			glColor3f(0.0f,0.0f,1.0f);
			glVertex3f(  0.0,  0.0, 10.0);
			glVertex3f(  0.0,  0.0,-10.0);
		glEnd();

		glBegin(GL_POINTS);
			glColor3f(1.0f,0.0f,1.0f);
			glVertex3f(_pointzor.x, _pointzor.y, _pointzor.z);
			glColor3f(1.0f,1.0f,1.0f);
			glVertex3f(_veczor.x, _veczor.y, _veczor.z);
		glEnd();
	glPopMatrix();
}

