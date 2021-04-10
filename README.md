# Various C++ experiments

This features various small projects, trying out various interactions.
===========================
## SDLtext (-win)

These projects are a test of rendering text using the SDLttf addon to the SDL library. The folders indicate if they are to be run on linux or windows.

Expected output is a large grid of zeros, bordered along the left and top to indicate a address. This has then been implemented into the 8080 project.

## bitshifting

A small test of the bitshifting operator. Expected output is 16 and 48 on seperate lines.

## class-function-pointers

A test of calling pointers to functions, from an array. Calls functions in the order A, B, B, A, A.

## classes

A file defines two classes, the main element of note is that TestClass can be called with a pointer to a B class. Output is:
```
UWU
469
Bee
Bee
0
6
```

## function-pointers

Features an array of function pointers.
```
funcB call!
Func D!!!
funcA called!
fundB called!
funcC called!
```

## pointer returning functions

Calls the varFetcher function in various manners:
```
0x5582f1f7050 // will be a different value each time this is run
222
456
```

## rendering efficiency

Test of differnt methods to draw the contents of an array. Pressing space will make it perform this task, with time taken output to stdout. This method implements using the SDL_RenderFillRect() function. Creates mosaic of random colours.
