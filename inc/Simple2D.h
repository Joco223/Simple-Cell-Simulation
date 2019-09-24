#pragma once

#include <SDL.h>
#include <math.h>
#include <algorithm>

struct Colour {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

namespace Simple2D {
	class Context {
	private:
		int width, height;
		Colour window_colour;

		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Event event;

	public:
		Context(int window_width, int window_height, const char* window_name, Colour w_colour, bool vsync, int scale);
		~Context();

		void clear();
		void draw();
		void handle_quit(bool& quit);
		SDL_Renderer* get_renderer();

		void draw_rect(int x, int y, int w, int h, Colour c, bool filled);
		void draw_pixel(int x, int y, Colour c);
		void draw_line(int x1, int y1, int x2, int y2, Colour c);
		void draw_circle(int x1, int y2, int radius, Colour c);
	};
}