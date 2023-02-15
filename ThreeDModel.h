#pragma once

/*
			This is a ThreeDModel system.
*/

#include "BaseSystem.h"
#include <shared/defs.h>
#include <util/util.h>
#include "animTcl.h"
#include <GLmodel/GLmodel.h>
#include "shared/opengl.h"
#include <vector>
#include <glm/vec3.hpp>



// ThreeDModel system
class ThreeDModel : public BaseSystem
{

public:
	ThreeDModel(const std::string& name);

	
	
	
	void reset(double time);


	void display(GLenum mode = GL_RENDER);
	// Position vector
	glm::vec3 position;
	// Distance travelled
	float distanceTravelled;
	// Velocity
	float velocity;
	// Orientation UVW
	glm::vec3 u;
	glm::vec3 w;
	glm::vec3 v;









protected:
	
	GLMmodel m_model;

};