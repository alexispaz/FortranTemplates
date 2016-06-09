
! Creating a real linked list
module real_list_template
#define _NODE real_list
#define _TYPE real(8)
#include "list.inc"
end module real_list_template



! Defining some objects
module lion_class

public
type :: lion
  character(20) :: color
end type
type, extends(lion) :: lionking
  character(20) :: name
end type    

! Creating a lion list
#define _NODE lion_list
#define _TYPE class(lion)
#define _SOFT
#include "list.inc"

end module lion_class


program pp
use real_list_template
use lion_class

type(real_list), target   :: list
class(real_list), pointer  :: node

type(lion_list), target   :: lions
type(lion), target        :: lion1, lion2, lion3
type(lionking)            :: simba
class(lion_list), pointer  :: thislion

! Real list
allocate(list%obj)
list%obj = 1.0d0
call list%add( 2.0d0 )
call list%add( 3.0d0 )

node => list
do while( associated(node) )
    print *, node%obj
    node => node%next
enddo
       
! Lion list
lion1%color = "orange"
lions%obj => lion1
lion2%color = "red"
call lions%add( lion2 )
lion3%color = "brown"
call lions%add( lion3 )

simba%color = "gold"
simba%name  = "simba"
call lions%add( simba )

thislion => lions
do while( associated(thislion) )
    print *, thislion%obj%color
    thislion => thislion%next
enddo
       
endprogram
