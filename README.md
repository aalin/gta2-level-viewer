# GTA2 map thing

This code is quite old. I wrote it in the summer of 2008 and I haven't touched it since.

![Screenshot. Broken textures.](http://imgur.com/ROJnA.png)

# How to run

1. Download GTA 2 from http://www.rockstargames.com/classics/?id=3
2. Install it somehow and get the .gmp and .sty-files and put them in data/

You need [CMake](http://www.cmake.org/). You also need [SDL](http://www.libsd.org/) and [Boost](http://www.boost.org/).
Build it by typing:

    cmake .
    make

And run it:

    src/worldzor

# Bugs

* Some "blocks" don't show up right.
* Transparent textures aren't transparent.
* There is no ordering of transparent quads.

