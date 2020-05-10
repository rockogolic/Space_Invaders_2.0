
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
