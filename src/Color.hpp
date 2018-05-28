#ifndef COLOR_H_
#define COLOR_H_

using namespace std;

class Color {

  private:
    int red;
    int green;
    int blue;

  public:
    Color(int, int, int);
    ~Color();
    int Red() const { return red;};
    int Green() const { return green;};
    int Blue() const { return blue;};

};

#endif
