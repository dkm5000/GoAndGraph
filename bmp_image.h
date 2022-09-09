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
    Image(int width, int height)
        : i_width(width), i_height(height), i_colors(vector<Color>(width * height))
    {
    };

    ~Image()
    {
    };

    Color get_color(int x, int y) const { return i_colors[y * i_width + x]; };

    void set_color(const Color& color, int x, int y);

    void export_bmp(const char* path);

private:
    int i_width;
    int i_height;
    vector<Color> i_colors;
};

#endif // BMP_IMAGE_H_INCLUDED
