#include "Object.h"

Object::Object(const std::string& name) :
	BaseSystem(name),
	m_sx(1.0f),
	m_sy(1.0f),
	m_sz(1.0f)
{

	setVector(m_pos, 0, 0, 0);

}	// Object

void Object::getState(double* p)
{

	VecCopy(p, m_pos);

}	// Object::getState

void Object::setState(double* p)
{

	VecCopy(m_pos, p);

}	// Object::setState

void Object::reset(double time)
{

	setVector(m_pos, 0, 0, 0);

}	// Object::Reset



void Object::display(GLenum mode)
{
	glEnable(GL_LIGHTING) ;
	glMatrixMode(GL_MODELVIEW) ;
	glPushMatrix() ;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glTranslated(m_pos[0],m_pos[1],m_pos[2]) ;
	glScalef(m_sx,m_sy,m_sz) ;

	if( m_model.numvertices > 0 )
		glmDraw(&m_model, GLM_SMOOTH | GLM_MATERIAL);
	else
		glutSolidSphere(1.0,20,20) ;

	glPopMatrix();
	glPopAttrib();

}	// Object::display
