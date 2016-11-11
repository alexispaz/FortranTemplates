
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

! Simple loop  
node => list
do while( associated(node) )
    print *, node%obj
    node => node%next
enddo
 
! Other loop form (first element must be empty)
! this allows "next" syntax
node => list
do while( associated(node%next) )
    node => node%next
    print *, node%obj
enddo
       
! Add lion 1 to lion list
lion1%color = "orange"
lions%obj => lion1

! Add lion 2 to lion list
lion2%color = "red"
call lions%add_ptr( lion2 )

! Add lion 3 to lion list
lion3%color = "brown"
call lions%add_ptr( lion3 )

! Add lionking to lion list
simba%color = "gold"
simba%name  = "simba"
call lions%add_ptr( simba )

print *, 'Access common properties in the class'
thislion => lions
do while( associated(thislion) )

    print *, 'a lion ', thislion%obj%color

    thislion => thislion%next
enddo
print *, ''
              
print *, 'Access all properties using select type.'
thislion => lions
do while( associated(thislion) )

    ! Print the lion name if is a lionking
    select type (a=>thislion%obj)
    type is (lionking)
      print *, a%name, a%color
    class default  
      ! Print the lion color
      print *, 'simple lion ', thislion%obj%color
    end select

    thislion => thislion%next
enddo
print *, ''


print *, 'Access all properties using internal procedures (cleaner in my opinion)'
thislion => lions
do while( associated(thislion) )
    call thislion%obj%printme
    thislion => thislion%next
enddo
print *, ''
 
contains


endprogram

