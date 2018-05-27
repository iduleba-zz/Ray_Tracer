#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {

  private:
    float x;
    float y;
    float z;

  public:
    Vector operator+(const Vector& v) const;
    Vector operator*(const float f) const;

};

#endif
