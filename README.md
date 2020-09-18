# Fortran Preprocesor Templates for Dynamic Data Strctures (FPT-DDS)

Here I present my way to implement _fortran templates_ to create **dynamic data
structures using preprocessor directives**.

A data structure for an arbitrary data type can be easily constructed by
defining a few preprocessor variables and including the corresponding files
distributed in the `include` folder as it is shown in [the simple example
below](#-A-simple-example).

Another examples of use can be found in the `src` folder. To compile this
example just type:

    ./configure
    make

# A simple example

To compile the following example, do not forget to add
`-I$(path_to_include_files)` and use `.F90` extension to activate preprocesing.

    module intrinsic_class

    ! Here we declare the type of the dynamic data structure (DDS)
    ! 1. _NODE define the name of the data type of the DDS
    ! 2. _CLASS or _TYPE is the data type of the objects handle by the DDS. 
    !   If the DDS use _CLASS, it can be polymorphic. If not, it use _TYPE
    ! 3. include file name allow to select between the different DDS, e.g linked list, double linked list, etc. 
    #define _NODE integer_dlist
    #define _CLASS integer
    #include "dlist_header.inc"

    contains

    ! Here we declare the procedures of the new integer_dlist DDS.
    ! Definition should match the one used in the header
    #define _NODE integer_dlist
    #define _CLASS integer
    #include "dlist_body.inc"

    end module intrinsic_class


    program example
    use intrinsic_class
    type(integer_dlist),target		:: rlist
    type(integer_dlist),pointer		:: ptr
    integer,target                :: i
    integer                       :: j

    i=3

    ! Add first item as a `hard node` (i.e. allocated in the list)
    ! rlist: head -> 2  
    call rlist%add_hardcpy(2)

    ! Add second item as another hard node
    ! rlist: head -> 3 -> 2  
    call rlist%add_hardcpy(i)

    ! Add third item as a `soft node` (i.e. allcoated elswhere)  
    ! rlist: head -> o -> 3 -> 2   with o -> i
    call rlist%add_soft(i)

    ! Print the list (output: 3 3 2)
    ptr=>rlist
    do j=1,3
      ptr=>ptr%next
      print *, ptr%o
    end do  

    ! Change the target of the first node
    i=4

    ! Print the list (output: 4 3 2)
    ptr=>rlist
    do j=1,3
      ptr=>ptr%next
      print *, ptr%o
    end do  
     
    end program example


# Supported Dynamic Data Strctures

## Linked list template (LL, polymorphic)

      #declare _NODE <LL type>
      #declare _CLASS <data type>
      #include list_header.inc

Any other type or object can be used. A common way to iterate might be:

    type(_NODE),pointer   :: list
    class(_NODE),pointer  :: node
   
    node => a
    do while(associated(node))
      ... !work with node%obj ("cycle" do not advance the node)
      node => node%next
    enddo

"cycle" fortran keyword might be wanted to advance the node. For that case it
is possible to leave the first node of the list empty to allow this kind of
iteration:
  
    node => a
    do while(associated(node%next))
      node => node%next
      ... !work with node%obj ("cycle" advance the list)   
    enddo

If the node object require deallocation and the object is a user type defined,
this type should have declared a final procedure or be destroy prior too
destroy the node.


## Double linked list template (DLL, polymorphic).

      #declare _NODE integer_list
      #declare _CLASS integer
      #include dlist_header.inc
    
      ... ! module declarations
    
    contains
    
      ... ! procedures
    
      #declare _NODE integer_list
      #declare _CLASS integer
      #include dlist_body.inc
    
      ... ! procedures
    
    end module !or program

where integer is just an example. Any other type or object can be used. See
`list_body` or `list_head` for examples of forward list iteration.
 

## Circular double linked list template (CDLL, polymorphic).

CDLL might not have any particular head. However it is needed to keep a total
count of the items to avoid infinit loops. Leaving the first node with a null
obj might be a way to avoid traking the number of items. In respect to DLL,
CDLL simplify the procedures of adding and removing nodes avoiding the
association testings needed for the beginning and final nodes of a DL. On the
other hand, CDLL requires a constructor.  See `list_head.inc` for information
in how to use the template.


# LICENSE

Fortran Preprocesor Templates for Dynamic Data Strctures (FPT-DDS) is hosted
in [github](https://github.com/alexispaz/FortranTemplates) with a BSD 3-Clause License. 

