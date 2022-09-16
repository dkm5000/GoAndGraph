# Go&Graph
Go&Graph is a simple graphing calculator that allows a user graph a mathematical function over a given interval.

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
#### Features
* works with mathematical functions, constants and variables
* evaluates expressions

### Image generator
* sketches the graph
* uses Bresenham's line algorithm
* can draw numbers (for axis scaling)

## Getting Started
[Download the app](https://github.com/dkm5000/GoAndGraph/releases/tag/v1.0) (currently available only for Windows) and create your first graph!
