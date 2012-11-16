Mandelzoom
==========

This is my take on the Mandelzoom program as described in the book ["The Armchair Universe"](http://www.goodreads.com/book/show/118421.The_Armchair_Universe).

The main files (`mandelzoom.c` and `mandelzoom.h`) are the core of this project. They provide the functions to:
* allocate/free a dynamic memory structure of a required size;
* create a Mandelbrot set representation with the desired size and resolution;
* print the representation as a matrix.

The command line program (`mandelzoom-command-line.c`) makes use of those functions to print a matrix into a file.

To compile, use `$gcc -Wall -std=c99 mandelzoom.c mandelzoom-command-line.c -o mandelzoom`.

To run, use `$./mandelzoom -2 -1.25 2.5 200 > out.txt`.

The parameters are, the starting x and y coordinates (Re and Im) parts, 
the length of the side of the rectangle to be rendered, and an _optional_ parameter
to indicate the resolution (default = 400). Higher resolution takes more processing time.

The output can be imported into Mathematica for visualization :
```M = Import["/Users/ollief/Documents/mandelzoom/out.txt", "csv"];
ArrayPlot[M, Frame -> None]```

The next steps
--------------
* implementing argument validation for functions in `mandelbrot.c`
* documenting the header file and the functions in `mandelbrot.c`
* creating a Cocoa (OS X) application to provide instant visualisation and control.

Screenshots
-----------

![Visualising Mandelbrot Set in Mathematica](https://github.com/ollief/mandelzoom/raw/master/img/mandelzoom-1.png)

