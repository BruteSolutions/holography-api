#ifndef __SCENE_H
#define __SCENE_H

class Scene
{
	public:
		Scene()
		{
			cPos = {-1-1,1};
			cDir = {1,1,-1};
			threeDeeSpace = new ThreeDeeSpace();
		}
		ThreeDeeSpace * get3DSpace()
		{	
			return threeDeeSpace;
		}
		
		Vec3 getCameraPosition()
		{
			return cPos;
		}	
		ThreeDeeSpace * threeDeeSpace;
		Vec3 cPos, cDir;
	private:
		
		
};

#endif