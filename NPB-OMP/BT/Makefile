SHELL=/bin/sh
BENCHMARK=bt
BENCHMARKU=BT

include ../config/make.def

#OBJS =	bt.o \
#	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o
OBJS =	bt.o \
	${COMMON}/c_print_results.o ${COMMON}/c_timers.o ${COMMON}/c_wtime.o ${COMMON}/papito.o

include ../sys/make.common

${PROGRAM}: config ${OBJS}
	${CLINK} ${CLINKFLAGS} -o ${PROGRAM} ${OBJS} ${C_LIB}

bt.o:             bt.cpp npbparams.hpp
	${CCOMPILE} bt.cpp
clean:
	- rm -f *.o *~ mputil*
	- rm -f  npbparams.hpp core
