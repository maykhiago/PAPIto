# PAPIto

PAPIto is a simple tool developed to facilitate the use of the Performance Application Programming Interface (PAPI)(https://icl.utk.edu/papi/).

# Installing

Just write the following command on the Linux's terminal:

chmod +x papito_install.sh

./papito_install.sh

The above commands install the necessary tools and run the example code *simple_array_sum.app.cpp* (to verify if everything is OK).

# Using PAPIto in your code

It is necesary to insert 3 simple commands in you code (see *papito.h*):

*papito_init()* Initialize the PAPI lib;

*papito_start()* Start measuring the hardware counters;

*papito_end()* Finnish the measurement and print the final results.

Also, the user must specify in *counters.in* the hardware counters to be measured.

Obs: to check the available hardware in your machine use the following command (from the PAPIto directory):

../papi/install/bin/papi_avail -a
