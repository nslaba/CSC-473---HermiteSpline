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
	//if distanceTravelled is greater than or equal to the length of the spine then make it equal to full length
	
	if (distanceTravelled >= fullPathLength) distanceTravelled = fullPathLength;
	
	//TEST BEFORE MOVING ON
	/*animTcl::OutputMessage("distanceTravelled in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(distanceTravelled).c_str()));*/

	/* STEP 2. b) get parameter U based on distance travelled by threeDModel*/
	LookUpTableEntry tempEntry = LookUpTableEntry();
	tempEntry.arcLength = distanceTravelled;
	double u = splinePath->getU(tempEntry);

	//TEST BEFORE MOVING ON
	//animTcl::OutputMessage("u in simulator is: ");
	//animTcl::OutputMessage(const_cast<char*>(std::to_string(u).c_str()));

	/* STEP 2. c) get POSITION of m_threeDmodel based on U--> use first and last points on the spline*/
		// Right now I am interpolating between first and last point. But I have to find the position along the spline
	// create a point
	ControlPoint point = ControlPoint();
	point = splinePath->getPointAtU(u);
	m_threeDmodel->position = point.point;

	/*animTcl::OutputMessage("x position in simulator is: ");
	animTcl::OutputMessage(const_cast<char*>(std::to_string(m_threeDmodel->position.x).c_str()));*/

	/* STEP 2 ACCOUNT FOR ROTAION*/

	/* STEP 2) a. update u,v,w*/
	m_threeDmodel->w = point.tangent;
	m_threeDmodel->u = glm::cross(point.tangent, point.secondTangent);
	m_threeDmodel->v = glm::cross(m_threeDmodel->w, m_threeDmodel->u);

	//normalize them
	m_threeDmodel->w = glm::normalize(m_threeDmodel->w);
	m_threeDmodel->u = glm::normalize(m_threeDmodel->u);
	m_threeDmodel->v = glm::normalize(m_threeDmodel->v);
	/* STEP 2) b. use quaternions for object rotation*/

	
	// Once I have position calculate first and second derrivatives in order to solve for u,v, w of the object
	

	return 0;

}	// ObjectPathSimulator::step