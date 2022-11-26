#pragma once
#include <fstream>

using namespace std;

class Coordinates
{
	friend ifstream& operator>>(ifstream& fin, Coordinates& obj)
	{
		fin >> obj.y;
		fin.ignore();
		fin >> obj.x;
		return fin;
	}
	friend ostream& operator<<(ostream& out, Coordinates& obj)
	{
		out << '(' << obj.x << ", " << obj.y << ')';
		return out;
	}
public:
	int x;
	int y;
	Coordinates(int x = 0, int y = 0);
	void operator=(const Coordinates& rhs);
	~Coordinates();
};

Coordinates::Coordinates(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Coordinates::operator=(const Coordinates& rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
}

Coordinates::~Coordinates()
{

}