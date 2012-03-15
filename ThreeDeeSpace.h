#ifndef __ThreeDeeSpace_H
#define __ThreeDeeSpace_H

#include <vector>
using namespace std;

class ThreeDeeSpace
{
	public:
		ThreeDeeSpace()
		{
			objects.reserve(10);
			Vec3 origin = {0,0,0};
			setOrigin(origin);
		}
		std::vector getObjects()
		{
			return objects;
		}
		
		void addObject(GraphicalObject obj)
		{
			objects.push_back(obj);
		}
		
		void setOrigin(Vec3 org)
		{
			origin=org;
		}
		
		std::vector<GraphicalObject> objects;
		Vec3 origin;
	private:
		
		
};

#endif