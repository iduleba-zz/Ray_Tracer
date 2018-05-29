#ifndef VECTOR_H_
#define VECTOR_H_

#include <math.h>

class Vector {

  public:
    Vector(float x, float y, float z);
    Vector(const Vector& v);
    Vector() {};
    ~Vector() {};
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator^(const Vector& v) const;
    Vector operator*(const float f) const;
    Vector operator/(const float f) const;
    float operator*(const Vector& v) const;

    float x;
    float y;
    float z;

    float Magnitude() const;
    void Normalize();

};

#endif
