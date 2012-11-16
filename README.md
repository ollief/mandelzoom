Mandelzoom
==========

This is my take on the Mandelzoom program as described in the book ["The Armchair Universe"](http://www.goodreads.com/book/show/118421.The_Armchair_Universe).

The main files (`mandelzoom.c` and `mandelzoom.h`) are the core of this project. They provide the functions to:
* allocate/free a dynamic memory structure of a required size;
* create a Mandelbrot set representation with the desired size and resolution;
* print the representation as a matrix.

The command line program (`mandelzoom-command-line.c`) makes use of those functions to print a matrix into a file: `$./mandelzoom -2 -1.25 2.5 200 > out.txt` which can then be imported into Mathematica for visualization :
    M = Import["/Users/ollief/Documents/mandelzoom/out.txt", "csv"];
    ArrayPlot[M, Frame -> None]

The next step is to create a Cocoa (OS X) application to provide instant visualisation and control.
