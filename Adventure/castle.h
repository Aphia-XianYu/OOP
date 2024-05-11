#pragma once
#include"Room.h"
#include<string>
#include<random>
#include<vector>
/*The class is the main part of the game.
* This class allows you to expolre the castle. 
*/

class castle {
public:
	castle();//Initialize. It create the room called lobby serving as the signal that you save the princess
	~castle();
	void run();
	void get_command(bool prin, bool mons);
	void ending();
	bool conversation();//interaction with princess, it decides the ending.
	/*A special case I met during test was there is no new room, in an ohter word, I had explored 
	all the room. But I didn't meet the princess or the monster
	so to solve this bug, I design this special case*/	
	bool special_case()
	{
		return channel == rooms.size() && now->get_room_name() != "looby";
	};

private:
	int channel  = 1;//it is used to record the number of the "edge" between two room
	int room_name = 1;//it is used to set room name.
	Room* now;
	std::default_random_engine prin, mons;
	std::vector<Room*> rooms;//it is used to record the number of the explored room.
	bool princess = 0;//it is used to check winning condition
};