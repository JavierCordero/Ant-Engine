#pragma once
#include <freeglut.h>
#include <glm.hpp>
#include "../Texture/Sprite.h"

class Texture;

class Interface : public Sprite
{
public:
	Interface(const char* _spriteImageName, float _width, float _height, float _x, float _y);
	Interface(Texture _texture, float _width, float _height, float _x, float _y);
	virtual void Render(glm::dmat4 const& modelViewMat) override;
};

