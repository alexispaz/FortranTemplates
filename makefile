

F90=gfortran

ifeq ($(COMPILER),gfortran)
  F90FLAGS+=-g
  F90FLAGS+=-O0
  F90FLAGS+=-fbacktrace 
  F90FLAGS+=-Wall
endif

MODULES += lion_class.o

main: list.inc
main: main.F90 ${MODULES}
	${F90} -o $@ ${FFLAGS} $< ${MODULES}

%.o: %.f90
	$(F90) $(F90FLAGS) -c $< $(INCLUDES)
  
%.o: %.F90
	$(F90) $(F90FLAGS) -c $< $(INCLUDES)


lion_class.o: list.inc

.PHONY: clean

clean:	
	rm -f *.mod *.o 
