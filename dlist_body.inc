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
!    end module
!         
! where integer is just an example. Any other type or object can be used. See
! `list_body` or `list_head` for examples of forward list iteration.

subroutine dlist_add_soft_after(node, obj)
!Insert a new node after `node`
  class(_NODE),target        :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  new%obj   =>  obj
  new%next  => node%next
  new%prev  => node
  if(associated(node%next)) node%next%prev => new
  node%next => new
end subroutine dlist_add_soft_after

subroutine dlist_add_hardcpy_after(node, obj)
!Insert a new node after `node`
  class(_NODE),target        :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next  => node%next
  new%prev  => node
  if(associated(node%next)) node%next%prev => new
  node%next => new
end subroutine dlist_add_hardcpy_after

subroutine dlist_add_hard_after(node)
!Insert a new node after `node`
  class(_NODE),target        :: node
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj)
  new%next  => node%next
  new%prev  => node
  if(associated(node%next)) node%next%prev => new
  node%next => new
end subroutine dlist_add_hard_after

function dlist_add_soft_before(node, obj) result(new)
!Insert a new node bedore `node`
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  new%obj  =>  obj
  new%next => node
  new%prev => node%prev
  if(associated(node%prev)) node%prev%next => new
  node%prev => new
end function dlist_add_soft_before
 
function dlist_add_hardcpy_before(node, obj) result(new)
!Insert a new node bedore `node`
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next => node
  new%prev => node%prev
  if(associated(node%prev)) node%prev%next => new
  node%prev => new
end function dlist_add_hardcpy_before

function dlist_add_hard_before(node) result(new)
!Insert a new node bedore `node`
  class(_NODE),target       :: node
  type(_NODE), pointer      :: new

  allocate(new)
  allocate(new%obj)
  new%next => node
  new%prev => node%prev
  if(associated(node%prev)) node%prev%next => new
  node%prev => new
end function dlist_add_hard_before

subroutine dlist_del_soft( node )
  ! WARNING: Do not forget to deallocate the node
  class(_NODE)                     :: node

  if(associated(node%prev)) node%prev%next => node%next
  if(associated(node%next)) node%next%prev => node%prev
  node%obj => null()

end subroutine dlist_del_soft
  
subroutine dlist_del_hard( node )
  ! WARNING: Do not forget to deallocate the node
  class(_NODE)                     :: node

  if(associated(node%prev)) node%prev%next => node%next
  if(associated(node%next)) node%next%prev => node%prev

#ifdef _ALLOCATABLE
  deallocate(node%obj) 
#endif

end subroutine dlist_del_hard
                                          
#ifdef _ALLOCATABLE
#undef _ALLOCATABLE
#endif
