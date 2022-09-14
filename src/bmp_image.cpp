#include "bmp_image.h"

const float PRIMARY_COLOR_MAX = 1;
const float PRIMARY_COLOR_MIN = 0;

Color::Color()
{
    r = PRIMARY_COLOR_MAX;
    g = PRIMARY_COLOR_MAX;
    b = PRIMARY_COLOR_MAX;
};

Color::Color(float r_inp, float g_inp, float b_inp)
{
    r = r_inp;
    g = g_inp;
    b = b_inp;
}

Color::~Color() {};

Image::Image(int width, int height)
{
    i_width = width;
    i_height = height;
    i_colors.resize(width * height);
};

Image::~Image() {};

void Image::set_color(const Color& color, int x, int y)
{
    i_colors[y * i_width + x].r = color.r;
    i_colors[y * i_width + x].g = color.g;
    i_colors[y * i_width + x].b = color.b;
};

void Image::export_bmp(const char* path)
{
    ofstream f;
    f.open(path, ios::out | ios::binary);
    if (!f.is_open())
    {
        cout << "File could not be opened\n";
        return;
    }

    unsigned char bmp_pad[3] = { 0, 0, 0 };
    const int pad_number = (4 - (i_width * 3) % 4) % 4;

    const int file_header_size = 14;
    const int information_header_size = 40;
    const int file_size = file_header_size + information_header_size + i_width * i_height * 3 + pad_number * i_height;

    unsigned char file_header[file_header_size];

    file_header[0] = 'B';
    file_header[1] = 'M';
    file_header[2] = file_size;
    file_header[3] = file_size >> 8;
    file_header[4] = file_size >> 16;
    file_header[5] = file_size >> 24;
    file_header[6] = 0;
    file_header[7] = 0;
    file_header[8] = 0;
    file_header[9] = 0;
    file_header[10] = file_header_size + information_header_size;
    file_header[11] = 0;
    file_header[12] = 0;
    file_header[13] = 0;

    unsigned char information_header[information_header_size];

    information_header[0] = information_header_size;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    information_header[4] = i_width;
    information_header[5] = i_width >> 8;
    information_header[6] = i_width >> 16;
    information_header[7] = i_height >> 24;
    information_header[8] = i_height;
    information_header[9] = i_height >> 8;
    information_header[10] = i_height >> 16;
    information_header[11] = i_height >> 24;
    information_header[12] = 1;
    information_header[13] = 0;
    information_header[14] = 24; //bits per pixel
    information_header[15] = 0;
    information_header[16] = 0;
    information_header[17] = 0;
    information_header[18] = 0;
    information_header[19] = 0;
    information_header[20] = 0;
    information_header[21] = 0;
    information_header[22] = 0;
    information_header[23] = 0;
    information_header[24] = 0;
    information_header[25] = 0;
    information_header[26] = 0;
    information_header[27] = 0;
    information_header[28] = 0;
    information_header[29] = 0;
    information_header[30] = 0;
    information_header[31] = 0;
    information_header[32] = 0;
    information_header[33] = 0;
    information_header[34] = 0;
    information_header[35] = 0;
    information_header[36] = 0;
    information_header[37] = 0;
    information_header[38] = 0;
    information_header[39] = 0;
    information_header[40] = 0;

    f.write(reinterpret_cast<char*>(file_header), file_header_size);
    f.write(reinterpret_cast<char*>(information_header), information_header_size);

    for (int y = 0; y < i_height; y++)
    {
        for (int x = 0; x < i_width; x++)
        {
            unsigned char r = static_cast<unsigned char>(get_color(x, y).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(get_color(x, y).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(get_color(x, y).b * 255.0f);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }

        f.write(reinterpret_cast<char*>(bmp_pad), pad_number);
    }

    f.close();

    cout << "\nGraph created in " << path << "\n";
};

void Image::line(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int xi = 1;

    if (dx < 0)
    {
        xi = -1;
        dx = -dx;
    }

    int d = 2 * dx - dy;
    int x = x1;

    for (int y = y1; y <= y2; ++y)
    {
        set_color(Color(PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN), x, y);
        if (d > 0)
        {
            x += xi;
            d += 2 * (dx - dy);
        }
        else
        {
            d += 2 * dx;
        }
    }
}

void Image::draw_line(int x1_input, int y1_input, int x2_input, int y2_input)
{
    if (x1_input == x2_input)
    {
        if (y1_input < y2_input)
        {
            for (int y = y1_input; y <= y2_input; ++y)
            {
                set_color(Color(PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN), x1_input, y);
            }
        }
        else
        {
            for (int y = y2_input; y <= y1_input; ++y)
            {
                set_color(Color(PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN), x1_input, y);
            }
        }
    }
    else if (y1_input == y2_input)
    {
        if (x1_input < x2_input)
        {
            for (int x = x1_input; x <= x2_input; ++x)
            {
                set_color(Color(PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN), x, y1_input);
            }
        }
        else
        {
            for (int x = x2_input; x <= x1_input; ++x)
            {
                set_color(Color(PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN, PRIMARY_COLOR_MIN), x, y1_input);
            }
        }

    }
    else if (abs(y2_input - y1_input) < abs(x2_input - x1_input))
    {
        if (y1_input > y2_input)
        {
            line(x2_input, y2_input, x1_input, y1_input);
        }
        else
        {
            line(x1_input, y1_input, x2_input, y2_input);
        }
    }
    else if (y1_input > y2_input)
    {
        line(x2_input, y2_input, x1_input, y1_input);
    }
    else
    {
        line(x1_input, y1_input, x2_input, y2_input);
    }
}

int to_pixel(double c, double min_c, double max_c, int len)
{
    return int ((c - min_c) * len / (max_c - min_c + 1));
}
