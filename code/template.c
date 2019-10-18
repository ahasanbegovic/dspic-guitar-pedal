const char CS_PIN = 1;
const char LD_PIN = 2;
const char AN10_PIN = 10;
const char RB8_PIN = 8;
const char IF_PIN = 0;


void ADC_Init_manual(){
     ADPCFG = 0;
     ADCON1 = 0x0004;
     ADCHS = 0x000A;
     ADCSSL = 0; //No scan
     ADCON3 = 0x0F00; //TAD = internalTCY
     ADCON3 = 0x1003; //ADCS=5 (min TAD for 10MHz is 3*TCY=300ns)
     ADCON2 = 0;
     ADCON1.F15 = 1;
     ADCON1.F9 = 1;
     ADCON1.F8 = 0; // Unsigned fractional
}

int ADC_Read_manual(unsigned int channel){
     ADCHS = channel;
     ADCON1.F1 = 0; //Clear SAMP bit (trigger conversion)
     while(ADCON1.F1 == 0) {
         asm nop; //Wait for DONE bit in ADCON1
     }
     return ADCBUF0;
}

void InitMain() {
    int i;
    for(i = 0; i < max_buffer_size; i++){
       delay_buffer[i] = 2048;
    }
    ADPCFG = 0xFBFF; //10th channel is sampled and coverted
    TRISB.AN10_PIN = 1;  // Set AN10 as input
    TRISB.RB8_PIN = 0;  // Set RB8 as output
    LATB.RB8_PIN = 0;
    //ADC1_Init();
    ADC_Init_Manual();

    // Spi2_Init(); // Initialize SPI2 module
    SPI2_Init_Advanced(_SPI_MASTER, // SPI in Master mode
                         _SPI_8_BIT, // 8-bit data
                         _SPI_PRESCALE_SEC_1, _SPI_PRESCALE_PRI_1, //prescaler = 1
                         _SPI_SS_DISABLE,
                         _SPI_DATA_SAMPLE_MIDDLE,
                         _SPI_CLK_IDLE_LOW,
                         _SPI_ACTIVE_2_IDLE //Falling edge
                        );

    TRISC.CS_PIN = 0; // Set CS pin as output
    TRISC.LD_PIN = 0; // Set LD pin as output


    T1IE_bit = 1;         //timer1
    IPC0 = IPC0 | 0x1000; //highest priority
    T1IF_bit = 0;         //first interrupt
    T1CON = 0x8000;       // Internal clock (20 Mhz), prescaler 1:1
    PR1= 226; // Period of Timer1 226 (interrupt every 22.6us, 44.1kHz sampling)
}//~


void DAC_Output(unsigned int valueDAC) {
    unsigned char temp;

    LATC.CS_PIN = 0; // Select DAC module
    LATC.LD_PIN = 0; // Enable data transfer



    // Send 2 bytes of valueDAC variable
    temp = (valueDAC >> 8) & 0x0F; // Prepare hi-byte for transfer
    // It's a 12-bit number, so only
    // lower nibble of high byte is used
    temp |= 0x30; // Set MCP4921 control bits
    Spi2_Write(temp); // Send data via SPI



    temp = valueDAC; // Prepare lo-byte for transfer
    Spi2_Write(temp); // Send data via SPI

    LATC.LD_PIN = 1; // Disable data transfer
    LATC.CS_PIN = 1; // Deselect DAC module
}//~

void Timer1Int() iv IVT_ADDR_T1INTERRUPT {
    int analog_data;
    int output_data;
    int pot_value;

    LATB.RB8_PIN = ~LATB.RB8_PIN;

    // Read pot_value from AN11
    pot_value = (ADC_Read_Manual(0x000B) >> 1) & 0xFFF0;
    if (pot_value > 16384){
       pot_value = 16384;
    }

    analog_data = ADC_Read_Manual(0x000A);

    ////
    // Calculate output_data as a function of analog_data and pot_value 
    output_data = analog_data;
    ////


    DAC_Output(((output_data) >> 4) & 0x0FFF); 

    T1IF_bit = 0;
}

void main() {
 InitMain();
 while (1);
}//~!

