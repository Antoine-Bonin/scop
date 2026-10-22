/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:24:28 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/22 14:32:58 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Texture.hpp"
#include <glad/glad.h>

Texture::Texture()
{
	const int size = 64;
	std::vector<unsigned char> pixels;

	for( int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			bool white = ((j / 8) + (i / 8)) % 2 == 0;
			unsigned char c = white ? 255 : 30;
			pixels.push_back(c);
			pixels.push_back(c);
			pixels.push_back(c);
		}
	}
	upload(pixels, size, size);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void	Texture::upload(const std::vector<unsigned char>& pixels, int width, int height)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	// Que faire si l'UV sort de 0..1 ? -> répéter l'image
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Comment calculer un pixel quand l'image est réduite ou agrandie à l'écran
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);   // cases bien nettes
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);   // nos lignes de pixels n'ont pas de padding
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
	             GL_RGB, GL_UNSIGNED_BYTE, pixels.data());   // copie CPU -> GPU
	glGenerateMipmap(GL_TEXTURE_2D);         // versions réduites de l'image (anti-scintillement)
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	Texture::bind(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}