#include "Sprite.h"
#include "../LogicEngine/Mesh.h"
#include "Texture.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <freeglut.h>
#include <glm.hpp>

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

Sprite::Sprite(const char* _spriteImageName, float _width, float _height, float _x, float _y)
	: Entity(glm::vec3(_x, _y, 0.f), glm::vec3(_width, _height, 0.f))
{
	m_Mesh = new RectangleMesh(this, 512, 512);
	m_Texture.Load(_spriteImageName);
	SetTexture(m_Texture);
	m_Material.Load();
	SetMaterial(m_Material);
}