#!/bin/bash

#Obs: Run the following command to make this script executable
#     chmod +x papito_install.sh

  echo ">>>>>>> Getting the path to the current directory"
  MY_PATH=$(pwd)

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
cd papi/src/ctests
./serial_hl

echo ">>>>>>> Going to PAPIto directory"
cd ../../../PAPIto

echo ">>>>>>> Compiling example code"
gcc simple_array_sum.c -I$PWD/../papi/src/install/include -L$PWD/../papi/src/install/lib $PWD/../papi/src/install/lib/libpapi.a -o simple_array_sum -lpapi

echo ">>>>>>> Running example code"
./simple_array_sum
