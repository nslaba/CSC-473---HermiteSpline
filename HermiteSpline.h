#pragma once

/*
			This is a HermiteSpline system.
			
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



// HermiteSpline system
class HermiteSpline : public BaseSystem
{

public:
	HermiteSpline(const std::string& name);
	virtual void getState(double* p);
	virtual void setState(double* p);
	//void reset(double time);

	void display(GLenum mode = GL_RENDER);

	int command(int argc, myCONST_SPEC char** argv);
	float getArcLength(float t);
	void load(std::string);
	ControlPoint getNext(ControlPoint, ControlPoint, double);
	void updateLookUpTable();
	


protected:

	
	/* Define an array of ControlPoint structs with maximum of 40 control points*/
	ControlPoint controlPoints[MAX_KNOTS];
	std::vector <LookUpTableEntry> lookUpTable;

	//keeps track of the knots set by the user
	int numKnots = 0;
	bool cr = false;
	Vector m_pos;

	GLMmodel m_model;

};
