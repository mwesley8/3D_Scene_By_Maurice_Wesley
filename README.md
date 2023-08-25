# 3D_Scene_By_Maurice_Wesley
This repository displays my work with OpenGL.

Everything in my 3D scene is something new that I learned and applied in my project. I can remember when I created my first window that had my name in the tope left corner. Now, I have primitives that form shapes with texture applied to a surface that reflects light.

I will continue to expand on the four pillars. OpenGL gave me an opportunity to work with pointers, pass by reference, data structures, and an API. Those are the ingredients for any software development project in the future. The course allowed me to apply all the knowledge that I learned in previous classes. I do not know my professional pathway. However, I will continue to build on the knowledge that this course has given me.

The professor provided an example image that showed four objects.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/7a8d77e4-c291-4d92-8b66-d7f53f0203e7)

After receiving permission, I started working on my interpretation of the bottles and eggs photo. The photo below displays my first attempt at recreating the 3D scene.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/f503049d-7ef3-4981-ae1e-fdae76f82c37)

One of our previous assignments required us to display a complex 3D object with different colors at the vertices. The picture below uses 60 degree angles.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/d7f54673-4f07-4926-b4be-dde1f13eac87)

The picture below uses 3.6 degree angles.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/afa1a8d7-37f0-4794-888a-c94c2c93d497)

Reducing the sector angle increases the number of sides that make up the circle. A 60-degree angle has to be drawn and rotated 6 times to create an object that can be perceived as a circle. The number of sides is calculated using the equation (360 / SECTOR ANGLE). A 3.6-degree angle has to be drawn and rotated 100 times to draw a circle. The circle has 100 sides but the object appears round with smooth edges.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/b0736549-3342-40be-8632-8202c3237b8f)

The picture below shows my work with textures. Texturing a plane was covered in the tutorials and videos. The circular objects were more difficult to texture. I am not a fan of GL_REPEAT. However, I was able to apply texture without vertical lines.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/4b2f5898-936e-46bf-a055-106206808389)

The picture below shows my work with lighting. The instructor provided a material ambient color. I added some lighting and the looks like someone sprayed furniture polish over the entire canvas. The scene is with one single point light at the top. You can see the reflection in the back wall.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/3fd15b00-848f-424c-a518-0a5a3492ac6b)

The picuture below displays my “final” interpretation. Point lights are located at the top left and top right of the back wall. Additionally, lights are located at the top center and behind the camera.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/72aa1afa-2c18-4339-a2d9-dca53cf5ea3d)

Background and Counter Top: The background and counter top are planes. The counter top is the plane that “supports” the bowl and bottles. The dimensions of the back plane was changed to replicate the bottle size relative to the back wall.

Bowl and Eggs: I would like to cover these objects together. The bowl is a half shere designed and created at the center, scaled to a bigger size, rotated on the x axis, and stretched on the y-axis. Originally, the half sphere was made from six angles. I modified my code to make the bowl smoothe and realistic.

Using transformations, the eggs were strategically placed inside the bowl. They barely touch each other. They are six layer spheres. More specifically, code was created to produce the second half of the sphere.

Bottles: The bottles were a little more difficult to design. The bottles have a cylinder for the bottom, a half sphere for the middle and a cylinder at the top. Another cylinder was added to replicate a bottle cap. The color contrast highlights the use of three diffferent objects to create the bottles. The same change was made to the number of angles used to generate a circular appearance. Similarly, transformations were used for sizes and locations.

Explain how a user can navigate your 3D scene.

The prompt is similar to the functional design requirements for the the 3D scene. The user can traverse the scene using horizontal, vertical, and depth camera navigation. The camera navigation is based on specific user input. The keyboard inputs WASD can be userd to move forward, left, back, and right respectively. The Q key allows the user to move up and the E key allows the user to move down.

Also, the user is able to control the viewing angle with a mouse. The mouse cursor is set to DISABLED and the user has to click the left mouse button to change the viewing angle in the scene. The mouse scroll controls the speed at which the camera moves around the scene (explained below).

Dynamically change between the two types of projection.

For creative purposes and to meet project requirments, the user is able to press the ‘p’ key to switch between othographic and perspective. Additionally, the user can press the  ‘r’ key to make a light move back and forth across the back wall.

Nuanced explanation of approach to user navigation.

Nuanced controls were classified as the ability for the user to dynamically change the speed at which the camera moved around the scene by rotating the mouse scroll wheel. Below you will see the code in action.

![image](https://github.com/mwesley8/3D_Scene_By_Maurice_Wesley/assets/105822088/45a3bd5b-b64e-4058-aaae-92ed4579c04f)

Briefly, MovementSpeed is a global variable that is assigned a const value in the overloaded custom constructor. The value of MovementSpeed increases or decreases relative to the vertical axis of the mouse scroll wheel. The speed has an upper and lower bound.

Afterwards, the MovementSpeed is multiplied by the change in frame rate. The product is added or substracted from the associated vector to replicate movement in a specific direction. The code illustrates how I was able to precisely moderate the speed of the movement.

Explain the custom functions in your program that you are using to make your code more modular and organized.

I concentrated on writing modular, organized, and reuaable code from the beginning of the class. One area that gets overlooked is readability. Initially, it was difficult to organize a program that I did not understand. I spent countless hours trying to understand the material. After time spent, I was able to develop code that satisfied the prompt.

Length requirements prevent me from annotating an exhaustive list of modularized functions. However, I will hightlight a few. All of the object functions are formalaic. They implement shader specifications, transformations, and ADS lighting. The objects can be easily imported into a different program. The shader, mesh, texture, camera, vertices, indicies, and light attributes were abstracted away from the main program. Data structures, object instances, function calls, and headers extentuate the modularity of my code.

The same vertices were used to create different objects. As I stated above, the vertices for a half sphere was used to create a bowl and the middle section of two bottle. The half sphere was extended to create a sphere for the eggs. A cylinder was transformed six different ways to create the bottles. Additionally, careful attention was given to formatting and commenting to enhance readability.

Explain code that was not encapsulated in a custom function but that could have been.

I prefer to abstract code away from the driver. Each header and associated cpp file performs essential operations that contributes to the overall functionality of the code. I was unable to determine how to put the GLFW, GLEW, and key process initialization into a separate header. Similarly, I could not decide if I should put my objects into a separate headers as well.

Conclusion

Overall, I am satisfied with the knowledge and experience I was able to gain during the course of this term. There are a few things that I would change if I had more time. Examples include: applying texture that does not warp/stretch/repeat, more pratice with lighting to create mirror images, and working with the geometry shader. However, the program demostrates my ability to create complex objects derived from code that is modular, reusable, readable, and maintainable.
