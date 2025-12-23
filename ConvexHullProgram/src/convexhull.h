#ifndef CONVEX_HULL_H
#define CONVEX_HULL_H

#include <vector>
#include <algorithm>

using namespace std;

struct Point { float x, y; };
static Point pivot;

inline float counterClockWise(Point a, Point b, Point c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline float distSquared(Point p1, Point p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

inline bool compare(Point a, Point b) {
	float order = counterClockWise(pivot, a, b);
	if (order == 0) return distSquared(pivot, a) < distSquared(pivot, b);
	return order > 0;
}

inline vector<Point> getConvexHull(vector<Point> points) {
	if (points.size() < 3) return {};

	int minIndex = 0;
	for (int i = 1; i < points.size(); i++) {
		if (points[i].y < points[minIndex].y || (points[i].y == points[minIndex].y && points[i].x < points[minIndex].x))
			minIndex = i;
	}

	swap(points[0], points[minIndex]);
	pivot = points[0];

	sort(points.begin() + 1, points.end(), compare);

	// Graham Scan
	vector<Point> hull;
	hull.push_back(points[0]);
	hull.push_back(points[1]);

	for (int i = 2; i < points.size(); i++) {
		while (hull.size() >= 2) {
			Point second = hull.back();
			hull.pop_back();
			Point first = hull.back();

			if (counterClockWise(first, second, points[i]) > 0) {
				hull.push_back(second);
				break;
			}
		}

		hull.push_back(points[i]);
	}

	return hull;
}


#endif