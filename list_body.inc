#include "prep.inc"

#define _AddHardAfter    _PASTE(_NODE,_add_hard_after)
#define _AddHardcpyAfter _PASTE(_NODE,_add_hardcpy_after)
#define _AddSoftAfter    _PASTE(_NODE,_add_soft_after)
#define _DelSoftAfter    _PASTE(_NODE,_del_soft_after)
#define _DelHardAfter    _PASTE(_NODE,_del_hard_after)
#define _AddHardHead     _PASTE(_NODE,_add_hard_head)
#define _AddSoftHead     _PASTE(_NODE,_add_soft_head)

! For more information read list_header.inc.

subroutine _AddSoftAfter(node, obj)
!Insert a new node after `node`
  class(_NODE)               :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  new%obj   =>  obj
  new%next  => node%next
  node%next => new
end subroutine _AddSoftAfter

subroutine _AddHardcpyAfter(node, obj)
!Insert a new node after `node`
  class(_NODE)               :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next  => node%next
  node%next => new
end subroutine _AddHardcpyAfter

subroutine _AddHardAfter(node)
!Insert a new node after `node`
  class(_NODE)               :: node
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj)
  new%next  => node%next
  node%next => new
end subroutine _AddHardAfter

function _AddSoftHead(node, obj) result(new)
!Insert a new head before node
!On output, node is the new head
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  new%obj  =>  obj
  new%next => node
end function _AddSoftHead

function _AddHardHead(node, obj) result(new)
!Insert a new head before node
!On output, node is the new head
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next => node
end function _AddHardHead

subroutine _DelSoftAfter( head, node )
  !head is excluded from the downstream search. In case node points to head or a
  !target that is not a member of the list nothing happens. Actual argument of
  !node must be the associated object to node or a pointer to it.
  class(_NODE),target,intent(in)  :: head
  _TYPE,target,intent(in)         :: node
  class(_NODE),pointer            :: current
  class(_NODE),pointer            :: prev

  prev    => head
  current => head%next
  do while ( associated(current) )
    if ( associated(current%obj,target=node) ) then
      prev%next => current%next
      current%obj => null()
      deallocate(current)
      exit
    endif
    prev    => current
    current => current%next
  enddo

end subroutine _DelSoftAfter

subroutine _DelHardAfter( head, node )
  !head is excluded from the downstream search. In case node points to head or
  !a target that is not a member of the list nothing happens.
  class(_NODE),target,intent(in)   :: head
  class(_NODE),pointer,intent(in)  :: node
  class(_NODE),pointer             :: current
  class(_NODE),pointer             :: prev

  prev    => head
  current => head%next
  do while (associated(current))
    if (associated(current,node)) then
      prev%next => current%next
#ifdef _ALLOCATABLE
      deallocate(current%obj)
#endif
      deallocate(current)
      exit
    endif
    prev    => current
    current => current%next
  enddo

end subroutine _DelHardAfter

#ifdef _ALLOCATABLE
#undef _ALLOCATABLE
#endif

#undef _NODE
#undef _TYPE
#undef _AddHardAfter
#undef _AddHardcpyAfter
#undef _AddSoftAfter
#undef _DelSoftAfter
#undef _DelHardAfter
#undef _AddHardHead
#undef _AddSoftHead

