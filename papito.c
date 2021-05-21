/*
	para compilar é preciso algo parecido com isso:
	gcc -I/usr/local/include -O3 energy_arm_so_mede.c /usr/local/lib/libpapi.a -fopenmp -a /usr/local/lib/energy_arm
	gcc simple.c -I/home/mayk/papi/src/install/include -L/home/mayk/papi/src/install/lib /home/mayk/papi/src/install/lib/libpapi.a -o simple -lpapi
*/

#include "papito.h"

/* Nanopi M3*/
#define NUM_EVENTS 4
#define NUM_CORES 4

int codeEvents[NUM_EVENTS] = {PAPI_TOT_CYC, PAPI_TOT_INS, PAPI_L1_ICM, PAPI_L1_DCM}; // é carregado com os codigos dos eventos.
int num_event_set[NUM_CORES]; // Cada thread registra o seu ID do EventSet, para sempre usar o mesmo

void papito_init()
{
	int retval;

	/* Initialize the library */
	// https://linux.die.net/man/3/papi_library_init
	retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT)
	{
      printf("PAPI library init error!\n");
      exit(1);
  }

	// Initialize thread support in the PAPI library.
	// The omp_get_thread_num routine returns the thread number, within the current team, of the calling thread.
	retval = PAPI_thread_init( ( unsigned long ( * )( void ) ) ( omp_get_thread_num ) );
	if ( retval != PAPI_OK )
	{
		printf("PAPI threads init error!\n");
        exit(1);
	}

	//printf("-->> %d ->", omp_get_thread_num());
}

void papito_handle_error (int retval)
{
	if(retval == 1) printf("Erro ao criar eventSet ");
	if(retval == 2) printf("Erro ao add events ao eventSet ");
	if(retval == 3) printf("Erro ao iniciar ");
	if(retval == 4) printf("Erro stop ");
	if(retval == 5) printf("Erro reset ");
	if(retval == 30) printf("Erro PAPI_overflow");
	if(retval == 31) printf("Erro PAPI_state");

    printf("PAPI error %d: %s\n", retval, PAPI_strerror(retval));
    exit(1);
}

void papito_start()
{
	int i;

	// Criando os eventSets
	for(i = 0; i < NUM_CORES; i++) num_event_set[i] = PAPI_NULL;
	#pragma omp parallel
	{
		int num_thread = omp_get_thread_num();
		//printf("-->> %d ->", omp_get_thread_num());
		// Create the Event Set
		if (PAPI_create_eventset(&num_event_set[num_thread]) != PAPI_OK) papito_handle_error(1);
		// Add Total Instructions Executed to our EventSet
		if (PAPI_add_events(num_event_set[num_thread], codeEvents, NUM_EVENTS) != PAPI_OK) papito_handle_error(2);
		// Start counting events in the Event Set
		if (PAPI_start(num_event_set[num_thread]) != PAPI_OK) papito_handle_error(3);
	}
}

void papito_end()
{
	int t;
	int max = omp_get_max_threads(); // pega o valor definido na variavel ambiente OMP_NUM_THREADS
	long_long values[max][NUM_EVENTS]; // Cada thread registra seu contadores aqui.

  long_long total_INST     = 0;
	long_long total_L1_dados = 0;
  long_long total_L1_instr = 0;
	long_long total_cycles   = 0;

	// Parar a contagem dos eventos
	#pragma omp parallel
	{
		int num_thread = omp_get_thread_num();
		if (PAPI_stop(num_event_set[num_thread], values[num_thread]) != PAPI_OK) papito_handle_error(4);
		if (PAPI_cleanup_eventset(num_event_set[num_thread]) != PAPI_OK) papito_handle_error(20);
		if (PAPI_destroy_eventset(&num_event_set[num_thread]) != PAPI_OK) papito_handle_error(21);
		PAPI_unregister_thread();
	}

	// Estimativa de energia com base nos contadores lidos

	//printf("Thread\tInstr\tL1I\tL1D\tCiclos\n");
	// Totalizando os eventos
	for(t = 0; t < max; t++)
	{
		total_INST     += values[t][INDEX_INST]; // usar index do evento no eventSet.
		total_L1_instr += values[t][INDEX_L1I];
		total_L1_dados += values[t][INDEX_L1D];
    total_cycles   += values[t][INDEX_CYCLE];

		/*
    printf("%d\t",t);
    printf("%lld\t",  values[t][INDEX_INST]);
    printf("%lld\t",  values[t][INDEX_L1I]);
    printf("%lld\t",  values[t][INDEX_L1D]);
    printf("%lld\n", values[t][INDEX_CYCLE]);
		*/
	}

    printf("Total:\t%lld\t%lld\t%lld\t%lld\n", total_INST, total_L1_instr, total_L1_dados, total_cycles);
}
