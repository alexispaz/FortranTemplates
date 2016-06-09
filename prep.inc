! Declaring preprocessor functions
#ifdef __GFORTRAN__
#define _IDENTITY(x) x
#define _PASTE(a,b) _IDENTITY(a)_IDENTITY(b)
#define _STR(name) "name"
#else
#define _PASTE(a,b) a ## b
#define _STR(name) #name
#endif
      
