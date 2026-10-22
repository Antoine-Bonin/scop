/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texture.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 14:21:53 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/22 14:24:11 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef _TEXTURE_H
# define _TEXTURE_H

# include <vector>

class Texture
{
public:
	Texture();
	~Texture();

	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
	
	void	bind(unsigned int unit) const;
private:
	unsigned int ID;

	void	upload(const std::vector<unsigned char>& pixels, int width, int height);
};
#endif // _TEXTURE_H