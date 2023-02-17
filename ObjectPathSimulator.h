#pragma once

#include <GLModel/GLModel.h>
#include <shared/defs.h>
#include <util/util.h>
#include "animTcl.h"
#include "BaseSimulator.h"
#include "BaseSystem.h"
#include "HermiteSpline.h"
#include <string>
#include "ThreeDModel.h"

// a sample simulator

class ObjectPathSimulator : public BaseSimulator
{
public:

	ObjectPathSimulator(const std::string& name, HermiteSpline* targetPath, ThreeDModel* targetObject);
	~ObjectPathSimulator();
	double distance(double time);
	int step(double time);
	int init(double time)
	{
		m_threeDmodel->position;

		// FOR NOW: set threeDmodel's velocity to a constant

		return 0;
	};

	int command(int argc, myCONST_SPEC char** argv) { return TCL_OK; }

protected:

	glm::vec3 m_pos0; // initial position
	float m_speedInit = 0; // initial velocity
	
	ThreeDModel* m_threeDmodel;
	HermiteSpline* splinePath;

};
