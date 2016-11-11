#include "prep.inc"
                  
! ## Linked list template.
!
! Invoke this template in a module like this:
!
!    module name
!    
!      ... ! module declarations
!    
!      #declare _NODE integer_list
!      #declare _TYPE integer
!      #include list_header.inc
!    
!      ... ! module declarations
!    
!    contains
!    
!      ... ! procedures
!    
!      #declare _NODE integer_list
!      #declare _TYPE integer
!      #include list_body.inc
!    
!      ... ! procedures
!    
!    end module !or program
!         
! where integer is just an example. Any other type or object can be used. A
! common way to iterate the list might be:
! 
!    type(_NODE),pointer   :: list
!    class(_NODE),pointer  :: node
!   
!    node => a
!    do while(associated(node))
!      ... !work with node%obj ("cycle" do not advance the node)
!      node => node%next
!    enddo
!
! "cycle" fortran keyword might be wanted to advance the node. For that case it
! is possible to leave the first node of the list empty to allow this kind of
! iteration:     
!   
!    node => a
!    do while(associated(node%next))
!      node => node%next
!      ... !work with node%obj ("cycle" advance the list)   
!    enddo
!
! If the node object require deallocation prior to elimination the option
! `_ALLOCATABLE` must be defined prior to include `list_body.inc`.
! If the object is a user type defined, this type should have declared a final
! procedure.

! Declaring the node
type, public :: _NODE
  class(_NODE), pointer :: next => null()
  _TYPE, pointer        :: obj   => null()
  logical               :: own=.false.
  contains
    procedure :: add_hard       => list_add_hard_after
    procedure :: add_hardcpy    => list_add_hardcpy_after
    procedure :: add_soft       => list_add_soft_after
    procedure :: del_soft       => list_del_soft_after
    procedure :: del_hard       => list_del_hard_after
    procedure :: add_head_hard  => list_add_hard_head
    procedure :: add_head_soft  => list_add_soft_head
    !final     :: node_destructor
end type _NODE

private  list_add_hard_after
private  list_add_hardcpy_after
private  list_add_soft_after
private  list_del_soft_after
private  list_del_hard_after
private  list_add_hard_head
private  list_add_soft_head 
