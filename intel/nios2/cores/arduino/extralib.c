#include "extralib.h"

/* A utility function to reverse a string  */
void reverse(char str[], int length) {
    int start = 0;
    int end = length -1;
    char temp;
    while (start < end) {
        temp = str[end];
        str[end] = str[start];
        str[start] = temp;
        
        start++;
        end--;
    }
}

//http://stackoverflow.com/questions/15685181/how-to-get-the-sign-mantissa-and-exponent-of-a-floating-point-number

//char *dtostrf(double val, signed char width, unsigned char prec, char *str) {
//	unsigned long long x = val;
//	unsigned int y  = (val * 10);
//	str[0] = (x%10) + '0';
//	str[1] = (y%10) + '0';
//	str[2] = '\0';
//	return str;	
//}
/* 
char *dtostrf(double val, signed char width, unsigned char prec, char *s) {
	sprintf(s,"%*.*f",width,prec,val);
	return s;
}
*/
/*
-12.3456789, %-8.2f, [-12.35  ]
-12.3456789, %8.2f   [  -12.35]
-12.345      %-16.8f [-12.34500027    ]
-12.345      %16.8f  [    -12.34500027]
-12.345E130 -16.8 [-123450000000000001334475683715793990475779772799327986582427863694743218186681442194800933096363941136660465710351930481894861307904.00000000]
-12.345E130 16.8  [-123450000000000001334475683715793990475779772799327986582427863694743218186681442194800933096363941136660465710351930481894861307904.00000000]
*/
char *dtostrf(double val, signed char width, unsigned char prec, char *str) {
	unsigned int valTop;
	double valRem;
	int rem;
	unsigned char strLen;
	int valInteger;
	
	int i = 0; /* keep track of integer processs so far */
	int diff;
	unsigned char rightAlign = 1; /* 0 if width is negative*/
	unsigned char negative = 0; /* 1 when val is nnegative*/
	
	/* max 9 digit */
	if( (val >= 1e9) || (val <= -1e9 ) ) {
		str[i++] = 'E';
		str[i++] = 'r';
		str[i++] = 'r';
		str[i++] = 'o';
		str[i++] = 'r';
		str[i++] = ':';
		str[i++] = 'd';
		str[i++] = 't';
		str[i++] = 'o';
		str[i++] = 's';
		str[i++] = 't';
		str[i++] = 'r';
		str[i++] = 'f';
		str[i++] = '(';
		str[i++] = ')';
		str[i++] = '\0';
		return str;
	}
	
	// handle width -128 using unsigned char?
	if(width<0) {
		width = -width;
		rightAlign = 0;
	}
	
	if(val < 0) {
		val = -val;
		negative = 1;
	}
	
	valTop = val;
	valRem = val - valTop;

	// assume left align first
	if(valTop == 0) {   
		str[i++] = '0';
	}
	// Process individual digits
	while (valTop != 0) {
		rem = valTop % 10;
		str[i++] = rem + '0';
		valTop = valTop/10;
	}
	
	if(negative) {
		str[i++] = '-';
	}
	
	/* reverse becasue -123.45 store as 321- in str */
	reverse(str, i); 
	
	// Always put '.' regardless of prec 
	str[i++] = '.';
	
	// process precision
	valInteger = 0;
	rem = 0;
	while (prec != 0)
	{
		valRem = (valRem - rem) * 10;
		int valInteger = valRem;
		rem = valInteger % 10;
		str[i++] = rem + '0';
		prec = prec - 1;
	}
	strLen = i;
	
	
	if(strLen >= width) {
		str[i] = '\0'; /* Append string terminator */
		return str; /* and return since exceed minimum width */
	}
	
	/* pad with space if less than minimum width */
	diff = width - strLen;
	
	/* adjust  & pad for rigth align */
	if(rightAlign) {
		for(i = (width-1); i>=(width-strLen); i--) {
			str[i] = str[i-diff];
		}
		for(;i>=0;i--) {
			str[i] = ' ';
		}
	} else {
		for(;i<width;i++) {
			str[i] = ' ';
		}
	}
	str[width] = '\0';	
	return str;
}
 
// Implementation of itoa()
char *itoa(int num, char* str, int base) {
    // negative numbers are handled only with base 10.
    // Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
    	str[0] = '-';
	ultoa(-num, (char *)(str+1),base);
    } else {
	ultoa(num, str, base);
    	    
    }
    return str;
}

char *ltoa(long num, char *str, int base) {
    // negative numbers are handled only with base 10.
    // Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
    	str[0] = '-';
	ultoa(-num, (char *)(str+1), base);
    } else {
	ultoa(num, str, base);
    	    
    }
    return str;
}

char *utoa(unsigned int num, char *str, int base) {
    return ultoa(num, str,base);
}

char *ultoa(unsigned long num, char *str, int base) {
    int i = 0;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    str[i] = '\0'; // Append string terminator
 
    // Reverse the string
    reverse(str, i);
 
    return str;
}








