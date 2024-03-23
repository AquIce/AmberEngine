#ifndef __AQUICE_UTILS_LINEGEN_HPP__
#define __AQUICE_UTILS_LINEGEN_HPP__

#include <vector>
#include <cmath>

typedef struct coords {
	int x;
	int y;
} coords;

std::vector<coords> linegen(coords start, coords end) {

	std::vector<coords> coords_vec = std::vector<coords>();

	int x, y;
	int dx = end.x - start.x;
	int dy = end.y - start.y;
	int dx1 = fabs(dx);
	int dy1 = fabs(dy);
	int px = 2 * dy1 - dx1;
	int py = 2 * dx1 - dy1;
	int xe, ye;
	int i;
	
	if (dy1 <= dx1) {
		if (dx >= 0) {
			x = start.x;
			y = start.y;
			xe = end.x;
		} else {
			x = end.x;
			y = end.y;
			xe = start.x;
		}
		coords_vec.push_back({x, y});
		for (i = 0; x < xe; i++) {
			x = x + 1;
			if (px < 0) {
				px = px + 2 * dy1;
			} else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					y = y + 1;
				} else {
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			coords_vec.push_back({x, y});
		}
	} else {
		if (dy >= 0) {
			x = start.x;
			y = start.y;
			ye = end.y;
		} else {
			x = end.x;
			y = end.y;
			ye = start.y;
		}
		coords_vec.push_back({x, y});
		for (i = 0; y < ye; i++) {
			y = y + 1;
			if (py <= 0) {
				py = py + 2 * dx1;
			} else {
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
					x = x + 1;
				} else {
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			coords_vec.push_back({x, y});
		}
	}

	return coords_vec;
}

#endif