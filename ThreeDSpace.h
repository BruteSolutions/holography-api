#ifndef ThreeDSpace_H_
#define ThreeDSpace_H_

class ThreeDSpace
{
	public:
		ThreeDSpace();
		std::vector<GraphicalObject> getObjects();
		void addObject(GraphicalObject * obj);
		void setOrigin(Vec3 org);
		std::vector<GraphicalObject> getObjects();
		
		std::vector<GraphicalObject> objects;
		Vec3 origin;
		
};

#endif
