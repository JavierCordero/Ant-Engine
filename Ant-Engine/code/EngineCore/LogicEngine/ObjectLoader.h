//#pragma once
#ifndef _H_ObjectLoader_H_
#define _H_ObjectLoader_H_

#include <freeglut.h>
#include <vector>
#include <glm.hpp>

class Mesh;
class Object;
//-------------------------------------------------------------------------

static class ObjectLoader
{

public:
	ObjectLoader();
	virtual ~ObjectLoader();

	static bool LoadOBJFile(const char* _path, Object* _parent, std::vector<Mesh*>& outMeshes_);
};

//-------------------------------------------------------------------------

#endif //_H_ObjectLoader_H_

