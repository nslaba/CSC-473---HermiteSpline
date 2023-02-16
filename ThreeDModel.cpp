#include "ThreeDModel.h"

ThreeDModel::ThreeDModel(const std::string& name) :
	BaseSystem(name),
	position(0),
	distanceTravelled(0),
	velocity(10),
	u(0),
	v(0),
	w(0)
{
	m_model.ReadOBJ("data/porsche.obj");
	

}	// ThreeDModel





void ThreeDModel::reset(double time)
{

	position = { 0,0,0 };

}	// ThreeDModel::Reset



void ThreeDModel::display(GLenum mode)
{
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslated(position[0], position[1], position[2]);
	glScalef(0.01f, 0.01f, 0.01f);

	if (m_model.numvertices > 0)
		glmDraw(&m_model, GLM_SMOOTH | GLM_MATERIAL);
	else
		glutSolidSphere(1.0, 20, 20);

	glPopMatrix();
	glPopAttrib();

}	// ThreeDModel::display