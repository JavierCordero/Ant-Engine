#include "MathLib.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG

glm::vec3 MathLib::ClampMagnitude(glm::vec3 _vector, float magnitude) {

	glm::vec3 norm = glm::normalize(_vector);
	glm::vec3 minimun = glm::min(norm, magnitude);

	float auxX = 0, auxY = 0, auxZ = 0;

	if (minimun.x != 0) {
		auxX = minimun.x / norm.x;
	}

	if (minimun.y != 0) {
		auxY = minimun.y / norm.y;
	}

	if (minimun.z != 0) {
		auxZ = minimun.z / norm.z;
	}

	glm::vec3 normalizedResult = glm::vec3(auxX, auxY, auxZ);

	return _vector * normalizedResult;
}

glm::vec3 MathLib::RandomVectorInsideSphere(float _radious)
{
	float r = _radious * sqrt((float)rand() / (RAND_MAX));
	float theta = (float)rand() / (RAND_MAX) * 2 * PI;
	float phi = (float)rand() / (RAND_MAX) * PI;

	float x = r * sin(phi) * cos(theta);
	float y = r * sin(phi)* sin(theta);
	float z = r * cos(phi);

	return glm::vec3(x, y, z);
}

bool MathLib::IsPointInsideCone(glm::vec3 _conePosition, glm::vec3 _forwardVector, float _height, float _baseRadious, glm::vec3 _point)
{
	float coneDistance = glm::dot(_point - _conePosition, _forwardVector);
	float coneDistanceB = glm::length(_point - _conePosition);

	//float heightDistance = glm::distance(_point, _forwardVector * _height);

	//if ( heightDistance > coneDistance || heightDistance <= 0)
	//{
	//	return false;
	//}

	if (coneDistanceB > _height)
	{
		return false;
	}

	float radious = (coneDistance / _height) * _baseRadious;

	float orthDistance = glm::length((_point - _conePosition) - coneDistance * _forwardVector);

	return orthDistance < radious;
}

bool MathLib::IsPointInCube(glm::vec3 _point, glm::vec3 _cubePosition, glm::vec3 _cubeSize) {
	int minX = _cubePosition.x - _cubeSize.x;
	int maxX = _cubePosition.x + _cubeSize.x;

	int minY = _cubePosition.y - _cubeSize.y;
	int maxY = _cubePosition.y + _cubeSize.y;

	int minZ = _cubePosition.z - _cubeSize.z;
	int maxZ = _cubePosition.z + _cubeSize.z;

	if (minX <= _point.x && _point.x <= maxX && minY <= _point.y && _point.y <= maxY && minZ <= _point.z && _point.z <= maxZ)
		return true;
	return false;
}

bool MathLib::OverlappingCubes(glm::vec3 _cubeAPosition, glm::vec3 _cubeASize, glm::vec3 _cubeBPosition, glm::vec3 _cubeBSize) {

	int minXA = _cubeAPosition.x - _cubeASize.x;
	int maxXA = _cubeAPosition.x + _cubeASize.x;

	int minYA = _cubeAPosition.y - _cubeASize.y;
	int maxYA = _cubeAPosition.y + _cubeASize.y;

	int minZA = _cubeAPosition.z - _cubeASize.z;
	int maxZA = _cubeAPosition.z + _cubeASize.z;

	int minXB = _cubeBPosition.x - _cubeBSize.x;
	int maxXB = _cubeBPosition.x + _cubeBSize.x;

	int minYB = _cubeBPosition.y - _cubeBSize.y;
	int maxYB = _cubeBPosition.y + _cubeBSize.y;

	int minZB = _cubeBPosition.z - _cubeBSize.z;
	int maxZB = _cubeBPosition.z + _cubeBSize.z;

	return (minXA <= maxXB && maxXA >= minXB) &&
		(minYA <= maxYB && maxYA >= minYB) &&
		(minZA <= maxZB && maxZA >= minZB);
}