#!/bin/bash
#Executes the compiled program, using input and output locations.
#Notably, this should be in the same directory as the program (front-end) and the folders with the tests themselves (/input, /actual-output)
cd input #Navigates into the input folder temporarily to grab test name prefixes
for filename in *in.txt; do
	echo Testing ${filename%_*} #Header to display progress
	#Run the compiled program using command line arguments.
    ../front-end ./${filename%_*}_acc.txt ./actual-output/${filename%_*}_transact.txt < $filename > ../actual-output/${filename%_*}_out.txt;
done
cd .. #Returns to the directory the script was run in
