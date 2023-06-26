// CS-330 Computational Graphics
// Assignment: Final Project
// Author: Maurice Wesley
// Theme: Bottles and Eggs Interpretation
// Date: June 13, 2023


#include <GLEW/glew.h>      // GLEW library
#include <GLFW/glfw3.h>     // GLFW library
#include <SOIL2/SOIL2.h>    // Soil library


// GLM Math Header inclusions
#include <glm/glm/glm.hpp>
#include <glm/glm/gtx/transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <MyShader.h>        // Shader
#include <MyCamera.h>        // Camera
#include <Generate.h>        // Generate object vertices and indices
#include <UpgradeMesh.h>     // Vertex array, buffer, element, and draw
#include <GenTexture.h>      // Reads an image and create a texture and location
#include <Lights.h>          // Light attributes

#include <cmath>
#include <vector>
#include <iostream>         // cout, cerr
#include <fstream>
#include <cstdlib>          // EXIT_FAILURE


using namespace std; // Standard namespace


// Unnamed namespace
namespace
{
    const char* const WINDOW_TITLE = "By Maurice Wesley"; // Macro for window title

    // Variables for window width and height
    const int WINDOW_WIDTH = 800;
    const int WINDOW_HEIGHT = 600;
    const float PI = 3.14159;
    const float ToRAD = PI / 180.0f;

    // Main GLFW window
    GLFWwindow* window = nullptr;

    // Mesh data
    MYMesh MESH;

    // Shader program
    MyShader myShader;
    GLuint   programID;

    MyShader firstLightShader;
    GLuint   lightShaderID1;



    // Object instantiations
    HalfSphereIndices   objectHSI;                   // Indices for half sphere
    GenCylIndices       objectCYL;                   // Indices for cylinders
    GetVertices         generateVertices;            // Vertices for half sphere
    GenCylVerts         generateCylinderVertices;    // Vertices for cylinders
    GenerateSphere      generateSphere;
    GetIndices          generateIndices;
    GenerateLightCube   generateLightCube;
    MySceneLights       SceneLights;

    // Structure for objects
    vector <Vert>       bowlStruct;                  // Vector of struct
    vector <Vert>       bottleMiddleStruct;          // Vector for middle bottle indices
    vector <Vert>       bottleVertexStruct;          // Vector for cylinder vertices
    vector <Vert>       sphereVertexStruct;          // Vecotor to store sphere vertices
    vector <Vert>       sceneVertexStruct;
    vector <Light>      lightVertexStruct;
    vector <PointLight> pointLightAttributes;        // Vector to store the location attributes of the lights

    // Structures for indicies
    vector <int>        hsIndices;                   // Vector of indices
    vector <int>        bottleIndices;               // Vector for cylinder indices
    vector <int>        bottleMiddleIndices;         // Vector for middle bottle indices
    vector <int>        sphereIndices;               // Vector for sphere indices
    vector <int>        sceneIndices;                // Vector for sceneIndice (Back Wall)
    vector <int>        tableIndices;                // Vector for table indices
    vector <int>        lightIndices;                // Vector for cube indices

    // Texture object
    GenerateTexture     genTexture;                  // Object read file and generate texture
    GLuint              textureIndex[10];            // Array to store the location of the textures 


    // camera
    Camera camera(glm::vec3(0.0f, 3.0f, 10.0f));
    float LastX = WINDOW_WIDTH / 2.0f;
    float LastY = WINDOW_HEIGHT / 2.0f;
    bool FirstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Variables and Structures to process keyboard and mouse input
    bool kPressed = false;
    bool Keys[1024] = { false };
    bool mouseButtons[3] = { false };

    // Declare vec3 postion for rotating light
    glm::vec3 lightPosition;
}

/* User-defined Function prototypes to:
 * initialize the program, set the window size,
 * redraw graphics on the window when resized,
 * render graphics on the screen, acquire keyboard
 * and mouse inputs, and release memory.
 */
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod);
void UDestroyMesh(MYMesh& MESH);
void URender();
void drawScene();
void drawBowl();
void drawHalfSpheres();
void drawSpheres();
void drawBottle();
void drawLights();
void UDestroyShaderProgram(GLuint programId);
void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void setUp();


