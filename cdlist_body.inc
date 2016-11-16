#include "prep.inc"

#define _Constructor      _PASTE(_NODE,_constructor)
#define _AddHardcpyAfter  _PASTE(_NODE,_add_hardcpy_after)
#define _AddHardAfter     _PASTE(_NODE,_add_hard_after)
#define _AddSoftAfter     _PASTE(_NODE,_add_soft_after)
#define _AddHardcpyBefore _PASTE(_NODE,_add_hardcpy_before)
#define _AddHardBefore    _PASTE(_NODE,_add_hard_before)
#define _AddSoftBefore    _PASTE(_NODE,_add_soft_before)
#define _DelSoft          _PASTE(_NODE,_del_soft)
#define _DelHard          _PASTE(_NODE,_del_hard)

! For more information read cdlist_header.inc.

subroutine _Constructor(node)
  class(_NODE),target        :: node
  node % next => node
  node % prev => node
  node % obj  => null()
end subroutine _Constructor

subroutine _AddSoftAfter(node, obj)
!Insert a new node after `node`
  class(_NODE),target        :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  new%obj   =>  obj
  new%next  => node%next
  new%prev  => node
  node%next%prev => new
  node%next => new
end subroutine _AddSoftAfter

subroutine _AddHardcpyAfter(node, obj)
!Insert a new node after `node`
  class(_NODE),target        :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next  => node%next
  new%prev  => node
  node%next%prev => new
  node%next => new
end subroutine _AddHardcpyAfter

subroutine _AddHardAfter(node)
!Insert a new node after `node`
  class(_NODE),target        :: node
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj)
  new%next  => node%next
  new%prev  => node
  node%next%prev => new
  node%next => new
end subroutine _AddHardAfter

function _AddSoftBefore(node, obj) result(new)
!Insert a new node bedore `node`
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  new%obj  =>  obj
  new%next => node
  new%prev => node%prev
  node%prev%next => new
  node%prev => new
end function _AddSoftBefore

function _AddHardcpyBefore(node, obj) result(new)
!Insert a new node bedore `node`
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next => node
  new%prev => node%prev
  node%prev%next => new
  node%prev => new
end function _AddHardcpyBefore

function _AddHardBefore(node) result(new)
!Insert a new node bedore `node`
  class(_NODE),target       :: node
  type(_NODE), pointer      :: new

  allocate(new)
  allocate(new%obj)
  new%next => node
  new%prev => node%prev
  node%prev%next => new
  node%prev => new
end function _AddHardBefore

subroutine _DelSoft( node )
  ! WARNING: Do not forget to deallocate the node
  class(_NODE)                     :: node

  node%prev%next => node%next
  node%next%prev => node%prev
  node%obj => null()

end subroutine _DelSoft

subroutine _DelHard( node )
  ! WARNING: Do not forget to deallocate the node
  class(_NODE)                     :: node

  node%prev%next => node%next
  node%next%prev => node%prev

#ifdef _ALLOCATABLE
  deallocate(node%obj)
#endif

end subroutine _DelHard

#ifdef _ALLOCATABLE
#undef _ALLOCATABLE
#endif

#undef _NODE
#undef _TYPE
#undef _Constructor
#undef _AddHardcpyAfter
#undef _AddHardAfter
#undef _AddSoftAfter
#undef _AddHardcpyBefore
#undef _AddHardBefore
#undef _AddSoftBefore
#undef _DelSoft
#undef _DelHard

