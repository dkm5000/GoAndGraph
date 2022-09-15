#include <iostream>
#include "graphics.h"
#include "parser.h"
#include <math.h>

using namespace std;

double derivative(double x1, double y1, double x2, double y2)
{
    return (y2 - y1) / (x2 - x1);
}

int main()
{
    string expr_str;
    double step = 0;
    double x1 = 0;
    double x2 = 0;
    double y1 = 0;
    double y2 = 0;
    double max_y = 0;
    double min_y = 0;
    double max_x = 0;
    double min_x = 0;
    double s = 0;
    int k = 0;
    int const FRAME = 80;
    int const AXIS_EXT = 50;
    int const BMP_WIDTH = 3000;
    int const BMP_HEIGHT = 3000;
    Image graph(BMP_WIDTH, BMP_HEIGHT);
    vector<double> y_values(0);

    cout << "This graphing calculator sketches the graph of a function y(x) over the interval [x1, x2]\n";

    cout << "\nEnter the function: y(x) = ";
    getline(cin, expr_str);
    Expression expr(expr_str);
    expr.reverse_polish();

    cout << "\nEnter the interval:\n   from x1 = ";
    cin >> x1;
    cout << "   to x2 = ";
    cin >> x2;

    step = 5 * (x2 - x1 + 1) / (BMP_WIDTH - 2 * FRAME);

    max_y = expr.calculate(x1);
    min_y = expr.calculate(x1);

    for (s = x1; s <= x2; s += step)
    {
        y_values.push_back(expr.calculate(s));

        if (max_y < y_values[k])
        {
            max_y = y_values[k];
        }
        if (min_y > y_values[k])
        {
            min_y = y_values[k];
        }
        ++k;
    }
    if (s - step < x2)
    {
        y_values.push_back(expr.calculate(x2));
        if (max_y < y_values[k])
        {
            max_y = y_values[k];
        }
        if (min_y > y_values[k])
        {
            min_y = y_values[k];
        }
    }

    y1 = min_y;
    y2 = max_y;

    if (x1 < 0)
    {
        min_x = x1;
    }
    if (x2 > 0)
    {
        max_x = x2;
    }
    if (min_y > 0)
    {
        min_y = 0;
    }
    if (max_y < 0)
    {
        max_y = 0;
    }

    //setting white background
    for (int i = 0; i < BMP_WIDTH; ++i)
    {
        for (int j = 0; j < BMP_HEIGHT; ++j)
        {
            graph.set_color(Color(), i, j);
        }
    }

    // y-axis
    graph.draw_line(to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                    to_pixel(max_y, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME + AXIS_EXT,
                    to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                    to_pixel(min_y, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME - AXIS_EXT);
    // x-axis
    graph.draw_line(to_pixel(max_x, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME + AXIS_EXT,
                    to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                    to_pixel(min_x, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME - AXIS_EXT,
                    to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);


    k = 0;
    double last = 0;
    for (double i = x1; i + step <= x2; i += step)
    {
        if (i > x1 &&
            (derivative(i - step, y_values[k - 1], i, y_values[k]) > 0 && derivative(i + step, y_values[k + 1], i + 2 * step, y_values[k + 2]) > 0 && y_values[k] > y_values[k + 1]))
        {
            graph.draw_line(to_pixel(i, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[k], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                        to_pixel(i, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(max_y, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
            graph.draw_line(to_pixel(i + step, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[k + 1], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                        to_pixel(i + step, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(min_y, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
        }
        else if (i > x1 &&
            (derivative(i - step, y_values[k - 1], i, y_values[k]) < 0 && derivative(i + step, y_values[k + 1], i + 2 * step, y_values[k + 2]) < 0 && y_values[k] < y_values[k + 1]))
        {
            graph.draw_line(to_pixel(i, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[k], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                        to_pixel(i, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(min_y, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
            graph.draw_line(to_pixel(i + step, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[k + 1], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                        to_pixel(i + step, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(max_y, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
        }
        else
        {
            graph.draw_line(to_pixel(i, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[k], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                        to_pixel(i + step, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[k + 1], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
        }
        last = i + step;
        ++k;
    }
    if (s - step < x2)
    {
        graph.draw_line(to_pixel(last, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[y_values.size() - 2], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                        to_pixel(x2, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                        to_pixel(y_values[y_values.size() - 1], min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
    }

    //axis scaling
    graph.draw_number(x1, to_pixel(x1, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME, to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME - graph.get_digit_height());
    graph.draw_line(to_pixel(x1, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                    to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME - graph.get_digit_height() / 2,
                    to_pixel(x1, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                    to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME + graph.get_digit_height() / 2);
    graph.draw_number(x2, to_pixel(x2, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME, to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME - graph.get_digit_height());
    graph.draw_line(to_pixel(x2, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                    to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME - graph.get_digit_height() / 2,
                    to_pixel(x2, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME,
                    to_pixel(0, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME + graph.get_digit_height() / 2);
    graph.draw_number(y1, to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME + graph.get_digit_width(), to_pixel(y1, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
    graph.draw_line(to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME - graph.get_digit_width() / 2,
                    to_pixel(y1, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                    to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME + graph.get_digit_width() / 2,
                    to_pixel(y1, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
    graph.draw_number(y2, to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME + graph.get_digit_width(), to_pixel(y2, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);
    graph.draw_line(to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME - graph.get_digit_width() / 2,
                    to_pixel(y2, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME,
                    to_pixel(0, min_x, max_x, BMP_WIDTH - 2 * FRAME) + FRAME + graph.get_digit_width() / 2,
                    to_pixel(y2, min_y, max_y, BMP_HEIGHT - 2 * FRAME) + FRAME);


    graph.export_bmp("graph.bmp");

    return 0;
}
