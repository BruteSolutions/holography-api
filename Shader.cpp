//============================================================================
// Name        : Shader.cpp
// Author      : David och Fredric E.
// Description : Shader class implementation.
//============================================================================

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
#include "glload/include/glload/gl_3_3.h"
#include <GL/freeglut.h>

#include "Shader.h"

using namespace std;

/*
   int main() {
// Endast för test
//todo Tas bos när vi har testat klart
Shader *bla = new Shader("what","eek");
(*bla).addParameter("harr", 2);

cout << bla->getParameters()[0].param;
(*bla).addParameter("yarr", 3);
(*bla).removeParameter("harr");
cout << bla->getParameters()[0].param;
return 0;
}
 */

/**
 * Shader constructor.
 * @param vsPath path to the vertex shader file.
 * An empty string indicates no shader.
 * @param fsPath path to the fragment shader file.
 * An empty string indicates no shader.
 */
Shader::Shader(std::string vsPath, std::string fsPath) : vertexId(0), fragId(0), progId(0)
{
    if(vsPath != "") {
        vertexId = compileShader(vsPath, GL_VERTEX_SHADER);
    }

    if(fsPath != "") {
        fragId = compileShader(fsPath, GL_FRAGMENT_SHADER);
    }

    if(vertexId && fragId) {
        progId = compileProgram();
    }
}

/**
 * Compile the given shader and return ID.
 * @param path Path to the shader source file.
 * @param type Type of shader.
 * @return Shader ID.
 */
GLuint Shader::compileShader(std::string path, GLenum type)
{
    GLuint shader = glCreateShader(type);
    const char * filePointer = path.c_str();
    glShaderSource(shader, 1, &filePointer, NULL);

    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        throw "Error in shader compilation";
    }

    return shader;
}

/**
 * Compile shaders into a program.
 * @return Program ID.
 */
GLuint Shader::compileProgram()
{
    GLuint program = glCreateProgram();

    glAttachShader(program, fragId);
    glAttachShader(program, vertexId);

    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        throw "Error in program compilation";
    }

    return program;
}

/**
 * Sets the current vertex shader to use.
 * @param openglRef ID of the shader.
 */
void Shader::setVertexShader(GLuint openglRef)
{
    vertexId = openglRef;
    if(vertexId && fragId) {
        //TODO: delete program and recompile
        progId = compileProgram();
    }
}

/**
 * Sets the current fragment shader to use.
 * @param openglRef ID of the shader.
 */
void Shader::setFragmentShader(GLuint openglRef)
{
    fragId = openglRef;
    if(vertexId && fragId) {
        //TODO: delete program and recompile
        progId = compileProgram();
    }
}

/**
 * Get the current vertex shader.
 * @return openglRef ID of the shader.
 */
GLuint Shader::getVertexShader()
{
    return(vertexId);
}

/**
 * Get the current fragment shader.
 * @return openglRef ID of the shader.
 */
GLuint Shader::getFragmentShader()
{
    return(fragId);
}

/**
 * Get the current shader program.
 * @return openglRef ID of the shader program.
 */
GLuint Shader::getShaderProgram()
{
    return(progId);
}

/**
 * Get the vector with all variables associated with this shader.
 * @return A vector with all variables
 */
std::vector<uniform_t> Shader::getParameters(){
    return uniforms;
}

/**
 * Removes the variable with the specified name from this Shader object’s uniforms.
 * Nothing happens if the variable is not present.
 * @param name Remove this variable
 */

void Shader::removeParameter(std::string name){
    for(unsigned int i = 0; i<uniforms.size();i++){
        if(name.compare(uniforms[i].param)==0){
            uniforms.erase(uniforms.begin()+i);
        }
    }
}

/**
 * Adds a parameter to the list of shared variables with this shader program, a so called uniform.
 * The GLuint p is a OpenGL reference pointing to a variable with name name.
 * @param name GLuint p is a OpenGL reference pointing to a variable with name name.
 * @param p GLuint p is a OpenGL reference pointing to a variable with name name.
 */
void Shader::addParameter(std::string name, GLuint p){
    uniforms.push_back(Uniforms_struct(name, p));
}
