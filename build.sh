#!/bin/env bash

set -x

gcc src/main.c src/food.h src/snake.h -o build/main -lraylib
./build/main