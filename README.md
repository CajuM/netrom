netrom
======

A nethack style adventure game wannabe

Installation
------------
The following dependencies are required:
- CMake >= 3.7
- luajit >= 2.1
- boost-system
- boost-filesystem

To build run:
```
mkdir out; cd out
cmake ..
make
```

To start the game run:
```
./src/netrom
```

The Game
--------
So far it's just a demo of a guy who wakes up in a cell at the police station without any memory how he got there. The game is in Romanian, for now, if you don't like it grab a dictionary and translate it. I'm still working on the plot.

Controls
---------
- Arrow keys for movement
- "e" for interaction

Caveats
-------
- JIT does not work due to segfaults
- the game also segfaults randomly without JIT
