#pragma once
//#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS

bool ReadObj(
	const char* a,
	std::vector <glm::vec3>& out_vertex,
	std::vector <glm::vec2>& out_uvs,
	std::vector <glm::vec3>& out_normals
);

