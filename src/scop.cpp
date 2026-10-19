/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:45:17 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 10:52:09 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "scop.hpp"

scop::scop()
{
	vertices.reserve(1024);
	indices.reserve(1024);
}

void	scop::parseObj(const std::string &filePath)
{
	std::ifstream file(filePath);
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

scop::~scop()
{
	
}