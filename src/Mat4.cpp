/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mat4.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 16:33:16 by antoine           #+#    #+#             */
/*   Updated: 2026/10/20 18:52:47 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Mat4.hpp"
# include <cmath>
Mat4::Mat4(){
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				m[i][j] = 1.0f;
			} else {
				m[i][j] = 0.0f;
			}
		}
	}
}

Mat4	Mat4::operator*(const Mat4& other) const {
	Mat4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m[i][k] * other.m[k][j];
			}
		}
	}
	return result;
}

Mat4	Mat4::translate(float x, float y, float z) {
	Mat4 result;
	result.m[0][3] = x;
	result.m[1][3] = y;
	result.m[2][3] = z;
	return result;
}

Mat4	Mat4::rotateY(float angle_rad) {
	Mat4 result;
	float c = std::cos(angle_rad);
	float s = std::sin(angle_rad);
	result.m[0][0] = c;
	result.m[0][2] = s;
	result.m[2][0] = -s;
	result.m[2][2] = c;
	return result;
}

Mat4	Mat4::perspective(float fov_rad, float aspect, float near_plane, float far_plane)
{
	Mat4 res;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.m[i][j] = 0.0f;
		}
	}
	float tanHalfFov = tan(fov_rad / 2.0f);

	res.m[0][0] = 1.0f / (aspect * tanHalfFov);
	res.m[1][1] = 1.0f / tanHalfFov;
	res.m[2][2] = -(far_plane + near_plane) / (far_plane - near_plane);
	res.m[2][3] = -(2.0f * far_plane * near_plane) / (far_plane - near_plane);
	res.m[3][2] = -1.0f;
	return res;
}

const float*	Mat4::data() const
{
	return &m[0][0];
}