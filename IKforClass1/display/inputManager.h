#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
#include "IK.h"



const int DISPLAY_WIDTH = 1200;
const int DISPLAY_HEIGHT = 800;
const float FAR = 100.0f;
const float NEAR = 1.0f;
const float CAM_ANGLE = 60.0f;
float relation = (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT;


Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");

IK scn(glm::vec3(0.0f, 5.0f, -20.0f), CAM_ANGLE, relation, NEAR, FAR);

float factor = 1.0;

double x1 = 0, x2=0;
double ys1 = 0, y2 = 0;
float depth;
	

	


	

	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
				case GLFW_KEY_ESCAPE:			
					glfwSetWindowShouldClose(window,GLFW_TRUE);
				break;
				case GLFW_KEY_RIGHT:
					//scn.shapeTransformation(scn.zGlobalRotate,-20.1f);
					scn.shapeTransformation(scn.zLocalRotate,5.f);
//						cout<< "right: "<<endl;
					break;
				case GLFW_KEY_LEFT:
					//scn.shapeTransformation(scn.zGlobalRotate,20.1f);
					scn.shapeTransformation(scn.zLocalRotate,-5.f);
//					cout<< "left: "<<endl;
					break;
				case GLFW_KEY_UP:
					//cout<< "up: "<<endl;
					scn.shapeTransformation(scn.xGlobalRotate,5.f);
					break;
				case GLFW_KEY_DOWN:
					scn.shapeTransformation(scn.xGlobalRotate,-5.f);
					//cout<< "down: "<<endl;
					break;
				case GLFW_KEY_SPACE:
					if(scn.isActive())
						scn.dActivate();
					else
						scn.makeChange();
					//std::cout<< "change direction "<<std::endl;
					//scn.changeDirection();
				break;
			default:
				break;
			}
		}
	}
	
	void updatePosition(double xpos, double ypos)
	{
		x1  = x2;
		x2 = xpos;
		ys1 = y2; 
		y2 = ypos;
	}

	

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		
		scn.resize(width,height,NEAR,FAR);
		relation = (float)width/(float)height;
	}