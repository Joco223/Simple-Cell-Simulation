#include "Cell.h"

Cell::Cell()
	:
		 id(-1),
		 x(0),
		 y(0),
		 hunger(0),
		 size(0.1) {};
		
Cell::Cell(float x_, float y_, int id_) 
	:
	id(id_),
	x(x_),
	y(y_),
	hunger(0),
	size(0.1) {};

float Cell::distance(Food food_drop) {
	return std::sqrt((x - food_drop.x)*(x - food_drop.x) + (y - food_drop.y)*(y - food_drop.y));
}

void Cell::reproduce(std::vector<Cell>& cells) {
	cells.push_back(Cell(x, y, cells.size()));
};

void Cell::move(std::vector<Food>& food_drops) {
	int food_id = -1;
	float closest = view_range;

	for(int i = 0; i < food_drops.size(); i++) {
		float dist = distance(food_drops[i]);
		if(dist < closest) {
			closest = dist;
			food_id = i;
		}
	}

	if(food_id != -1 && hunger > 0.1) {
		float x_distance = food_drops[food_id].x - x;
		float y_distance = food_drops[food_id].y - y;

		if(abs(x_distance) > speed) {
			if(x_distance > 0) {
				x += speed;
			}else{
				x -= speed;
			}
		}else{
			x += x_distance;
		}

		if(abs(y_distance) > speed) {
			if(y_distance > 0) {
				y += speed;
			}else{
				y -= speed;
			}
		}else{
			y += y_distance;
		}
	
		if(distance(food_drops[food_id]) < 2) {
			hunger -= 0.3;
			size += 0.3;
			
			food_drops.erase(food_drops.begin()+food_id);
		}
	}else{
		x += rand_move(speed);
		y += rand_move(speed);
	}
};

void Cell::live(std::vector<Cell>& cells, std::vector<Food>& food_drops) {
	if(size > 1) {
		reproduce(cells);
		size = 0.1;
	}

	hunger += 0.05;
	move(food_drops);
};

void Cell::draw_cell(Simple2D::Context* ctx) {
	ctx->draw_pixel((int)x, (int)y, {255, 255, 255, 255});
};