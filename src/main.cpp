/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:44:35 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/23 14:52:46 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Mesh.hpp"
# include <iostream>
# include "App.hpp"
# include "Shader.hpp"
# include <cmath>
# include "Texture.hpp"

int main(int ac , char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: make sure to launch the program : ./scop [file.obj]" << std::endl;
		exit(1);
	}
	App app(800, 600, "SCOP - Logo 42");
	Shader shader("shaders/vertex.glsl", "shaders/fragment.glsl");
	Texture texture;
	Mesh mesh(av[1]);
	Vec3 position = {0.0f, 0.0f, 0.0f};
	Vec3 angles   = {0.0f, 0.0f, 0.0f};
	const float moveSpeed = 2.0f;
	const float rotSpeed  = 1.5f;
	while(app.isRunning())
	{
		app.processInput();
		app.clearScreen();
		float dt = app.getDeltaTime();
		const InputState& in = app.getInput();
		
		position.x += in.move.x * moveSpeed * dt;
		position.y += in.move.y * moveSpeed * dt;
		position.z += in.move.z * moveSpeed * dt;
		angles.x += in.rotate.x * rotSpeed * dt;
		angles.y += in.rotate.y * rotSpeed * dt;
		angles.z += in.rotate.z * rotSpeed * dt;

		Mat4 model = Mat4::translate(position.x, position.y, position.z)
				* Mat4::rotateY(angles.y)
				* Mat4::rotateX(angles.x)
				* Mat4::rotateZ(angles.z);
		Mat4 view = Mat4::translate(0.0f, 0.0f, -5.0f);
		Mat4 projection = Mat4::perspective(45 * (M_PI / 180), app.getAspect(), 0.1f, 100.f);
		Mat4 MVP = projection * view * model;
		shader.use();
		shader.setMat4("u_MVP", MVP);
		shader.setInt("u_texture", 0); 
		texture.bind(0);
		mesh.draw();
		app.swapBuffers();
	}   
	return 0;
}