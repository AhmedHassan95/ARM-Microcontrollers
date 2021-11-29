#include "UART.h"

//---------------------Convert-------------------------------
// Convert a 12-bit binary ADC sample into a 32-bit unsigned
// fixed-point distance (resolution 0.001 cm).  Calibration
// data is gathered using known distances and reading the
// ADC value measured on PE1.  
// Overflow and dropout should be considered 
// Input: sample  12-bit ADC sample
// Output: 32-bit distance (resolution 0.001cm)
unsigned long Convert(unsigned long sample)
{
  return ((500 * sample) >>10) + 1; 
}

//-----------------------UART_ConvertDistance-----------------
// Converts a 32-bit distance into an ASCII string
// Input: 32-bit number to be converted (resolution 0.001cm)
// Output: store the conversion in global variable String[10]
// Fixed format 1 digit, point, 3 digits, space, units, null termination
// Examples
//    4 to "0.004 cm"  
//   31 to "0.031 cm" 
//  102 to "0.102 cm" 
// 2210 to "2.210 cm"
//10000 to "*.*** cm"  any value larger than 9999 converted to "*.*** cm"
void UART_ConvertDistance(unsigned long n)
{
	// as part of Lab 11 implement this function
  
	unsigned long d = 0;
	
	if(n >= 10000)
	{
		String[0] = '*';
		String[1] = '.';
		String[2] = '*';
		String[3] = '*';
		String[4] = '*';
	}
	else
	{
			d = n / 1000;
			String[0] = d + 0x30;
			
			String[1] = '.';
		
			n = n % 1000;
			d = n / 100;
			String[2] = d + 0x30;
			
			n = n % 100;
			d = n / 10;
			String[3] = d + 0x30;
			
			n = n % 10;
			String[4] = n + 0x30;
			
	}
	String[5] = ' ';
	String[6] = 'c';
	String[7] = 'm';
	String[8] = '\0';	/* Null terminator */
}
