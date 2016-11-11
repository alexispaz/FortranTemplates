#include "prep.inc"
                  
! ## Double linked list template.
!
! Double linked lists allow to insert a new node before the current
! one. Invoke this template in a module like this:
!
!    module name
!    
!      ... ! module declarations
!    
!      #declare _NODE integer_list
!      #declare _TYPE integer
!      #include dlist_header.inc
!    
!      ... ! module declarations
!    
!    contains
!    
!      ... ! procedures
!    
!      #declare _NODE integer_list
!      #declare _TYPE integer
!      #include dlist_body.inc
!    
!      ... ! procedures
!    
!    end module !or program
!         
! where integer is just an example. Any other type or object can be used. See
! `list_body` or `list_head` for examples of forward list iteration.


! Declaring the node
type, public :: _NODE
  class(_NODE), pointer :: prev => null()
  class(_NODE), pointer :: next => null()
  _TYPE, pointer        :: obj   => null()
  logical               :: own=.false.
  contains
    procedure :: add_hardcpy     => dlist_add_hardcpy_after
    procedure :: add_hard        => dlist_add_hard_after
    procedure :: add_soft        => dlist_add_soft_after
    procedure :: add_before_hardcpy => dlist_add_hardcpy_before
    procedure :: add_before_hard    => dlist_add_hard_before
    procedure :: add_before_soft => dlist_add_soft_before
    procedure :: del_soft        => dlist_del_soft
    procedure :: del_hard        => dlist_del_hard
    !final     :: node_destructor
end type _NODE

private dlist_add_hardcpy_after
private dlist_add_soft_after
private dlist_add_hard_before
private dlist_add_soft_before
private dlist_del_soft_after
private dlist_del_hard_after
