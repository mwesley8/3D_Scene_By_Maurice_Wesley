#ifndef GENERATE_H
#define GENERATE_H

#include <iostream>         // cout, cerr
#include <fstream>
#include <cstdlib>          // EXIT_FAILURE
#include <GLEW/glew.h>      // GLEW library
#include <GLFW/glfw3.h>     // GLFW library

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
#include <UpgradeMesh.h>
//#include <Lights.h>

using namespace std;


class GetIndices {

public:

    GetIndices() {}

    // Function to generate the scene's indices
    void generateSceneIndices(vector<int>& backSceneIndices, vector<int>& tableIndices) {
        backSceneIndices.push_back(0); backSceneIndices.push_back(1); backSceneIndices.push_back(2);
        
        backSceneIndices.push_back(2); backSceneIndices.push_back(1); backSceneIndices.push_back(3);

        // The table and back wall vertices were passed in together for the Mesh
        // Created two different indices for the function calls when the objects are rendered

        tableIndices.push_back(5);     tableIndices.push_back(4);     tableIndices.push_back(6);
        
        tableIndices.push_back(6);     tableIndices.push_back(5);     tableIndices.push_back(7);
    }
};

class HalfSphereIndices {

public:
    
    HalfSphereIndices() {}

    // Function to generate sphere indices
    void genBottleMiddleAndBowlIndices(int k1, int k2, int k3, vector <int> &indices) {
        // k1 = 1, k2 = 0, k3 = 2
        
        // Loop to generate number of sphere sides (sector)
        for (int x = 0; x < 100; ++x) {

            // Loop to generate stack
            for (int i = 0; i < 7; ++i) {

                // Add first value to the vector first triangle
                if (i == 0) {
                    indices.push_back(k1);   indices.push_back(k2);   indices.push_back(k3);
                }

                // Second rectangle or second two triangle
                else if (x == 0) {
                    k1 += 1;                 k2 += 1;                 k3 += 1;

                    indices.push_back(k1);   indices.push_back(k2);   indices.push_back(k3);
                }

                // Third rectangle or third two triangels
                else if (x == 1) {
                    k2 = k1;                 k1 = k3;
                    
                    // Every other "k3" in a row is either 1 or 2 larger than "k2"
                    if ((i + 1) % 2 == 0) {
                        k3 = k2 + 1;
                    }
                    else {
                        k3 = k2 + 2;
                    }
                    
                    indices.push_back(k1);   indices.push_back(k2);      indices.push_back(k3);

                }

                // We are sharing vertices. Program replicates from here
                else {
                    k2 = k1;                 k1 = k3;                    k3 = k2 + 1;
                    indices.push_back(k1);   indices.push_back(k2);      indices.push_back(k3);
                }
            }

            // Condition to set index pointers after first triangle
            if (x < 1) {
                k1 = k1 + 3;                 k2 = k2 + 3;                k3 = k3 - 7;
            }

            // Condition to set index pointer after second triangle
            else if (x + 1 % 2 == 0) {
                k2 = k3 + 1;                 k3 = k1 - 3;                k1 = k1 + 2;
            }

            // Condition to set index pointers for the rest of the loops.
            else {
                k2 = k1 + 1;                 k3 = k1 - 3;                k1 = k1 + 2;

            }
        }
    }
};
// Done
class GetVertices {
public:

    GetVertices() {}

