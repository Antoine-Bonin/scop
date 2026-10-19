/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mesh.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:20:51 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 16:35:10 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Mesh.hpp"
# include <glad/glad.h>
# include <iostream>
# include <fstream>
# include <sstream>


Mesh::Mesh(const std::string &path)
{
	parseObj(path);
	centerModel();
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
			Vec3 vertex;
			ss >> vertex.x >> vertex.y >> vertex.z;
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
	float minX = vertices[0].x, maxX = vertices[0].x;
	float minY = vertices[0].y, maxY = vertices[0].y;
	float minZ = vertices[0].z, maxZ = vertices[0].z;
	
	for (const auto& v : vertices)
	{
		if (v.x < minX)
			minX = v.x;
		if (v.x > maxX)
			maxX = v.x;
		if (v.y < minY)
			minY = v.y;
		if (v.y > maxY)
			maxY = v.y;
		if (v.z < minZ)
			minZ = v.z;
		if (v.z > maxZ)
			maxZ = v.z;
	}

	float centerX = (minX + maxX) / 2.0f;
	float centerY = (minY + maxY) / 2.0f;
	float centerZ = (minZ + maxZ) / 2.0f;

	for (auto& v : vertices)
	{
		v.x -= centerX;
		v.y -= centerY;
		v.z -= centerZ;
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
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vec3), vertices.data(), GL_STATIC_DRAW);
	//remplis le buffer de la facon d'interpreter le montage du chanter
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	//explique au VAO comment lire les sommets vertex
	// la loc de 0 a 3 en float non normaliser, leur taille	et l'offset = 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), (void*)0);
	glEnableVertexAttribArray(0);
	//desactive le vao par securiter
	glBindVertexArray(0);
}