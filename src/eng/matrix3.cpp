#include "matrix3.hpp"

matrix3 scalerMultyMatrix3 (matrix3 matrix, float value){

    matrix3 result;
    
    result.m00 = result.m00 * value;
    result.m01 = result.m01 * value;
    result.m02 = result.m02 * value;
    result.m10 = result.m10 * value;
    result.m11 = result.m11 * value;
    result.m12 = result.m12 * value;
    result.m20 = result.m20 * value;
    result.m21 = result.m21 * value;
    result.m22 = result.m22 * value;

    return result;
}

matrix3 addMatrix3 (matrix3 matrix, matrix3 matrix2){

    matrix3 result;
    
    result.m00 = matrix.m00 * matrix2.m00;
    result.m01 = matrix.m01 * matrix2.m01;
    result.m02 = matrix.m02 * matrix2.m02;
    result.m10 = matrix.m10 * matrix2.m10;
    result.m11 = matrix.m11 * matrix2.m11;
    result.m12 = matrix.m12 * matrix2.m12;
    result.m20 = matrix.m20 * matrix2.m20;
    result.m21 = matrix.m21 * matrix2.m21;
    result.m22 = matrix.m22 * matrix2.m22;

    return result;
}

//angle in radiant
//matrix3 rotationMatrix3 (float angle, float x,float y, float z){

    //float cose = (float)cos(angle);
//
    //matrix3 coseMatrix = scalerMultyMatrix3(identityMatrix3, cose);
//
    //matrix3 tangeMatrix = {
    //    x *x, x*y, x*z,
    //    x *y, y*y, y*z,
    //    x *z, z*y, z*z
    //};
//
    //matrix3 sinMatrix = {
    //    0.0, z, -y,
    //    -z, 0.0, x,
    //    y, -x, 0.0
    //};
//
    //float sine = (float)sin(angle);
    //matrix3 sineMatrix = scalerMultyMatrix3(sineMatrix, sine);
//
    //return addMatrix3(
    //    addMatrix3(
    //        coseMatrix, tangeMatrix
    //    ),
    //    sineMatrix
    //);
//} 