    // Function to generate the scene's vertices
    void genSceneVertices(vector <Vert>& backWallVertices) {
        Vert v;

        // Vector position and texture for the table
        v.Position.x = -5.0; v.Position.y = -0.1; v.Position.z = -5.0; v.Texture.s = 0.0; v.Texture.t = 0.0;
        
        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z =  1; 
        
        backWallVertices.push_back(v);
        
        v.Position.x =  5.0; v.Position.y = -0.1; v.Position.z = -5.0; v.Texture.s = 1.0; v.Texture.t = 0.0;

        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z =  1;

        backWallVertices.push_back(v);
        
        v.Position.x = -5.0; v.Position.y =  0.1; v.Position.z =  5.0; v.Texture.s = 0.0; v.Texture.t = 1.0; 
        
        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z = -1;

        backWallVertices.push_back(v);

        v.Position.x =  5.0; v.Position.y =  0.1; v.Position.z =  5.0; v.Texture.s = 1.0; v.Texture.t = 1.0; 
        
        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z = -1;

        backWallVertices.push_back(v);
        
        // Vector position and texture for the wall
        v.Position.x = -5.0; v.Position.y = -0.1; v.Position.z = -5.0; v.Texture.s = 0.0; v.Texture.t = 0.0; 
        
        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z = 1;

        backWallVertices.push_back(v);
        
        v.Position.x =  5.0; v.Position.y = -0.1; v.Position.z = -5.0; v.Texture.s = 1.0; v.Texture.t = 0.0; 
        
        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z = 1;

        backWallVertices.push_back(v);
        
        v.Position.x = -5.0; v.Position.y =  8.0; v.Position.z = -5.0; v.Texture.s = 0.0; v.Texture.t = 1.0; 
        
        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z = 1;

        backWallVertices.push_back(v);

        v.Position.x =  5.0; v.Position.y =  8.0; v.Position.z = -5.0; v.Texture.s = 1.0; v.Texture.t = 1.0; 
        
        v.Normal.x = 0;      v.Normal.y = 0;      v.Normal.z = 1;

        backWallVertices.push_back(v);
    }
    // Done
    // Function to generate the sphere's vertices
    void genBottleMiddleVertices(vector <Vert>& vertices, bool islarge) {
        Vert v;

        //vector <glm::vec2> textureCoords;
        float across = 1.0;
        float up = 0.0;
        int totalAngle = 90;
        float baseAngle = 3.6;
        int numberOfAngles = totalAngle / baseAngle;

        // Assign initial angle to the sector angle
        float theta = baseAngle;

        // Number of loops to create circle.
        for (int i = 0; i < 4; ++i) {

            for (int j = 0; j < numberOfAngles; ++j) {

                // Set up point at the ceter
                v.Position.x = 0.0; v.Position.y = 0.0; v.Position.z = 0.0; v.Texture.s = 0.0; v.Texture.t = 0.0;

                v.Normal.x = 0;     v.Normal.y = 0;     v.Normal.z = 1;
                
                // Add object instance to data structure
                vertices.push_back(v);

                // generate location of next point on the circle
                float xloc = (cos(theta * (3.14 / 180)));    float yloc = (sin(theta * (3.14 / 180)));


                // Devide the point on the circle into stacks
                if (islarge) {
                    v.Position.x = xloc;           v.Position.y = yloc;                    v.Position.z = 0;
                    v.Texture.s = abs(xloc * .45); v.Texture.t = abs(yloc * .45);

                    v.Normal.x = 0;                v.Normal.y = 0;                         v.Normal.z = 1;

                    // Add vector information to data structure
                    vertices.push_back(v);
                }
                else {
                    v.Position.x = xloc / 2;             v.Position.y = yloc / 2;          v.Position.z = 0;
                    v.Texture.s = abs(xloc * .45);       v.Texture.t = abs(yloc * .45);

                    v.Normal.x = 0;                      v.Normal.y = 0;                   v.Normal.z = 1;

                    vertices.push_back(v);
                }

                if (islarge) {
                    // We have to account for the first sector.
                    if (j < 1 and i == 0) {
                        v.Position.x = across;            v.Position.y = up;               v.Position.z = 0;
                        v.Texture.s = abs(xloc * .45);    v.Texture.t = abs(up);

                        v.Normal.x = 0;                   v.Normal.y = 0;                  v.Normal.z = 1;

                        vertices.push_back(v);
                    }
                }
                else {
                    // We have to account for the first sector.
                    if (j < 1 and i == 0) {
                        v.Position.x = across / 2;        v.Position.y = up / 2;           v.Position.z = 0;
                        v.Texture.s = abs(xloc * .45);    v.Texture.t = abs(up);

                        v.Normal.x = 0;                   v.Normal.y = 0;                  v.Normal.z = 1;

                        vertices.push_back(v);
                    }
                }

                v.Position.x = xloc * 1.5;                v.Position.y = yloc * 1.5;       v.Position.z = -.25;
                v.Texture.s = abs(xloc * 0.60);           v.Texture.t = abs(yloc * 0.60);

                v.Normal.x = 0;                           v.Normal.y = 0;                  v.Normal.z = 1;

                vertices.push_back(v);

                // We have to account for the first secotr. We are not sharing points
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.5;            v.Position.y = up;               v.Position.z = -.25;
                    v.Texture.s = abs(xloc * .60);        v.Texture.t = abs(up);

                    v.Normal.x = 0;                       v.Normal.y = 0;                  v.Normal.z = 1;

                    vertices.push_back(v);
                }

                // Rise over run section
                v.Position.x = xloc * 1.75;               v.Position.y = yloc * 1.75;      v.Position.z = -.375;
                v.Texture.s = abs(xloc * 0.80);           v.Texture.t = abs(yloc * 0.80);

                v.Normal.x = 0;                           v.Normal.y = 0;                  v.Normal.z = 1;

                vertices.push_back(v);

                // Acconting for first scctor
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.75;           v.Position.y = up * 1.75;        v.Position.z = -.375;
                    v.Texture.s = abs(xloc * .80);        v.Texture.t = abs(up);

                    v.Normal.x = 0;                       v.Normal.y = 0;                  v.Normal.z = 1;

                    vertices.push_back(v);
                }

                // Rise over run section
                v.Position.x = xloc * 1.75;               v.Position.y = yloc * 1.75;      v.Position.z = -.5;
                v.Texture.s = abs(xloc * 1.25);           v.Texture.t = abs(yloc * 1.25);

                v.Normal.x = 0;                           v.Normal.y = 0;                  v.Normal.z = 1;

                vertices.push_back(v);

                // We have to account for the first sector
                if ((j < 1 and i == 0) or ((j == numberOfAngles - 1) and i == 3)) {
                    v.Position.x = 1.75;                  v.Position.y = 0;                v.Position.z = -.5;
                    v.Texture.s = abs(across * 1.25);     v.Texture.t = abs(up);

                    v.Normal.x = 0;                       v.Normal.y = 0;                  v.Normal.z = 1;

                    vertices.push_back(v);;
                }

                // Increase the sector 
                theta = theta + baseAngle;

                // Set base line to the cos of current angle
                across = xloc;

                // Set y for texture to the sin of the current angle
                up = yloc;
            }
        }
    }

    // Function to generate the sphere's vertices
    void genBowlVertices(vector <Vert>& vertices, bool islarge) {
        Vert v;

        //vector <glm::vec2> textureCoords;
        float across = 1.0;
        float up = 0.0;
        int totalAngle = 90;
        float baseAngle = 3.6;
        int numberOfAngles = totalAngle / baseAngle;

        // Assign initial angle to the sector angle
        float theta = baseAngle;

        // Number of loops to create circle.
        for (int i = 0; i < 4; ++i) {

            for (int j = 0; j < numberOfAngles; ++j) {

                // Set up point at the ceter
                v.Position.x = 0.0; v.Position.y = 0.0; v.Position.z = 0.0; v.Texture.s = 0.0; v.Texture.t = 0.0;

                v.Normal.x = 0;     v.Normal.y = 0;     v.Normal.z = 1;

                // Add object instance to data structure
                vertices.push_back(v);

                // generate location of next point on the circle
                float xloc = (cos(theta * (3.14 / 180)));    float yloc = (sin(theta * (3.14 / 180)));


                // Devide the point on the circle into stacks
                if (islarge) {
                    v.Position.x = xloc;           v.Position.y = yloc;                    v.Position.z = 0;
                    v.Texture.s = abs(xloc * .45); v.Texture.t = abs(yloc * .45);

                    v.Normal.x = 0;                v.Normal.y = 0;                         v.Normal.z = 1;

                    // Add vector information to data structure
                    vertices.push_back(v);
                }
                else {
                    v.Position.x = xloc / 2;             v.Position.y = yloc / 2;          v.Position.z = 0;
                    v.Texture.s = abs(xloc * .45);       v.Texture.t = abs(yloc * .45);

                    v.Normal.x = 0;                      v.Normal.y = 0;                   v.Normal.z = 1;

                    vertices.push_back(v);
                }

                if (islarge) {
                    // We have to account for the first sector.
                    if (j < 1 and i == 0) {
                        v.Position.x = across;            v.Position.y = up;               v.Position.z = 0;
                        v.Texture.s = abs(xloc * .45);    v.Texture.t = abs(up);

                        v.Normal.x = 0;                   v.Normal.y = 0;                  v.Normal.z = 1;

                        vertices.push_back(v);
                    }
                }
                else {
                    // We have to account for the first sector.
                    if (j < 1 and i == 0) {
                        v.Position.x = across / 2;        v.Position.y = up / 2;           v.Position.z = 0;
                        v.Texture.s = abs(xloc * .45);    v.Texture.t = abs(up);

                        v.Normal.x = 0;                   v.Normal.y = 0;                  v.Normal.z = 1;

                        vertices.push_back(v);
                    }
                }

                v.Position.x = xloc * 1.5;                v.Position.y = yloc * 1.5;       v.Position.z = .25;
                v.Texture.s = abs(xloc * 0.60);           v.Texture.t = abs(yloc * 0.60);

                v.Normal.x = 0;                           v.Normal.y = 0;                  v.Normal.z = 1;

                vertices.push_back(v);

                // We have to account for the first secotr. We are not sharing points
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.5;            v.Position.y = up;               v.Position.z = .25;
                    v.Texture.s = abs(xloc * .60);        v.Texture.t = abs(up);

                    v.Normal.x = 0;                       v.Normal.y = 0;                  v.Normal.z = 1;

                    vertices.push_back(v);
                }

                // Rise over run section
                v.Position.x = xloc * 1.75;               v.Position.y = yloc * 1.75;      v.Position.z = .375;
                v.Texture.s = abs(xloc * 0.80);           v.Texture.t = abs(yloc * 0.80);

                v.Normal.x = 0;                           v.Normal.y = 0;                  v.Normal.z = 1;

                vertices.push_back(v);

                // Acconting for first scctor
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.75;           v.Position.y = up * 1.75;        v.Position.z = .375;
                    v.Texture.s = abs(xloc * .80);        v.Texture.t = abs(up);

                    v.Normal.x = 0;                       v.Normal.y = 0;                  v.Normal.z = 1;

                    vertices.push_back(v);
                }

                // Rise over run section
                v.Position.x = xloc * 1.75;               v.Position.y = yloc * 1.75;      v.Position.z = .5;
                v.Texture.s = abs(xloc * 1.25);           v.Texture.t = abs(yloc * 1.25);

                v.Normal.x = 0;                           v.Normal.y = 0;                  v.Normal.z = 1;

                vertices.push_back(v);

                // We have to account for the first sector
                if ((j < 1 and i == 0) or ((j == numberOfAngles - 1) and i == 3)) {
                    v.Position.x = 1.75;                  v.Position.y = 0;                v.Position.z = .5;
                    v.Texture.s = abs(across * 1.25);     v.Texture.t = abs(up);

                    v.Normal.x = 0;                       v.Normal.y = 0;                  v.Normal.z = 1;

                    vertices.push_back(v);;
                }

                // Increase the sector 
                theta = theta + baseAngle;

                // Set base line to the cos of current angle
                across = xloc;

                // Set y for texture to the sin of the current angle
                up = yloc;
            }
        }
    }
};

