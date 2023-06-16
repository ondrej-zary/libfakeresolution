libfakeresolution
=================

Fake screen resolution to a X11 application using LD_PRELOAD

The application must use Xlib XGetWindowAttributes() function for this to
work. If you have more than one screen, the resolution will be faked on all
of them.

Compiling from source
---------------------
Requirements: make, gcc, libx11-dev

To compile, simply run "make":

    $ make


Usage
-----
Fake X resolution for a full-screen Java application designed for 4:3
screens that calculates its height based on screen width. It does not fit
the screen on a 16:9 1920x1080 display:

    FAKE_RES_X=1440 LD_PRELOAD=/path/to/libfakeresolution.so your_application

Fake resolution to 1024x768:

    FAKE_RES_X=1024 FAKE_RES_Y=768 LD_PRELOAD=/path/to/libfakeresolution.so your_application
