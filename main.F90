
! Creating a real linked list
module real_dlist_template
#define _NODE real_dlist
#define _TYPE real(8)
#include "dlist.inc"
end module real_dlist_template

program pp
use real_dlist_template
use lion_class

type(real_dlist), target   :: list
class(real_dlist), pointer  :: node

type(lion_list), target   :: lions
type(lion), target        :: lion1, lion2, lion3
type(lionking)            :: simba
class(lion_list), pointer  :: thislion

! Real list
allocate(list%obj)
list%obj = 1.0d0
call list%add_cpy( 2.0d0 )
call list%add_cpy( 3.0d0 )

node => list
do while( associated(node) )
    print *, node%obj
    node => node%next
enddo
       
! Lion list
lion1%color = "orange"
lions%obj => lion1
lion2%color = "red"
call lions%add_ptr( lion2 )
lion3%color = "brown"
call lions%add_ptr( lion3 )

simba%color = "gold"
simba%name  = "simba"
call lions%add_ptr( simba )

thislion => lions
do while( associated(thislion) )
    print *, thislion%obj%color
    thislion => thislion%next
enddo
       
endprogram
