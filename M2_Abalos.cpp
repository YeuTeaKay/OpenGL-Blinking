#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")  //include this so that console window will not display

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

const char* vertexShaderSource =	"#version 330 core\n"
									"layout (location = 0) in vec3 aPos;\n"
									"void main()\n"
									"{\n"
									"   gl_Position = vec4(aPos, 1.0);\n"
									"}\0";

const char* fragmentShaderSource =	"#version 330 core\n"
									"out vec4 FragColor;\n"
									"uniform vec4 whiteColor;\n"
									"void main()\n"
									"{\n"
									"   FragColor = whiteColor;\n"
									"}\n\0";

const char* fragmentShader1Source =	"#version 330 core\n"
									"out vec4 FragColor;\n"
									"uniform vec4 redColor;\n"
									"void main()\n"
									"{\n"
									"   FragColor = redColor;\n"
									"}\n\0";

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

														 // glfw window creation
														 // --------------------
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	int fragmentShader1 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader1, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShader1);
	// check for shader compile errors
	glGetShaderiv(fragmentShader1, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader1, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, fragmentShader1);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader1);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.2f, -0.6f, 0.0f,  // 0 bottom right
		-0.2f, 0.9f, 0.0f,  // 1 bottom left
		-0.15f,  0.85f, 0.0f,   // 2 top 

		-0.2f, -0.6f, 0.0f,  // 3 bottom right
		-0.15f,  0.85f, 0.0f,  // 4 bottom left
		-0.15f,  -0.6f, 0.0f,   // 5 top 

		-0.15f,  0.85f, 0.0f,  // 6 bottom right
		-0.2f,  0.9f, 0.0f,  // 7 bottom left
		-0.15f,  0.95f, 0.0f,   // 8 top 

		-0.15f,  0.85f, 0.0f,  // 9 bottom right
		-0.15f,  0.95f, 0.0f,  // 10 bottom left
		-0.1f,  0.9f, 0.0f,   // 11 top 

		-0.15f,  0.95f, 0.0f,  // 12 bottom right
		-0.1f,  0.98f, 0.0f,  // 13 bottom left
		-0.1f,  0.9f, 0.0f,   // 14 top 

		-0.1f,  0.9f, 0.0f,  // 15 bottom right
		-0.1f,  0.98f, 0.0f,  // 16 bottom left
		0.0f,  1.0f, 0.0f,   // 17 top

		-0.1f,  0.9f, 0.0f,  // 18 bottom right
		0.0f,  1.0f, 0.0f,  // 19 bottom left
		0.0f,  0.92f, 0.0f,   // 20 top 

		0.0f,  0.92f, 0.0f,  // 21 bottom right
		0.0f,  1.0f, 0.0f,  // 22 bottom left
		0.1f, 0.9f, 0.0f,   // 23 top

		0.0f,  1.0f, 0.0f,  // 24 bottom right
		0.1f,  0.98f, 0.0f,  // 25 bottom left
		0.1f,  0.9f, 0.0f,   // 26 top

		0.1f,  0.9f, 0.0f,  // 27 bottom right
		0.1f,  0.98f, 0.0f,  // 28 bottom left
		0.15f,  0.95f, 0.0f,   // 29 top

		0.1f,  0.9f, 0.0f,  // 30 bottom right
		0.15f,  0.95f, 0.0f,  // 31 bottom left
		0.15f,  0.85f, 0.0f,   // 32 top

		0.15f,  0.85f, 0.0f,  // 33 bottom right
		0.15f,  0.95f, 0.0f,  // 34 bottom left
		0.2f,  0.9f, 0.0f,   // 35 top

		0.15f,  -0.6f, 0.0f,  // 36 bottom right
		0.15f,  0.85f, 0.0f,  // 37 bottom left
		0.2f,  0.9f, 0.0f,   // 38 top

		0.15f,  -0.6f, 0.0f,  // 39 bottom right
		0.2f,  0.9f, 0.0f,  // 40 bottom left
		0.2f,  -0.6f, 0.0f,   // 41 top

		-0.12f,  -0.6f, 0.0f,  // 42 bottom right
		-0.1f,  -0.5f, 0.0f,  // 43 bottom left
		0.0f,  -0.5f, 0.0f,   // 44 top

		-0.12f,  -0.6f, 0.0f,  // 45 bottom right
		0.0f,  -0.5f, 0.0f,  // 46 bottom left
		0.1f,  -0.5f, 0.0f,   // 47 top

		-0.12f,  -0.6f, 0.0f,  // 48 bottom right
		0.1f,  -0.5f, 0.0f,  // 49 bottom left
		0.12f,  -0.6f, 0.0f,   // 50 top

		-0.12f,  -0.6f, 0.0f,  // 51 bottom right
		0.12f,  -0.6f, 0.0f,  // 52 bottom left
		0.12f,  -0.62f, 0.0f,   // 53 top

		-0.12f,  -0.6f, 0.0f,  // 54 bottom right
		0.12f,  -0.62f, 0.0f,  // 55 bottom left
		-0.12f,  -0.62f, 0.0f,   // 56 top

		-0.03f,  -0.9f, 0.0f,  // 57 bottom right
		-0.03f,  -0.62f, 0.0f,  // 58 bottom left
		0.03f,  -0.62f, 0.0f,   // 59 top

		-0.03f,  -0.9f, 0.0f,  // 60 bottom right
		0.03f,  -0.62f, 0.0f,  // 61 bottom left
		0.03f,  -0.9f, 0.0f,   // 62 top

		-0.04f,  -0.92f, 0.0f,  // 63 bottom right
		-0.03f,  -0.9f, 0.0f,  // 64 bottom left
		0.03f,  -0.9f, 0.0f,   // 65 top

		-0.04f,  -0.92f, 0.0f,  // 66 bottom right
		0.03f,  -0.9f, 0.0f,  // 67 bottom left
		0.04f,  -0.92f, 0.0f,   // 68 top

		-0.04f,  -0.92f, 0.0f,  // 69 bottom right
		0.04f,  -0.92f, 0.0f,  // 70 bottom left
		0.04f,  -0.94f, 0.0f,   // 71 top

		-0.04f,  -0.92f, 0.0f,  // 72 bottom right
		0.04f,  -0.94f, 0.0f,  // 73 bottom left
		-0.04f,  -0.94f, 0.0f,   // 74 top
	};


	unsigned indices[] = {
		0, 1, 2,
		3, 4, 5,
		6, 7, 8,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
		18, 19, 20,
		21, 22, 23,
		24, 25, 26,
		27, 28, 29,
		30, 31, 32,
		33, 34, 35,
		36, 37, 38,
		39, 40, 41,
		42, 43, 44,
		45, 46, 47,
		48, 49, 50,
		51, 52, 53,
		54, 55, 56,
		57, 58, 59,
		60, 61, 62,
		63, 64, 65,
		66, 67, 68,
		69, 70, 71,
		72, 73, 74,
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	// bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can 
	// just bind it beforehand before rendering the respective triangle; this is another approach.
	glBindVertexArray(VAO);


	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// be sure to activate the shader before any calls to glUniform
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);

		// update shader uniform
		float timeValue = glfwGetTime();
		float whiteValue = tan(timeValue) / 0.5f + 0.0f; //Changeable
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "whiteColor");
		glUniform4f(vertexColorLocation, whiteValue, whiteValue, whiteValue, 1.0f);

		float timeValue = glfwGetTime();
		float redValue = tan(timeValue) / 0.5f + 0.0f; //Changeable
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "redColor");
		glUniform4f(vertexColorLocation, redValue, 0.0f, 0.0f, 1.0f);

		// render the triangle
		glDrawElements(GL_TRIANGLES, 120, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}