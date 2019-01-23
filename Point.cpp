#include "Point.h"
void Point::move() {
	int dir = rand() % 4;
	move(dir);
}

void Point::move(int dir) {
	switch (dir) {
	case 0: // UP
		--y;
		if (y < 1) {
			y = 19;
		}
		break;
	case 1: // DOWN
		++y;
		if (y > 19) {
			y = 1;
		}
		break;
	case 2: // LEFT
		--x;
		if (x < 1) {
			x =78;
		}
		break;
	case 3: // RIGHT
		++x;
		if (x > 78) {
			x = 1;
		}
		break;
	}
}

