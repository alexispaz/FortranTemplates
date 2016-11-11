! Defining some objects
module lion_class

public
type :: lion
  character(20) :: color
  contains
    procedure   :: printme=>printlion
end type

type, extends(lion) :: lionking
  character(20) :: name
  contains
    procedure   :: printme=>printlionking
end type    



! Creating a lion list
#define _NODE lion_list
#define _TYPE class(lion)
#define _SOFT
#include "list.inc"


subroutine printlion(l)
  class(lion)      :: l
  print *, 'simple lion ', l%color
end subroutine

subroutine printlionking(l)
  class(lionking)      :: l
  print *, l%name, l%color
end subroutine

end module lion_class
 
