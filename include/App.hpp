/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:48:22 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/23 14:51:44 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _APP_H
# define _APP_H

# pragma once
# include <glad/glad.h>
# include <GLFW/glfw3.h>
# include <string>
# include "Mat4.hpp"

struct InputState
{
	Vec3 move;
	Vec3 rotate;
};

class App
{
public:

	App(int w, int h ,const std::string &title);
	~App();

	void	processInput();

	bool	isRunning()		const;
	void	swapBuffers() 	const;
	void	clearScreen() 	const;

	float	getAspect()		const;
	float	getDeltaTime() 	const;
	
	const InputState&	getInput() const;

private:
	
	static void framebufferSizeCallback(GLFWwindow* window, int w, int h);

	GLFWwindow*	window;
	
	int 	width;
	int		height;
	float	deltaTime;
	float	lastFrame;
	
	InputState	input;
	float		keyValue(int key) const;
};

#endif // _APP_H