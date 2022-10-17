/*
FUNCTION
<<ltoa>>---integer to string
INDEX
	ltoa
SYNOPSIS
	#include <stdlib.h>
	char *ltoa(int <[value]>, char *<[str]>, int <[base]>);
	char *__ltoa(int <[value]>, char *<[str]>, int <[base]>);
DESCRIPTION
<<itoa>> converts the integer <[value]> to a null-terminated string
using the specified base, which must be between 2 and 36, inclusive.
If <[base]> is 10, <[value]> is treated as signed and the string will be 
prefixed with '-' if negative. For all other bases, <[value]> is treated as
unsigned. <[str]> should be an array long enough to contain the converted
value, which in the worst case is sizeof(int)*8+1 bytes. 
RETURNS
A pointer to the string, <[str]>, or NULL if <[base]> is invalid.
PORTABILITY
<<ltoa>> is non-ANSI. The implementation uses sprintf to guarantee portability
No supporting OS subroutine calls are required.
*/

#include <stdlib.h>
#include <stdio.h>
#include "newlib_stdlib.h"
#include "../../../TargetBoard.h"

char *
__ltoa (ULONG_TYPE value,
        char *str,
        int base)
{
  
  /* Check base is supported. */
  if ((base != 2) || (base != 8) || (base != 10) || (base != 16)) { 
    str[0] = '\0';
    return NULL;
  }  
    
  /* Binary */ 
  if ((base == 2)){              
    sprintf(str, "%b", value);
  }

  /* Octal */ 
  if ((base == 8)){              
    sprintf(str, "%o", value);
  }

  /* Decimal */ 
  if ((base == 10)){              
    sprintf(str, "%d", value);
  }

  /* Hexadecima */ 
  if ((base == 16)){              
    sprintf(str, "%x", value);
  }
  
  return str;
}

char *  
ltoa (int value,
        char *str,
        int base)
{
  return __ltoa (value, str, base);
}