#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "glfw3.lib")

#define WIDTH 400		
#define HEIGHT 300	

bool HasGLSLSupport(void);
bool InitOpenGLExtensions(void);
bool HasOpenGL2Support(void);
bool HasGeometryShaderSupport(void);
bool HasShaderModel4(void);

bool useGLSL = false;
bool extensions_init = false;
bool bGeometryShader = false;
bool bGPUShader4 = false;

bool InitOpenGLExtensions(void) {
	if (extensions_init)
		return true;

	extensions_init = true;

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		cout << "Error:" << glewGetErrorString(err) << endl;
		extensions_init = false;
		return false;
	}

	cout << "OpenGL Vendor: " << (char*)glGetString(GL_VENDOR) << "\n";
	cout << "OpenGL Renderer: " << (char*)glGetString(GL_RENDERER) << "\n";
	cout << "OpenGL Version: " << (char*)glGetString(GL_VERSION) << "\n\n";

	HasGLSLSupport();

	//cout << "OpenGL Extensions:\n" << (char*) glGetString(GL_EXTENSIONS) << "\n\n";

	return true;
}

bool HasGLSLSupport(void) 
{
	bGeometryShader = HasGeometryShaderSupport();
	bGPUShader4 = HasShaderModel4();

	if (useGLSL)
		return true;  // already initialized and GLSL is available

	useGLSL = true;

	if (!extensions_init)
		InitOpenGLExtensions();  // extensions were not yet initialized!!

	if (GLEW_VERSION_2_0) 
	{
		cout << "OpenGL 2.0 (or higher) is available!" << endl;
	}
	else if (GLEW_VERSION_1_5) 
	{
		cout << "OpenGL 1.5 core functions are available" << endl;
	}
	else if (GLEW_VERSION_1_4) 
	{
		cout << "OpenGL 1.4 core functions are available" << endl;
	}
	else if (GLEW_VERSION_1_3) {
		cout << "OpenGL 1.3 core functions are available" << endl;
	}
	else if (GLEW_VERSION_1_2) 
	{
		cout << "OpenGL 1.2 core functions are available" << endl;
	}

	if (GL_TRUE != glewGetExtension("GL_ARB_fragment_shader")) 
	{
		cout << "[WARNING] GL_ARB_fragment_shader extension is not available!\n";
		useGLSL = false;
	}
	else
	{
		cout << " -> GL_ARB_fragment_shader extension is available!\n";
	}

	if (GL_TRUE != glewGetExtension("GL_ARB_vertex_shader")) 
	{
		cout << "[WARNING] GL_ARB_vertex_shader extension is not available!\n";
		useGLSL = false;
	}
	else
	{
		cout << " -> GL_ARB_vertex_shader extension is available!\n";
	}

	if (GL_TRUE != glewGetExtension("GL_ARB_shader_objects")) 
	{
		cout << "[WARNING] GL_ARB_shader_objects extension is not available!\n";
		useGLSL = false;
	}
	else
	{
		cout << " -> GL_ARB_shader_objects extension is available!\n";
	}

	if (useGLSL) 
	{
		cout << endl << "[OK] OpenGL Shading Language version " << glGetString(GL_SHADING_LANGUAGE_VERSION) <<
			" is available" << endl;
	}
	else 
	{
		cout << "[FAILED] OpenGL Shading Language is not available...\n\n";
	}

	return useGLSL;
}

bool HasOpenGL2Support(void) 
{
	if (!extensions_init)
		InitOpenGLExtensions();

	return (GLEW_VERSION_2_0 == GL_TRUE);
}

bool HasGeometryShaderSupport(void) 
{
	if (GL_TRUE != glewGetExtension("GL_EXT_geometry_shader4"))
		return false;

	return true;
}

bool HasShaderModel4(void) 
{
	if (GL_TRUE != glewGetExtension("GL_EXT_gpu_shader4"))
		return false;

	return true;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
	GLFWwindow* window;
	if (!glfwInit())
		exit(EXIT_FAILURE);

	//Tell rendering window which version of OpenGL the program will expect, or use highest available if omitted.
	//The following call to glfwCreateWindow will fail if values are invalid for the system
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Function callbacks to handle input from user
	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		cout << glewGetErrorString(err) << endl;
		exit(EXIT_FAILURE);
	}

	if (InitOpenGLExtensions()) 
	{
		while (!glfwWindowShouldClose(window))
		{
    		glfwSwapBuffers(window);

			glfwWaitEvents();
		}
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
