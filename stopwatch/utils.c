#include <stdint.h>
/**
 *counts Digits in integer
 *
 * @return number of digits
 */
int countDigits(int c) {
  int counter = 0;
  do{
  	c /= 10;
  	++counter;
  }while (c != 0);
  
  return counter;
}

char * buffer;

/**
 *  counts Digits in integer
 *
 * @return number of digits
 
 */
 
char * cvr2string(uint32_t time, uint32_t reloadValue) {
	int digits = time/2;
	int digitsAfterPoint = time%2*50000000 + 25 * (2000000-reloadValue);
  int c= countDigits(digits) | 1;

  
  

  if( 0 == digits ) {
    buffer[0] = '0';
  }

  for(int i = n-1; i >= 0; i--) {
    buffer[i] = '0' + digits%10;
    digits /= 10;
  }
  

  buffer[c] = '.';

  for(int i = c+8; i > c; i--) {
    buffer[i] = '0' + digitsAfterPoint%10;
    digitsAfterPoint /= 10;
  }
  

  buffer[c+9] = '\n';
  buffer[c+10] = '\0';

  return buffer;
}

