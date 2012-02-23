/*
 * Shader.h
 *
 *  Created on: Feb 23, 2012
 *      Author: fericss
 */

#ifndef SHADER_H_
#define SHADER_H_

typedef struct {
	String param;
	GLuint id;
} uniform_t;

class Shader {
public:
	Shader(String vsPath, String fsPath);
	void setVertexShader(GLuint openglRef);
	void setFragmentShader(GLuint openglRef);
	GLuint getVertexShader();
	Gluint getFragmentShader();
	String getParameters();
	void removeParameter(String name);
	void addParameter(String name, GLuint p);
private:
	GLuint id;
	std::vector<uniform_t> uniforms;
};

#endif /* SHADER_H_ */
