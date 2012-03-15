#ifndef __SCENE_H
#define __SCENE_H

#include "ThreeDSpace.h"

class Scene
{
	public:
		Scene()
		{
			cPos = {-1-1,1};
			cDir = {1,1,-1};
			threeDSpace = new ThreeDSpace();
		}
		ThreeDSpace * get3DSpace()
		{	
			return threeDSpace;
		}
		
		Vec3 getCameraPosition()
		{
			return cPos;
		}	
		ThreeDSpace * threeDSpace;
		Vec3 cPos, cDir;
	private:
		
		
};

#endif
