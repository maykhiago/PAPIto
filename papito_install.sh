#!/bin/bash

#Obs: Run the following command to make this script executable
#     chmod +x papito_install.sh

cd ..

echo ">>>>>>> Cloning PAPI repository"
git clone https://bitbucket.org/icl/papi.git

echo ">>>>>>> Entrer the directory"
cd papi/src

echo ">>>>>>> Configuring"
./configure --prefix=$PWD/../install

echo ">>>>>>> Installing"
make && make install

echo ">>>>>>> Checking if everything is OK"
cd ctests
./serial_hl

echo ">>>>>>> Going to PAPIto directory"
cd ../../../PAPIto

sed -i "s+#define NUM_CORES 4+#define NUM_CORES $(grep -c ^processor /proc/cpuinfo)+g" papito.cpp

echo ">>>>>>> Compiling example code"
g++ simple_array_sum.cpp papito.cpp -I$PWD/../papi/install/include -L$PWD/../papi/install/lib $PWD/../papi/install/lib/libpapi.a -o simple_array_sum -fopenmp -lpapi

echo ">>>>>>> Running example code"
./simple_array_sum

cd GAPBS
sed -i "s+#define NUM_CORES 4+#define NUM_CORES $(grep -c ^processor /proc/cpuinfo)+g" papito.cpp

cd ..
cd NPB-OMP/common
sed -i "s+#define NUM_CORES 4+#define NUM_CORES $(grep -c ^processor /proc/cpuinfo)+g" papito.cpp

cd ..

echo ">>>>>>> Cloning GAPBS repository"
git clone https://github.com/sbeamer/gapbs.git

echo ">>>>>>> Copying the modified files"
cp PAPIto/GAPBS/*.cpp gapbs/src
cp PAPIto/GAPBS/*.cc gapbs/src
cp PAPIto/GAPBS/*.h gapbs/src
cp PAPIto/GAPBS/*.in gapbs/src
cp PAPIto/GAPBS/Makefile gapbs/

cd gapbs/src

echo ">>>>>>> In Makefile inserting the correct path to counters.in"
sed -i "s+counters.in+$PWD/counters.in+g" papito.cpp

cd ..

echo ">>>>>>> Compilling"
make

echo ">>>>>>> Running PageRank Algorithm"
./pr -f test/graphs/4.el -n1

cd ..

echo ">>>>>>> Copying NAS repository"
cp -r PAPIto/NPB-OMP .

echo ">>>>>>> Compilling"
cd NPB-OMP
./compile_all.sh

echo ">>>>>>> Running bt.A"
bin/bt.A

cd ../PAPIto
