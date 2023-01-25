# PAPIto

PAPIto is a simple tool developed to facilitate the use of the Performance Application Programming Interface (PAPI)(https://icl.utk.edu/papi/).

## Installing

Just write the following command on the Linux terminal:

***chmod +x papito_install.sh***

***./papito_install.sh***

The above commands install the necessary tools and run the example code ***simple_array_sum.cpp*** (to verify if everything is OK).

Obs1: You will need superuser privileges, for example:
***sudo ./simple_array_sum***

## Using PAPIto in your code

It is necessary to insert three simple commands in your code (see ***papito.h***):

***papito_init()*** Initialize the PAPI lib;

***papito_start()*** Start measuring the hardware counters;

***papito_end()*** Finnish the measurement and print the final results.

Also, the user must specify in ***counters.in*** the hardware counters to be measured.

Obs2: to check the available hardware in your machine, use the following command (from the PAPIto directory):

***../papi/install/bin/papi_avail -a***

Obs3: For serial execution, you must to set the following OpenMP variables:
export OMP_NUM_THREADS=1	#Running with a single thread
export GOMP_CPU_AFFINITY="0"	#Mapping the thread to core 0

Then, your results will be the ones presented in thread index 0:

For example, using the simple_array_sum execution, you will get the following:

Thread	TOT_CYC	L1_DCM	L2_DCM	

***0	  1093736	8186	17945***	

1	  917686	  37	  109	

2	  1045753	  50	  258	

3	  932284	  62	  180	

Total:	3989459	8335	18492	

128000	8191936000	512000
