#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "GameObject.h"
#include "Weapon.h"
#include "Pickup.h"
//created by Player

class Inventory : public GameObject {
public:
	Inventory();
	Inventory(std::vector<Weapon> slots);
	std::vector<Weapon> _slots;

	Weapon selectSlot();
	Pickup dropSlot();
	void emptySlot();
	void addItem(Pickup item);

private:
	Weapon currentSlot;
	const int capacity = 5;
};