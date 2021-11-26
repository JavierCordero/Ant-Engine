#include "Material.h"
#include <gtc/type_ptr.hpp>
#ifdef _DEBUG
#include "checkML.h"
#endif // _DEBUG
Material::Material()
{
}


Material::~Material()
{
}

void Material::load() {
	glMaterialfv(face, GL_AMBIENT, glm::value_ptr(ambient));
	glShadeModel(sh);
};
