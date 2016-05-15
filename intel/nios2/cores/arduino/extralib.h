#ifndef __EXTRALIB__
#define __EXTRALIB__

#include<stdio.h>



#ifdef __cplusplus
extern "C"{
#endif

#ifndef PGM_P
#define PGM_P const char *
#endif
 
extern char *dtostrf(double val, signed char width, unsigned char prec, char *s);
extern char *itoa(int num, char* str, int base);

extern char *ltoa(long num, char *str, int base);
extern char *ultoa(unsigned long num, char *str, int base);
extern char *utoa(unsigned int num, char *str, int base);

#define strcpy_P(aa, bb) strcpy(aa, bb)
#define strlen_P(aa) strlen(aa)


#ifdef __cplusplus
}
#endif

#endif
