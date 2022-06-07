#include "Compute.h"

ComputeShader::ComputeShader(const char* computePath) {
	std::string computeCode;
	std::ifstream computeShaderFile;
	computeShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        computeShaderFile.open(computePath);
        std::stringstream computeShaderStream;
        // read file's buffer contents into streams
        computeShaderStream << computeShaderFile.rdbuf();
        // close file handlers
        computeShaderFile.close();
        // convert stream into string
        computeCode = computeShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
    }
    const char* computeShaderCode = computeCode.c_str();
    // 2. compile shaders
    unsigned int compute;
    // vertex shader
    compute = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(compute, 1, &computeShaderCode, NULL);
    glCompileShader(compute);
    checkCompileErrors(compute, "COMPUTE");
    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, compute);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(compute);
}

void ComputeShader::createTexture(unsigned int width, unsigned int height) {
    glUseProgram(ID);
    // generate texture
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // create empty texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, NULL);
    glBindImageTexture(0, texture, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGB);
    glUseProgram(0);
}

void ComputeShader::setValues(float* values, glm::vec3 dim) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dim.x, dim.y, dim.z, GL_RED, GL_FLOAT, values);
}

void ComputeShader::use() {
    glUseProgram(ID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void ComputeShader::dispatch(glm::vec3 dim) {
    glDispatchCompute(dim.x, dim.y, dim.z);
}

void ComputeShader::wait() {
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void ComputeShader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}