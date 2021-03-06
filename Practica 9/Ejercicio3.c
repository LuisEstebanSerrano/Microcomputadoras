/*  Realizar un programa el cual constantemente transmita el resultado de la conversi�n a la
    terminal, y cada 30 segundos interrumpa la ejecuci�n de este y env�e un mensaje */
#include <16f877.h>
#device ADC=10
#fuses HS,NOPROTECT,
#use delay(clock=20000000)
//Configuraci�n Puerto SERIAL
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#org 0x1F00, 0x1FFF

void loader16F877(void) {}

long var;
int16 contador=0;

#int_rtcc

clock_isr(){
   contador++;
   if(contador==2310){
     printf("\nPONGANOS 10 POR FAVOR\n");
     contador=0;
   }
}

void main(){
     setup_port_a(ALL_ANALOG);                       // Configura PORTA como anal�gico
     setup_adc(ADC_CLOCK_INTERNAL);                  // Relog interno de Conv. A/D
     set_adc_channel(0);                             // Selecci�n del Canal 0
     set_timer0(0);                                  // Inicia el timer0 en 00H
     setup_counters(RTCC_INTERNAL,RTCC_DIV_256);
     enable_interrupts(INT_RTCC);                    // Habilita la interrupci�n TIMER0
     enable_interrupts(GLOBAL);                      // Habilita interrupciones generales
	 
     while(1){
        delay_us(20);                                // Retardo 
        var=read_adc();                              // Resultado de la Conversi�n
        delay_us(20);
        
        printf(" voltaje =%lu [dec], %LX [hex], %2f[v]\n\r ",var,var,(var*0.0196)); 
        delay_ms(100);    //Retardo
     }
}
