#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

struct PT
{
	int x, y;
	PT() { x = y = 0; }

	PT(int a, int b)
	{
		x = a;
		y = b;
	}

	bool operator < (const PT& p)const
	{
		return x < p.x;
	}
};

void drawLine(int x0, int x1, int y) {
	cout << y << ": " << x0 << "  -  " << x1 << endl;
}

struct EDGE
{
	int y_min, y_max, x_with_y_min, m_inv;

	EDGE() {}
	EDGE(int a, int b, int c, int d)
	{
		y_min = a;
		y_max = b;
		x_with_y_min = c;
		m_inv = d;
	}

	bool operator < (const EDGE& p)const
	{
		return y_min < p.y_min;
	}
};


void drawPixel(PT p, int color)
{
}


void scanLine(vector<PT> points)
{
	vector<EDGE> edges;

	int n = points.size();
	int st = INT_MAX, en = INT_MIN;
	unordered_map<int, int>mp;
	for (int i = 0; i < n; i++)
	{
		PT a = points[i];
		PT b = points[(i + 1) % n];

		if (a.y == b.y) continue;

		EDGE temp;
		temp.y_min = min(a.y, b.y);
		temp.y_max = max(a.y, b.y);
		temp.x_with_y_min = (a.y < b.y) ? a.x : b.x;
		temp.m_inv = (b.x - a.x) / (b.y - a.y);

		st = min(st, temp.y_min);
		en = max(en, temp.y_max);

		mp[temp.y_min] = 1;

		edges.push_back(temp);
	}
	sort(edges.begin(), edges.end());
	n = edges.size();

	for (int i = 0; i < n; i++)
	{
		if (mp[edges[i].y_max]) edges[i].y_max--;
	}
	for (int y = st; y <= en; y++)
	{
		vector<PT> int_points;
		for (int i = 0; i < n; i++)
		{
			if (y >= edges[i].y_min && y <= edges[i].y_max)
			{
				PT tmp;
				tmp.x = edges[i].x_with_y_min;
				tmp.y = y;
				edges[i].x_with_y_min += edges[i].m_inv;
				int_points.push_back(tmp);
			}
		}

		sort(int_points.begin(), int_points.end());

		for (int i = 0; i < int_points.size() - 1; i += 2)
		{
			drawLine(int_points[i].x, int_points[i + 1].x, int_points[i].y);
		}
	}
}


int main()
{

	vector<PT> poly{ {0,0},{0,4},{100,4} };

	scanLine(poly);

	return 0;
}
