#!/bin/bash
# Compares the expected and actual output folders.
diff -rsc actual-output/ expected-output/
cd expected-output #Navigates into the expected-output folder temporarily to grab test name prefixes
for filename in *out.txt; do
    cmp -c ./$filename ../actual-output/$filename;
    cmp -c ./${filename%_*}_transact.txt ../actual-output/./${filename%_*}_transact.txt
done
cd .. #Returns to the directory the script was run in