#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>

#include "Room.h"
#include "helper.h"

using namespace std;

class HauntedHouse
{
	int numberOfRooms;
	char** roomsFiles;
	Room* rooms;
	Stack<Room> roomsTaken;
	Stack<Coordinates> pathTaken;
	Room* currentRoom;
	bool treasureFound;
public:
	HauntedHouse();
	void loadDataFromFile(ifstream&, const char*);
	void loadRooms(ifstream&);
	void run(ifstream&, const char*);
	void gameLoop();
	char getKeyInput();
	Room& searchTreasureRoom();
	Room& getRandomRoom();
	~HauntedHouse();
};

HauntedHouse::HauntedHouse()
{
	numberOfRooms = 0;
	roomsFiles = 0;
	rooms = 0;
	roomsTaken = Stack<Room>();
	pathTaken = Stack<Coordinates>();
	currentRoom = new Room();
	treasureFound = false;
}

void HauntedHouse::loadDataFromFile(ifstream& fin, const char* fileName)
{
	fin.open(fileName);
	if (fin.is_open()) 
	{
		char buffer[80];

		fin >> numberOfRooms;
		fin.ignore();

		roomsFiles = new char* [numberOfRooms];

		for (int i = 0; i < numberOfRooms; i++) 
		{
			fin.getline(buffer, 80);
			roomsFiles[i] = helper().getDataFromBuffer(buffer);
		}
		rooms = new Room[numberOfRooms];
	}
	fin.close();
}

void HauntedHouse::loadRooms(ifstream& fin)
{
	for (int i = 0; i < numberOfRooms; i++) 
	{
		fin.open(roomsFiles[i]);
		if (fin.is_open()) 
		{
			rooms[i].loadDataFromFile(fin, roomsFiles[i]);
		}
		fin.close();
	}
}

void HauntedHouse::run(ifstream& fin, const char* hauntedHouseFile)
{
	loadDataFromFile(fin, hauntedHouseFile);
	loadRooms(fin);

	srand(time(0));
	int n = (rand() % numberOfRooms);
	roomsTaken.push(rooms[n]);
	*currentRoom = rooms[n];

	gameLoop();
}

void HauntedHouse::gameLoop()
{
	system("cls");
	cout << *currentRoom;
	bool moveMade = false;

	if (treasureFound) //checks if treasure was found or not
	{
		int n = 0;
		for (int i = 0; i < numberOfRooms; i++)
		{
			if (rooms[i].isTreasureRoom())
				n = i + 1;
		}
		cout << "Treasure Found In Room " << n << " At Position: ";
		currentRoom->printCurrCoordinates();
		cout << "\nPath taken was:\n";
		pathTaken.print();
		return;
	}

	char move = getKeyInput();
	if (move == 'q') 
	{
		system("cls");
		cout << "Game Quit";
		return;
	}
	moveMade = currentRoom->makeMove(move, pathTaken);

	if (moveMade) 
	{
		int status = currentRoom->checkStatus(); //checks the status of current position
		if (status == 1) 
		{
			treasureFound = true;
		}
		else if (status == 2) 
		{
			system("cls");
			cout << *currentRoom;
			cout << "Devil Ate You Alive";
			return;
		}
		else if (status == 3) 
		{
			system("cls");
			pathTaken.removeAll();
			*currentRoom = searchTreasureRoom();
			roomsTaken.push(*currentRoom);
			cout << *currentRoom;
			cout << "Gasper teleported you to the tresure room";
			system("pause");
		}
		else if (status == 4) 
		{
			int coinFlip = currentRoom->portal();

			if (coinFlip == 0) 
			{
				pathTaken.removeAll();
				roomsTaken.push(*currentRoom);
				*currentRoom = getRandomRoom();
				system("cls");
				cout << *currentRoom;
				cout << "You were Teleported to a new room\n";
				system("pause");
			}
			else if (coinFlip == 1) 
			{
				if (roomsTaken.size() == 1) 
				{
					system("cls");
					cout << "You were kicked out of the house";
					return;
				}
				else 
				{
					pathTaken.removeAll();
					Room temp;
					roomsTaken.top(temp);
					roomsTaken.pop();
					*currentRoom = temp;
					system("cls");
					cout << *currentRoom;
					cout << "You were taken back to previous room\n";
					system("pause");
				}
			}
		}
	}

	gameLoop();
}

char HauntedHouse::getKeyInput()
{
	char getKey = 0;
	switch ((getKey = _getch()))
	{
	case 'q':
		return 'q';
	case 'Q':
		return 'q';
	case 72:
		return 'u';
	case 80:
		return 'd';
	case 75:
		return 'l';
	case 77:
		return 'r';
	default:
		break;
	}
	return 0;
}

Room& HauntedHouse::searchTreasureRoom()
{
	for (int i = 0; i < numberOfRooms; i++) {
		if (rooms[i].isTreasureRoom()) {
			return rooms[i];
		}
	}
}

Room& HauntedHouse::getRandomRoom()
{
	int roomNo = (rand() % numberOfRooms);
	if (*currentRoom == rooms[roomNo]) {
		return getRandomRoom();
	}
	return rooms[roomNo];
}

HauntedHouse::~HauntedHouse()
{
	if (rooms) {
		delete[] rooms;
		rooms = 0;
	}
	if (roomsFiles) {
		for (int i = 0; i < numberOfRooms; i++) {
			delete[] roomsFiles[i];
			roomsFiles[i] = 0;
		}
		delete[] roomsFiles;
		roomsFiles = 0;
	}

	currentRoom = 0;
}