#include <iostream> 
using namespace std; 
#define MAXX 10000 

struct Coordinate
{ 
	double x; 
	double y; 
}; 

bool PresentOnLine(Coordinate p, Coordinate q, Coordinate r) 
{ 
	if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
			q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
		return true; 
	return false; 
} 

int Direction(Coordinate p, Coordinate q, Coordinate r) 
{ 
	int val = (q.y - p.y) * (r.x - q.x) - 
			(q.x - p.x) * (r.y - q.y); 
	if (val == 0) return 0; 
	return (val > 0)? 1: 2; 
} 

bool WhetherIntersect(Coordinate p1, Coordinate q1, Coordinate p2, Coordinate q2) 
{ 
	int o1 = direction(p1, q1, p2); 
	int o2 = direction(p1, q1, q2); 
	int o3 = direction(p2, q2, p1); 
	int o4 = direction(p2, q2, q1); 
	
	if (o1 != o2 && o3 != o4) 
		return true; 

	if (o1 == 0 && PresentOnLine(p1, p2, q1)) return true; 
	if (o2 == 0 && PresentOnLine(p1, q2, q1)) return true; 
	if (o3 == 0 && PresentOnLine(p2, p1, q2)) return true; 
	if (o4 == 0 && PresentOnLine(p2, q1, q2)) return true; 
	return false; 
} 

bool WhetherPointIsInside(Coordinate polygon[], Coordinate p) 
{   int n = (sizeof(*polygon));
	if (n < 3) return false; 
	Coordinate extreme = {MAXX, p.y}; 
	int count = 0, i = 0; 
	do
	{ 
		int next = (i+1)%n; 
		if (WhetherIntersect(polygon[i], polygon[next], p, extreme)) 
		{ 
			if (direction(polygon[i], p, polygon[next]) == 0) 
			return PresentOnLine(polygon[i], p, polygon[next]); 
			count++; 
		} 
		i = next; 
	} while (i != 0); 
	
	return count&1; 
} 

int main() 
{ 
	Coordinate polygon1[] = {{1, 0}, {8, 3}, {8, 8}, {1, 5}}; 
	Coordinate p = {3, 5}; 
	WhetherPointIsInside(polygon1, p)? cout << "True \n": cout << "False \n"; 

	Coordinate polygon2[] = {{-3, 2}, {-2, -0.8}, {0, 1.2},{2.2,0},{2,4.5}}; 
	p = {0, 0}; 
	WhetherPointIsInside(polygon2, p)? cout << "True \n": cout << "False \n"; 
	
	return 0; 
}
