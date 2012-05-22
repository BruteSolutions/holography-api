#ifndef SHARED_H_
#define SHARED_H_

//struct Configuration {};

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
};

struct Mat4 {
    float m[16];
};
struct KeystoneSetting{
    float k[8];
};
#endif
