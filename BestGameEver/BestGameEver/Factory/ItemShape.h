#pragma once
#include "Factory/ItemShapeType.h"
#include <assert.h>

class CircleItem : public ItemShapeType {

public:
	CircleItem(float rad, b2Vec2 pnt) { radius = rad; point = pnt; };
	~CircleItem() {};

	float radius;
	b2Vec2 point;
	b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle);

};

class PolyItem : public ItemShapeType {

public:
	PolyItem(std::vector<b2Vec2> inputCoords) { 
		assert(inputCoords.size() <= 8); // Limitation of box2d // check what happens in box2d if 9 is passed  
		coords = inputCoords; 
	};

	~PolyItem() {};
	
	std::vector<b2Vec2> coords;

	b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle);

};

class ChainItem : public ItemShapeType {

public:
	ChainItem(std::vector<b2Vec2> inputCoords) { coords = inputCoords; };
	~ChainItem() {};

	std::vector<b2Vec2> coords;

	b2Shape * GetShape(b2Vec2 size, b2Vec2 center, float angle);

};