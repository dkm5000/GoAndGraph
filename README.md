# Go&Graph
Go&Graph is a simple graphing calculator, designed as a console application, that allows users to graph mathematical functions over a given interval.

## Features
Go&Graph supports:
* most common operators: +, - (unary and binary), *, /, ^
* following mathematical functions: sin(x), cos(x), tan(x), log(x), abs(x)
* variables: x
* mathematical constants: pi, e

The application generates the graph as a bitmap image file that can be found in the Go&Graph installation directory.

## Implementation
The whole project is developed using C++ and includes multiple source and header files:
* parser.cpp and parser.h for parsing user input
* graphics.cpp and graphics.h for generating BMP files
* main.cpp

### Mathematical expression parser
Based on the shunting yard algorithm, the evaluator converts user input (infix expressions) to Reverse Polish notation.
* works with mathematical functions, constants and variables
* evaluates expressions

### Image generator
Creates BMP files without using external graphics libraries.
* sketches graphs
* uses Bresenham's line algorithm
* can draw numbers (for axis scaling)

## Examples
### y(x) = 5sin(1 / (x - 5)
![](https://github.com/dkm5000/GoAndGraph/blob/main/doc/examples/console_app_example1.png)
![](https://github.com/dkm5000/GoAndGraph/blob/main/doc/examples/graph_example1.png)
### y(x) = 0.25x^3 + 0.5x^2 - 2x + 5
![](https://github.com/dkm5000/GoAndGraph/blob/main/doc/examples/console_app_example2.png)
![](https://github.com/dkm5000/GoAndGraph/blob/main/doc/examples/graph_example2.png)
### y(x) = x^2 + 1/x
![](https://github.com/dkm5000/GoAndGraph/blob/main/doc/examples/console_app_example3.png)
![](https://github.com/dkm5000/GoAndGraph/blob/main/doc/examples/graph_example3.png)

## Getting Started
[Download the app](https://github.com/dkm5000/GoAndGraph/releases/tag/v1.0) (currently available only for Windows) and create your first graph!
