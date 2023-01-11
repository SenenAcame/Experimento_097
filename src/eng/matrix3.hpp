#pragma once
#include <iostream>
#include <math.h>

typedef struct{

    float m00;
    float m01;
    float m02;
    float m10;
    float m11;
    float m12;
    float m20;
    float m21;
    float m22;

} matrix3;


matrix3 scalerMultyMatrix3 (matrix3 matrix, float value);
matrix3 addMatrix3 (matrix3 matrix, matrix3 matrix2);
matrix3 rotationMatrix3 (float angle, float x,float y, float z); //angle in radiant

const matrix3 identityMatrix3 = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
};
