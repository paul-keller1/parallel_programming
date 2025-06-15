#!/bin/bash

touch results.txt

echo "" > results.txt

echo "serial" >> results.txt
./serial >> results.txt
echo -e >> results.txt

echo "critical:" >> results.txt
echo "1 thread" >> results.txt
export OMP_NUM_THREADS=1
./critical >> results.txt
echo -e "2 threads" >> results.txt
export OMP_NUM_THREADS=2
./critical >> results.txt
echo -e "4 threads" >> results.txt
export OMP_NUM_THREADS=4
./critical >> results.txt
echo -e "8 threads" >> results.txt
export OMP_NUM_THREADS=8
./critical >> results.txt
echo -e "12 threads" >> results.txt
export OMP_NUM_THREADS=12
./critical >> results.txt
echo -e >> results.txt


echo "atomic:" >> results.txt
echo "1 thread" >> results.txt
export OMP_NUM_THREADS=1
./atomic >> results.txt
echo -e "2 threads" >> results.txt
export OMP_NUM_THREADS=2
./atomic >> results.txt
echo -e "4 threads" >> results.txt
export OMP_NUM_THREADS=4
./atomic >> results.txt
echo -e "8 threads" >> results.txt
export OMP_NUM_THREADS=8
./atomic >> results.txt
echo -e "12 threads" >> results.txt
export OMP_NUM_THREADS=12
./atomic >> results.txt
echo -e >> results.txt

echo "reduction:" >> results.txt
echo "1 thread" >> results.txt
export OMP_NUM_THREADS=1
./reduction >> results.txt
echo -e "2 threads" >> results.txt
export OMP_NUM_THREADS=2
./reduction >> results.txt
echo -e "4 threads" >> results.txt
export OMP_NUM_THREADS=4
./reduction >> results.txt
echo -e "8 threads" >> results.txt
export OMP_NUM_THREADS=8
./reduction >> results.txt
echo -e "12 threads" >> results.txt
export OMP_NUM_THREADS=12
./reduction >> results.txt
echo -e >> results.txt







/bin/hostname
