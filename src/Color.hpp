#ifndef COLOR_H_
#define COLOR_H_

#include <algorithm>

using namespace std;

class Color {

  private:
    int red;
    int green;
    int blue;

  public:
    Color(int red, int green, int blue);
    Color(Color *color);
    Color(const Color &color);
    ~Color() {};
    int Red() const { return red;};
    int Green() const { return green;};
    int Blue() const { return blue;};
    Color operator+(const Color& v) const;
    void operator+=(const Color& v);
    Color operator*(const float& f) const;
    Color operator&(const Color& light) const;
};

#endif
