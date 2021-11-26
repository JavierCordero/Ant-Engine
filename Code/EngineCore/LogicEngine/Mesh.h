//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/constants.hpp>
#include "Object.h"

//-------------------------------------------------------------------------

class Mesh
{
public:
	Mesh(Object* _objectReference) : objectReference(_objectReference) {};
	virtual ~Mesh();
	virtual void Render(glm::dmat4 const& modelViewMat) {};
	virtual void UpdateMeshPosition(glm::dvec3 _newPosition);
	
	void Draw(glm::dmat4 const& modelViewMat);
	void FinalDraw();
	glm::dvec3* getVertices() { return vertices; };
	glm::dvec4* getColors() { return colors; };

	inline void ChangeColor(glm::dvec4 _newColor) { for (int i = 0; i < (int)numVertices; ++i) { colors[i] = _newColor; }; }

	inline void SetObjectReference(Object* _objectReference) { objectReference = _objectReference; }

	void ChangeAlpha(float _alpha) {
		alpha = _alpha; 

		for (unsigned int i = 0; i < numVertices; ++i)
		{
			colors[i].a = _alpha;
		}
	}

	GLuint numVertices = 0;
	GLuint type = GL_POINTS;
	glm::dvec3* vertices = nullptr;
	glm::dvec4* colors = nullptr;
	glm::dvec2* texCoords = nullptr;

	bool drawDebug = false;

private: 

	Object* objectReference = nullptr;
	float alpha = 0.1f;

};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_