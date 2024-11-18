#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "math.h"

class Game
{
public:
	Game();
	void run();
	static void renderScene();

	// Freeglut stuff
    static void displayNewFrame(int deltaTime);  
    static void keyboardListener(unsigned char key, int mouse_x, int mouse_y);
	static void specialKeyboardListener(int key, int mouse_x, int mouse_y);
	static void mouseListener(int x, int y);
	static void glutCallbacks();

};

