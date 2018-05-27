#ifndef VECTOR_H_
#define VECTOR_H_

class Vector {

  private:
    float x;
    float y;
    float z;

  public:
    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;
    Vector operator*(const float f) const;
    Vector operator/(const float f) const;
    float operator*(const Vector& v) const;

    float GetX() const;
    float GetY() const;
    float GetZ() const;

    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);

    float Magnitude() const;

};

#endif
