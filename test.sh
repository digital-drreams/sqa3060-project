#!/bin/bash
cd input
for filename in *in.txt; do
	echo Testing ${filename%_*}
    ../front-end ./input/${filename%_*}_acc.txt ./actual-output/${filename%_*}_transact.txt < $filename > ../actual-output/${filename%_*}_out.txt;
done
cd ..
