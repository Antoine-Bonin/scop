/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:20:51 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/22 14:00:10 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Mesh.hpp"
# include <glad/glad.h>
# include <iostream>
# include <fstream>
# include <sstream>
# include <cstddef>


Mesh::Mesh(const std::string &path)
{
	parseObj(path);
	centerModel();
	generateUvs();
	setupOpenGlBuffer();
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void	Mesh::draw() const
{
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void	Mesh::parseObj(const std::string &path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		std::cerr << "Error: can't open the .obj make sure it's spelled right" << std::endl;
		return ;
	}
	std::string line;
	while(std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string prefix;
		ss >> prefix;
		if (prefix == "v")
		{
			Vertex vertex;
			ss >> vertex.pos.x >> vertex.pos.y >> vertex.pos.z;
			vertex.u = 0.0f, vertex.v = 0.0f;
			vertices.push_back(vertex);
		}
		else if (prefix == "f")
		{
			std::vector<unsigned int> face_vertices;
			unsigned int vertex_index;
			while(ss >> vertex_index)
			{
				face_vertices.push_back(vertex_index - 1);
			}
			if (face_vertices.size() == 3)
			{
				indices.push_back(face_vertices[0]);
				indices.push_back(face_vertices[1]);
				indices.push_back(face_vertices[2]);
			}
			else if (face_vertices.size() == 4)
			{
				indices.push_back(face_vertices[0]);
				indices.push_back(face_vertices[1]);
				indices.push_back(face_vertices[2]);
				
				indices.push_back(face_vertices[0]);
				indices.push_back(face_vertices[2]);
				indices.push_back(face_vertices[3]);
			}
			else
				std::cerr << "Error: too many faces can't handle this much : " << face_vertices.size() << std::endl;
		}
	}
	std::cout << "Vertex found : " << vertices.size() << std::endl;
	std::cout << "Indices found : " << indices.size() << std::endl;
	
}

void	Mesh::centerModel()
{
	if (vertices.empty())
		return ;
	float minX = vertices[0].pos.x, maxX = vertices[0].pos.x;
	float minY = vertices[0].pos.y, maxY = vertices[0].pos.y;
	float minZ = vertices[0].pos.z, maxZ = vertices[0].pos.z;
	
	for (const auto& v : vertices)
	{
		if (v.pos.x < minX)
			minX = v.pos.x;
		if (v.pos.x > maxX)
			maxX = v.pos.x;
		if (v.pos.y < minY)
			minY = v.pos.y;
		if (v.pos.y > maxY)
			maxY = v.pos.y;
		if (v.pos.z < minZ)
			minZ = v.pos.z;
		if (v.pos.z > maxZ)
			maxZ = v.pos.z;
	}

	float centerX = (minX + maxX) / 2.0f;
	float centerY = (minY + maxY) / 2.0f;
	float centerZ = (minZ + maxZ) / 2.0f;

	for (auto& v : vertices)
	{
		v.pos.x -= centerX;
		v.pos.y -= centerY;
		v.pos.z -= centerZ;
	}
	size = {maxX - minX, maxY - minY, maxZ - minZ};
}

void	Mesh::generateUvs()
{
	for (auto &v :vertices)
	{
		v.u = v.pos.z / size.z + 0.5f;
		v.v = v.pos.y / size.y + 0.5f;
	}
}

void	Mesh::setupOpenGlBuffer()
{
	//remplis les blocs memoires du gpu
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	//active VAO = facon d'interpreter le chantier et le VBO = valeurs du chantier (indices des sommets)
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	//remplis le buffer de la facon d'interpreter le montage du chanter
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	//explique au VAO comment lire les sommets vertex
	// la loc de 0 a 3 en float non normaliser, leur taille	et l'offset = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex	), (void*)offsetof(Vertex, pos));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, u));
	glEnableVertexAttribArray(1);
	//desactive le vao par securiter
	glBindVertexArray(0);
}