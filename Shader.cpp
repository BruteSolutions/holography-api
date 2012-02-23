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
#include <glload/gl_3_2_comp.h>
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
 * short description.
 * @param
 * @return
 */
Shader::Shader(std::string vsPath, std::string fsPath)
{

}

void Shader::setVertexShader(GLuint openglRef)
{
}

void Shader::setFragmentShader(GLuint openglRef)
{
}

GLuint Shader::getVertexShader()
{
}

GLuint Shader::getFragmentShader()
{
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

