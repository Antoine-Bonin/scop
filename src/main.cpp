/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:44:35 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/22 14:34:20 by antbonin         ###   ########.fr       */
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
    float rotation = 0.0f;
    while(app.isRunning())
    {
        app.processInput();
        app.clearScreen();
        rotation += 0.01f;
        Mat4 model = Mat4::rotateY(rotation);
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