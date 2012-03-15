#ifndef __SCENE_H
#define __SCENE_H

class Scene
{
	public:
		Scene();
		ThreeDSpace * get3DSpace();		
		Vec3 getCameraPosition();
		
		
		ThreeDSpace * threeDSpace;
		Vec3 cPos, cDir;
		
	private:		
};

#endif
