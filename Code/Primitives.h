#pragma once
#include "Mesh.h"


static class Primitives
{
public:
    static Mesh* CreateCubeOutline(double _width, glm::vec3 _color, Object* _objectReference, Mesh* _targetMesh);
    static Mesh* CreateRectangleOutline(glm::vec3 _size, glm::vec3 _color, Object* _objectReference, Mesh* _targetMesh);
    static Mesh* CreateConeOutline(float _baseRadious, float _height, glm::vec4 _color, Object* _objectReference, Mesh* _targetMesh);
    static Mesh* CreateCircle(float _radious, glm::vec4 _color, Object* _objectReference, Mesh* _targetMesh, float _height = 0);
};

