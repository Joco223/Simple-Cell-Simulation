#define SDL_MAIN_HANDLED

#include <random>

#include "Simple2D.h"
#include "Living_Area.h"

constexpr int r_width  = 640; //Real width
constexpr int r_height = 480; //Real height
constexpr int scale    = 4;
constexpr int width    = r_width  / scale;
constexpr int height   = r_height / scale;

std::random_device rd;
std::mt19937 gen;
float rand_move(int speed) {
	std::uniform_real_distribution<> dist(0, speed);
	return dist(gen) - speed/2.0;
}

int main(int argc, char** argv) {

	//Simple2D Context object, arguments, window width and height, window title, window colour, and vSync on/off, scale
	Simple2D::Context ctx(r_width, r_height, "Cell Simulation", {50, 50, 50, 255}, true, scale);

	gen = std::mt19937(rd());

	Living_Area living_area(width, height, &gen);

	bool quit = false;
	unsigned int frame_counter = 0;

	while(!quit) {
		//Handle exit event
		ctx.handle_quit(quit);

		//Clear the screen
		ctx.clear();

		if(frame_counter % 3 == 0) { //Assuimg 60hz, 20 updates per second
			living_area.update();
		}
		living_area.draw(&ctx);
		frame_counter++;
		
		//Update the screen
		ctx.draw();
	}

	return 0;
}

