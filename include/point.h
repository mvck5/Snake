#pragma once

struct Point2d {
	int x{};
	int y{};

	friend bool operator==(const Point2d& p1, const Point2d& p2) {
		if (p1.x == p2.x && p1.y == p2.y) {
			return true;
		}
		return false;
	}
};