#include<iostream>
#include<vector>
using namespace std;

class Point {
	int xPos, yPos;
public:
	Point(int x, int y) : xPos(x), yPos(y) {}

	void move(int toX, int toY) {
		xPos += toX;
		yPos += toY;
	}

	int getX() const { return xPos; }
	int getY() const { return yPos; }
	void setX(int x) { xPos = x; }
	void setY(int y) { yPos = y; }

	bool operator == (const Point& ref) {
		return xPos == ref.xPos and yPos == ref.yPos;
	}
	friend ostream& operator<< (ostream& os, const Point& ref) {
		os << ref.xPos << " " << ref.yPos << endl;
		return os;
	}
};

class Robocop{
	vector<Point> pointsTrack;
	Point location; 
	int numPoints, index;
	int vel;
	int dx, dy;
public:
	Robocop(const vector<Point>& points, int numP, int startIndex, int dir)
		:pointsTrack(points), numPoints(numP), index(startIndex), location(points.at(startIndex)), vel(dir) {
		dx = 0;
		dy = 0;
	}

	Point getLocation() const {
		return location;
	}
	void setDirection() {
		dx = pointsTrack.at(index).getX() - location.getX();
		dy = pointsTrack.at(index).getY() - location.getY();

		if (dx != 0) dx /= abs(dx);
		else		 dy /= abs(dy);
	}

	void reflection() {
		vel *= -1;
		index += vel;
		setDirection();
	}

	void step() {
		if (pointsTrack.at(index) == location) {
			location.setX(pointsTrack.at(index).getX());
			location.setY(pointsTrack.at(index).getY());
			index += vel;
			if (index < 0) index = numPoints - 1;
			index %= numPoints;
			setDirection();
		}
		location.move(dx, dy);
	}
};

int main(void) {
	int numPoints;
	cin >> numPoints;

	vector<Point> points;
	for (int i = 0; i < numPoints; i++) {
		int x, y;
		cin >> x >> y;
		Point p(x, y);
		points.push_back(p);
	}

	Robocop robot1(points, numPoints, 0, 1);
	Robocop robot2(points, numPoints, (numPoints / 2) - 1, -1);

	int time; 
	cin >> time;
	for (int i = 0; i < time; i++) {
		if (robot1.getLocation() == robot2.getLocation()) {
			robot1.reflection();
			robot2.reflection();
		}

		robot1.step();

		if (robot1.getLocation() == robot2.getLocation()) {
			robot1.reflection();
			robot2.reflection();
			robot1.step();
		}
		else
			robot2.step();
	}
	
	cout << robot1.getLocation();
	cout << robot2.getLocation();
	return 0;
}