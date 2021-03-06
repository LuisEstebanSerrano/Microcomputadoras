/* Utilizando la interrupción del TIMER0, realizar un programa que transmita el resultado
   de la conversión cada 10 segundos.*/
#include <16f877.h>
#device ADC=10
#fuses HS,NOPROTECT,
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#org 0x1F00, 0x1FFF

void loader16F877(void) {}

long var;
int16 contador=0;

#int_rtcc

clock_isr(){                        // Rutina de interrupcion por Timer0
    contador++;                     // Incrementa contador
    if(contador==770){
       output_b(var);               //Se muestra  resultado como salida

       printf(" voltaje =%lu [dec], %LX [hex], %2f[v]\n\r ",var,var,(var*0.0196));
       contador=0;                  // Inicializa contador, se reinicia
    }
}
void main(){
    //Configuración del Puerto A como analógico
    setup_port_a(ALL_ANALOG);
    //Configuración del reloj interno ADC
    setup_adc(ADC_CLOCK_INTERNAL);
    set_adc_channel(0);             //Configuración del Canal 0

    set_timer0(0);

    setup_counters(RTCC_INTERNAL,RTCC_DIV_256);

    enable_interrupts(INT_RTCC);    // Habilita la interrupción TIMER0
    enable_interrupts(GLOBAL);      // Habilita interrupciones generales

    while(1){                       // Ciclo while infinito
        delay_us(20);               // Retardo de 20us (microsegundos)
        var=read_adc();             // Resultado=valor de ADC
        delay_us(20);               // Retardo de 20us (microsegundos)
    }
}
