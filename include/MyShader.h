#ifndef MYSHADER_H
#define MYSHADER_H

// Base code provided by SNHU and adapted by Maurice Wesley

#include <GLEW/glew.h>
#include <GLFW/glfw3.h> 
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>

#include <stdlib.h>
#include <string.h>
#include <Generate.h>
#include <UpgradeMesh.h>
#include "MyShader.h"

// The original shader was connected to a glad application. Also, similar shaders may be
// built on a 32/86 bit and not a 64 like the one from the book. My current application is ran
// using GLEW. Credentials were given to each header. Each header is linked to each other. The load shaders function
// was wrapped in a class called MyShader. I had to include the pass by reference programID in the funciton declaration.
// Replaced int ID with programID. Now the header returns a shader linked to the program.


using namespace std;

class MyShader {

public:

	MyShader() {}

	void loadShaders(const char* vertex_file_path, const char* fragment_file_path, GLuint& programID, const char* geometry_file_path = nullptr) {
	    // Create the shaders
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		// Read the Vertex Shader code from the file
		std::string VertexShaderCode;
		std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
		if (VertexShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << VertexShaderStream.rdbuf();
			VertexShaderCode = sstr.str();
			VertexShaderStream.close();
		}
		else {
			printf("Unable to open %", vertex_file_path);
		}

		// Read the Fragment Shader code from the file
		std::string FragmentShaderCode;
		std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
		if (FragmentShaderStream.is_open()) {
			std::stringstream sstr;
			sstr << FragmentShaderStream.rdbuf();
			FragmentShaderCode = sstr.str();
			FragmentShaderStream.close();
		}

		GLint Result = GL_FALSE;
		int InfoLogLength;


		// Compile Vertex Shader
		printf("Compiling shader : %s\n", vertex_file_path);
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
		glCompileShader(VertexShaderID);

		// Check Vertex Shader
		glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
			printf("%s\n", &VertexShaderErrorMessage[0]);
		}



		// Compile Fragment Shader
		printf("Compiling shader : %s\n", fragment_file_path);
		char const* FragmentSourcePointer = FragmentShaderCode.c_str();
		glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
		glCompileShader(FragmentShaderID);

		// Check Fragment Shader
		glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
		glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
			glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
			printf("%s\n", &FragmentShaderErrorMessage[0]);
		}



		// Link the program
		printf("Linking program\n");
		programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);
		glLinkProgram(programID);

		// Check the program
		glGetProgramiv(programID, GL_LINK_STATUS, &Result);
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
		if (InfoLogLength > 0) {
			std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
			glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
			printf("%s\n", &ProgramErrorMessage[0]);
		}


		glDetachShader(programID, VertexShaderID);
		glDetachShader(programID, FragmentShaderID);

		glDeleteShader(VertexShaderID);
		glDeleteShader(FragmentShaderID);
	}

	// activate the shader
	// ------------------------------------------------------------------------
	void use(GLuint &programID)
	{
		glUseProgram(programID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(GLuint& programID, const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(GLuint& programID, const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(GLuint& programID, const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setVec2(GLuint& programID, const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
	}
	void setVec2(GLuint& programID, const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(programID, name.c_str()), x, y);
	}
	// ------------------------------------------------------------------------
	void setVec3(GLuint& programID, const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
	}
	void setVec3(GLuint& programID, const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(programID, name.c_str()), x, y, z);
	}
	// ------------------------------------------------------------------------
	void setVec4(GLuint& programID, const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(programID, name.c_str()), 1, &value[0]);
	}
	void setVec4(GLuint& programID, const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(programID, name.c_str()), x, y, z, w);
	}
	// ------------------------------------------------------------------------
	void setMat2(GLuint& programID, const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat3(GLuint& programID, const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
	// ------------------------------------------------------------------------
	void setMat4(GLuint& programID, const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
	}
};
#endif