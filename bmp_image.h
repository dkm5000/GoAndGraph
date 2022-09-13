#ifndef BMP_IMAGE_H_INCLUDED
#define BMP_IMAGE_H_INCLUDED

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Color
{
    float r, g, b;

    Color();

    Color(float r_inp, float g_inp, float b_inp);

    ~Color();
};

class Image
{
public:
    Image(int width, int height);

    ~Image();

    Color get_color(int x, int y) const { return i_colors[y * i_width + x]; };

    void set_color(const Color& color, int x, int y);

    void export_bmp(const char* path);

    void draw_line(int x1_input, int y1_input, int x2_input, int y2_input);
    void line(int x1, int y1, int x2, int y2);

private:
    int i_width;
    int i_height;
    vector<Color> i_colors;
};

int to_pixel(double c, double min_c, double max_c, int len);


#endif // BMP_IMAGE_H_INCLUDED
