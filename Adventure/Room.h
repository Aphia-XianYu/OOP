#pragma once
#include<vector>
#include<string>
#include<map>
#include<memory>
#include<vector>
#include<set>
/*This class is used to set the room.
* The main attributes of room include the name, the rooms connecting to this room, 
* and most importantly if the monster or the princess is in room.
* The functions I designed are mainly to set the room and return the information of the room.
*/
class Room {
public:
	Room() = default;
	Room(std::string pos, Room* neighbor);
	void print_room_info();//it is used to show the information of each room
	void room_set(std::string id,bool prin,bool mons);
	std::map<std::string, Room*>& get_neighbor() { return neighbors; };
	bool check_princess() { return princess; };//check if the princess is in the room
	bool check_monster() { return monster; };//check if the monster is in the room
	bool room_exist(const std::string&pos) 
		{ return neighbors.count(pos); };//check if the room has been setted.
	bool neigbor_exist(const std::string& pos) 
		{ return std::count(neighbors_pos.begin(), neighbors_pos.end(), pos); };//check if the room you intend to get in is valid
	std::string get_room_name() { return name; };
	int get_neigbor_numbers() {return neighbors_pos.size() };
private:
	std::string name;
	std::map<std::string,Room*> neighbors;//it is store other rooms connecting to this room
	std::vector<std::string> pos = { "east","west","up"};//position
	std::set<std::string> neighbors_pos = {};//Record the room to which the object is connected
	bool princess = 0;
	bool monster = 0;
};
