#ifndef __SCENE_H
#define __SCENE_H
#include "Shader.h"
#include "Shared.h"
#include "ThreeDSpace.h"
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>

class Scene
{
	public:
		Scene();
		ThreeDSpace * get3DSpace();		
		Vec3 getCameraPosition();
		void translateCam(Vec3 trans);
		
		
		ThreeDSpace * threeDSpace;
		Vec3 cPos, cDir;
		void selectNext();
		GraphicalObject * getNext();
		GraphicalObject * getNextSelected();
		void deselectAll();
		std::vector<GraphicalObject*> getSelected();
		Mat4 worldPos, worldRotX, worldRotY, worldRotZ;
		void applyPos(GLuint shader);
		float fFrustumScale ; float fzNear; float fzFar;
		void applyRot(GLuint shader);
		void setRotation();
		float angleX, angleY,angleZ;
		
	private:		
		Vec4* matMult(Vec3 vec3);
};

#endif
