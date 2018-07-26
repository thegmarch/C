volatile unsigned char *myADCSRA = (volatile unsigned char *) 0x7A; // ADC control & status register A 
volatile unsigned char *myADCSRB = (volatile unsigned char *) 0x7B; // ADC conterol & status register B
volatile unsigned char *myADMUX= (volatile unsigned char *) 0x7C;   // ADC multiplexer selection register
volatile unsigned char *myDIDR0 = (volatile unsigned char *) 0x73;  // Digital input disable register 0
volatile unsigned char *portADCDataRegisterHigh = (volatile unsigned char*) 0x79; // High order bits stored in ADC Data Register 
                                                                                  //needed because data is left justified


                                                                                  
//Port K: Controlling LEDS                                                                                  
volatile unsigned short int* portK = (unsigned short int*) 0x108; // Port K output
volatile unsigned short int* portDDRK = (unsigned short int*) 0x107; // Port K data direction register

//Port B: Analog In
unsigned char *portDDRB = (unsigned char *) 0x24;
unsigned char *portB = (unsigned char *) 0x25;

void initADC(); 
void MyDelay(unsigned long mSecondApx);
void cycleSevSeg();



//LED Segment Array
volatile unsigned char segmentArray[] = 
    {
      0x3F, //disp 0  
      0x06, //disp 1 
      0x5B, //disp 2
      0x4F, //disp 3
      0x66, //disp 4
      0x6D, //disp 5
      0x7C, //disp 6 
      0x07, //disp 7
      0x7F, //disp 8
      0x67, //disp 9
      0x77, //disp A
      0x7C, //disp b
      0x39, //disp C
      0x5E, //disp d
      0x79, //disp E
      0x71  //disp F
    };

void setup() 
{
  // put your setup code here, to run once:

  //configure PortK as output on Arduino
  *portDDRK = (*portDDRK | 0xFF);
  
  *portDDRB = ( *portDDRB | 0x80);
  
   
   //congfigure Analog-to-Digital 
   initADC(); 
}

void loop() 
{
  // put your main code here, to run repeatedly:
  cycleSevSeg();
} 

void initADC()
{
  // Initialize details:
  // pre-scale division of 16
  // use the internal 5V V_ref
  // use right justification
  // use ADC channel 5

  *myADCSRA = (*myADCSRA & 0xA4); // enable ADC, enable auto-trigger, pre-scaler set to 16
  *myADCSRB = (*myADCSRB & 0x00); // free running mode 
  *myADMUX = (*myADMUX & 0xE0); // reserved voltage set, left justified, Channel 5 activated
  *myDIDR0 = (*myDIDR0 & 0xDF); // disable unused ADC pins (enable ADC0)
  
}

void cycleSevSeg()
{
 
  for(int i = 0; i < 16; i++)
  {
    //analog delay dependant of ADC Data Register
    unsigned char value = *portADCDataRegisterHigh;
    
    unsigned char adcVal = ((value * 1024)/5); 

    
    *portK = (*portK | segmentArray[i]);
     myDelay(adcVal);
    *portK = (*portK & 0x00);
    
  }  
  
}

void myDelay(unsigned long mSecondsApx)
{
  volatile unsigned long i;
  unsigned long endTime = 1000 * mSecondsApx;

  //time loop
  for(i = 0; i < endTime; i++);
}




