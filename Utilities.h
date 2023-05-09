#ifndef Utilities.h
#define Utilities.h

#define SET(reg,val)    reg|=val
#define CLR(reg,val)    reg&=~val
#define Read(reg,val)    reg&=val 

#endif