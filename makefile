

F90=gfortran

ifeq ($(COMPILER),gfortran)
  FFLAGS+=-g
  FFLAGS+=-O0
  FFLAGS+=-fbacktrace 
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