int main(int argc, char* argv[])
{
    if (!UInitialize(argc, argv, &window))
        return EXIT_FAILURE;

    // Function call to load object vertex, texture, and indicies information
    setUp();

    // Declare and initialize shader source variables to file path
    const char* MyVertexShaderSource = "SceneVS.txt";
    const char* MyFragmentShaderSource = "SceneFS.txt";

    const char* light1VertexShaderSource = "LightCubeVertexShader.txt";
    const char* lightFragmentShaderSource = "LightCubeFragmentShader.txt";

    // Create, compile, attach, and link shaders
    myShader.loadShaders(MyVertexShaderSource, MyFragmentShaderSource, programID);
    firstLightShader.loadShaders(light1VertexShaderSource, lightFragmentShaderSource, lightShaderID1);


    // Sets the background color of the window to black (it will be implicitely used by glClear)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_COLOR_BUFFER_BIT | GL_DEPTH_TEST);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // Processor program modification
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        UProcessInput(window);

        lightPosition.x = 1.0f + sin(glfwGetTime()) * 5.0f;
        lightPosition.y = 7;
        lightPosition.z = 0;

        // Render this frame
        URender();

        // Process keyboard button inputs
        glfwSetKeyCallback(window, key_callback);

        glfwPollEvents();
    }

    // Release mesh data
    UDestroyMesh(MESH);

    // Release shader program
    UDestroyShaderProgram(programID);
    UDestroyShaderProgram(lightShaderID1);

    // Terminates the program successfully
    exit(EXIT_SUCCESS);
}

// Initialize GLFW, GLEW, and create a window
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
    // GLFW: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW: window creation
    // ---------------------
    * window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (*window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetFramebufferSizeCallback(*window, UResizeWindow);

    // For the camera and mouse position
    glfwSetCursorPosCallback(*window, MousePositionCallback);
    glfwSetScrollCallback(*window, MouseScrollCallback);
    glfwSetMouseButtonCallback(*window, UMouseButtonCallback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLEW: initialize
    // ----------------
    // Note: if using GLEW version 1.13 or earlier
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult)
    {
        std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
        return false;
    }

    // Displays GPU OpenGL version
    cout << "INFO: OpenGL Version: " << glGetString(GL_VERSION) << endl;

    return true;
}


// process all input: query GLFW whether relevant keys are
// pressed/released this frame and react accordingly
void UProcessInput(GLFWwindow* window)
{
    static const float cameraSpeed = 2.5f;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(window, true);
    }

    // Condition to check key press to Zoom camera in
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    // Condition to check key press to Zoom camera out
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    // Condition to check key press to Move camera to the left
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    // Condition to check key press to Move camera to the right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    // Condition to check key press to Move camera up
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }

    // Condition to check key press to Move camera down
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    // The action is zero when the key is released. Enables/Disables with booleans
    if (action == GLFW_RELEASE) {
        if (Keys[key] == false) {
            Keys[key] = true;
        }
        else {
            Keys[key] = false;
        }
    }
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void UResizeWindow(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0, width, 0, height, -5, 5);

    // switch to modelview matrix in order to set scene
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
}

