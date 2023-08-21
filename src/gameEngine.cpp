#include "Headers/gameEngine.h"+
#include "Headers/asteroid.h"
#include "Headers/ship.h"



GameEngine::GameEngine() 

{
	// Initialize GLFW
	glfwInit();

	// Set OpenGL version.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	// Create <window> Window object.
	// terminal output of if window is created.  if not, terminates and
	// return -1 and exit if fails (need to fix later so that it throws an error. also handle error)
	//
GLFWwindow* w = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, NULL, NULL);
	if (w)
	{
		std::cout << "Created GLFW window" << std::endl;
	}
	else {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	// set <window> to active Window
	window = w;
	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	//set pixel viewport (0,0),(WINDOW_WIDTH,0),(0,WINDOW_HEIGHT),(WINDOW_WIDTH,WINDOW_HEIGHT)
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
void GameEngine::initializeGraphics() {

	Asteroid a(0.75f, 0.75f, 0.1f);
	asteroids.push_back(a);



	// Generates Shader object using shaders defualt.vert and default.frag
	Ship s;
	ship = s;


	Shader shaderProgram("../Shaders/ship.vert", "../Shaders/ship.frag");
	Shader AProgram("../Shaders/asteroid.vert", "../Shaders/asteroid.frag");
	shaders.push_back(shaderProgram);
	shaders.push_back(AProgram);
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAOs.push_back(VAO1);
	VAOs[0].Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(ship.vertices, sizeof(ship.vertices));
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(ship.indices, sizeof(ship.indices));
	VBOs.push_back(VBO1);
	EBOs.push_back(EBO1);
	// Links VBO attributes such as coordinates and colors to VAO
	VAOs[0].LinkAttrib(VBOs[0], 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAOs[0].LinkAttrib(VBOs[0], 1, 3, GL_FLOAT, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOs[0].Unbind();
	VBOs[0].Unbind();
	EBOs[0].Unbind();

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaders[0].ID, "scale");
	VAO VAO2;
	VAOs.push_back(VAO2);
	
	VAOs[1].Bind();

	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO2(asteroids[0].vertices, sizeof(asteroids[0].vertices));
	// Generates Element Buffer Object and links it to indices
	
	VBOs.push_back(VBO2);
	// Links VBO attributes such as coordinates and colors to VAO
	VAOs[1].LinkAttrib(VBOs[1], 0, 2, GL_FLOAT, 5 * sizeof(float), (void*)0);
	VAOs[1].LinkAttrib(VBOs[1], 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	// Unbind all to prevent accidentally modifying them
	VAOs[1].Unbind();
	VBOs[1].Unbind();
	
	GLuint uniID2 = glGetUniformLocation(shaders[1].ID, "scale");
}
void GameEngine::run() {
	
	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		// Specify the color of the background
		glClearColor(CLEAR_RED, CLEAR_GREEN, CLEAR_BLUE, CLEAR_ALPHA);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		shaders[0].Activate();
		// Assigns a value to the uniform; NOTE: Must always be done after activating the Shader Program
		glUniform1f(uniID, 0.5f);
		// Bind the VAO so OpenGL knows to use it
		VAOs[0].Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		shaders[0].Deactivate();
		shaders[1].Activate();
		glUniform1f(uniID2, 0.5f);
		VAOs[1].Bind();
		glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, asteroids[0].indices);
		shaders[1].Deactivate();
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
}
void GameEngine::close() {

	// Delete all the objects we've created
	VAOs[0].Delete();
	VBOs[0].Delete();
	EBOs[0].Delete();
	VAOs[1].Delete();
	VBOs[1].Delete();

	shaders[0].Delete();
	shaders[1].Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}