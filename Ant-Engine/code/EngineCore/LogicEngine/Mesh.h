//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <freeglut.h>
#include <glm.hpp>
#include <gtc/constants.hpp>
#include "Object.h"
#include <vector>

//-------------------------------------------------------------------------

class Mesh
{
public:
	Mesh(Object* _objectReference) : m_ParentReference(_objectReference) {};
	virtual ~Mesh();
	virtual void Render(glm::dmat4 const& _modelViewMat) {};
	virtual void UpdateMeshPosition(glm::dvec3 _newPosition);
	
	void Draw(glm::dmat4 const& _modelViewMat);
	void FinalDraw();

	void SetType(GLuint _type) { m_Type = _type; };
	void SetNumVertices(GLuint _numVertices) { m_NumVertices = _numVertices; };
	inline void SetColors(glm::dvec4 _colors) { for (int i = 0; i < m_NumVertices; ++i) { m_Colors[i] = _colors; }; };
	inline void SetColors(glm::dvec4* _colors) { m_Colors = _colors; };
	void SetVertices(glm::dvec3* _vertices) { m_Vertices = _vertices; };

	void SetScale(glm::vec3 _newScale) { m_MeshScale = _newScale; };

	GLuint GetNumVertices() { return m_NumVertices; };
	glm::dvec3* GetVertices() { return m_Vertices; };
	glm::dvec4* GetColors() { return m_Colors; };
	GLuint GetType() { return m_Type; };

	void ParseFromOBJ(int _numVertices, std::vector<glm::dvec3> _vertices);

	inline void ChangeColor(glm::dvec4 _newColor) { for (int i = 0; i < (int)m_NumVertices; ++i) { m_Colors[i] = _newColor; }; }

	inline void SetObjectReference(Object* _objectReference) { m_ParentReference = _objectReference; }

	void ChangeAlpha(float _alpha) {
		m_TextureAlpha = _alpha;

		for (unsigned int i = 0; i < m_NumVertices; ++i)
		{
			m_Colors[i].a = _alpha;
		}
	}

protected:
	GLuint m_NumVertices = 0;
	GLuint m_Type = GL_POINTS;
	glm::dvec3* m_Vertices = nullptr;
	glm::dvec4* m_Colors = nullptr;
	glm::dvec2* m_TexCoords = nullptr;

private: 

	Object* m_ParentReference = nullptr;
	float m_TextureAlpha = 0.1f;

	glm::vec3 m_MeshScale = {1,1,1};
};

class RectangleMesh : public Mesh
{
public:
	RectangleMesh(Object* _objectReference, float _width, float _height);
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_