// Function called to render a frame
void URender()
{
    // Enable Z Depth
    glEnable(GL_DEPTH_TEST);

    // Clear the background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Declare and initialize local variables with identity matrix
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view  = glm::mat4(1.0f);
    glm::mat4 proj  = glm::mat4(1.0f);
    glm::mat4 obj   = glm::mat4(1.0f);

    // Create a rotation matrix and multiply it by the given matriz
    // Model matrix to transform
    // Angle in radians, magnitude of rotation// To make it move multify by (float)time
    // What axis to rotate
    model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));


    // Method call to retrieve camera matrix
    view = camera.GetViewMatrix();

    // Field of view in radians: increases and decreases will zoom in and out
    // Set the height of the perspecitve fostrum: Aspect ration
    // Coordinates in front of the near plane will not be drawn
    // Corrdinates begind the rear plane will not be drawn
    if (!Keys[80]) {
        proj = glm::perspective(glm::radians(camera.Zoom), (float)(WINDOW_WIDTH / (float)WINDOW_HEIGHT), 0.1f, 100.0f);
    }
    else {
        // When key pressed, the view changes to orthographic mode
        proj = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 10.0f);
    }

    // Transformations are applied right-to-left order
    glm::mat4 transformation = proj * view * model;


    // Set the shader to be used
    glUseProgram(programID);

    // Sends camera transform information to the Vertex shader
    myShader.setMat4(programID, "shaderTransform", transformation);

    // Sends indentity matrix for object location to Vertex Shader
    myShader.setMat4(programID, "objectPosition", obj);

    // Declare local vec2 variable to access uniform variable in fragment shader
    glm::vec2 uvScale = glm::vec2(1.0, 1.0);

    // Sends indentity matrix for object location to Vertex Shader
    myShader.setVec2(programID, "uvScale", uvScale);

    // The position of the camera information sent to the fragment shader
    myShader.setVec3(programID, "viewPosition", camera.Position.x, camera.Position.y, camera.Position.z);

    // Set the value of another texture was not used in the current version
    myShader.setInt(programID, "myTexture2", textureIndex[7]);

    // Directional Light
    myShader.setVec3(programID, "dirLight.direction", glm::vec3(-0.2, 7.0, -0.3));
    myShader.setVec3(programID, "dirLight.ambient"  , 0.26f, 0.15f, 0.11f);
    myShader.setVec3(programID, "dirLight.diffuse"  , 0.6f, 0.5f, 0.31f);
    myShader.setVec3(programID, "dirLight.specular" , 0.2f, 0.2f, 0.2f);

    // Set the light color if the developer would like to change the overall lighting
    myShader.setVec3(programID, "lightColor", glm::vec3(1.0, 1.0, 1.0));

    // Send light information to the fragment shader
    for (int i = 0; i < 5; ++i) {

        // Condition to rotate the light across the back wall
        if (Keys[82] and i == 0) {
            myShader.setVec3(programID, "light[" + to_string(i) + "].position", lightPosition);
        }
        else {
            myShader.setVec3(programID, "light[" + to_string(i) + "].position", pointLightAttributes.at(i).pointPosition);
        }

        // Send the light attributes to the fragment shader
        myShader.setVec3(programID , "light[" + to_string(i) + "].ambient"  , pointLightAttributes.at(i).ambient);
        myShader.setVec3(programID , "light[" + to_string(i) + "].diffuse"  , pointLightAttributes.at(i).diffuse);
        myShader.setVec3(programID , "light[" + to_string(i) + "].specular" , pointLightAttributes.at(i).specular);
        myShader.setFloat(programID, "light[" + to_string(i) + "].constant" , pointLightAttributes.at(i).constant);
        myShader.setFloat(programID, "light[" + to_string(i) + "].linear"   , pointLightAttributes.at(i).linear);
        myShader.setFloat(programID, "light[" + to_string(i) + "].quadratic", pointLightAttributes.at(i).quadratic);
    }

    // Unbind the program
    glUseProgram(0);

    // Set up the light cubes
    glUseProgram(lightShaderID1);

    // Sends camera transform information to the Vertex shader
    firstLightShader.setMat4(lightShaderID1, "shaderTransform", transformation);

    // Sends indentity matrix for object location to Vertex Shader
    firstLightShader.setMat4(lightShaderID1, "objectPosition", obj);

    // Unbind the program
    glUseProgram(0);


    // Uncomment to print triangle with lines
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Draw
    drawScene();
    drawBowl();
    drawBottle();
    drawHalfSpheres();
    drawSpheres();
    drawLights();

    // Unbind the vertex array object
    glBindVertexArray(0);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // Flips the the back buffer with the front buffer every frame.
    glfwSwapBuffers(window);
}

// Release array and buffer memory
void UDestroyMesh(MYMesh& MESH)
{
    glDeleteVertexArrays(1, &MESH.VAO);
    glDeleteVertexArrays(1, &MESH.lightVAO);
    glDeleteBuffers(1, &MESH.VBO);
    glDeleteBuffers(1, &MESH.lightVBO);
    glDeleteBuffers(1, &MESH.EBO);
    glDeleteBuffers(1, &MESH.lightEBO);
}

// Destroy Shader
void UDestroyShaderProgram(GLuint progID) {
    glDeleteProgram(progID);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (FirstMouse)
    {
        LastX = xpos;
        LastY = ypos;
        FirstMouse = false;
    }

    float xoffset = xpos - LastX;
    float yoffset = LastY - ypos; // reversed since y-coordinates go from bottom to top

    LastX = xpos;
    LastY = ypos;

    if (mouseButtons[0]) {
        camera.ProcessMouseMovement(xoffset, yoffset);
    }
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);

}

// glfw: handle mouse button events
// --------------------------------
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // Condtion with argument
    switch (button)
    {

        // When left mouse button condition is true
    case GLFW_MOUSE_BUTTON_LEFT:
    {
        // While the mouse button is pressed
        if (action == GLFW_PRESS) {

            // Set mouse button index to true
            mouseButtons[0] = true;
        }

        // When the button is released
        else {

            // Set mouse button index to false
            mouseButtons[0] = false;
        }
    }
    break;

    case GLFW_MOUSE_BUTTON_MIDDLE: {
    }
                                 break;

    case GLFW_MOUSE_BUTTON_RIGHT: {
    }
                                break;

    default:
        cout << "Unhandled mouse button event" << endl;
        break;
    }
}

