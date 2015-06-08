/*
@author:        Walter Gonzalez Domenzain
@description:   8020 Group
@functions:     None
@environment:   KL25Z
@date:          27/05/2015
@comments:
- Board red led 	connected to B18 	(turns on with 0) 
- Board green led 	connected to B19 	(turns on with 0) 
- Board blue led 	connected to D1  	(turns on with 0) 
- Push button 1 	connected to B3		(sends 0 when pressed)      
@version:       1.0 - Initial
*/
 
#include "derivative.h" 
//Ports
#define setPortB(x) 	(GPIOB_PDOR |= (1 << x))
#define clearPortB(x) 	(GPIOB_PDOR &= ~(1 << x))
#define setPortD(x) 	(GPIOD_PDOR |= (1 << x))
#define clearPortD(x) 	(GPIOD_PDOR &= ~(1 << x))

#define readPortB(x)	((GPIOB_PDIR &= (1 << x)) >> x)
#define	nButtonPressed  0
#define	nButtonFree     1 

#define btn1			3

//Leds
#define turnOnRedLed	clearPortB(18)
#define turnOffRedLed	setPortB(18)
#define turnOnGreenLed	clearPortB(19)
#define turnOffGreenLed	setPortB(19)
#define turnOnBlueLed	clearPortD(1)
#define turnOffBlueLed	setPortD(1)

//Time
#define	n1sec			2000000  
#define	n2sec			4000000
#define	n500ms			1000000  
//--------------------------------------------------------------
//Declare Prototypes
void cfgPorts(void);
void delay(long ltime);
             
int main(void)
{	
	cfgPorts();	
	
	turnOffGreenLed;
	turnOffRedLed;
	turnOffBlueLed;
	
	for(;;)
	{
	if(readPortB(btn1) == 1)
	{
	for(;;)
    {
		//if((GPIOB_PDIR & 0x00000008) == 0)
			
		if(readPortB(btn1) == 0)
		{
			turnOnGreenLed;
			turnOffRedLed;
			turnOffBlueLed;
		}
		
		else
		{
			turnOnRedLed;
			turnOffGreenLed;
			turnOffBlueLed;
		}
    }
		
	}	
		
    } 
    return 0;
}
 //--------------------------------------------------------------
void cfgPorts(void)
{
    //Turn on clock for portb and portd
    SIM_SCGC5 = SIM_SCGC5_PORTB_MASK;
    SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;   
     
    /* Set pins of PORTB as GPIO */
    PORTB_PCR3 	= PORT_PCR_MUX(1);
	PORTB_PCR18 = PORT_PCR_MUX(1);
    PORTB_PCR19 = PORT_PCR_MUX(1);
	PORTD_PCR1 	= PORT_PCR_MUX(1);
     
    //Configure all PortB as outputs
    GPIOB_PDDR = 0xFFFFFFF7; //1111 1111 1111 1111 1111 1111 1111 0111
     
    //Configure all PortD as outputs
    GPIOD_PDDR = 0xFFFFFFFF;
}
//--------------------------------------------------------------
