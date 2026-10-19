/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   App.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:48:22 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 17:08:02 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _APP_H
# define _APP_H

# pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class App
{
public:

	App(int w, int h ,const std::string &title);
	~App();

	void	processInput();

	bool	isRunning() 	const;
	void	swapBuffers() 	const;
	void	clearScreen() 	const;

	float	getAspect()		const;
	float	getDeltaTime() 	const;

private:

	GLFWwindow* window;
	int width;
	int height;

	float deltaTime;
	float lastFrame;
};

#endif // _APP_H