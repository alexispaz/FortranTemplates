
! Creating a double linked list o real numbers
module intrinsic_class


integer, parameter :: dp=8

#define _NODE real_dlist
#define _CLASS real(dp)
#include "dlist_header.inc"
           
#define _NODE real_v
#define _TYPE real(dp)
#include "vector_header.inc"
              
#define _NODE integer_v
#define _TYPE integer
#include "vector_header.inc"
    
contains

#define _NODE real_dlist
#define _CLASS real(dp)
#include "dlist_body.inc"
          
#define _NODE real_v
#define _TYPE real(dp)
#include "vector_body.inc"
               
#define _NODE integer_v
#define _TYPE integer
#include "vector_body.inc"
    
end module intrinsic_class




                  
