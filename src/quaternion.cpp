#include <vector>
#include <cmath>
#include "quaternion.h"
using namespace std;

Quaternion::Quaternion(float r, vector<float> im){
    real = r;
    imaginary = im;
}

Quaternion::~Quaternion(void){}

//addition and subtraction
Quaternion Quaternion::operator -(const Quaternion& other){
    float r = real - other.real;

    vector<float> im(imaginary);
    im[0] -= other.imaginary[0];
    im[1] -= other.imaginary[1];
    im[2] -= other.imaginary[2];

    return Quaternion(r, im);
}


Quaternion Quaternion::operator +(const Quaternion& other){
    float r = real + other.real;

    vector<float> im(imaginary);
    im[0] += other.imaginary[0];
    im[1] += other.imaginary[1];
    im[2] += other.imaginary[2];

    return Quaternion(r, im);
}

/*
 *
        a1, a2 = self.real, other.real
        b1,c1,d1 = self.imaginary
        b2,c2,d2 = other.imaginary
            
        r = a1*a2 - b1*b2 - c1*c2 - d1*d2
        
        im = [0,0,0]
        im[0] += a1*b2 + b1*a2 + c1*d2 - d1*c2
        im[1] += a1*c2 - b1*d2 + c1*a2 + d1*b2
        im[2] += a1*d2 + b1*c2 - c1*b2 + d1*a2
 */
//multiplication
Quaternion Quaternion::operator *(const Quaternion& other){
    float r = 0;
    r = (real * other.real)
      - (imaginary[0] * other.imaginary[0])
      - (imaginary[1] * other.imaginary[1])
      - (imaginary[2] * other.imaginary[2]);

    vector<float> im(3,0);
    //first imaginary
    im[0] = (real         * other.imaginary[0])
          + (imaginary[0] * other.real)
          + (imaginary[1] * other.imaginary[2])
          - (imaginary[2] * other.imaginary[1]);


    //second imaginary
    im[1] += (real         * other.imaginary[1])
          -  (imaginary[0] * other.imaginary[2])
          +  (imaginary[1] * other.real)
          +  (imaginary[2] * other.imaginary[0]);

    //third imaginary
    im[2] = (real         * other.imaginary[2])
          + (imaginary[0] * other.imaginary[1])
          - (imaginary[1] * other.imaginary[0])
          + (imaginary[2] * other.real);

    return Quaternion(r, im);
}

//conjugation
Quaternion Quaternion::operator -(void){
    vector<float> im(imaginary);
    im[0] *= -1;
    im[1] *= -1;
    im[2] *= -1;

    return Quaternion(real, im);
}

vector<float> rotatePoint(vector<float> pt, vector<float> vec, unsigned int rot){
    Quaternion point(0,pt);

    float sin_val = sin((float) ( (PI * rot / 180.0) / 2.0));
    vec[0] *= sin_val;
    vec[1] *= sin_val;
    vec[2] *= sin_val;
    

    Quaternion vector(cos( (float)( (PI * rot  / 180.0)  / 2.0)), vec);


    Quaternion result = vector * point * -vector;
    return result.imaginary; 
}
