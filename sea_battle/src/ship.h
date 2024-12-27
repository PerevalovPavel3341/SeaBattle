#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <iostream>

class Ship{
	private:
		std::string intact = "intact";
		std::string damaged = "damaged";
		std::string destroyed = "destroyed";

	public:
		std::string condition;
		int length;
		std::vector<int> hp_bar;
		int id;

		Ship(int ship_length, int ship_index);
		void restore_the_ship();
		void damage_the_ship(int ship_part_index);
};

#endif