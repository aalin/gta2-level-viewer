#include "common.hpp"

Engine::Engine(int width, int height, bool fullscreen)
	: _width(width), _height(height)
{
	_running = true;

	const SDL_VideoInfo* video_info = SDL_GetVideoInfo();

	Uint32 flags = SDL_OPENGL;
	flags |= SDL_GL_DOUBLEBUFFER;
	flags |= SDL_HWPALETTE;

	if(video_info->hw_available)
		flags |= SDL_HWSURFACE;
	else
		flags |= SDL_SWSURFACE;

	if (video_info->blit_hw)
		flags |= SDL_HWACCEL;

	if(fullscreen)
		flags = flags|SDL_FULLSCREEN;

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	_surface = SDL_SetVideoMode(width, height, 32, flags);
	if(_surface == 0)
		throw std::runtime_error("could init surface");

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_WM_GrabInput(SDL_GRAB_ON);
	//SDL_GrabMode(SDL_GRAB_ON);
	SDL_ShowCursor(0);

	initGL();
}

Engine::~Engine()
{
	std::cout << "~Engine();" << std::endl;
	while(!_states.empty())
		_states.pop();
}

void
Engine::changeState(boost::shared_ptr<AbstractState> state)
{
	if(!_states.empty())
		_states.pop();

	_states.push(state);
	_states.top()->init();
}

void
Engine::initGL()
{
	glClearColor(0.07, 0.62, 1.0, 0);
	glClearDepth(1);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_TEXTURE_2D);

	//glShadeModel(GL_SMOOTH);
	glShadeModel(GL_FLAT);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

/*	GLfloat light_pos[] = {-2.0, 2.0, 2.0, 1.0};
	GLfloat light_ka[] = {0.5, 0.5, 0.5, 1.0};
	GLfloat light_kd[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_ks[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_ks);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat material_ka[] = {1, 1, 1, 1.0};
	GLfloat material_kd[] = {0.43, 0.47, 0.54, 1.0};
	GLfloat material_ks[] = {0.33, 0.33, 0.53, 1.0};
	GLfloat material_ke[] = {0.0, 0.0, 0.0, 0.0};
	GLfloat material_se = 10;
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ka);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_kd);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_ks);
	glMaterialfv(GL_FRONT, GL_EMISSION, material_ke);
	glMaterialfv(GL_FRONT, GL_SHININESS, &material_se);*/

	glEnable(GL_FOG);
	GLfloat fog_color[] = {0.0, 0.0, 0.0, 0.5};
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogi(GL_FOG_MODE, GL_LINEAR);
	glFogf(GL_FOG_DENSITY, 0.05);
	glHint(GL_FOG_HINT, GL_NICEST);
	glFogf(GL_FOG_START, 50.0);
	glFogf(GL_FOG_END, 100.0);

	glPointSize(10.0);
	glEnable(GL_POINT_SMOOTH);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glAlphaFunc(GL_GREATER, 0.1);
	//glEnable(GL_ALPHA_TEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_COORD_ARRAY);

//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void
Engine::pushState(boost::shared_ptr<AbstractState> state)
{
	if(!_states.empty())
		_states.top()->pause();

	_states.push(state);
	_states.top()->init();
}

void
Engine::popState()
{
	if(!_states.empty())
		_states.pop();

	if(!_states.empty())
		_states.top()->resume();
}

bool
Engine::isRunning() const
{
	return _running;
}

void
Engine::handleInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if(event.type == SDL_QUIT)
			_running = false;
		else
		{
			if(event.type == SDL_KEYDOWN)
			{
				switch(event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						_running = false;
						break;
					default:
						break;
				}
			}
		}
		_states.top()->handleInput(event);
	}
}

void
Engine::update()
{
	while(GLenum error = glGetError())
	{
		if(error == GL_NO_ERROR)
			break;
		//std::cerr << glGetError() << std::endl;
	}

	if(_states.empty())
		throw std::runtime_error("No states.");
	_states.top()->update();
}

void
Engine::draw()
{
	if(_states.empty())
		throw std::runtime_error("No states.");
	_states.top()->draw();
	SDL_GL_SwapBuffers();
}

int
Engine::getWidth() const
{
	return _width;
}

int
Engine::getHeight() const
{
	return _height;
}

