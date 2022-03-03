#include "Display.h"
#include <GL/glew.h>

Display::Display(int width, int height, const std::string& title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	// set gl attributes
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	main_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, width, height, 
		SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);

	main_glContext = SDL_GL_CreateContext(main_window);

	if(glewInit() != GLEW_OK) printf("GLEW: FAILED TO INITIALIZE!\n");

	__hasQuit = false;
	__ticks = 0;

	//Enable alpha blending
	glEnable(GL_BLEND); 
	//Set blending function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Display::~Display()
{
	SDL_GL_DeleteContext(main_glContext);
	SDL_DestroyWindow(main_window);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Display::Update()
{
	// Process events
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_QUIT)
			__hasQuit = true;
	}

	// Display buffer to screen
	SDL_GL_SwapWindow(main_window);
}

bool Display::HasQuit()
{
	return __hasQuit;
}

bool Display::ShouldNext()
{
	if(SDL_GetTicks() >= __ticks + (int)(1000/FPS_CAP)){
		__ticks = SDL_GetTicks();
		return true;
	}else{
		SDL_Delay(1);
		return false;
	}
}