#!/bin/bash

for N in {1..8}; do
	echo -ne "\n$N\t"
	\time -pf "%e" build/mandelbrot $N 2>&1 | tr -d '\n'
	echo -ne "\t"
	\time -pf "%e" build/mandelbrot $N 2>&1 | tr -d '\n'
	echo -ne "\t"
	\time -pf "%e" build/mandelbrot $N 2>&1 | tr -d '\n'
	echo -ne "\t"
	\time -pf "%e" build/mandelbrot $N 2>&1 | tr -d '\n'
	echo -ne "\t"
	\time -pf "%e" build/mandelbrot $N 2>&1 | tr -d '\n'
done