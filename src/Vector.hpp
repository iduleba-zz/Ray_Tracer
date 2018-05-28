#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {

  private:

  public:
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(const float f) const;
    Vector operator/(const float f) const;
    float operator*(const Vector& v) const;

    float x;
    float y;
    float z;

    float Magnitude() const;

};

#endif
