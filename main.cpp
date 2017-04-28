#include "main.h"

GLFWwindow* window;

void error_callback(int error, const char* description)
{
	// Print error
	fputs(description, stderr);
}

void setup_callbacks()
{
	// Set the error callback
	glfwSetErrorCallback(error_callback);
    
    //set mouse callback
    glfwSetCursorPosCallback(window, Window::cursor_callback);
    
    glfwSetMouseButtonCallback(window, Window::mouse_button_callback);
    
	// Set the key callback
	glfwSetKeyCallback(window, Window::key_callback);
    
    //Set scroll callback
    glfwSetScrollCallback(window , Window::scroll_callback);
    
    // Set the window resize callback
	glfwSetFramebufferSizeCallback(window, Window::resize_callback);
}

void setup_glew()
{
    glewExperimental = GL_TRUE;
	// Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		glfwTerminate();
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
}

//my functions
void setup_materials()
{
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float shininess[] = { 100.0 };
    
    // Enable color materials
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void setup_lighting()
{
    // Enable lighting
    glEnable(GL_LIGHTING);
    // Enable Local Viewer Light Model
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    
    // Lightsource position
    float position[] = { 10.0, 10.0, 10.0, 1.0 };
    
    // Generate light source
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    // Enable GL_LIGHT0
    glEnable(GL_LIGHT0);
}
//end

void setup_opengl_settings()
{
	// Setup GLEW
	setup_glew();
	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);
	// Related to shaders and z value comparisons for the depth buffer
	glDepthFunc(GL_LEQUAL);
	// Set polygon drawing mode to fill front and back of each polygon
	// You can also use the paramter of GL_LINE instead of GL_FILL to see wireframes
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Disable backface culling to render both sides of polygons
	glDisable(GL_CULL_FACE);
	// Set clear color
	glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
    
    //my calls
    // Set shading to smooth
    glShadeModel(GL_SMOOTH);
    // Auto normalize surface normals
    glEnable(GL_NORMALIZE);
    //setup materials
    setup_materials();
    //setup lighting
    setup_lighting();
    
}

void print_versions()
{
	// Get info of GPU and supported OpenGL version
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version supported %s\n", glGetString(GL_VERSION));

	//If the shading language symbol is defined
#ifdef GL_SHADING_LANGUAGE_VERSION
	std::printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
#endif
}



int main(void)
{
    printf("Calling Window::create_window() from main()\n");
	// Create the GLFW window
	window = Window::create_window(640, 480);
	// Print OpenGL and GLSL versions
	print_versions();
	// Setup callbacks
	setup_callbacks();
	// Setup OpenGL settings, including lighting, materials, etc.
	setup_opengl_settings();
	// Initialize objects/pointers for rendering
	Window::initialize_objects();

	// Loop while GLFW window should stay open
	while (!glfwWindowShouldClose(window))
	{
		// Main render display callback. Rendering of objects is done here.
		Window::display_callback(window);
		// Idle callback. Updating objects, etc. can be done here.
		Window::idle_callback();
	}

	Window::clean_up();
	// Destroy the window
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();

	exit(EXIT_SUCCESS);
}