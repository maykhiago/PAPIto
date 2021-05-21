#include <stdio.h>
#include "papito.h"

// Compilar com:
//	gcc simple_array_sum.c mypapi.c -I/home/mayk/papi/src/install/include -L/home/mayk/papi/src/install/lib /home/mayk/papi/src/install/lib/libpapi.a -o simple_array_sum -fopenmp -lpapi

int main(int argc, const char * argv[])
{
		papito_init();

		int K = 128;

		//auto ans = time(N);
		int N = (K*1024)/4; // Byte to Kilo

		int array[N];

		// Initialize the elements
		for (int i=0; i<N; ++i)
			array[i] = i;

		papito_start();

		// Run:
		long long int sum = 0;
		for (int i = 0; i < N; i++)
		{
			sum += array[i];
		}

		papito_end();

		printf("%d\t%lld\t%d\n", N, sum, N*4);
}
