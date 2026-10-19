/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 09:42:29 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 09:44:15 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SCOP_H
# define _SCOP_H
# include <vector>
# include <string>
# include <iostream>
# include <fstream>
# include <sstream>

struct Vec3 {
    float x, y, z;
};

class scop
{
public:
	scop();
	scop(const scop& other);
	~scop();
	scop& operator=(const scop& other);
	void	parseObj(const std::string &filePath);

private:

	std::vector<Vec3> vertices;
	std::vector<unsigned int> indices;

};

#endif // _SCOP_H