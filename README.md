# FortranTemplates

Here I present my way to implement Fortran templates to create dynamic data
structures using preprocessor directives.

Since the list may use a final procedure to destroy the object when deallocation
is needed, gfortran v5.0 or grater may be needed.

This code is hosted in [github](https://github.com/alexispaz/FortranTemplates).
An example of use can be found in `main.F90`.

## Polymorphic linked list template.

Invoke this template in a module like this:

    module name
    
      ... ! module declarations
    
      #declare _NODE integer_list
      #declare _TYPE integer
      #include list_header.inc
    
      ... ! module declarations
    
    contains
    
      ... ! procedures
    
      #declare _NODE integer_list
      #declare _TYPE integer
      #include list_body.inc
    
      ... ! procedures
    
    end module
        
where integer is just an example. Any other type or object can be used. A
common way to iterate the list might be:

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

If the node object require deallocation prior to elimination the option
`_ALLOCATABLE` must be defined prior to include `list_body.inc`.
If the object is a user type defined, this type should have declared a final
procedure.


## Polymorphic double linked list template.

Double linked list allows to insert a new node before the current
one. Invoke this template in a module like this:

    module name
    
      ... ! module declarations
    
      #declare _NODE integer_list
      #declare _TYPE integer
      #include dlist_header.inc
    
      ... ! module declarations
    
    contains
    
      ... ! procedures
    
      #declare _NODE integer_list
      #declare _TYPE integer
      #include dlist_body.inc
    
      ... ! procedures
    
    end module !or program
        
where integer is just an example. Any other type or object can be used. See
`list_body` or `list_head` for examples of forward list iteration.

