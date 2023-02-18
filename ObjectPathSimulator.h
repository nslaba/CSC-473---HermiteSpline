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

#define T1 0.1
#define T2 0.9
#define A0 2000
#define SCENE 8.0

// a sample simulator

class ObjectPathSimulator : public BaseSimulator
{
public:

	ObjectPathSimulator(const std::string& name, HermiteSpline* targetPath, ThreeDModel* targetObject);
	~ObjectPathSimulator();
	double distance(double time);
	double d(double time); //Temp while I debug
	int step(double time);
	int init(double time)
	{
		m_threeDmodel->position;

		// FOR NOW: set threeDmodel's velocity to a constant

		return 0;
	};

	int command(int argc, myCONST_SPEC char** argv) { return TCL_OK; }

protected:


	
	ThreeDModel* m_threeDmodel;
	HermiteSpline* splinePath;

};
