#ifndef __SCENE_H
#define __SCENE_H
#include "Shader.h"
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

class Scene
{
	public:
		Scene();
		ThreeDSpace * get3DSpace();		
		Vec3 getCameraPosition();
		
		
		ThreeDSpace * threeDSpace;
		Vec3 cPos, cDir;
		Mat4 worldPos, worldRotX, worldRotY, worldRotZ;
		void applyPos(GLuint shader);
		float fFrustumScale ; float fzNear; float fzFar;
		void applyRot(GLuint shader);
	private:		
};

#endif
