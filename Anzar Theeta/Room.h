#pragma once

#include "coordinates.h"
#include "helper.h"
#include "stack.h"

using namespace std;

class Room
{
	friend ostream& operator<<(ostream& out, const Room& obj)
	{
		cout << "---------------------------------------\n";
		for (int i = 0; i < obj.roomDimensions.y; i++) {
			cout << "|  ";
			for (int j = 0; j < obj.roomDimensions.x; j++) {
				if (i == obj.currentPosition.y && j == obj.currentPosition.x)
					cout << "*    ";
				else if (obj.matrix[i][j] == '0')
					cout << "     ";
				else
					cout << obj.matrix[i][j] << "    ";
			}
			cout << "|\n\n";
		}
		cout << "---------------------------------------\n";
		return out;
	}

	char* id;
	char** matrix;
	Coordinates roomDimensions;
	Coordinates startPosition;
	Coordinates currentPosition;
	bool isTRoom;
public:
	Room();
	void loadDataFromFile(ifstream&, char*);
	bool makeMove(char move, Stack<Coordinates>& moves);
	bool spaceAvailable(char move);
	int checkStatus();
	int portal();
	void operator=(const Room& rhs);
	void checkTreasureRoom();
	bool isTreasureRoom();
	bool operator==(const Room& rhs);
	void printCurrCoordinates();
	~Room();
};

Room::Room()
{
	id = 0;
	matrix = 0;
	startPosition = Coordinates();
	roomDimensions = Coordinates();
	currentPosition = Coordinates();
	isTRoom = false;
}

void Room::loadDataFromFile(ifstream& fin, char* id)
{
	helper().stringCopy(id, this->id);
	fin >> roomDimensions;
	fin >> startPosition;
	currentPosition = startPosition;

	fin.ignore();
	matrix = new char* [roomDimensions.y];
	for (int i = 0; i < roomDimensions.y; i++) 
	{
		matrix[i] = new char[roomDimensions.x + 1];
		int j;
		for (j = 0; j < roomDimensions.x; j++) 
		{
			fin.get(matrix[i][j]);
			fin.ignore();
		}
		matrix[i][j] = '\0';
	}
	checkTreasureRoom();
}

bool Room::makeMove(char move, Stack<Coordinates>& moves)
{
	if (spaceAvailable(move)) {
		switch (move) {
		case 'u':
			currentPosition.y--;
			moves.push(currentPosition);
			break;
		case 'd':
			currentPosition.y++;
			moves.push(currentPosition);
			break;
		case 'l':
			currentPosition.x--;
			moves.push(currentPosition);
			break;
		case 'r':
			currentPosition.x++;
			moves.push(currentPosition);
			break;
		default:
			break;
		}
		return true;
	}
	return false;
}

bool Room::spaceAvailable(char move)
{
	switch (move)
	{
	case 'u':
		if (currentPosition.y - 1 < 0) {
			return false;
		}
		if (matrix[currentPosition.y - 1][currentPosition.x] == 'X') {
			return false;
		}
		break;
	case 'd':
		if (currentPosition.y + 1 >= roomDimensions.y) {
			return false;
		}
		if (matrix[currentPosition.y + 1][currentPosition.x] == 'X') {
			return false;
		}
		break;
	case 'l':
		if (currentPosition.x - 1 < 0) {
			return false;
		}
		if (matrix[currentPosition.y][currentPosition.x - 1] == 'X') {
			return false;
		}
		break;
	case 'r':
		if (currentPosition.x + 1 >= roomDimensions.x) {
			return false;
		}
		if (matrix[currentPosition.y][currentPosition.x + 1] == 'X') {
			return false;
		}
		break;
	default:
		break;
	}
	return true;
}

int Room::checkStatus()
{
	//returns 1 if tresure found
	//returns 2 for devil
	//returns 3 for gasper
	//returns 4 for portal

	switch (matrix[currentPosition.y][currentPosition.x]) {
	case 'T':
		return 1;
	case 'D':
		return 2;
	case 'G':
		return 3;
	case 'P':
		return 4;
	}
	return -1;
}

int Room::portal()
{
	if (spaceAvailable('r')) {
		currentPosition.x++;
	}
	else if (spaceAvailable('l')) {
		currentPosition.x--;
	}
	else if (spaceAvailable('u')) {
		currentPosition.y--;
	}
	else if (spaceAvailable('d')) {
		currentPosition.y++;
	}

	return (rand() % 2);
}

void Room::operator=(const Room& rhs)
{
	helper().stringCopy(rhs.id, this->id);
	this->currentPosition = rhs.currentPosition;
	this->startPosition = rhs.startPosition;
	this->roomDimensions = rhs.roomDimensions;

	this->matrix = new char* [this->roomDimensions.y];
	for (int i = 0; i < this->roomDimensions.y; i++) {
		this->matrix[i] = 0;
		helper().stringCopy(rhs.matrix[i], this->matrix[i]);
	}
}

void Room::checkTreasureRoom()
{
	for (int i = 0; i < roomDimensions.y; i++) {
		for (int j = 0; j < roomDimensions.x; j++) {
			if (matrix[i][j] == 'T') {
				isTRoom = true;
			}
		}
	}
}

bool Room::isTreasureRoom()
{
	return isTRoom;
}

bool Room::operator==(const Room& rhs)
{
	return (helper().stringCompare(this->id, rhs.id));
}

void Room::printCurrCoordinates()
{
	cout << currentPosition;
}

Room::~Room()
{
	if (id) {
		delete[] id;
		id = 0;
	}
	if (matrix) {
		for (int i = 0; i < roomDimensions.y; i++) {
			if (matrix[i]) {
				delete[] matrix[i];
				matrix[i] = 0;
			}
		}
	}
}