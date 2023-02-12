#pragma once

/*
			This is a Object system.

*/

#include "BaseSystem.h"
#include <shared/defs.h>
#include <util/util.h>
#include "animTcl.h"
#include <GLmodel/GLmodel.h>
#include "ControlPoint.h"
#include "LookUpTableEntry.h"
#include "shared/opengl.h"
#include <vector>

#define MAX_KNOTS 40



// Object system
class Object : public BaseSystem
{

public:
	Object(const std::string& name);
	
	void reset(double time);
	virtual void getState(double* p);
	virtual void setState(double* p);
	//void reset(double time);

	void display(GLenum mode = GL_RENDER);








protected:

	float m_sx;
	float m_sy;
	float m_sz;
	/* Define an array of ControlPoint structs with maximum of 40 control points*/
	ControlPoint controlPoints[MAX_KNOTS];
	Vector m_pos;
	GLMmodel m_model;

};