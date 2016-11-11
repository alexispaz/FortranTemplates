! Defining some objects
module lion_class

public
type :: lion
  character(20) :: color
  contains
    procedure   :: printme=>printlion
    ! final       :: free_lion
end type

type, extends(lion) :: lionking
  character(20) :: name
  contains
    procedure   :: printme=>printlionking
    ! final       :: free_lionking
end type    



! Creating a lion list
#define _NODE lion_list
#define _TYPE class(lion)
#include "list_header.inc"

contains

! Procedures of a lion list
#define _NODE lion_list
#define _TYPE class(lion)
#include "list_body.inc"

subroutine printlion(l)
  class(lion)      :: l
  print *, 'simple lion ', l%color
end subroutine

subroutine printlionking(l)
  class(lionking)      :: l
  print *, l%name, l%color
end subroutine

! subroutine free_lionking(l)
!   type(lionking)      :: l
! end subroutine
!  
! subroutine free_lion(l)
!   type(lion)      :: l
! end subroutine

end module lion_class
 
