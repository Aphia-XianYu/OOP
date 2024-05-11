#include<iostream>
#include<string>
#include<random>
#include<algorithm>
#include"castle.h"


castle::castle() {
	std::cout << "Welcome to the castle!\n";
	prin.seed(time(0));
	mons.seed(1);

	Room* lobby = new Room();
	lobby->room_set("lobby", 0, 0);//set no monster or princess
	rooms.emplace_back(lobby);
	now = lobby;
}

castle::~castle() {
	ending();
	for (auto it : rooms) {
		delete it;
		it = nullptr;
	}
}//I use new to create pointers so I have to free memory

void castle::ending() {
	if (princess)
	{
		std::cout << "\nYou win!\nThe castle now lay in ruins";
	}
	else {
		std::cout << "\nYou lost!\nYou become a noboby in history";
	}
}

bool castle::conversation() {
	//You are supposed to input yes to save the princess.
	std::string response;
	std::cout << "\nYou find the princess\nPrincess : Are you going to save me ?\n(Enter Yes or No)\nYou : ";
	std::cin >> response;
	//ensure you input yes whatever form it is.
	std::transform(response.begin(), response.end(), response.begin(), ::tolower);
	if (response == "yes") {
		princess = 1;
		std::cout << "Back to the room lobby to escape from the castle.\n";
		return true;
	}
	else {// in case the player enter someting wrong.
		std::cout << "The princess is disappointed with you. So you are killed by princess.:)\n";//I prefer this ending :)
		return false;
	}
}

void castle::get_command(bool prin,bool mons) {
	now->print_room_info();
	std::string command, pos;
	std::cin >> command >> pos;

	if (command != "go") {
		std::cout << "Invalid Command\n";
	}
	else if (!now->neigbor_exist(pos)) {
		std::cout << "Invalid Postion\n";
	}//prevent invalid input
	else{
		if (now->room_exist(pos)) {
			Room* next_room = now->get_neighbor()[pos];
			now = next_room;
		}
		else {
			/*
			* You create a new room and set the information.After that, you enter a new room
			* And the program will record some infomation.
			*/
			//Create new room
			Room* next_room = new Room(pos,now);
			next_room->room_set(std::to_string(room_name++), prin, mons);
			//Record information
			rooms.emplace_back(next_room);
			channel += next_room->get_neigbor_numbers() - 1;
			now->get_neighbor().insert({pos, next_room});
			//Enter a new room
			now = next_room;
		}
	}
}

void castle::run() {
	std::bernoulli_distribution u(0.1), v(0.1);

	while (!now->check_princess()&&!now->check_monster()) {
		if (special_case()) {
			get_command(0, 1);//I set it to lost.
		}
		else {
			get_command(u(prin),v(mons));
		}
	}

	if (now->check_princess()) {
		if(conversation())
		while (now->get_room_name() != "lobby") {
			if (now->check_monster()) {
				std::cout << "\nCongratulation! You meet the monster\n";
			}/*it is still possible to meet the monster if you explore the new room instead of running
			away from the castle*/
			else{
				get_command(0, v(mons));
			}
		}
	}else if(now->check_monster()){
		std::cout << "\nCongratulation! You meet the monster\n";
	}
}



