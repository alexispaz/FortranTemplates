#include "prep.inc"

#define _AddHardAfter    _PASTE(_NODE,_add_hard_after)
#define _AddHardcpyAfter _PASTE(_NODE,_add_hardcpy_after)
#define _AddSoftAfter    _PASTE(_NODE,_add_soft_after)
#define _DelSoftAfter    _PASTE(_NODE,_del_soft_after)
#define _DelHardAfter    _PASTE(_NODE,_del_hard_after)
#define _AddHardHead     _PASTE(_NODE,_add_hard_head)
#define _AddSoftHead     _PASTE(_NODE,_add_soft_head)

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
!    end module
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
    procedure :: add_hard       => _AddHardAfter
    procedure :: add_hardcpy    => _AddHardcpyAfter
    procedure :: add_soft       => _AddSoftAfter
    procedure :: del_soft       => _DelSoftAfter
    procedure :: del_hard       => _DelHardAfter
    procedure :: add_head_hard  => _AddHardHead
    procedure :: add_head_soft  => _AddSoftHead
    !final     :: node_destructor
end type _NODE

private  _AddHardAfter
private  _AddHardcpyAfter
private  _AddSoftAfter
private  _DelSoftAfter
private  _DelHardAfter
private  _AddHardHead
private  _AddSoftHead

#undef _NODE
#undef _TYPE
#undef _AddHardAfter
#undef _AddHardcpyAfter
#undef _AddSoftAfter
#undef _DelSoftAfter
#undef _DelHardAfter
#undef _AddHardHead
#undef _AddSoftHead