void drawScene() {

    glUseProgram(programID);

    // Declare Array to hold location of texture during render
    int texture[] = { 1, 0 };

    // Local variable to store which object is being rendered
    int numberOfObjects = 2;

    // Pass the mesh data on the fly
    MESH.getData(sceneVertexStruct, tableIndices);

    // Get loction of uniform variable
    GLuint objectPositionLoc = glGetUniformLocation(programID, "objectPosition");

    // Declare local variable to transform object location
    glm::mat4 Plane(1.0f);

    // Was experimenting with normal and researched the changes on different axes
    Plane = glm::rotate(Plane, 0 * ToRAD, glm::vec3(0.0, 1.0, 0.0));

    // Loop to generate objects
    for (int i = 0; i < numberOfObjects; i++) {

        // Material
        myShader.setVec3(programID , "material.ambient"  , 0.26f, 0.15f, 0.11f);
        myShader.setVec3(programID , "material.diffuse"  , 0.6f, 0.5f, 0.31f);
        myShader.setVec3(programID , "material.specular" , 0.2f, 0.2f, 0.2f);
        myShader.setFloat(programID, "material.shininess",32.0f);

        // Call to draw object
        MESH.Draw(programID, textureIndex[i]);

        // Manually update the position and location of object. Was not used.
        glUniformMatrix4fv(objectPositionLoc, 1, GL_FALSE, glm::value_ptr(Plane));

        // Pass object information to the mesh
        MESH.getData(sceneVertexStruct, sceneIndices);
    }

    // Unbind the texture befor exciting scope
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

void drawHalfSpheres() {
    glUseProgram(programID);

    // Send object information to the Mesh
    MESH.getData(bottleMiddleStruct, bottleMiddleIndices);

    // Structure to hold texture location index
    int texture[] = { 2, 7 };

    // Get loction of uniform variable
    GLuint objectPositionLoc = glGetUniformLocation(programID, "objectPosition");

    // Declare local vec2 variable to access uniform variable in fragment shader
    glm::vec2 uvScale = glm::vec2(0.5, 0.5);

    // Send information to the fragment shader
    myShader.setVec2(programID, "uvScale", uvScale);

    // Declare and initialize local variable
    glm::mat4 Plane = glm::mat4(1.0);

    //Half sphere size
    vector<glm::vec3> halfSphereScale = {
        glm::vec3(0.225, 1.75, 0.225),     // Back Bottle 
        glm::vec3(0.34 ,  2.0,  0.34)      // Front Bottle
    };

    // Half sphere location
    vector<glm::vec3> halfSphereTranslate = {
        glm::vec3(2.66f, 2.50f, -8.00f),       // Back Bottle
        glm::vec3(4.41f, 1.35f, -2.66f)        // front Bottle
    };

    // Half sphere rotation
    vector<glm::vec3> halfSphereRotation = {
        glm::vec3(1.0f, 0.0f, 0.0f),           // Back Bottle
        glm::vec3(1.0f, 0.0f, 0.0f)            // front Bottle
    };

    // Half sphere degrees rotated
    vector<GLfloat> halfSphereDegreeRotate = {
        -90.0, -90.0
    };

    vector<glm::vec3> halfSphereAmbient = {
        glm::vec3(0.40f, 0.56f, 0.00f),      // Back Bottle
        glm::vec3(0.30f, 0.30f, 0.30f)       // front Bottle
    };

    vector<glm::vec3> halfSphereDiffuse = {
        glm::vec3(0.25f, 0.25f, 0.25f),       // Back Bottle
        glm::vec3(0.05f, 0.05f, 0.05f)        // front Bottle
    };

    vector<glm::vec3> halfSphereSpecular = {
        glm::vec3(1.00f, 1.00f, 1.00f),      // Back Bottle
        glm::vec3(1.00f, 1.00f, 1.00f)       // front Bottle
    };

    vector<float> halfSphereShininess = {
        32.0f, 32.0f
    };

    int numberOfHalfSpheres = 2;

    // Loop to create number of half spheres
    for (int i = 0; i < numberOfHalfSpheres; i++) {

        // Reinitialize local variable to identity matrix
        Plane = glm::mat4(1.0f);

        // Scale the sphere to half its size
        Plane = glm::scale(Plane, halfSphereScale[i]);

        // Move object down on the y-axis
        Plane = glm::translate(Plane, halfSphereTranslate[i]);

        // Rotate object on the x-axis: WORKS (for now)
        Plane = glm::rotate(Plane, (halfSphereDegreeRotate[i] * ToRAD), halfSphereRotation[i]);

        // Send uniform information to the vertex shader
        //glUniformMatrix4fv(objectPositionLoc, 1, GL_FALSE, glm::value_ptr(Plane));
        myShader.setMat4(programID, "objectPosition", Plane);

        myShader.setVec3(programID, "material.ambient", halfSphereAmbient[i]);

        myShader.setVec3(programID, "material.diffuse", halfSphereDiffuse[i]);

        myShader.setVec3(programID, "material.specular", halfSphereSpecular[i]);

        myShader.setFloat(programID, "material.shininess", halfSphereShininess[i]);

        MESH.Draw(programID, textureIndex[texture[i]]);
    }

    // Reset Texture information before leaving the scope
    myShader.setVec2(programID, "uvScale", glm::vec2(1.0, 1.0));
    glUseProgram(0);
}


void drawBowl() {
    glUseProgram(programID);

    // Send object information to the Mesh
    MESH.getData(bowlStruct, hsIndices);

    // Get loction of uniform variable
    GLuint objectPositionLoc = glGetUniformLocation(programID, "objectPosition");

    // Declare local vec2 variable to access uniform variable in fragment shader
    glm::vec2 uvScale = glm::vec2(1.0f, 1.0f);

    // Send texture information to the fragment shader
    myShader.setVec2(programID, "uvScale", uvScale);

    // Number of bowls
    int numberOfBowls = 1;

    // Declare and initialize local variable
    glm::mat4 Plane = glm::mat4(1.0);

    // Bowl size
    vector<glm::vec3> bowlScale = {
        glm::vec3(0.80f, 2.2f, 0.80f),    // Bowl
    };

    // Bowl location
    vector<glm::vec3> bowlTranslate = {
        glm::vec3(-.5 , 0.025,  0.0),    // Bowl
    };

    // Bowl rotation
    vector<glm::vec3> bowlRotation = {
        glm::vec3(1.0, 0.0, 0.0),
    };

    // Bowl degrees rotated
    vector<GLfloat> bowlDegreeRotate = {
        -90.0
    };

    // Loop to create number of bowls
    for (int i = 0; i < numberOfBowls; i++) {

        // Reinitialize local variable to identity matrix
        Plane = glm::mat4(1.0f);

        // Scale the bowl to half its size
        Plane = glm::scale(Plane, bowlScale[i]);

        // Move object down on the y-axis
        Plane = glm::translate(Plane, bowlTranslate[i]);

        // Rotate object on the x-axis: WORKS (for now)
        Plane = glm::rotate(Plane, (glm::radians(bowlDegreeRotate[i])), bowlRotation[i]);

        // Transformation to rotate vertices 3.6 degrees on the z-axis
        Plane = glm::rotate(Plane, (glm::radians(-3.6f)), glm::vec3(0.0f, 0.0f, 1.0f));

        // Send uniform information to the vertex shader
        myShader.setMat4(programID, "objectPosition", Plane);

        // Send material information to fragment shader
        myShader.setVec3(programID , "material.ambient"  , 0.20f, 0.25f, 0.07f);
        myShader.setVec3(programID , "material.diffuse"  , 0.25f, 0.25f, 0.25f);
        myShader.setVec3(programID , "material.specular" , 0.00f, 0.00f, 0.00f);
        myShader.setFloat(programID, "material.shininess",32.0f);

        // Draw call
        MESH.Draw(programID, textureIndex[2]);
    }

    // Reset texture scale before next render
    myShader.setVec2(programID, "uvScale", glm::vec2(1.0, 1.0));
    glUseProgram(0);
}

void drawBottle() {
    glUseProgram(programID);

    // Send object information to the Mesh
    MESH.getData(bottleVertexStruct, bottleIndices);

    // Array to specify the texture
    int texture[] = { 2, 7, 2, 7, 4, 5 };

    // Get loction of uniform variable
    GLuint objectPositionLoc = glGetUniformLocation(programID, "objectPosition");

    // Declare local vec2 variable to access uniform variable in fragment shader
    glm::vec2 uvScale = glm::vec2(1.5, 1.5);

    // Assign uniform variable value in fragment shader
    myShader.setVec2(programID, "uvScale", uvScale);

    // Number of bottles
    int numberOfBottles = 6;

    // Declare and initialize local variable
    glm::mat4 Plane = glm::mat4(1.0);

    //Bottle size
    vector<glm::vec3> bottleScale = {
        glm::vec3(0.40, 3.50, 0.40),      // Back bottle  bottom cylinder
        glm::vec3(0.60, 1.75, 0.60),      // Front bottle bottom cylinder
        glm::vec3(0.20, 1.80, 0.20),      // Back Bottle top cylinder
        glm::vec3(0.15, 2.00, 0.15),      // Front bottle top cylinder
        glm::vec3(0.20, 0.10, 0.20),      // Back Bottle Cap
        glm::vec3(0.15, 0.15, 0.16)       // Front Bottle Cap
    };

    // Bottle location
    vector<glm::vec3> bottleTranslate = {
        glm::vec3(1.5,   0.0,  -4.50),   // Back Bottle bottom cylinder
        glm::vec3(2.5,   0.0,  -1.50),   // Front Bottle bottom cylinder
        glm::vec3(3.0,   2.2,  -8.99),   // Back bottle top cylinder
        glm::vec3(10.02,   1.0,  -6.01),  // front bottle top cylinder
        glm::vec3(2.99,  58.0,  -9.00),   // Back Bottle Cap
        glm::vec3(10.05,  27.0,  -5.7)     // Front bottle Cap
    };

    // Bottle rotation
    vector<glm::vec3> bottleRotation = {
        glm::vec3(1.0, 0.0, 0.0),         // Back Bottle cylinder
        glm::vec3(1.0, 0.0, 0.0),         // Front Bottle bottom cylinder
        glm::vec3(1.0, 0.0, 0.0),         // Back Bottle bottom cylinder
        glm::vec3(1.0, 0.0, 0.0),         // Front Bottle top cylinder
        glm::vec3(1.0, 0.0, 0.0),         // Back Bottle Cap
        glm::vec3(1.0, 0.0, 0.0)          // Front Bottle Cap
    };

    vector<glm::vec3> bottleAmbient = {
        glm::vec3(0.40f, 0.56f, 0.00f),   // Back Bottle cylinder
        glm::vec3(0.30f, 0.30f, 0.30f),   // Front Bottle bottom cylinder
        glm::vec3(0.40f, 0.56f, 0.00f),   // Back Bottle top cylinder
        glm::vec3(0.00f, 0.00f, 0.00f),   // Front Bottle top cylinder
        glm::vec3(0.10f, 0.20f, 0.10f),   // Back Bottle Cap
        glm::vec3(0.46f, 0.36f, 0.25f)    // Front Bottle Cap
    };

    vector<glm::vec3> bottleDiffuse = {
        glm::vec3(0.25f, 0.25f, 0.25f),   // Back Bottle cylinder
        glm::vec3(0.05f, 0.05f, 0.05f),   // Front Bottle bottom cylinder
        glm::vec3(0.25f, 0.25f, 0.25f),   // Back Bottle bottom cylinder
        glm::vec3(0.05f, 0.05f, 0.05f),   // Front Bottle top cylinder
        glm::vec3(0.25f, 0.25f, 0.25f),   // Back Bottle Cap
        glm::vec3(0.25f, 0.25f, 0.25f)    // Front Bottle Cap
    };

    vector<glm::vec3> bottleSpecular = {
        glm::vec3(1.00f, 1.00f, 1.00f),   // Back Bottle cylinder
        glm::vec3(1.00f, 1.00f, 1.00f),   // Front Bottle bottom cylinder
        glm::vec3(1.00f, 1.00f, 1.00f),   // Back Bottle bottom cylinder
        glm::vec3(1.00f, 1.00f, 1.00f),   // Front Bottle top cylinder
        glm::vec3(1.00f, 1.00f, 1.00f),   // Back Bottle Cap
        glm::vec3(1.00f, 1.00f, 1.00f)    // Front Bottle Cap
    };

    vector<float> bottleShininess = {
        32.0f, 128.0f, 32.0f, 32.0f, 32.0f, 32.0f
    };

    // Bottle degrees rotated
    vector<GLfloat> bottleDegreeRotate = {
        -90.0, -90.0, -90.0, -90.0, -90.0, -90.0
    };

    // Loop to create number of bottle
    for (int i = 0; i < numberOfBottles; i++) {

        // Reinitialize local variable to identity matrix
        Plane = glm::mat4(1.0f);

        // Scale the bottle
        Plane = glm::scale(Plane, bottleScale[i]);

        // Move object down on the y-axis
        Plane = glm::translate(Plane, bottleTranslate[i]);

        // Rotate object on the x-axis
        Plane = glm::rotate(Plane, (glm::radians(bottleDegreeRotate[i])), bottleRotation[i]);

        // Transformation to rotate vertices for camera----> my design
        Plane = glm::rotate(Plane, (glm::radians(-3.6f)), glm::vec3(0.0f, 0.0f, 1.0f));

        // Send uniform information to the vertex shader
        myShader.setMat4(programID , "objectPosition"    , Plane);

        myShader.setVec3(programID , "material.ambient"  , bottleAmbient[i]);

        myShader.setVec3(programID , "material.diffuse"  , bottleDiffuse[i]);

        myShader.setVec3(programID , "material.specular" , bottleSpecular[i]);

        myShader.setFloat(programID, "material.shininess", bottleShininess[i]);

        MESH.Draw(programID, textureIndex[texture[i]]);
    }

    // Reset textue format before next render
    myShader.setVec2(programID, "uvScale", glm::vec2(50.0, 50.0));
    glUseProgram(0);
}

void drawSpheres() {
    glUseProgram(programID);

    // Send information to the Mesh
    MESH.getData(sphereVertexStruct, sphereIndices);

    // Array to specify the texture
    int texture[] = { 3, 1 };

    // Get location of uniform variable in vertex shader
    GLuint objectPositionLoc = glGetUniformLocation(programID, "objectPosition");

    // Lighten up the brown color on the eggs/marshmellows/bon bons
    myShader.setVec3(programID, "objectColor", glm::vec3(0.6f, 0.6f, 0.6f));

    // Declare and intialize local variable to identity matrix
    glm::vec2 uvScale = glm::vec2(1.0, 1.0);

    // Send information to the fragment shader
    myShader.setVec2(programID, "uvScale", uvScale);

    // Declare and intialize local variable to identity matrix
    glm::mat4 Plane = glm::mat4(1.0f);

    // Number of ratations
    GLuint rotations = 100;

    // Vector to store sphere scale values
    vector<glm::vec3> sphereScale2 = {
        glm::vec3(0.35, 0.70, 0.35),   // Bottom front egg
        glm::vec3(0.35, 0.70, 0.35),   // Left bottom egg
        glm::vec3(0.38, 0.70, 0.38),   // Left top Egg
        glm::vec3(0.40, 1.00, 0.40),   // Right top Egg
        glm::vec3(0.35, 0.70, 0.35)    // Back top Egg
    };

    // Vector to hold sphere locations
    vector<glm::vec3> sphereTranslate2 = {
        glm::vec3(-0.2 ,  0.2,  1.0),      // Bottom front egg
        glm::vec3(-1.7 ,  0.2, -1.3),      // Left bottom egg
        glm::vec3(-2.40,  0.9,  1.0),      // Left top Egg
        glm::vec3(0.30,  0.7, -0.8),       // Right top Egg
        glm::vec3(-2.5 ,  1.5, -1.2),
    };

    // Vector to hold sphere rotations
    vector<glm::vec3> sphereRotation = {
        glm::vec3(1.0, 0.0, 0.0),          // Bottom front egg
        glm::vec3(1.0, 0.0, 0.0),          // Left bottom egg
        glm::vec3(1.0, 0.0, 0.0),          // Left top Egg
        glm::vec3(1.0, 0.0, 0.0),          // Right top Egg
        glm::vec3(1.0, 0.0, 0.0)
    };

    // Vector to hold sphere degree rotated
    vector<GLfloat> sphereDegreeRotate = {
        -90.0, -90.0, -90.0, -90.0, -90.0
    };

    int numberOfSpheres = 5;

    // Loop to generate spheres
    for (int i = 0; i < numberOfSpheres; i++) {
        // Reinitialize local variable each iteration
        Plane = glm::mat4(1.0);

        // Scale the sphere to half its size
        Plane = glm::scale(Plane, sphereScale2[i]);

        // Move object down on the y-axis
        Plane = glm::translate(Plane, sphereTranslate2[i]);

        // Rotate object on the x-axis: WORKS (for now)
        Plane = glm::rotate(Plane, (glm::radians(sphereDegreeRotate[i])), sphereRotation[i]);

        Plane = glm::rotate(Plane, (glm::radians(-3.6f)), glm::vec3(0.0f, 0.0f, 1.0f));

        // Send information to shader. Would not let me use shader functions inside for loop????;
        myShader.setMat4(programID, "objectPosition", Plane);

        // Send material information to fragment shader
        myShader.setVec3(programID , "material.ambient"  , 0.449f, 0.45f, 0.44f);
        myShader.setVec3(programID , "material.diffuse"  , 0.25f, 0.25f, 0.25f);
        myShader.setVec3(programID , "material.specular" , 0.80f, 0.80f, 0.80f);
        myShader.setFloat(programID, "material.shininess", 32.0f);

        // Draw Object
        MESH.Draw(programID, textureIndex[texture[0]]);
    }

    // Reset texture format before next render
    myShader.setVec2(programID, "uvScale", glm::vec2(1.0, 1.0));
    glUseProgram(0);
}

void drawLights() {
    // Send object information to the Mesh

    glUseProgram(lightShaderID1);
    // First Change
    MESH.getLightData(lightVertexStruct, lightIndices);

    int texture[] = { 2, 1 };

    // Get loction of uniform variable
    GLuint objectPositionLoc = glGetUniformLocation(lightShaderID1, "objectPosition");

    // Number of bottles
    int numberOfLights = 1;

    // Declare and initialize local variable
    glm::mat4 Plane = glm::mat4(1.0);

    //Light size
    vector<glm::vec3> lightScale = {
        glm::vec3(1.00, 1.00, 1.00),            // Locations for lights: Current scene does not 
        glm::vec3(1.00, 1.00, 1.00),            // Require a visual que for lights
        glm::vec3(1.00, 1.00, 1.00),
        glm::vec3(1.00, 1.00, 1.00),
        glm::vec3(1.00, 1.00, 1.00),
        glm::vec3(0.15, 0.15, 0.16)
    };

    // Light location
    vector<glm::vec3> lightTranslate = {
        glm::vec3(0.00,   7.0,  0.00) ,         // Locations for lights: Current scene does not
        glm::vec3(-6.00,  2.5,  -2.50),         // Require a visual que for lights
        glm::vec3(-6.00,  2.5,   2.50),
        glm::vec3(6.00,   2.5,  -2.50),
        glm::vec3(6.00,   2.5,   2.50),
        glm::vec3(10.05,  27.0,  -5.7)
    };

    // Light rotation
    vector<glm::vec3> lightRotation = {
        glm::vec3(1.0, 0.0, 0.0),               // Locations for lights: Current scene does not
        glm::vec3(1.0, 0.0, 0.0),               // Require a visual que for lights
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0)
    };

    // light degrees rotated
    vector<GLfloat> lightDegreeRotate = {
        00.0, 00.0, 00.0, 00.0, 00.0, 00.0
    };

    // Loop to create number of bottle
    for (int i = 0; i < numberOfLights; i++) {

        // Reinitialize local variable to identity matrix
        Plane = glm::mat4(1.0f);

        // Scale the light
        Plane = glm::scale(Plane, lightScale[i]);

        // Move object down on the y-axis
        Plane = glm::translate(Plane, lightTranslate[i]);

        // Rotate object on the x-axis
        Plane = glm::rotate(Plane, (glm::radians(lightDegreeRotate[i])), lightRotation[i]);

        // Transformation to rotate vertices for camera----> my design
        Plane = glm::rotate(Plane, (glm::radians(0.0f)), glm::vec3(0.0f, 0.0f, 1.0f));


        // Send uniform information to the vertex shader
        glUniformMatrix4fv(objectPositionLoc, 1, GL_FALSE, glm::value_ptr(Plane));

        //firstLightShader.setMat4(lightShaderIssw
        MESH.DrawLight(lightShaderID1, textureIndex[texture[0]]);
    }

    // Reset textue format before next render
    firstLightShader.setMat4(lightShaderID1, "objectPostionLoc", glm::mat4(1.0f));
    glUseProgram(0);
}

