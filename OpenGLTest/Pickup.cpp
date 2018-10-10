#include "Pickup.h"

Pickup::Pickup() {

}

Pickup::Pickup(Weapon weapon) {
	_weapon = weapon;
}

// Destroy Pickup and returns its contents
// (Doesn't destroy anything yet)
Weapon Pickup::pickedUp() {
	return _weapon;
}