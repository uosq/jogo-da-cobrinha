#!/bin/env bash

set -x

mkdir build
gcc src/main.c src/food.h src/snake.h -o build/main -lraylib
./build/main