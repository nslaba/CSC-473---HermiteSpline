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
double ObjectPathSimulator::distance(double t)
{
	/* STEP 1: update time constants*/

	double t1 = 0.1;
	double t2 = 0.9;

	/* STEP 2: update constants*/
	float a0 = 100; // not a0 != -a1 nescessairly
	float vm = a0 * t1;

	/* STEP 3: Initialize velocities for each segment & distanceTravelled*/
	float v1 = vm * (t / t1); // Increasing over time
	float v2 = vm; //max velocity
	float v3 = vm * (1.0 - ((t - t2) / (1.0 - t2))); // Decreasing over time

	animTcl::OutputMessage("v3 after calculated is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(v3).c_str()));

	animTcl::OutputMessage("for t: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(t).c_str()));

	float distanceTravelled = 0;

	/* STEP 4: update distanceTravelled based on acceleration */

	if (t <= 0.1)
	{
		distanceTravelled = v1 * (pow(t, 2)) / (2.0 * t1);
		animTcl::OutputMessage(" in t<=0.1 ");

		/*animTcl::OutputMessage("v1 is: ");
		animTcl::OutputMessage(const_cast<char*>(std::to_string(v1).c_str()));*/

		animTcl::OutputMessage("distance travelled is for t<=0.1: ");
		animTcl::OutputMessage(const_cast<char*>(std::to_string(distanceTravelled).c_str()));
	}
	else if (t > 0.1 && t < 0.9)
	{
		distanceTravelled = vm * (t1 / 2.0) + v2 * (t - t1);
		animTcl::OutputMessage(" in t> 0.1 && t< 0.9 ");

		/*animTcl::OutputMessage("v2 is: ");
		animTcl::OutputMessage(const_cast<char*>(std::to_string(v2).c_str()));*/

		animTcl::OutputMessage("distance travelled is for t>=0.1 and t<0.9: ");
		animTcl::OutputMessage(const_cast<char*>(std::to_string(distanceTravelled).c_str()));
	}
	else
	{
		animTcl::OutputMessage("v3 in else before is: ");
		animTcl::OutputMessage(const_cast<char*>(std::to_string(v3).c_str()));
		distanceTravelled = vm * (t1 / 2.0) + v2 * (t2 - t1) + v3 * (t - t2) * (1 - (t - t2) / (2 * (1 - t2)));


		animTcl::OutputMessage("distance travelled is for t>=0.9: ");
		animTcl::OutputMessage(const_cast<char*>(std::to_string(distanceTravelled).c_str()));

		
	}

	return distanceTravelled;
}

int ObjectPathSimulator::step(double time)
{
	/* STEP 1: Get the correct distance travelled based on acceleration*/

	/* STEP 1. a) parameterize time to be between 0 and 1*/

	double t = time / 5.0; // 5 seconds for the whole animation

	/* STEP 1. b) Parameterize distance and then cast it*/

	double distanceTravelled = (distance(t) / distance(1.0)) * splinePath->getFullLength();
	if (t >= 0.9) distanceTravelled = splinePath->getFullLength();

	/* STEP 2: Calculate position based on P(u(s(t)))*/
		
	//TEST BEFORE MOVING ON
	/*animTcl::OutputMessage("distanceTravelled in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(distanceTravelled).c_str()));
	animTcl::OutputMessage("for t: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(t).c_str()));


	animTcl::OutputMessage("non parameterized distance at t= 1: ");
	double d1 = distance(1);
	animTcl::OutputMessage(const_cast<char*>(std::to_string(d1).c_str()));

	animTcl::OutputMessage("non parameterized distance at t= 0.9: ");
	double d2 = distance(0.9);
	animTcl::OutputMessage(const_cast<char*>(std::to_string(d2).c_str()));

	animTcl::OutputMessage("non parameterized distance d(0.15)/ d(1.0): ");
	double d3 = d2/d1;
	animTcl::OutputMessage(const_cast<char*>(std::to_string(d3).c_str()));

	animTcl::OutputMessage("parameterized distance d(0.1)/ d(1.0) * full length: ");
	double d4 = d2 / d1 * splinePath->getFullLength();
	animTcl::OutputMessage(const_cast<char*>(std::to_string(d4).c_str()));

	animTcl::OutputMessage("full length: ");
	double d5 = splinePath->getFullLength();
	animTcl::OutputMessage(const_cast<char*>(std::to_string(d5).c_str()));*/

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