// Done
class GenCylVerts {

public:

    GenCylVerts() {}

    // Function to generate the cylinder vertices
    void genCylVerts(vector <Vert>& cylVectors) {
        vector<Vert> cylinderVerts;
        Vert v;

        // Declare and define local variables
        int k1 = 1;
        int k2 = 0;
        int k3 = 2;

        float across = 1.0;
        float up = 0.0;
        int totalAngle = 90;
        float baseAngle = 3.6;
        int numberOfAngles = totalAngle / baseAngle;

        // Assign intial angle to sector angle
        float theta = baseAngle;

        // Loop to generate four pieces of the pie
        for (int i = 0; i < 4; ++i) {

            // Loop to generate one piece ie 90 degrees
            for (int j = 0; j < numberOfAngles; ++j) {

                // Set up point at the ceter
                v.Position.x = 0.0;             v.Position.y = 0.0;             v.Position.z = 0.0;
                v.Texture.s = 0.0;              v.Texture.t = 0.0;

                v.Normal.x = 0;                 v.Normal.y = 0;                 v.Normal.z = 1;

                // Add object instance to data structure
                cylinderVerts.push_back(v);

                // generate location of next point on the circle
                float xloc = (cos(theta * (3.14 / 180)));                       float yloc = (sin(theta * (3.14 / 180)));


                // Devide the point on the circle into stacks
                v.Position.x = xloc;            v.Position.y = yloc;            v.Position.z = 0;
                v.Texture.s = abs(xloc * 0.25); v.Texture.t = abs(yloc * 0.25);

                v.Normal.x = 0;                 v.Normal.y = 0;                 v.Normal.z = 1;

                cylinderVerts.push_back(v);

                // We have to account for the first sector.
                if (j < 1 and i == 0) {
                    v.Position.x = xloc;              v.Position.y = up;             v.Position.z = 0;
                    v.Texture.s = abs(xloc * 0.25);   v.Texture.t = abs(up);
                    
                    v.Normal.x = 0;                   v.Normal.y = 0;                v.Normal.z = 1;
                    
                    cylinderVerts.push_back(v);
                }

                // Rise over run section
                v.Position.x = xloc;                  v.Position.y = yloc;            v.Position.z = 1;
                v.Texture.s = abs(xloc * 0.50);       v.Texture.t = abs(yloc * 0.50);
                
                v.Normal.x = 0;                       v.Normal.y = 0;                 v.Normal.z = 1;
                
                cylinderVerts.push_back(v);

                // We have to account for the first sector. We are not sharing points
                if (j < 1 and i == 0) {
                    v.Position.x = across;            v.Position.y = up;              v.Position.z = 1;
                    v.Texture.s = abs(across * 0.50); v.Texture.t = abs(up);
                    
                    v.Normal.x = 0;                   v.Normal.y = 0;                 v.Normal.z = 1;
                    
                    cylinderVerts.push_back(v);
                }

                // Cylinder center
                v.Position.x = 0.0;                   v.Position.y = 0.0;             v.Position.z = 1;
                v.Texture.s = abs(across);            v.Texture.t = abs(up);
                
                v.Normal.x = 0;                       v.Normal.y = 0;                 v.Normal.z = 1;
                
                cylinderVerts.push_back(v);

                // Set sector angle to current angle plus base angle
                theta = theta + baseAngle;

                // Set base line to cos of current anle
                across = xloc;

                // Set Texture line to sine of current angle
                up = yloc;
            }
        }

        // Use pass by reference to assign value
        cylVectors = cylinderVerts;
    }
};

