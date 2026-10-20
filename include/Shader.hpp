/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 16:40:31 by antoine           #+#    #+#             */
/*   Updated: 2026/10/20 18:52:05 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _SHADER_H
# define _SHADER_H

# pragma once
# include <string>
# include "Mat4.hpp"

class Shader
{
public:
	Shader(const std::string& vertexPath, const char* fragmentPath);
	~Shader();

	void	use() const;
	void	setFloat(const std::string& name, float value) const;
	void	setMat4(const std::string& name, const Mat4& mat) const;
private:
	unsigned int ID;

	void	checkCompileErrors(unsigned int shader, const std::string& type) const;
};

#endif // _SHADER_H