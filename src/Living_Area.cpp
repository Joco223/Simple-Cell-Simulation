#include "Living_Area.h"

Living_Area::Living_Area(int width_, int height_, std::mt19937* gen_) {
	width = width_;
	height = height_;
	gen = gen_;
	

	std::uniform_real_distribution<float> spawn_x(0, width);
	std::uniform_real_distribution<float> spawn_y(0, height);

	for(int i = 0; i < starting_cells; i++)
		cells.push_back(Cell(spawn_x(*gen), spawn_y(*gen), i));

	for(int i = 0; i < food_spawn; i++) 
		food_drops.push_back({i, spawn_x(*gen), spawn_y(*gen)});
}

void Living_Area::update() {
	for(int i = 0; i < cells.size(); i++) {
		if(cells[i].hunger > 1) {
			cells.erase(cells.begin()+i);
		}

		cells[i].live(cells, food_drops);
		cells[i].x = (int)cells[i].x % width;
		cells[i].y = (int)cells[i].y % height;
	}

	if(current_tick >= food_interval) {
		current_tick = 0;
		std::uniform_real_distribution<float> spawn_x(0, width);
		std::uniform_real_distribution<float> spawn_y(0, height);
		for(int i = 0; i < food_spawn; i++) 
			food_drops.push_back({i, spawn_x(*gen), spawn_y(*gen)});
	}
	current_tick++;
}

void Living_Area::draw(Simple2D::Context* ctx) {
	for(auto& i : cells)
		i.draw_cell(ctx);

	for(auto& i : food_drops) {
		ctx->draw_pixel((int)i.x, (int)i.y, {255, 100, 100, 255});
	}
}