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
 
subroutine list_add_soft_after(node, obj)
!Insert a new node after `node`
  class(_NODE)               :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  new%obj   =>  obj
  new%next  => node%next
  node%next => new
end subroutine list_add_soft_after

subroutine list_add_hardcpy_after(node, obj)
!Insert a new node after `node`
  class(_NODE)               :: node
  _TYPE, target, intent(in)  :: obj
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next  => node%next
  node%next => new
end subroutine list_add_hardcpy_after

subroutine list_add_hard_after(node)
!Insert a new node after `node`
  class(_NODE)               :: node
  type(_NODE), pointer       :: new

  allocate(new)
  allocate(new%obj)
  new%next  => node%next
  node%next => new
end subroutine list_add_hard_after

function list_add_soft_head(node, obj) result(new)
!Insert a new head before node
!On output, node is the new head
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  new%obj  =>  obj
  new%next => node
end function list_add_soft_head
    
function list_add_hard_head(node, obj) result(new)
!Insert a new head before node
!On output, node is the new head
  class(_NODE),target       :: node
  _TYPE, target, intent(in) :: obj
  type(_NODE), pointer      :: new

  allocate(new)
  allocate(new%obj,source=obj)
  new%next => node
end function list_add_hard_head

subroutine list_del_soft_after( head, node )
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

end subroutine list_del_soft_after
 
subroutine list_del_hard_after( head, node )
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

end subroutine list_del_hard_after
 
#ifdef _ALLOCATABLE
#undef _ALLOCATABLE
#endif
