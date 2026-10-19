/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:16:10 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 16:20:39 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MESH_H
# define _MESH_H

# pragma once

# include <vector>
# include <string>
# include <Mat4.hpp>

class Mesh
{
public:

	Mesh(const std::string& filePath);
	~Mesh();
	
	void	draw() const;
	
private:

	std::vector<Vec3> vertices;
	std::vector<unsigned int> indices;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void	parseObj(const std::string &filePath);
	void	centerModel();
	void	setupOpenGlBuffer();
};

#endif // _MESH_H