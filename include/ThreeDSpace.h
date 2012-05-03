#ifndef ThreeDSpace_H_
#define ThreeDSpace_H_
#include <vector>
#include "GraphicalObject.h"

class ThreeDSpace
{
	public:
		ThreeDSpace();
		std::vector<GraphicalObject*> getObjects();
		void addObject(GraphicalObject * obj);
		void setOrigin(Vec3 org);
		void bindBuffers();
		void selectNext();
		std::vector<GraphicalObject*> objects;
		Vec3 origin;
		int current;
		std::vector<GraphicalObject*> selected;
		float scale;
		void resize(double factor);
		void setScale(double _scale);
		double getScale();
		void incrementScale(double inc);
		void applyScale();
};

#endif
