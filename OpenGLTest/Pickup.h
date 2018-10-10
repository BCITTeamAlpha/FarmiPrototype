#pragma once
#include "PhysicsObject.h"
#include "Weapon.h"

class Pickup : public PhysicsObject {
public:
	Pickup();
	Pickup(Weapon weapon);
	Weapon pickedUp();
private:
	Weapon _weapon;
};