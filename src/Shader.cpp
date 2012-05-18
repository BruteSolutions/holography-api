#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include <string>
#include <fstream>

#include "Shader.h"

using namespace std;

/**
 * Shader constructor.
 * @param vsPath path to the vertex shader file.
 * An empty string indicates no shader.
 * @param fsPath path to the fragment shader file.
 * An empty string indicates no shader.
 */
Shader::Shader(std::string vsPath, std::string fsPath) : vertexId(0), fragId(0), progId(0) {
    if (vsPath != "") {
        vertexId = compileShader("shader/" + vsPath, GL_VERTEX_SHADER);
    }
    else{
        throw std::string("VertexShaderNotFoundException(The vertex shader file name is empty.)");
    }
    if (fsPath != "") {
        fragId = compileShader("shader/" + fsPath, GL_FRAGMENT_SHADER);
    }
    else{
    	throw std::string("FragmentShaderNotFoundException(The fragment shader file name is empty.)");
    }
    if (vertexId && fragId) {
        progId = compileProgram();
    }
    std::cout << "End of Shader-constructor \n";
}

/**
 * Compile the given shader and return ID.
 * @param path Path to the shader source file.
 * @return Shader ID.
 */
std::string Shader::loadFileToString(std::string path) {
    std::ifstream ifile(path);
    std::string filetext;
    
    if(ifile.fail()){
        throw std::string("FileNotFoundException(The file was not found or could not be opened.)");
    }

    while (ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }
     if(!ifile.eof()){
        throw std::string("IllegalShaderException(The shader file was correct.)");
    }
    
    return filetext;
}

/**
 * Compiles the given shader source of the given type.
 * @param shader_string Source code of shader.
 * @param type Type of shader.
 * @return Shader ID.
 *
 */
GLuint Shader::glcppShaderSource(std::string const &shader_string, GLenum type) {
    GLuint shader = glCreateShader(type);
    GLchar const *shader_source = shader_string.c_str();
    GLint const shader_length = shader_string.size();

    glShaderSource(shader, 1, &shader_source, &shader_length);
    glCompileShader(shader);
    return shader;
}

/**
 * Compiles shader file at path of the given type.
 * @param path File path to shader.
 * @param type Type of shader.
 * @return Shader program ID.
 */
GLuint Shader::compileShader(std::string path, GLenum type) {
    GLuint shader = glcppShaderSource(loadFileToString(path), type);
    return shader;
}

/**
 * Compile shaders into a program.
 * @return Program ID.
 */
GLuint Shader::compileProgram() {
    std::cout << "Compiling program\n";
    GLuint program = glCreateProgram();

    glAttachShader(program, fragId);
    glAttachShader(program, vertexId);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    
    if (status == GL_FALSE)
        throw std::string("CompilationException(The compliation failed.)");

    return program;
}

/**
 * Sets the current vertex shader to use.
 * @param openglRef ID of the shader.
 */
void Shader::setVertexShader(GLuint openglRef) {
    vertexId = openglRef;
    if (vertexId && fragId) {
        //TODO: delete program and recompile
        progId = compileProgram();
    }
}

/**
 * Sets the current fragment shader to use.
 * @param openglRef ID of the shader.
 */
void Shader::setFragmentShader(GLuint openglRef) {
    fragId = openglRef;
    if (vertexId && fragId) {
        //TODO: delete program and recompile
        progId = compileProgram();
    }
}

/**
 * Get the current vertex shader.
 * @return openglRef ID of the shader.
 */
GLuint Shader::getVertexShader() {
    return(vertexId);
}

/**
 * Get the current fragment shader.
 * @return openglRef ID of the shader.
 */
GLuint Shader::getFragmentShader() {
    return(fragId);
}

/**
 * Get the current shader program.
 * @return openglRef ID of the shader program.
 */
GLuint Shader::getShaderProgram() {
    return(progId);
}

/**
 * Get the vector with all variables associated with this shader.
 * @return A vector with all variables
 */
std::vector<uniform_t> Shader::getParameters() {
    return uniforms;
}

/**
 * Removes the variable with the specified name from this Shader objects uniforms.
 * Nothing happens if the variable is not present.
 * @param name Remove this variable
 */
void Shader::removeParameter(std::string name) {
    for (unsigned int i = 0; i < uniforms.size(); i++) {
        if (name.compare(uniforms[i].param) == 0) {
            uniforms.erase(uniforms.begin() + i);
        }
    }
}

/**
 * Adds a parameter to the list of shared variables with this shader program, a so called uniform.
 * The GLuint p is a OpenGL reference pointing to a variable with name name.
 * @param name GLuint p is a OpenGL reference pointing to a variable with name name.
 * @param p GLuint p is a OpenGL reference pointing to a variable with name name.
 */
void Shader::addParameter(std::string name, GLuint p) {
    uniforms.push_back(Uniforms_struct(name, p));
}