class GenCylIndices {

public:

    GenCylIndices (){}

    // Function to generate cylinder indices
    void genCylIndices(vector <int>& cylIndices) {
        // Declare and define local variables
        int k1 = 1;
        int k2 = 0;
        int k3 = 2;

        // Not needed, However, declare local vector variable to store values
        vector <int> cylinderIndices;

        // Loop to generate number of sphere sides (sector)
        for (int x = 0; x < 100; ++x) {

            for (int i = 0; i < 4; ++i) {

                // Add first value to the vector first triangle
                if (i == 0) {
                    cylinderIndices.push_back(k1);     cylinderIndices.push_back(k2);        cylinderIndices.push_back(k3);
                }

                // Second rectangle or second two triangle
                else if (x == 0) {
                    k1 += 1;                           k2 += 1;                               k3 += 1;

                    cylinderIndices.push_back(k1);     cylinderIndices.push_back(k2);         cylinderIndices.push_back(k3);
                }

                // Third rectangle or third two triangels
                else if (x == 1) {

                    // Did not like to hard code values in. It reduces the scalabity. 
                    // The can be adapted to different sizes with more time and research.

                    if (i == 2) {k2 = k2;}
                    else {
                        k2 = k1;
                    }

                    k1 = k3;

                    if ((i + 1) % 2 == 0) {
                        if (i == 1) {
                            k3 = 3;
                        }
                        else {
                            k3 = 9;
                        }
                    }
                    else {
                        k3 = k2 + 1;
                    }
                    cylinderIndices.push_back(k1);      cylinderIndices.push_back(k2);         cylinderIndices.push_back(k3);
                }

                // Program replicates from here
                else {
                    if (i == 2) {
                        k2 = k2;
                    }
                    else {
                        k2 = k1;
                    }

                    k1 = k3;

                    if ((i + 1) % 2 == 0) {
                        k3 = k1 + 1;
                    }
                    else {
                        k3 = k2 + 1;
                    }
                    cylinderIndices.push_back(k1);      cylinderIndices.push_back(k2);          cylinderIndices.push_back(k3);
                }
            }

            // Condition to set index pointers after first triangle
            if (x < 1) {
                k1 = k3 + 2;  k2 = k1 - 1;     k3 = k2 - 5;;
            }

            // Condition to set index pointers for the rest of the loop.
            else {
                k1 = k3 + 2;  k2 = k1 - 1;     k3 = k2 - 3;

            }
        }
        cylIndices = cylinderIndices;
    }
};

