/*
 * Shader.h
 *
 *  Created on: Feb 23, 2012
 *  Author: David och Fredric E.
 */

#ifndef SHADER_H_
#define SHADER_H_
#include <algorithm>
#include <string>
#include <vector>
#include <stdio.h>
#include <GL/freeglut.h>
#include <string>
#include <fstream>

typedef struct Uniforms_struct{
  std::string param;
  GLuint id;
  Uniforms_struct(std::string a, GLuint b){
    param = a;
    id = b;
  }
} uniform_t;

class Shader {
  public:
    Shader(std::string vsPath, std::string  fsPath);
    void setVertexShader(GLuint openglRef);
    void setFragmentShader(GLuint openglRef);
    GLuint getVertexShader();
    GLuint getFragmentShader();
    GLuint getShaderProgram();
    std::vector<uniform_t> getParameters();
    void removeParameter(std::string name);
    void addParameter(std::string name, GLuint p);
	std::string loadFileToString(std::string path);
	GLuint glcppShaderSource(std::string const &shader_string, GLenum type);

  private:
    GLuint compileShader(std::string path, GLenum type);
    GLuint compileProgram();

    GLuint progId, fragId, vertexId;
    std::vector<uniform_t> uniforms;
};

#endif /* SHADER_H_ */
