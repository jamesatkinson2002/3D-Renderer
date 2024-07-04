#include "ShaderManager.h"

ShaderManager::ShaderManager(const char* vertexFilePath, const char* fragmentFilePath) {

	string vertexCode, fragmentCode;

	try {

		vertexCode = readShaderFile(vertexFilePath);
		fragmentCode = readShaderFile(fragmentFilePath);

	}
	catch (const ifstream::failure& e) {
		cout << "Shader File Reading Error: " << e.what() << endl;
	}

	const char* vertexCodeStr = vertexCode.c_str();
	const char* fragmentCodeStr = fragmentCode.c_str();


	unsigned int vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderId, 1, &vertexCodeStr, NULL);
	glCompileShader(vertexShaderId);

	int success;
	char infoLog[512];

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		cout << "Vertex Shader failed to compile: " << infoLog << endl;
	}

	unsigned int fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderId, 1, &fragmentCodeStr, NULL);
	glCompileShader(fragmentShaderId);

	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderId, 512, NULL, infoLog);
		cout << "Fragment Shader failed to compile: " << infoLog << endl;
	}

	mProgramId = glCreateProgram();

	glAttachShader(mProgramId, vertexShaderId);
	glAttachShader(mProgramId, fragmentShaderId);
	glLinkProgram(mProgramId);

	glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(mProgramId, 512, NULL, infoLog);
		cout << "Shader Program Failed to link shaders: " << infoLog << endl;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

}

string ShaderManager::readShaderFile(const char* path)
{
	ifstream shaderFile;
	shaderFile.exceptions(ifstream::badbit);
	shaderFile.open(path);

	stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();

	shaderFile.close();

	string shaderCode = shaderStream.str();
	return shaderCode;
}

void ShaderManager::use() {
	glUseProgram(mProgramId);
}

void ShaderManager::setUniformFloat(const char* name, float value) {
	int uniformLocation = glGetUniformLocation(mProgramId, name);
	glUniform1f(uniformLocation, value);
}

void ShaderManager::setUniformInt(const char* name, int value) {
	int uniformLocation = glGetUniformLocation(mProgramId, name);
	glUniform1i(uniformLocation, value);
}

void ShaderManager::setUniformBool(const char* name, bool value) {
	int uniformLocation = glGetUniformLocation(mProgramId, name);
	glUniform1i(uniformLocation, (int)value);
}

void ShaderManager::setUniformMat4f(const char* name, const glm::mat4& mat) {
	int uniformLocation = glGetUniformLocation(mProgramId, name);
	glUniformMatrix4fv(uniformLocation, 1, false, glm::value_ptr(mat));
}

void ShaderManager::setUniformVec3f(const char* name, const glm::vec3& vec) {
	int uniformLocation = glGetUniformLocation(mProgramId, name);
	glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
}


