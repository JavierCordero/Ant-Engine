//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include "Object.h"

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Mesh.h"
#include "..\Texture\Texture.h"
#include "..\Texture\Material.h"
#include <map>
#include <vector>
#include <list>
#include "Component.h"

//-------------------------------------------------------------------------

class Entity : public Object
{

public:
	Entity(glm::vec3 _position, glm::vec3 _size) : Object(_position, _size) {}
	virtual ~Entity();

	virtual void Render(glm::dmat4 const& modelViewMat);
	virtual void Update(double timeElapsed);
	virtual void PostUpdate(double elapsedTime);
	virtual void Destroy();

	void OnCollision(Object* _otherObject) { Object::OnCollision(_otherObject); };
	void OnTriggerEnter(Object* _otherObject) { Object::OnTriggerEnter(_otherObject); };

	std::map<const char*, Texture> textures;
	std::map<const char*, Material> materials;

	void AddMaterial(const char* _name, Material const& _material) { materials.insert(std::pair<const char*, Material>(_name, _material)); }
	void AddTexture(const char* _name, Texture const& _texture) { textures.insert(std::pair<const char*, Texture>(_name, _texture)); };

	std::list<Component*> entityComponents;

	bool isVisible = true;

protected:

	//std::vector<Mesh*> meshes;
	Material* currentMaterial = nullptr;
};

//-------------------------------------------------------------------------

//class ContCubo : public Entity
//{
//public:
//	ContCubo(GLdouble l, GLint x, GLint y);
//	~ContCubo() { };
//	virtual void draw();
//};
//
//
//class Cubo : public Entity
//{
//public:
//	Cubo(GLdouble w, GLdouble h, GLint x, GLint y, GLint z);
//	~Cubo() { };
//	void draw();
//	virtual void render(glm::dmat4 const& modelViewMat);
//private:
//	Mesh* meshC = nullptr;
//	Mesh* meshR = nullptr;
//	GLint x_, y_, z_;
//};
//
//
//
//class RectangleText : public Entity
//{
//public:
//	RectangleText(GLdouble l, GLdouble h, GLint xRep, GLint  yRep, GLint x, GLint y, GLint z);
//	~RectangleText() { };
//	virtual void draw();
//	virtual void render(glm::dmat4 const& modelViewMat);
//private:
//	Mesh* mesh = nullptr;
//};
//
//class CuboText : public Entity
//{
//public:
//	CuboText(GLdouble l, GLdouble h, GLint x, GLint y);
//	~CuboText() { };
//	virtual void draw();
//	virtual void render(glm::dmat4 const& modelViewMat);
//private:
//	Mesh* mesh = nullptr;
//};

//class Foto : public Entity
//{
//public:
//	Foto(GLdouble l, GLdouble h, GLint xRep, GLint  yRep, GLint x, GLint y, GLint z);
//	~Foto() { };
//	virtual void draw();
//
//	virtual void update(GLuint timeElapsed) {  // Cargamos en el buffer la imagen actual de la pantalla y se la asignamos a la textura de la foto cada segundo si 
//		//en el main está activado
//
//		if (timeElapsed % 1000 == 0) {
//
//			textura.bind();
//			textura.loadColorBuffer(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
//			textura.unbind();
//
//		}
//	};
//	virtual void render(glm::dmat4 const& modelViewMat);
//private:
//	Mesh* mesh = nullptr;
//};
//
//class GlassPot : public Entity
//{
//public:
//	GlassPot(GLdouble l, GLdouble h, GLint x, GLint y, GLint z);
//	~GlassPot() { };
//	virtual void draw();
//	virtual void render(glm::dmat4 const& modelViewMat);
//private:
//	Mesh* mesh = nullptr;
//	GLint x_, y_, z_;
//};
//
//class Grass : public Entity
//{
//public:
//	Grass(GLdouble l, GLdouble h, GLint x, GLint y, GLint z);
//	~Grass() { };
//	virtual void draw();
//	virtual void render(glm::dmat4 const& modelViewMat);
//private:
//	Mesh* mesh = nullptr;
//	GLint x_, y_, z_;
//	GLdouble r_, h_;
//};

#endif //_H_Entities_H_