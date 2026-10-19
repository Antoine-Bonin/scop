/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:44:35 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 17:11:43 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Mesh.hpp"
# include <iostream>
# include "App.hpp"

int main(int ac , char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: make sure to launch the program : ./scop [file.obj]" << std::endl;
        exit(1);
    }
    App app(800, 600, "SCOP - Logo 42");
    Mesh mesh(av[1]);
    while(app.isRunning())
    {
        app.processInput();
        app.clearScreen();
        app.swapBuffers();
    }   
    return 0;
}