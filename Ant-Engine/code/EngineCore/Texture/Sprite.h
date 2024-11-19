#pragma once
#include "../LogicEngine/Entity.h"

class Texture;

class Sprite : public Entity
{
public:
	Sprite(const char* _spriteImageName, float _width, float _height, float _x, float _y, float _z);
	Sprite(Texture _texture, float _width, float _height, float _x, float _y, float _z);
	~Sprite() { };
private:
	
};