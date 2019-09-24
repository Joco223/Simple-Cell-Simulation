#include "Simple2D.h"

namespace Simple2D {
	Context::Context(int window_width, int window_height, const char* window_name, Colour w_colour, bool vsync, int scale)
			:
			width(window_width),
			height(window_height) {
				window_colour = w_colour;
				window = SDL_CreateWindow(window_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
				
				if(vsync) {
					renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
				}else{
					renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
				}

				width = window_width;
				height = window_height;

				SDL_RenderSetScale(renderer, scale, scale);
			}

	Context::~Context() {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
	};

	void Context::clear() {
		SDL_RenderClear(renderer);
	};

	void Context::draw() {
		SDL_SetRenderDrawColor(renderer, window_colour.red, window_colour.green, window_colour.blue, window_colour.alpha);
		SDL_RenderPresent(renderer);
	};

	void Context::handle_quit(bool& quit) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					quit = true;
					break;
			}
		}
	}

	SDL_Renderer* Context::get_renderer() {
		return renderer;
	};

	void Context::draw_rect(int x, int y, int w, int h, Colour c, bool filled) {
		SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, c.alpha);
		SDL_Rect rect = {x, y, w, h};
		if(filled) {
			SDL_RenderFillRect(renderer, &rect);
		}else{
			SDL_RenderDrawRect(renderer, &rect);
		}
	};

	void Context::draw_pixel(int x, int y, Colour c) {
		SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, c.alpha);
		SDL_Rect rect = {x, y, 1, 1};
		SDL_RenderDrawRect(renderer, &rect);
	}

	void Context::draw_line(int x1, int y1, int x2, int y2, Colour c) {
		SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, c.alpha);

		bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
		if(steep) {
			std::swap(x1, y1);
			std::swap(x2, y2);
		}

		if(x1 > x2) {
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		float dx = x2 - x1;
		float dy = fabs(y2 - y1);

		float error = dx / 2.0f;
		int ystep = (y1 < y2) ? 1 : -1;
		int y = (int)y1;

		const int maxX = (int)x2;

		for(int x = (int)x1; x < maxX; x++) {
			if(steep) {
				SDL_RenderDrawPoint(renderer, x, y);
			}else{
				SDL_RenderDrawPoint(renderer, x, y);
			}

			error -= dy;
			if(error < 0) {
				y += ystep;
				error += dx;
			}
		}
	}

	void Context::draw_circle(int x1, int y1, int radius, Colour c) {
		SDL_SetRenderDrawColor(renderer, c.red, c.green, c.blue, c.alpha);

		int x = radius-1;
		int y = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (radius << 1);

		while (x >= y) {
			SDL_RenderDrawPoint(renderer, x1 + x, y1 + y);
			SDL_RenderDrawPoint(renderer, x1 + y, y1 + x);
			SDL_RenderDrawPoint(renderer, x1 - y, y1 + x);
			SDL_RenderDrawPoint(renderer, x1 - x, y1 + y);
			SDL_RenderDrawPoint(renderer, x1 - x, y1 - y);
			SDL_RenderDrawPoint(renderer, x1 - y, y1 - x);
			SDL_RenderDrawPoint(renderer, x1 + y, y1 - x);
			SDL_RenderDrawPoint(renderer, x1 + x, y1 - y);

			if (err <= 0) {
				y++;
				err += dy;
				dy += 2;
			}
			
			if (err > 0) {
				x--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}
	};
}