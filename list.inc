#include "prep.inc"
                  
! Linked list template.
!
! Invoque this tamplate like this:
!
!   #declare _TYPE integer
!   #declare _SOFT
!   #include template_list.inc
!
! where integer is just an example and any other type or object can be used.
! The _SOFT declaration is optional: if is presented each node will contain a
! pointer of type _TYPE instead of an allocated _TYPE object.
! 
! To iterate in the list:
! 
! type(_NODE),pointer  :: node
! ...     
! node => a
! do while(associated(node))
!   ...     
!   !work with node%obj
!   !NOTE: do not use "continue"
!   ...     
!   node => node%next
! enddo
!
! If the use of "continue" is required, it is possible to left the first item
! of the list empty to allow this kind of iteration:     
!   
! node => a
! do while(associated(node%next))
!   node => node%next
!   ...     
!   !work with node%obj
!   !use "continue" if needed 
!   ...     
! enddo
!            
!    
! To keep the list general, the objets in each node should be manually
! allocated. Therefore, no constructor neither destructur for the list is
! defined here.

! Declaring the node
type, public :: _NODE
  class(_NODE), pointer :: next => null()
  _TYPE, pointer       :: obj
  contains
    procedure :: add        => list_add_after
    procedure :: add_before => list_add_head
    !procedure :: remove     => list_delete_downstream
end type _NODE

private  :: list_add_after, list_add_head

contains

subroutine list_add_after(node, obj)
!Insert a new node after node
  class(_NODE)               :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
#ifdef _SOFT  
  new%obj  =>  obj
#else
  allocate(new%obj)
  new%obj  =  obj
#endif
  new%next  => node%next
  node%next => new
end subroutine list_add_after

function list_add_head(node, obj) result(new)
!Insert a new head before node
!On output, node is the new head
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
#ifdef _SOFT  
  new%obj  =>  obj
#else
  allocate(new%obj)
  new%obj  =  obj
#endif
  new%next => node
end function list_add_head

! subroutine list_delete_downstream( head, node )
! !Delete node from the list
!   class(_NODE), target   :: head
!   class(_NODE), pointer  :: node
!   class(_NODE), pointer  :: current
!   class(_NODE), pointer  :: prev
!
!   if ( associated(node,head) ) then
!     ! COMO HAGO ACA SI HEAD NO PUEDE SER POINTER
!     head => node%next
!     deallocate(node)
!   else
!     current => head
!     prev    => head
!     do while ( associated(current) )
!       if ( associated(current,node) ) then
!         prev%next => current%next
!         !XXX: deallocate( current%obj ) ! need final
!         deallocate( current )     ! is also "node"
!         exit
!       endif
!       prev    => current
!       current => current%next
!     enddo
!   endif
! end subroutine list_delete_downstream

#ifdef _SOFT
#undef _SOFT
#endif
#undef _TYPE
#undef _NODE
