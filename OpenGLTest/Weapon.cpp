#include "Weapon.h"

Weapon::Weapon() {

}

Weapon::Weapon(std::string name, int charges, int damage) {
	_name = name;
	_charges = charges;
	_damage = damage;
}

// Uses a charge when used by player
void Weapon::use() {
	_charges--;
}