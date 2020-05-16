
NOTE to SELF: 

* pragma once and ifndef - define; endif are the same algorithms for compiling the header file only once!
Although, the pragma once is quite risky for multiplatforming, as it can not be supported in all the cases.
That is why ifndef define endif is a more reliable and universal tool to use!

* internal include guard: 
- inside the header file -> ifndef NAME_H define NAME_H ednif

* external include guard:
- outside of the name.h header file, in some other header file -> Consider SNAME_H -> 
-> ifndef SNAME_H define SNAME_H ... ifndef NAME_H include "name.h" endif ... endif // SNAME_H


 NOTE to SELF:
1) break; in switch -> redundant
2) If we have a Vector2i (call it, vector) and we need Vector2f for a function -> we can cast integer to floats:
there are two ways to do that:
2.1) :C-STYLE CAST: unsafe and short -> (float)vector.x and (float)vector.y
2.2) :STATIC CAST: safe and long (safe for casting one class to another (?) ) -> static_cast<float>(vector.x) and (or, if only one), static_cast<float>(vector.y)


static Class members:
they are not initialized using constructor, as they are not dependent on object initialization. Hence, they are a class variable, and are the same for all objects of the 
same class!

FORWARD DECLARATION:
It is not a good practice to include both headers into each other. "To understand A, you must first understand B" and then "To understand B, you must first understand A"
To resolve the issue, one can use forward declaration.

The wrong:

//A.h    
#include "B.h"
class A{
    B* b;
    ..
};

//B.h
#include "A.h"
class B{ 
    A* a; // error error C4430: missing type specifier - int assumed.
};

The right way to resolve it:

//A.h    
#include "B.h"
class A{
    B* b;
    ..
};

//B.h
class A;  // forward declaration
class B{ 
    A* a; // error error C4430: missing type specifier - int assumed.
};