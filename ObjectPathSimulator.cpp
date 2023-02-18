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

/* Distance: takes in parameterized time and returns local distance*/
double ObjectPathSimulator::d(double t)
{

	/* STEP 2: update constants*/

	float vm = A0 * T1;
	/* STEP 3: Initialize velocities for each segment & distanceTravelled*/
	float v1 = vm * (t / T1); // Increasing over time
	float v2 = vm; //max velocity
	float v3 = vm * (1.0 - ((t - T2) / (1.0 - T2))); // Decreasing over time

	float distanceTravelled = 0;

	/* STEP 4: update distanceTravelled based on acceleration */

	if (t <= T1)
	{
		distanceTravelled = v1 * (pow(t, 2)) / (2.0 * T1);
	}
	else if (t > T1 && t <= T2)
	{
		distanceTravelled = vm * (T1 / 2.0) + v2 * (t - T1);
	}
	else if (t > T2 && t<1)
	{
		distanceTravelled = (vm * (T1 / 2.0)				// before t1
			+ vm * (T2 - T1)								// btwn t1 and t2
			+ (vm  - (vm*(t - T2)/(1-T2))/2)*(t-T2));		// after t2				
	}
	else {
		distanceTravelled = vm * (T1 / 2.0) +
			v2 * (T2 - T1) +
			vm * (1.0 - T2) * (1.0/2.0);
	}

	return distanceTravelled;
}


double ObjectPathSimulator::distance(double time)
{
	
	float fullLength = splinePath->getFullLength();
	float vm = 10;

	double t0 = fullLength / (5 * vm);
	double t1 = 4 * t0;

	float distance = 0;
	double a0 = vm / t0;
	if (time < t0) {
		// b X h / 2
		
		distance = a0 * pow(time, 2) / 2.0;
	}
	else if (time >= t0 && time < (t0 + t1)) {
		// b X h / 2 + b X h
		distance = (fullLength / 10.0) + vm * (time - t0);
	}
	else if (time > (t0+t1) && time < (2*t0 + t1)){
		distance = fullLength - (a0 * (pow(2 * t0 + t1 - time, 2)) / 2);
	}
	else {
		distance = fullLength;
	}
	return distance;
}

int ObjectPathSimulator::step(double time)
{
	/* STEP 1: Get the correct distance travelled based on acceleration*/

	/* STEP 1. a) parameterize time to be between 0 and 1*/

	double t = time / SCENE; // 10 seconds for the whole animation

	/* STEP 1. b) Parameterize distance and then cast it*/

	double dTravelled = (d(t) / d(1.0)) * splinePath->getFullLength();

	if (t >= 0.99) dTravelled = splinePath->getFullLength();

	float distanceTravelled = distance(time);

	/* STEP 2: Calculate position based on P(u(s(t)))*/
		
	//TEST BEFORE MOVING ON
	/*animTcl::OutputMessage("distanceTravelled in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(distanceTravelled).c_str()));
	animTcl::OutputMessage("for t: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(t).c_str()));

	*/

	/* STEP 2. b) get parameter U based on distance travelled by threeDModel*/
	LookUpTableEntry tempEntry = LookUpTableEntry();
	tempEntry.arcLength = distanceTravelled;
	double u = splinePath->getU(tempEntry);

	//TEST BEFORE MOVING ON
	//animTcl::OutputMessage("u in simulator is: ");
	//animTcl::OutputMessage(const_cast<char*>(std::to_string(u).c_str()));

	/* STEP 2. c) get POSITION of m_threeDmodel based on U*/

	// create a temp point
	ControlPoint point = ControlPoint();
	point = splinePath->getPointAtU(u);
	m_threeDmodel->position = point.point;

	/*animTcl::OutputMessage("x position in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(m_threeDmodel->position.x).c_str()));*/

	/* STEP 3 ACCOUNT FOR ROTATION*/

	/* STEP 3) a. update u,v,w*/
	m_threeDmodel->w = point.tangent;
	m_threeDmodel->u = glm::cross(point.tangent, point.secondTangent);
	m_threeDmodel->v = glm::cross(m_threeDmodel->w, m_threeDmodel->u);

	//normalize them
	m_threeDmodel->w = glm::normalize(m_threeDmodel->w);
	m_threeDmodel->u = glm::normalize(m_threeDmodel->u);
	m_threeDmodel->v = glm::normalize(m_threeDmodel->v);
	/* STEP 3) b. use quaternions for object rotation*/


	return 0;

}	// ObjectPathSimulator::step