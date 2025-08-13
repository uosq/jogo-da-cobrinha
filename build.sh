#!/bin/env bash

set -x

gcc src/main.c -o build/main -lraylib
./build/main