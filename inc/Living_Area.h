#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "Cell.h"
#include "Simple2D.h"

class Living_Area {
private:
	int width, height;
	int starting_cells = 10; //Number of starting cells
	int food_spawn = 25;     //Number of food drops spawned
	int food_interval = 5;   //Amount of updates to wait before spawning more food
	int current_tick = 0;
	std::mt19937* gen;

	std::vector<Cell> cells;
	std::vector<Food> food_drops;
public:
	Living_Area(int width, int height, std::mt19937* gen);
	
	void update();
	void draw(Simple2D::Context* ctx);
};