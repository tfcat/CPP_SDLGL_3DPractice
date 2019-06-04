#pragma once
#include <string>
#include <stdio.h>
#include <SDL2\SDL.h>

#define FPS_CAP 60

class Display {
public:
	Display(int width, int height, const std::string& title);
	
	void Clear(float r, float g, float b, float a);
	void Update();
	bool HasQuit();
	bool ShouldNext();

	virtual ~Display();
protected:
private:
	SDL_Window* main_window;
	SDL_GLContext main_glContext;
	bool __hasQuit;
	int __ticks;
};