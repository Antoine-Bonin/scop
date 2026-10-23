/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:56:11 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/23 14:45:27 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "App.hpp"
# include <iostream>

App::App(int w, int h, const std::string &title): width(w), height(h), deltaTime(0.0f), lastFrame(0.0f)
{
	if (!glfwInit())
	{
		std::cerr << "Error: failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		std::cerr << "Error: failed to initalize the window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Error: failed to initialize GLAD" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

App::~App()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

void App::framebufferSizeCallback(GLFWwindow* window, int w, int h)
{
	App* self = static_cast<App*>(glfwGetWindowUserPointer(window));
	self->width = w;
	self->height = h;
	glViewport(0, 0, w, h);
}

bool	App::isRunning() const
{
	return !glfwWindowShouldClose(window);
}

void	App::processInput()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		 glfwSetWindowShouldClose(window, true);
		 
	input.move.x = keyValue(GLFW_KEY_D) - keyValue(GLFW_KEY_A);
	input.move.y = keyValue(GLFW_KEY_W) - keyValue(GLFW_KEY_S);
	input.move.z = keyValue(GLFW_KEY_F) - keyValue(GLFW_KEY_R);
	
	input.rotate.y = keyValue(GLFW_KEY_RIGHT) - keyValue(GLFW_KEY_LEFT);
	input.rotate.x = keyValue(GLFW_KEY_DOWN)  - keyValue(GLFW_KEY_UP);
	input.rotate.z = keyValue(GLFW_KEY_E)     - keyValue(GLFW_KEY_Q);
	
}

const InputState&	App::getInput() const
{
	return input;
}

float	App::keyValue(int key) const
{
	return glfwGetKey(window, key) == GLFW_PRESS ? 1.0f : 0.0f;
}

void	App::clearScreen() const
{
	glClearColor(0.15f, 0.15f , 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void App::swapBuffers() const
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

float App::getDeltaTime() const
{
	return deltaTime;
}

float App::getAspect() const
{
	if (height == 0)
		return 1.0f;
	return (float)width / (float)height;
}