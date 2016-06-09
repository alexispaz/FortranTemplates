

FCC=gfortran

ifeq ($(COMPILER),gfortran)
  FFLAGS+=-g
  FFLAGS+=-O0
  FFLAGS+=-fbacktrace 
endif

main: main.F90 list.inc
	${FCC} -o $@ ${FFLAGS} $<

.PHONY: clean

clean:	
	rm -f *.mod *.o 
