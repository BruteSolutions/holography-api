#ifndef SHARED_H_
#define SHARED_H_
#include <cstring>
//struct Configuration {};

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
};

struct Mat4 {
    float m[16];
static Mat4 matrixMultiplication(Mat4 a, Mat4 b){
	
    Mat4 m;
    memset(&m.m, 0, sizeof(m));
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
	    for(int k=0;k<4;k++){
	    	m.m[i+4*j] += a.m[i+4*k]*b.m[k+4*j];
            }
        }
    }
    return m;
}
};

struct KeystoneSetting{
    float k[8];
};
#endif
