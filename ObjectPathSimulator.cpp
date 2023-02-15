#include "ObjectPathSimulator.h"

ObjectPathSimulator::ObjectPathSimulator(const std::string& name, HermiteSpline* targetPath, ThreeDModel* targetObject) :
	BaseSimulator(name),
	splinePath(targetPath),
	m_threeDmodel(targetObject)
{
}	// ObjectPathSimulator

ObjectPathSimulator::~ObjectPathSimulator()
{
}	// ObjectPathSimulator::~ObjectPathSimulator

int ObjectPathSimulator::step(double time)
{
	/* STEP 1: Get the full length of the path*/
	double fullPathLength = splinePath->getFullLength();

	/* STEP 2: Calculate position based on P(u(s(t)))*/
	
	/*STEP 2. a) Calculate distance travelled by object assuming innitial velocity is fixed for now*/

	float distanceTravelled = time * m_speed;
	
	
	//TEST BEFORE MOVING ON
	/*animTcl::OutputMessage("ArcLength in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(s).c_str()));*/

	/* STEP 2. b) get parameter U based on arclength S*/
	/*double u = m_object->getU(s);*/

	//TEST BEFORE MOVING ON
	
	/* STEP 2. c) get POSITION of m_threeDmodel based on U--> use first and last points on the spline*/
	
	/*m_object->getState(pos);*/
	/*pos = float(2 * pow(u, 3) - 3 * pow(u, 2) + 1) * HermiteSpline::lookUpTable[0].point
		+ float(-2 * pow(u, 3) + 3 * pow(u, 2)) * end.point
		+ float(pow(u, 3) - 2 * pow(u, 2) + u) * start.tangent
		+ float(pow(u, 3) - pow(u, 2)) * end.tangent;*/

	

	/*m_object->setState(pos);*/
	// Once I have position calculate first and second derrivatives in order to solve for u,v, w of the object
	

	return 0;

}	// ObjectPathSimulator::step