class GenerateSphere {

public:

    GenerateSphere() {}

    // Program to generate sphere vertices
    void generateSphereVertices(vector <Vert>& sphereStruct) {

        // Declare structure object instance
        Vert v;


        // Declare and define local variables
        int k1 = 1;
        int k2 = 0;
        int k3 = 2;

        //vector <glm::vec2> textureCoords;
        float across = 1.0;
        float up = 0.0;
        int totalAngle = 90;
        float baseAngle = 3.6;
        int numberOfAngles = totalAngle / baseAngle;

        // Assign initial angle to secor angle 3.6 degrees
        float theta = baseAngle;

        // Loop to generate quarters of a circle or 90 degrees
        for (int i = 0; i < 4; ++i) {

            // Loop to generate 25 angle to create 90 degree
            for (int j = 0; j < numberOfAngles; ++j) {

                // Set up point at the ceter
                v.Position.x = 0.0;              v.Position.y = 0.0;            v.Position.z = -0.1;
                v.Texture.s  = 0.0;              v.Texture.t  = 0.0;

                v.Normal.x = 0;                  v.Normal.y = 0;                v.Normal.z = 1;

                // Add object instance to data structure
                sphereStruct.push_back(v);

                // generate location of next point on the circle
                float xloc = (cos(theta * (3.14 / 180)));                        float yloc = (sin(theta * (3.14 / 180)));


            
                // Multiply the point on the circle into stacks
                v.Position.x = xloc * 1.2;       v.Position.y = yloc * 1.2;      v.Position.z = .125;
                v.Texture.s  = abs(xloc * 0.2);  v.Texture.t  = abs(yloc * 0.2);

                v.Normal.x = 0;                  v.Normal.y = 0;                 v.Normal.z = 1;

                sphereStruct.push_back(v);


                
                // We have to account for the first sector.
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.2;          v.Position.y = up;             v.Position.z = .125;
                    v.Texture.s  = abs(across * 0.20);  v.Texture.t  = abs(up);

                    v.Normal.x = 0;                     v.Normal.y = 0;                v.Normal.z = 1;

                    sphereStruct.push_back(v);
                }

                
                // Multiply the point on the circle into stacks
                v.Position.x = xloc * 1.3;              v.Position.y = yloc * 1.3;      v.Position.z = .188;
                v.Texture.s  = abs(xloc * 0.30);        v.Texture.t  = abs(yloc * 0.30);

                v.Normal.x = 0;                         v.Normal.y = 0;                 v.Normal.z = 1;

                sphereStruct.push_back(v);


                
                // We have to account for the first sector.
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.3;         v.Position.y = up * 1.3;         v.Position.z = .188;
                    v.Texture.s  = abs(xloc * 0.30);   v.Texture.t  = abs(up);

                    v.Normal.x = 0;                    v.Normal.y = 0;                  v.Normal.z = 1;

                    sphereStruct.push_back(v);
                }

                
                // Multiply the point on the circle into stacks
                v.Position.x = xloc * 1.4;             v.Position.y = yloc * 1.4;       v.Position.z = .375;
                v.Texture.s  = abs(xloc * 0.40);       v.Texture.t  = abs(yloc * 0.40);

                v.Normal.x = 0;                        v.Normal.y = 0;                  v.Normal.z = 1;

                sphereStruct.push_back(v);


                
                // We have to account for the first sector.
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.4;         v.Position.y = up * 1.4;          v.Position.z = .375;
                    v.Texture.s  = abs(xloc * 0.40);   v.Texture.t  = abs(up);

                    v.Normal.x = 0;                    v.Normal.y = 0;                   v.Normal.z = 1;

                    sphereStruct.push_back(v);
                }

                
                // Multiply the point on the circle into stacks
                v.Position.x = xloc * 1.4;             v.Position.y = yloc * 1.4;        v.Position.z = .5;
                v.Texture.s  = abs(xloc * 0.50);       v.Texture.t  = abs(yloc * 0.50);

