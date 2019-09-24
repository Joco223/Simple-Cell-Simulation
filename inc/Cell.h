#pragma once

#include <vector>
#include <cmath>
#include <math.h>
#include <iostream>

#include "Simple2D.h"

struct Food {
	int id;
	float x, y;
};

extern float rand_move(int speed);

class Cell {
private:
	float x, y;
	float hunger;
	float size;
	float view_range = 40;
	int speed = 1;

	float distance(Food food_drop);
	
	void reproduce(std::vector<Cell>& cells);
	void move(std::vector<Food>& food_drops);
	
	friend class Living_Area;
public:
	int id;
	Cell();
	Cell(float x, float y, int id);

	void live(std::vector<Cell>& cells, std::vector<Food>& food_drops);
	void draw_cell(Simple2D::Context* ctx);
};