#include <iostream> 
using namespace std; 
#define MAXX 10000 

struct Coordinate
{ 
	double x; 
	double y; 
}; 

int Direction(Coordinate a, Coordinate b, Coordinate c) 
{ 
	int value = (b.y - a.y) * (c.x - b.x) - 
			(b.x - a.x) * (c.y - b.y); 
	if (value == 0) return 0; 
	return (value > 0)? 1: 2; 
} 

bool PresentOnLine(Coordinate a, Coordinate b, Coordinate c) 
{ 
	if (b.x <= max(a.x, c.x) && b.x >= min(a.x, c.x) && 
			b.y <= max(a.y, c.y) && b.y >= min(a.y, c.y)) 
		return true; 
	return false; 
} 

bool WhetherIntersect(Coordinate a1, Coordinate b1, Coordinate a2, Coordinate b2) 
{ 
	int d1 = Direction(a1, b1, a2); 
	int d2 = Direction(a1, b1, b2); 
	int d3 = Direction(a2, b2, a1); 
	int d4 = Direction(a2, b2, b1); 
	
	if (d1 != d2 && d3 != d4) 
		return true; 

	if (d1 == 0 && PresentOnLine(a1, a2, b1)) return true; 
	if (d2 == 0 && PresentOnLine(a1, b2, b1)) return true; 
	if (d3 == 0 && PresentOnLine(a2, a1, b2)) return true; 
	if (d4 == 0 && PresentOnLine(a2, b1, b2)) return true; 
	return false; 
} 

bool WhetherPointIsInside(Coordinate poly[], Coordinate p) 
{   int n = (sizeof(*poly));
	if (n < 3) return false; 
	Coordinate extreme = {MAXX, p.y}; 
	int count = 0, k = 0; 
	do
	{ 
		int nextpoint = (k+1)%n; 
		if (WhetherIntersect(poly[k], poly[nextpoint], p, extreme)) 
		{ 
			if (Direction(poly[k], p, poly[nextpoint]) == 0) 
			return PresentOnLine(poly[k], p, poly[nextpoint]); 
			count++; 
		} 
		k = nextpoint; 
	} while (k != 0); 
	
	return count&1; 
} 

int main() 
{ 
	Coordinate poly[] = {{1, 0}, {8, 3}, {8, 8}, {1, 5}}; 
	Coordinate p = {3, 5}; 
	WhetherPointIsInside(poly, p)? cout << "True \n": cout << "False \n"; 

	Coordinate poly1[] = {{-3, 2}, {-2, -0.8}, {0, 1.2},{2.2,0},{2,4.5}}; 
	p = {0, 0}; 
	WhetherPointIsInside(poly1, p)? cout << "True \n": cout << "False \n"; 
	
	return 0; 
}
