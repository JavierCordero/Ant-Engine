#pragma once
#include <math.h>
#include <detail/type_vec.hpp>
#include <detail/func_geometric.hpp>
#include <random>

#define PI 3.14159265358979323846

static class MathLib
{
public:
	static glm::vec3 ClampMagnitude(glm::vec3 _vector, float magnitude);
	static glm::vec3 RandomVectorInsideSphere(float _radious);

	static bool IsPointInsideCone(glm::vec3 _conePosition, glm::vec3 _forwardVector, float _height, float _baseRadious, glm::vec3 _point);
	static bool IsPointInCube(glm::vec3 _point, glm::vec3 _cubePosition, glm::vec3 _cubeSize);
	static bool OverlappingCubes(glm::vec3 _cubeAPosition, glm::vec3 _cubeASize, glm::vec3 _cubeBPosition, glm::vec3 _cubeBSize);

	static inline float Distance(glm::vec3 pointA, glm::vec3 pointB) { return sqrt(pow(pointB.x - pointA.x, 2) + pow(pointB.y - pointA.y, 2) + pow(pointB.z - pointA.z, 2)); }
};

