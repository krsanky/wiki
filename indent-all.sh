#!/bin/sh

for f in include/*.h src/*.c ; do
	echo indent $f
	#indent $f
done

