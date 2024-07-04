#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "glad/glad.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;

class ShaderManager {
private:
	unsigned int mProgramId;
	string readShaderFile(const char* path);
public:
	ShaderManager(const char* vertexFilePath, const char* fragmentFilePath);
	void use();
	void setUniformFloat(const char* name, float value);
	void setUniformInt(const char* name, int value);
	void setUniformBool(const char* name, bool value);
	void setUniformMat4f(const char* name, const glm::mat4& mat);
	void setUniformVec3f(const char* name, const glm::vec3& vec);
};