void setUp() {

    // Use global object instance and function to retrieve indices
    objectHSI.genBottleMiddleAndBowlIndices(1, 0, 2, hsIndices);

    objectHSI.genBottleMiddleAndBowlIndices(1, 0, 2, bottleMiddleIndices);

    objectCYL.genCylIndices(bottleIndices);

    generateIndices.generateSceneIndices(sceneIndices, tableIndices);

    generateSphere.generateSphereIndices(sphereIndices);

    generateLightCube.generateLightCubeIndices(lightIndices);

    // Use global object instance and function to retreive vertices

    generateVertices.genBowlVertices(bowlStruct, true);

    generateVertices.genBottleMiddleVertices(bottleMiddleStruct, false);

    generateCylinderVertices.genCylVerts(bottleVertexStruct);

    generateSphere.generateSphereVertices(sphereVertexStruct);

    generateVertices.genSceneVertices(sceneVertexStruct);

    generateLightCube.generateLightCubeVertices(lightVertexStruct);


    // Declare initialize create and store location of textures
    const char* projectBackWall     = "Test_Back_Wall2.png";
    genTexture.genObjectTexture(projectBackWall, textureIndex[0]);

    const char* projectTable        = "Project_Table.png";
    genTexture.genObjectTexture(projectTable, textureIndex[1]);


    // Bowl, half spheres, cylinders
    const char* projectBowlImage    = "Project_Bowl.png";
    genTexture.genObjectTexture(projectBowlImage, textureIndex[2]);

    const char* projectEggImage     = "Project_Egg_Image.png";
    genTexture.genObjectTexture(projectEggImage, textureIndex[3]);

    const char* backBottleCapImage  = "Back_Bottle_Cap.png";
    genTexture.genObjectTexture(backBottleCapImage, textureIndex[4]);

    const char* frontBottleCapImage = "Front_Bottle_Cap.png";
    genTexture.genObjectTexture(frontBottleCapImage, textureIndex[5]);

    const char* blackColorImage     = "Black_Color.png";
    genTexture.genObjectTexture(frontBottleCapImage, textureIndex[6]);

    const char* wideBottleBlack     = "WideBottle.png";
    genTexture.genObjectTexture(wideBottleBlack, textureIndex[7]);


    /// Working with lights
    vector <glm::vec3> pointPosition = {
        glm::vec3( 0.0,  8.0,  -1.0),
        glm::vec3(-5.0,  7.0,  -4.0),
        glm::vec3( 5.0,  7.0,  -4.0),
        glm::vec3( 0.0,  1.0,   1.0),
        glm::vec3( 0.0,  1.0,   1.0)
    };

    SceneLights.getPointLight(pointLightAttributes, pointPosition);
}