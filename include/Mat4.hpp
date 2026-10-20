/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antbonin <antbonin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 11:26:53 by antbonin          #+#    #+#             */
/*   Updated: 2026/10/19 17:44:07 by antbonin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MAT4_H
# define _MAT4_H

# pragma once

struct Vec3 {
	float x, y, z;
};
class Mat4
{
public:
	Mat4();

	Mat4 operator*(const Mat4& other) const;

	static Mat4	translate(float x, float y, float z);
	static Mat4	rotateY(float angle_rad);
	static Mat4 perspective(float fov_rad, float aspect, float near_plane, float far_plane);

	const float* data() const;

private:
	float m[4][4];
};

#endif // _MAT4_H