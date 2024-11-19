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

Sprite::Sprite(const char* _spriteImageName, float _width, float _height, float _x, float _y, float _z)
	: Entity(glm::vec3(_x, _y, _z), glm::vec3(_width, _height, 0.f))
{
	m_Meshes.push_back(new RectangleMesh(this, _width, _height));
	m_Texture.Load(_spriteImageName);
	SetTexture(m_Texture);
	m_Material.Load();
	SetMaterial(m_Material);
}

Sprite::Sprite(Texture _texture, float _width, float _height, float _x, float _y, float _z)
	: Entity(glm::vec3(_x, _y, _z), glm::vec3(_width, _height, 0.f))
{
	m_Meshes.push_back(new RectangleMesh(this, _width, _height));
	m_Texture = _texture;
	SetTexture(m_Texture);
	m_Material.Load();
	SetMaterial(m_Material);
}