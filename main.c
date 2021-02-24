/**********************************************************************
*
* © James D. Broesch, 2011, 2012, 2021
* 
* Template program for the C level FIR
* 
* A timer interrupt provides background functions.
*
* FileName:        main.c
* Dependencies:    Header (.h) files if applicable, see below
* Processor:       dsPIC33FJ256GP506
* Compiler:        MPLAB® C30 v3.00 or higher
*
************************************************************************/
#include <math.h>
#include <xc.h>

#include "WM8510CODEC.h"
#include "timer.h"
#include "dscInit.h"
#include "dma.h"

_FGS(GWRP_OFF & GCP_OFF);
_FOSCSEL(FNOSC_FRC);
_FOSC(FCKSM_CSECMD & OSCIOFNC_ON & POSCMD_NONE);
_FWDT(FWDTEN_OFF);

// Make varibles in other modules visibile in this one.
extern unsigned int timer1Count; // Not used in this module.
// Frame recieved interrupt flag.
extern unsigned int rxFlag; // Not used in this module.
extern unsigned int txFlag; // Not used in this module.

// Transmit and recieve buffers.
extern signed int txSignal;
extern signed int rxSignal;

// Working pointers. Use if you like.
extern signed int *pSignalRx; // Not used in this module.
extern signed int *pSignalTx; // Not used in this module.

#define FILTER_SIZE 61
short signed int signalBuffer[FILTER_SIZE];
short signed int coefficents[FILTER_SIZE]
 = {
        0xEDB6,
        0xEEE7,
        0xF258,
        0xF799,
        0xFE0C,
        0x04E6,
        0x0B4D,
        0x106C,
        0x1395,
        0x1446,
        0x124A,
        0x0DB8,
        0x06FC,
        0xFEC5,
        0xF5FE,
        0xEDB6,
        0xE70B,
        0xE2FC,
        0xE26C,
        0xE5EA,
        0xEDB6,
        0xF9B3,
        0x0958,
        0x1BC9,
        0x2FDF,
        0x443F,
        0x5776,
        0x6827,
        0x750E,
        0x7D35,
        0x7FFF,
        0x7D35,
        0x750E,
        0x6827,
        0x5776,
        0x443F,
        0x2FDF,
        0x1BC9,
        0x0958,
        0xF9B3,
        0xEDB6,
        0xE5EA,
        0xE26C,
        0xE2FC,
        0xE70B,
        0xEDB6,
        0xF5FE,
        0xFEC5,
        0x06FC,
        0x0DB8,
        0x124A,
        0x1446,
        0x1395,
        0x106C,
        0x0B4D,
        0x04E6,
        0xFE0C,
        0xF799,
        0xF258,
        0xEEE7,
        0xEDB6
};

int main(void)
{	
	signed long int filterSum;
	unsigned short int n;

	// Intialize the board and the drivers
	DSCInit();

	// Clear the working signal buffer.
	for (n = 0; n < FILTER_SIZE; n++) signalBuffer[n] = 0;

	// Initalize the CODEC.
	WM8510Init();
	// Start Audio input and output function
	WM8510Start();
		
	// Configure the CODEC for 8K operation	
	WM8510SampleRate8KConfig();

	// Use timer 1 as a real time clock.
	// 1 tick = 15,625 * 256 clock cycles = 100ms.
	timer1Init(15625);

	// Intialize and start the DMA channels.
	// Channel 0 moves data from the transmit buffers to the DCI.
	// Channel 1 moves data from the DCI to the recieve buffers.
	dmaInit();

	// Main processing loop.
	// Quit if switch 1 is pressed.
	while(SWITCH_S1)
		{
		if (rxFlag)
		{
		rxFlag = 0;
		if (SWITCH_S2)
		{
			txSignal = rxSignal;
		} else
		{
			
		// Your code goes here. 
					
		// Trap for timing errors.
		if (rxFlag)
			n = 0; // Set a break point here.
			
		}
		} 
		}

	// Disable the DMA Channels.
	DMA0CONbits.CHEN = 0;
	DMA1CONbits.CHEN = 0;

	// Stop the CODEC interface.
	WM8510Stop();

return(0); // Go home.
}
