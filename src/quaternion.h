#ifndef __QUATERNION_H
#define __QUATERNION_H
#include <vector>

#define PI 3.14159265


class Quaternion {
    public:
    Quaternion(float r, std::vector<float> im);
    ~Quaternion(void);

    //addition and subtraction
    Quaternion operator -(const Quaternion& other);
    Quaternion operator +(const Quaternion& other);

    //multiplication
    Quaternion operator *(const Quaternion& other);

    //conjugation
    Quaternion operator -(void);

    float real;
    std::vector<float> imaginary;
};

std::vector<float> rotatePoint(std::vector<float> pt, std::vector<float> vec, unsigned int rot);
#endif
