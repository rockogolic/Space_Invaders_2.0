
// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.



#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here

#include <iostream>

#include <random>

#include <vector>

#endif //PCH_H

/*
NOTE to SELF: 

* pragma once and ifndef - define; endif are the same algorithms for compiling the header file only once!
Although, the pragma once is quite risky for multiplatforming, as it can not be supported in all the cases.
That is why ifndef define endif is a more reliable and universal tool to use!

* internal include guard: 
- inside the header file -> ifndef NAME_H define NAME_H ednif

* external include guard:
- outside of the name.h header file, in some other header file -> Consider SNAME_H -> 
-> ifndef SNAME_H define SNAME_H ... ifndef NAME_H include "name.h" endif ... endif // SNAME_H


*/
