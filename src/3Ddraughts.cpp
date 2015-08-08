// 3Ddraughts.cpp : Defines the entry point for the console application.
//
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl\GLU.h>
#include "../include/Vector3d.hpp"
#include "../include/Camera.hpp"
#include "../include/ChequeredBoard.hpp"

int main()
{
	// Create the main window
	const int width = 600, height = 600;
	sf::ContextSettings settings;
	settings.depthBits = 24; // Request a 24-bit depth buffer
	settings.stencilBits = 8;  // Request a 8 bits stencil buffer
	settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
	sf::RenderWindow App(sf::VideoMode(width, height, 32), "SFML OpenGL", sf::Style::Default, settings);
	App.setFramerateLimit(60);

	// Camara
	Camera camera(
		Vector3d<float>(0, 5, 0),      // position
		Vector3d<float>(0, 0, -10),    // forward
		Vector3d<float>::YAXIS);       // up


	sf::Texture rosewood, woodash;
	rosewood.loadFromFile("resource/images/rosewood.jpg");
	woodash.loadFromFile("resource/images/woodash.jpg");
	ChequeredBoard board(Vector3d<int>(200, 200),        // number of cells
		Vector3d<float>(1, 1),          // size
		Vector3d<float>(-100, -100),    // position
		rosewood,  // texture 1
		woodash);  // texture 2


	//prepare OpenGL surface for HSR 
	glClearDepth(1.f);
	glClearColor(0.3f, 0.3f, 0.6f, 0.f); //background colour
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	//// Setup a perspective projection & Camera position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//set up a 3D Perspective View volume
	gluPerspective(90.f, (float)width / height, 1.f, 50.0f);//fov, aspect, zNear, zFar


	// Start game loop
	while (App.isOpen())
	{
		// Process events
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				App.close();

			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				App.close();
		}

		//Prepare for drawing
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations
		//initialise the worldview matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//get the viewing transform from the camera
		camera.ViewingTransform();
		App.draw(board);

		App.display();
	}

	return EXIT_SUCCESS;
}