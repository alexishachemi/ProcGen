# ProcGen

ProcGen is a procedural generation library for creating room-based dungeons and caves.

It is heavily based off of Pierre Vigier's [Dungeon and Cave Generation](https://pvigier.github.io/2019/06/23/vagabond-dungeon-cave-generation.html) blog post where he explains how he made the generation for his game, Vagabond.

For more information about how to use the library and how generation works, check the [manual](MANUAL.md).

## Dependencies

- [GNU Compiler Collection](https://gcc.gnu.org/) (11.4.0)
- [GNU Make](https://www.gnu.org/software/make/) (4.3)
- [Raylib](https://www.raylib.com/) (5.5+) *Optional, only for debugging*

## Building

to build the library you can use the included Makefile:

```sh
make
```

It will then build the `libprocgen.so` shared library.

## Debug

To run the [debug program](debug/main.c) that was used to produced the example images, you can use the provided debug script `debug.sh`.

[<- Manual](MANUAL.md)
