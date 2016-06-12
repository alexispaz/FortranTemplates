! Defining some objects
module lion_class

public
type :: lion
  character(20) :: color
end type
type, extends(lion) :: lionking
  character(20) :: name
end type    

! Creating a lion list
#define _NODE lion_list
#define _TYPE class(lion)
#define _SOFT
#include "list.inc"

end module lion_class
 
