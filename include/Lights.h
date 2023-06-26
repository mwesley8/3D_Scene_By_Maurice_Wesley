#ifndef LIGHTS_H
#define LIGHTS_H

#include <iostream>         // cout, cerr
#include <fstream>
#include <cstdlib>          // EXIT_FAILURE
#include <GLEW/glew.h>      // GLEW library
#include <GLFW/glfw3.h>     // GLFW library
#include <SOIL2/SOIL2.h>


// GLM Math Header inclusions
#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <MyShader.h>
#include <MyCamera.h>
#include <Generate.h>       // Must be included
#include <UpgradeMesh.h>
#include <GenTexture.h>
#include <cmath>
#include <vector>

// The code in the book recommended a better solution to assigning light properties. I came up with the following.
// Created with inspiration from the resource material provided by SNHU. THe Lights header is an adaptation of the Mesh
// header. It is comprosied of a structure and a class. The structure holds vec3 variables and floats. The struct is instantiated
// and pass into a vector to hold the point lights information. The information is return to the program. Once the program has 
// the point light's information, the program can iterate over the vector to assign specific point light attributes.

using namespace std;

// Struct to hold point light information
struct PointLight {
	glm::vec3 pointPosition;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	GLfloat constant;
	GLfloat linear;
	GLfloat quadratic;
};

class MySceneLights {

public:

	// Function to retrieve a specific light's information
	void getPointLight(vector<PointLight>& pointLights, vector <glm::vec3> pointLocations) {
		// Note: I could have put the following in a for loop. However, I wanted access to the attributes
		//       of each light. That enables me to change one without affecting the others.


		PointLight pL;

		// Center Light
		pL.pointPosition = pointLocations.at(0);
		pL.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
		pL.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		pL.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		pL.constant = 0.8f;
		pL.linear = 0.09f;
		pL.quadratic = 0.032f;
			
		pointLights.push_back(pL);

		// left back light
		pL.pointPosition = pointLocations.at(1);
		pL.ambient = glm::vec3(0.5f, 0.5f, 0.5f);
		pL.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		pL.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		pL.constant = 1.0f;
		pL.linear = 0.09f;
		pL.quadratic = 0.032f;

		pointLights.push_back(pL);

		// Right back light
		pL.pointPosition = pointLocations.at(2);
		pL.ambient = glm::vec3(0.8f, 0.8f, 0.8f);
		pL.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		pL.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		pL.constant = 1.0f;
		pL.linear = 0.09f;
		pL.quadratic = 0.032f;

		pointLights.push_back(pL);

		// Left front light
		pL.pointPosition = pointLocations.at(3);
		pL.ambient = glm::vec3(0.3f, 0.3f, 0.3f);
		pL.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		pL.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		pL.constant = 1.0f;
		pL.linear = 0.09f;
		pL.quadratic = 0.032f;

		pointLights.push_back(pL);

		// Right front light
		pL.pointPosition = pointLocations.at(4);
		pL.ambient = glm::vec3(0.3f, 0.3f, 0.3f);
		pL.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		pL.specular = glm::vec3(1.0f, 1.0f, 1.0f);
		pL.constant = 1.0f;
		pL.linear = 0.09f;
		pL.quadratic = 0.032f;

		pointLights.push_back(pL);
	}
};
#endif