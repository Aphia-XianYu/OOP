#include"Room.h"
#include<string>
#include<map>
#include<random>
#include<iostream>
#include<random>

Room::Room(std::string pos, Room* neighbor) {
	// to record where you get in the new room
	if (pos == "up") {
		neighbors["down"] = neighbor;
		neighbors_pos.insert("down");
	}
	if (pos == "west")
	{
		neighbors["east"] = neighbor;
		neighbors_pos.insert("east");
	}
	if (pos == "east")
	{
		neighbors["west"] = neighbor;
		neighbors_pos.insert("west");
	}
}

void Room::print_room_info() {
	std::cout << "\nYou are now in room " << name
		<<" There are "<<neighbors_pos.size()<< " exits: \n"  ;
	for (auto& it : neighbors_pos) {
		std::cout << it << " ";
	}
	std::cout << "\nEnter your command:\n";
}

void Room::room_set(std::string id,bool prin,bool mons) {
	name = id;
	std::default_random_engine e;
	std::bernoulli_distribution create_room(0.5);
	e.seed(time(0));
	//the room lobby and room 1 are set to no monster or princess
	if (name == "lobby") {
		neighbors_pos.insert("up");
		
	}
	else if (name == "1") {
		for (auto& it : pos) {
			neighbors_pos.insert(it);
			prin = 0;
			mons = 0;
		}
	}
	else {
		for (auto& it : pos) {
			if (create_room(e)) {
				neighbors_pos.insert(it);
			}
		}
	}

	if (prin) {
		princess = 1;
	}
	else if (mons) {
		monster = 1;
	}//ensure that princess and monster will not appear in the same room

}

