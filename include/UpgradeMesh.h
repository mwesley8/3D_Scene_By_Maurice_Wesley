#ifndef UPGRADEMESH_H
#define UPGRADEMESH_H

#include <iostream>         // cout, cerr
#include <fstream>
#include <cstdlib>          // EXIT_FAILURE
#include <GLEW/glew.h>      // GLEW library
#include <GLFW/glfw3.h>     // GLFW library


#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>


#include <MyShader.h>
#include <string>
#include <vector>
#include <Generate.h>
#include <GenTexture.h>

using namespace std;


struct Vert {
	// position
	glm::vec3 Position;
	// texCoords
	glm::vec2 Texture;
	// normal
	glm::vec3 Normal;
};

struct Light {
	// Position
	glm::vec3 Position;
	
	// Normal
	glm::vec3 Normal;
};

//struct Texture {
//	unsigned int id;
//	string type;
//	string path;
//};

class MYMesh {
public:
	// mesh Data
	vector<Vert>          vertices;
	vector<int>           indices;
	vector<Light>         lightVertices;
	vector<int>           lightIndices;
	
	unsigned int VAO;
	unsigned int lightVAO;
	unsigned int VBO;
	unsigned int lightVBO;
	unsigned int EBO;
	unsigned int lightEBO;

	MYMesh(){}

	// constructor
	MYMesh(vector<Vert> vertices, vector<int> indices)
	{
		this->vertices = vertices;
		this->indices  = indices;

		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	// Function to retrieve object vertex and indices
	void getData(vector<Vert>& vertices, vector<int>& indices) {

		// Assign member variables to arguments passed in function
		this->vertices = vertices;
		this->indices  = indices;
		
		// now that we have the vertices and indices, we can set up the objects
		setupMesh();
	}

	

	// Function to retrieve light vertex and indices information
	void getLightData(vector<Light>& lightVertices, vector<int>& lightIndices) {
		this->lightVertices = lightVertices;
		this->lightIndices   = lightIndices;

		// now that we have the vertices and indices, we can set up the lights
		setupLight();
	}

	// render the mesh
	void Draw(GLuint& shader, GLuint& texture)
	{
		glUseProgram(shader);

		glBindTexture(GL_TEXTURE_2D, texture);

		// draw mesh

		glBindVertexArray(VAO);
		// load vertex information into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// load the indices in the element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		// Draw vertices
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the Vertex Array Object after render
		glBindVertexArray(0);

		// Set back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

	// Function to draw Lights
	void DrawLight(GLuint& shader, GLuint& texture)
	{
		// Bind the shader program to argument passed in function
		glUseProgram(shader);

		// Bind the texture that was passed in the aray
		//glBindTexture(GL_TEXTURE_2D, texture);

		// Bind the VAO generated from the previous call
		glBindVertexArray(lightVAO);

		// load vertex information into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, lightVBO);

		// load the indices in the element buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);

		// Draw the light
		glDrawElements(GL_TRIANGLES, lightIndices.size(), GL_UNSIGNED_INT, 0);

		// Unbind the Vertex Array after render
		glBindVertexArray(0);

		// Set back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}

public:
	// render data 
	

	// initializes all the buffer objects/arrays
	void setupMesh()
	{
		// Pass in a number to specify the VAO and VBOS -> setupObject(int num)
		// May need to generate Array Buffer earlier if used in conjunction with another instance
		
		
		// create buffers/arrays
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vert), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), &indices[0], GL_STATIC_DRAW);

		//Has to be stated to render object. Either when bound to VAO or when drawn
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)0);
		
		// vertex texture
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, Texture));

		// vertex normal
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, Normal));

		// Unbind array and buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void setupLight()
	{
		// Pass in a number to specify the VAO and VBOS -> setupObject(int num)
		// May need to generate Array Buffer earlier if used in conjunction with another instance


		// create buffers/arrays
		glGenVertexArrays(1, &lightVAO);
		glGenBuffers(1, &lightVBO);
		glGenBuffers(1, &lightEBO);

		glBindVertexArray(lightVAO);
		
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
		
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, lightVertices.size() * sizeof(Light), &lightVertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, lightIndices.size() * sizeof(int), &lightIndices[0], GL_STATIC_DRAW);

		//Has to be stated to render object. Either when bound to VAO or when drawn
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Light), (void*)0);

		// vertex texture
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Light), (void*)offsetof(Vert, Normal));
		

		// We are not working with texture in the light cube.
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (void*)offsetof(Vert, Texture));

		// Unbind array and buffers for next draw call
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};
#endif
