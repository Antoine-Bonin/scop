/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:44:35 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 10:09:57 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "scop.hpp"

int main(int ac , char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: make sure to launch the program : ./scop [file.obj]" << std::endl;
        exit(1);
    }
    
    scop Scop;
    Scop.parseObj(av[1]);
    return 0;
}