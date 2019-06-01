#include "TerrainShader.h"

TerrainShader::TerrainShader(const char* vShaderPath, const char* fShaderPath)
{
	this->Program = createProgram(vShaderPath, fShaderPath);
	this->uniformLocations = getAllUniformLocations();
}

GLuint TerrainShader::createProgram(const char* vShaderPath, const char* fShaderPath)
{
	std::string vShaderCode;
	std::string fShaderCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fShaderFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);

	try {
		vShaderFile.open(vShaderPath);
		fShaderFile.open(fShaderPath);

		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vShaderCode = vShaderStream.str();
		fShaderCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n" << std::endl;
	}

	const GLchar* vertexShaderSource = vShaderCode.c_str();
	const GLchar* fragmentShaderSource = fShaderCode.c_str();

	GLuint vertexShader, fragmentShader;
	GLint success;
	GLchar infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED/n" << infoLog << std::endl;
	}

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED/n" << infoLog << std::endl;
	}

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED/n" << infoLog << std::endl;
	}
	glUseProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return program;
}

std::map<const char*, GLuint> TerrainShader::getAllUniformLocations()
{
	std::map<const char*, GLuint> temp;
	temp["lightPositionLocation"] = glGetUniformLocation(this->Program, "lightPosition");
	temp["lightColorLocation"] = glGetUniformLocation(this->Program, "lightColor");
	temp["shineDampLocation"] = glGetUniformLocation(this->Program, "shineDamp");
	temp["reflectivityLocation"] = glGetUniformLocation(this->Program, "reflectivity");
	temp["skyColorLocation"] = glGetUniformLocation(this->Program, "skyColor");
	temp["viewMatrixLocation"] = glGetUniformLocation(this->Program, "view_matrix");
	temp["projectionMatrixLocation"] = glGetUniformLocation(this->Program, "projection_matrix");
	temp["modelMatrixLocation"] = glGetUniformLocation(this->Program, "model_matrix");
	temp["bgTextureLocation"] = glGetUniformLocation(this->Program, "bgTexture");
	temp["rTextureLocation"] = glGetUniformLocation(this->Program, "rTexture");
	temp["gTextureLocation"] = glGetUniformLocation(this->Program, "gTexture");
	temp["bTextureLocation"] = glGetUniformLocation(this->Program, "bTexture");
	temp["blendMapLocation"] = glGetUniformLocation(this->Program, "blendMap");
	return temp;
}

std::map<const char*, GLuint> TerrainShader::getUniformLocationDictionary() {
	return this->uniformLocations;
}

void TerrainShader::start()
{
	glUseProgram(this->Program);
}

void TerrainShader::stop()
{
	glUseProgram(0);
}

void TerrainShader::connectTextureUnits() 
{	
	GLuint location = this->uniformLocations.find("bgTextureLocation")->second;
	glUniform1i(location, 0);
	location = this->uniformLocations.find("rTextureLocation")->second;
	glUniform1i(location, 1);
	location = this->uniformLocations.find("gTextureLocation")->second;
	glUniform1i(location, 2);
	location = this->uniformLocations.find("bTextureLocation")->second;
	glUniform1i(location, 3);
	location = this->uniformLocations.find("blendMapLocation")->second;
	glUniform1i(location, 4);

}

void TerrainShader::loadProjectionMatrix()
{
	glm::mat4 projectionMatrix = createProjectionMatrix();
	GLuint location = this->uniformLocations.find("projectionMatrixLocation")->second;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void TerrainShader::loadViewMatrix(Camera* camera)
{
	glm::mat4 viewMatrix = createViewMatrix(camera);
	GLuint location = this->uniformLocations.find("viewMatrixLocation")->second;
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));
}

glm::mat4 TerrainShader::createViewMatrix(Camera* camera)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	glm::vec3 cameraPosition = camera->getPosition();
	matrix = glm::rotate(matrix, glm::radians(camera->getPitch()), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(camera->getYaw()), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(camera->getRoll()), glm::vec3(0, 0, 1));
	matrix = glm::translate(matrix, -cameraPosition);
	return matrix;
}

glm::mat4 TerrainShader::createProjectionMatrix(float fov, float aspect, float near, float far)
{
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::perspective(glm::radians(fov), aspect, near, far);
	return matrix;
}

void TerrainShader::loadShine(float damp, float reflectivity)
{
	GLuint location = this->uniformLocations.find("shineDampLocation")->second;
	glUniform1f(location, damp);
	location = this->uniformLocations.find("reflectivityLocation")->second;
	glUniform1f(location, reflectivity);
}

void TerrainShader::loadLight(glm::vec3 position, glm::vec3 color)
{
	GLuint location = this->uniformLocations.find("lightPositionLocation")->second;
	glUniform3fv(location, 1, glm::value_ptr(position));
	location = this->uniformLocations.find("lightColorLocation")->second;
	glUniform3fv(location, 1, glm::value_ptr(color));

}

void TerrainShader::loadSkyColor(glm::vec3 skyColor)
{
	GLuint location = this->uniformLocations.find("skyColorLocation")->second;
	glUniform3fv(location, 1, glm::value_ptr(skyColor));
}