                v.Normal.x = 0;                        v.Normal.y = 0;                   v.Normal.z = 1;

                sphereStruct.push_back(v);


                
                // We have to account for the first sector.
                if (j < 1 and i == 0) {
                    v.Position.x = xloc   * 1.4;       v.Position.y = up     * 1.4;      v.Position.z = .5;
                    v.Texture.s  = abs(xloc * 0.50);   v.Texture.t  = abs(up);

                    v.Normal.x = 0;                    v.Normal.y = 0;                   v.Normal.z = 1;

                    sphereStruct.push_back(v);
                }



                
                // Multiply the point on the circle into stacks
                v.Position.x = xloc * 1.3;             v.Position.y = yloc * 1.3;         v.Position.z = 0.625;
                v.Texture.s  = abs(xloc * 0.60);       v.Texture.t  = abs(yloc * 0.60);

                v.Normal.x = 0;                        v.Normal.y = 0;                    v.Normal.z = 1;

                sphereStruct.push_back(v);


                
                // We have to account for the first sector.
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.3;         v.Position.y = up * 1.3;           v.Position.z = 0.625;
                    v.Texture.s  = abs(xloc * 0.60);   v.Texture.t  = abs(up);

                    v.Normal.x = 0;                    v.Normal.y = 0;                    v.Normal.z = 1;

