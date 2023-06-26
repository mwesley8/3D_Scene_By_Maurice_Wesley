#ifndef GENTEXTURE
#define GENTEXTURE

#include <iostream>         // cout, cerr
#include <fstream>
#include <cstdlib>          // EXIT_FAILURE
#include <GLEW/glew.h>      // GLEW library
#include <GLFW/glfw3.h>     // GLFW library
#include <SOIL2/SOIL2.h>

#include <Generate.h>       // Must be included
#include <UpgradeMesh.h>



using namespace std;

class GenerateTexture {
	
public:
	GenerateTexture() {}

	void genObjectTexture(const char* image, GLuint &location) {

        // Declare local variables for back wall width and height
        int wallWidth, wallHeight;

        // Load picture from SOIL
        unsigned char* Image = SOIL_load_image(image, &wallWidth, &wallHeight, 0, SOIL_LOAD_RGB);

        // Generate Texture
        glGenTextures(1, &location);

        // Activate the Texture
        glBindTexture(GL_TEXTURE_2D, location);

        // Condition to check if image was loaded
        if (Image) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, wallWidth, wallHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, Image);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        // Output to user when condition is false
        else {
            cout << "Failed to load texture" << endl;
        }

        // Release memory
        SOIL_free_image_data(Image);

        // Deactivate the texture
        glBindTexture(GL_TEXTURE_2D, 0);
	}
};
#endif // !GENTEXTURE

