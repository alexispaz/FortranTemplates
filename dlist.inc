#include "prep.inc"
                  
! Double linked list template.
!
! Invoque this tamplate like this:
!
!   #declare _TYPE integer
!   #declare _SOFT
!   #include template_dlist.inc
!
! where integer is just an example and any other type or object can be used.
! The _SOFT declaration is optional: if is presented each node will contain a
! pointer of type _TYPE instead of an allocated _TYPE object.
! 
! Iterate in the double list like in the simple linked list (see list.inc).

! Declaring the node
type, public :: _NODE
  class(_NODE), pointer :: prev => null()
  class(_NODE), pointer :: next => null()
  _TYPE, pointer        :: obj   => null()
  logical               :: own=.false.
  contains
    procedure :: add_cpy        => list_add_copy_after
    procedure :: add_ptr        => list_add_pointer_after
    procedure :: add_before_cpy => list_add_copy_before
    procedure :: add_before_ptr => list_add_pointer_before
    procedure :: extract        => list_extract
    final     :: node_destructor
end type _NODE

private  :: list_add_copy_after, list_add_pointer_after
private  :: list_add_copy_before, list_add_pointer_before

contains
            
subroutine node_destructor( node )
  type(_NODE)  :: node
  if(node%own) deallocate(node%obj) ! need final
end subroutine node_destructor
 
subroutine list_add_pointer_after(node, obj)
!Insert a new node after node
  class(_NODE),target        :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  new%obj   =>  obj
  new%next  => node%next
  new%prev  => node
  node%next => new
end subroutine list_add_pointer_after
               
subroutine list_add_copy_after(node, obj)
!Insert a new node after node
  class(_NODE),target        :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next  => node%next
  new%prev  => node
  node%next => new
end subroutine list_add_copy_after

function list_add_pointer_before(node, obj) result(new)
!Insert a new head before node
!On output, node is the new head
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  new%obj  =>  obj
  new%next => node
  new%prev => node%prev
  node%prev => new
end function list_add_pointer_before
 
function list_add_copy_before(node, obj) result(new)
!Insert a new head before node
!On output, node is the new head
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next => node
  new%prev => node%prev
  node%prev => new
end function list_add_copy_before
            
subroutine list_extract(node)
  !Remove node from the list (but this does not destroy it)
  class(_NODE)  :: node
  if(associated(node%prev)) node%prev%next => node%next
  if(associated(node%next)) node%next%prev => node%prev
end subroutine list_extract

#ifdef _SOFT
#undef _SOFT
#endif
#undef _TYPE
#undef _NODE