                    sphereStruct.push_back(v);
                }

                
                // Multiply the point on the circle into stacks
                v.Position.x = xloc * 1.2;             v.Position.y = yloc * 1.2;          v.Position.z = 0.75;
                v.Texture.s  = abs(xloc * 0.70);       v.Texture.t  = abs(yloc * 0.70);

                v.Normal.x = 0;                        v.Normal.y = 0;                     v.Normal.z = 1;

                sphereStruct.push_back(v);


                
                // We have to account for the first sector.
                if (j < 1 and i == 0) {
                    v.Position.x = xloc * 1.2;         v.Position.y = up;                  v.Position.z = 0.75;
                    v.Texture.s  = abs(across * 0.70); v.Texture.t  = abs(up);

                    v.Normal.x = 0;                    v.Normal.y = 0;                     v.Normal.z = 1;

                    sphereStruct.push_back(v);
                }
                
                // Rise over run section
                v.Position.x = xloc;                   v.Position.y = yloc;                v.Position.z = 0.875;
                v.Texture.s  = abs(xloc * 0.80);       v.Texture.t  = abs(yloc * 0.80);

                v.Normal.x = 0;                        v.Normal.y = 0;                     v.Normal.z = 1;

                sphereStruct.push_back(v);

                
                // We have to account for the first sector
                if (j < 1 and i == 0) {
                    v.Position.x = xloc;                v.Position.y = up;                 v.Position.z = 0.875;
                    v.Texture.s  = abs(across * 0.8);   v.Texture.t  = abs(up);

                    v.Normal.x = 0;                     v.Normal.y = 0;                    v.Normal.z = 1;

                    sphereStruct.push_back(v);
                }

                
                // Rise over run section
                v.Position.x = 0.0;                     v.Position.y = 0.0;                v.Position.z = 1.0;
                v.Texture.s  = abs(across);             v.Texture.t  = abs(up);

                v.Normal.x = 0;                         v.Normal.y = 0;                    v.Normal.z = 1;

                sphereStruct.push_back(v);

                // Assign angle to current angle plus base angle
                theta = theta + baseAngle;

                // Set base line for texture to the cos of current angle
                across = xloc;

                // Set top texture point to sin of the current angle
                up = yloc;
            }
        }
    }

    void generateSphereIndices(vector <int>& sphIndices) {

        // Declare and define local variables
        int k1 = 1;
        int k2 = 0;
        int k3 = 2;

        // Loop to generate number of sphere sides (sector)
        for (int x = 0; x < 100; ++x) {

            for (int i = 0; i < 14; ++i) {

                // Add first value to the vector first triangle
                if (i == 0) {
                    sphIndices.push_back(k1);       sphIndices.push_back(k2);       sphIndices.push_back(k3);
                }

                // Second rectangle or second two triangle
                else if (x == 0) {
                    k1 += 1;
                    k2 += 1;
                    k3 += 1;

                    sphIndices.push_back(k1);       sphIndices.push_back(k2);       sphIndices.push_back(k3);

                }

                // Third rectangle or third two triangels
                else if (x == 1) {
                    k2 = k1;

                    k1 = k3;

                    if ((i + 1) % 2 == 0) {
                        k3 = k2 + 1;
                    }
                    else {
                        k3 = k2 + 2;
                    }
                    sphIndices.push_back(k1);       sphIndices.push_back(k2);        sphIndices.push_back(k3);
                }

                // We are sharing vertices. Program replicates from here
                else {
                    k2 = k1;

                    k1 = k3;

                    k3 = k2 + 1;

                    sphIndices.push_back(k1);        sphIndices.push_back(k2);        sphIndices.push_back(k3);

                }
            }

            // Condition to set index pointers after first triangle
            if (x < 1) {
                k1 = k3 + 2;                          k2 = k1 - 1;                     k3 = k2 - 15;;
            }

            // Condition to set index pointers for the rest of the loop.
            else {
                k1 = k3 + 2;                          k2 = k1 - 1;                     k3 = k2 - 8;

            }
        }
    }
};

