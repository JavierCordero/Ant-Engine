#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "..\EngineCore.h"

#ifdef _DEBUG
#include "..\checkML.h"
#endif // _DEBUG
//-------------------------------------------------------------------------

Entity::~Entity()
{
	delete currentMaterial;
	currentMaterial = nullptr;

	for (auto& item : entityComponents)
		delete[] item;

	

	entityComponents.clear();
}

void Entity::Render(glm::dmat4 const& modelViewMat)
{ 
	if (isVisible) {
		if (currentMaterial != nullptr) {
			currentMaterial->load();
		}

		for each (Component * component in entityComponents)
		{
			component->Render(modelViewMat);
		}

		//Mesh::Render(modelViewMat);

		SetModelViewMat(modelViewMat);

		//for each (Mesh* mesh  in meshes)
		//{
		//	mesh->Render(modelViewMat);
		//}
	}
}

void Entity::Update(double timeElapsed) {
	//Mesh::Update(timeElapsed);

	Object::Update(timeElapsed);

	for each (Component* component in entityComponents)
	{
		component->Update(timeElapsed);
	}

	/*for each (Mesh * mesh  in meshes)
	{
		mesh->Update(timeElapsed);
	}*/
}


void Entity::PostUpdate(double elapsedTime) {
	Object::PostUpdate(elapsedTime);

	for each (Component * component in entityComponents)
	{
		component->PostUpdate(elapsedTime);
	}
}

void Entity::Destroy() {
	EngineCore::GetScene()->EraseSceneEntity(this);
}

//-------------------------------------------------------------------------

//void Entity::Draw() 
//{ 
//	if (mesh != nullptr) {
//		currentMaterial->load();
//		mesh->Draw();
//	}
//}

//-------------------------------------------------------------------------

//ContCubo::ContCubo(GLdouble l, GLint x, GLint y) : Entity(x,y)
//{
//	mesh = Mesh::generateContCubo(l);
//}
////-------------------------------------------------------------------------
//
//void ContCubo::draw()
//{
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glColor3d(0, 0, 0);
//	glLineWidth(2);
//	mesh->Draw();
//
//	glLineWidth(1);
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//}
//

//
//void RectangleText::draw()
//{
//	glEnable(GL_REPEAT);
//	textura.bind();
//	glLineWidth(2);
//	mesh->Draw();
//	glLineWidth(1);
//	textura.unbind();
//	glDisable(GL_REPEAT);
//
//}
//
//void RectangleText::render(glm::dmat4 const & modelViewMat)
//{
//
//	dmat4 aMat = modelViewMat * modelMat;
//	
//	glLoadMatrixd(value_ptr(aMat));
//	draw();
//}
//
//CuboText::CuboText(GLdouble l, GLdouble h, GLint x, GLint y) : Entity(x, y)
//{
//	mesh = Mesh::generateCuboText(l); // con coord. de textura
//	textura.load("..\\Resources\\Bmps\\container.bmp"); // cargamos la imagen
//}
//
//void CuboText::draw()
//{
//
//	textura.bind();
//	glLineWidth(2);
//	mesh->Draw();
//	glLineWidth(1);
//	textura.unbind();
//
//}
//
//void CuboText::render(glm::dmat4 const & modelViewMat)
//{
//
//	dmat4 aMat = modelViewMat * modelMat;
//
//	glLoadMatrixd(value_ptr(aMat));
//	draw();
//}
//
//Foto::Foto(GLdouble l, GLdouble h, GLint xRep, GLint  yRep, GLint x, GLint y, GLint z) : Entity(x, y)
//{
//	mesh = Mesh::generateRectangleTex(l, h, xRep, yRep); // con coord. de textura
//	textura.load("..\\Bmps\\foto.bmp"); // cargamos la imagen
//
//	modelMat = translate(modelMat, dvec3(x, y, z));
//	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0));
//	modelMat = rotate(modelMat, radians(180.0), dvec3(0, 0, 1));
//	modelMat = rotate(modelMat, radians(180.0), dvec3(0, 1, 0));
//
//}
//
//void Foto::draw()
//{
//	glEnable(GL_REPEAT);
//	textura.bind();
//	glLineWidth(2);
//	mesh->Draw();
//	glLineWidth(1);
//	textura.unbind();
//	glDisable(GL_REPEAT);
//
//}
//
//void Foto::render(glm::dmat4 const & modelViewMat)
//{
//
//	dmat4 aMat = modelViewMat * modelMat;
//
//	glLoadMatrixd(value_ptr(aMat));
//	draw();
//}
//
//GlassPot::GlassPot(GLdouble l, GLdouble h, GLint x, GLint y, GLint z) : Entity(x, y)
//{
//	mesh = Mesh::generateCuboText(l); // con coord. de textura
//	textura.load("..\\Bmps\\window.bmp", 100); // cargamos la imagen
//
//	modelMat = translate(modelMat, dvec3(x, y, z));
//	modelMat = rotate(modelMat, radians(90.0), dvec3(1, 0, 0));
//
//}
//
//void GlassPot::draw()
//{
//	
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	
//	textura.bind();
//	mesh->Draw();
//	textura.unbind();
//
//
//}
//
//void GlassPot::render(glm::dmat4 const & modelViewMat)
//{
//	glDepthMask(FALSE);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	dmat4 aMat = modelViewMat * modelMat;
//
//	glLoadMatrixd(value_ptr(aMat));
//	draw();
//
//	glDepthMask(TRUE);
//}
//
//Grass::Grass(GLdouble r, GLdouble h, GLint x, GLint y, GLint z) : Entity(x, y)
//{
//	mesh = Mesh::generateRectangleTex(r, h, 0, 0);
//
//	textura.load("..\\Resources\\Bmps\\grass.bmp", {0,0,0}, 0); // cargamos la imagen (el segundo parámetro es el color que queremos hacer transparente, el tercero el
//	//valor d transparencia que queremos);
//
//	textura.wrap(); //Para que wrap no sea REPEAT
//
//	modelMat = translate(modelMat, dvec3(x, y, z)); // movemos el objeto
//	
//	r_ = r; h_ = h;
//	x_ = x; y_ = y; z_ = z;
//
//}
////-------------------------------------------------------------------------
//
//void Grass::draw() {
//	textura.bind();
//	glLineWidth(2);
//	mesh->Draw();
//	glLineWidth(1);
//	textura.unbind();
//}
//
//void Grass::render(glm::dmat4 const& modelViewMat)
//{
//	//Al ser dos objetos, tenemos que moverlo dos veces y dibujarlo
//	glDepthMask(FALSE);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	dmat4 aMat = modelViewMat * modelMat;
//	aMat = rotate(aMat, radians(45.0), dvec3(0, 1, 0));
//	glLoadMatrixd(value_ptr(aMat));
//	draw();
//
//	aMat = modelViewMat * modelMat;
//	aMat = rotate(aMat, radians(45.0), dvec3(0, -1, 0));
//	glLoadMatrixd(value_ptr(aMat));
//	draw();
//
//	glDepthMask(TRUE);
//}