#pragma once
//Instantiated in the game class, uses the event system
#include "Map.h"
#include "PhysicsObject.h"
#include <glm/glm.hpp>
#include <iostream>
#include "EventManager.h"
#include "Character.h"
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

class PhysicsManager/* : public ISubscriber*/ {
public:
	PhysicsManager(std::vector<Planetoid> *p, Map *m);
	void calcPhysics(float dTime);
	void addObject(PhysicsObject *obj);
	glm::vec2 genSpawnPos(float object_radius);

	static const float VELOCITY_CAP;
	static float normalizeAngle(float var);

	//void ISubscriber::notify(EventName eventName, Param* param);
	
private:
	glm::vec2 gravAcceleration(glm::vec2 pos, glm::vec2 &max_acc_contrib);
	glm::vec2 posOnPlanet(int pInd, float object_radius);
	
	std::vector<Planetoid> *planets;
	std::vector<PhysicsObject*> objects;
	std::vector<Character*> chars;
	Map *map;
};