class GenerateLightCube {

public:

    // Default Constuctor
    GenerateLightCube(){}

    // Function to generate light cube vertices
    void generateLightCubeVertices(vector<Light>& lightCube) {
        
        // 
        Light l;

        l.Position.x = -1.0;  l.Position.y = 1.0;  l.Position.z = -1.0;
        
        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z   = 1.0;
        
        lightCube.push_back(l);

        l.Position.x =  1.0;  l.Position.y = 1.0;  l.Position.z = -1.0;

        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z = 1.0;

        lightCube.push_back(l);

        l.Position.x = -1.0;  l.Position.y = 1.0;  l.Position.z =  1.0;
        
        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z = 1.0;

        lightCube.push_back(l);

        l.Position.x =  1.0;  l.Position.y = 1.0;  l.Position.z =  1.0;
        
        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z = 1.0;

        lightCube.push_back(l);

        l.Position.x = -1.0;  l.Position.y = 0.0;  l.Position.z =  1.0;
        
        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z = 1.0;

        lightCube.push_back(l);

        l.Position.x =  1.0;  l.Position.y = 0.0;  l.Position.z =  1.0;
        
        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z = 1.0;

        lightCube.push_back(l);

        l.Position.x = -1.0;  l.Position.y = 0.0;  l.Position.z = -1.0;
        
        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z = 1.0;

        lightCube.push_back(l);

        l.Position.x =  1.0;  l.Position.y = 0.0;  l.Position.z = -1.0;

        //l.Normal.x = 0.0;     l.Normal.y = 0.0;  l.Normal.z = 1.0;

        lightCube.push_back(l);
    }
   
    void generateLightCubeIndices(vector<int>& lightCubeIndices) {
        lightCubeIndices.push_back(1); lightCubeIndices.push_back(0); lightCubeIndices.push_back(2); // Top
        lightCubeIndices.push_back(2); lightCubeIndices.push_back(1); lightCubeIndices.push_back(3);
        lightCubeIndices.push_back(3); lightCubeIndices.push_back(2); lightCubeIndices.push_back(4); // Front
        lightCubeIndices.push_back(4); lightCubeIndices.push_back(3); lightCubeIndices.push_back(5);
        lightCubeIndices.push_back(5); lightCubeIndices.push_back(4); lightCubeIndices.push_back(6); // Bottom
        lightCubeIndices.push_back(6); lightCubeIndices.push_back(5); lightCubeIndices.push_back(7);
        lightCubeIndices.push_back(6); lightCubeIndices.push_back(0); lightCubeIndices.push_back(1); // Back
        lightCubeIndices.push_back(1); lightCubeIndices.push_back(6); lightCubeIndices.push_back(7);
        lightCubeIndices.push_back(0); lightCubeIndices.push_back(2); lightCubeIndices.push_back(4); // Left
        lightCubeIndices.push_back(4); lightCubeIndices.push_back(0); lightCubeIndices.push_back(6);
        lightCubeIndices.push_back(1); lightCubeIndices.push_back(3); lightCubeIndices.push_back(5); // Right
        lightCubeIndices.push_back(5); lightCubeIndices.push_back(3); lightCubeIndices.push_back(7);
    }
};
#endif // !GENERATE_H

