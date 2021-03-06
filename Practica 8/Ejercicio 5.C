/*Realizar las modificaciones necesarias al ejercicio 2 de la pr�ctica tres para
  que ahora el comando que selecciona la acci�n sea a trav�s del puerto serie,
  usar retardos de � segundos, usando programaci�n en C.
     TECLA  |          ACCION
            |         Puerto B
-------------------------------------------
       0    |  Todos los bits
            |  del puerto apagados
-------------------------------------------
       1    |  Todos los bits del
            |  puerto encendidos
-------------------------------------------
       2    |  Corrimiento del bit
            |  m�s significativo hacia
            |  la derecha
-------------------------------------------
       3    |  Corrimiento del bit menos
            |  significativo hacia la
            |  izquierda
-------------------------------------------
       4    |  Corrimiento del bit m�s
            |  significativo hacia la
            |  derecha y a la izquierda
-------------------------------------------
       5    |  Apagar y encender todos
            |  los bits.                                                      */
            
#include <16f877.h>
#fuses HS,NOPROTECT,
#use delay(clock=20000000)
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7)
#org 0x1F00, 0x1FFF void loader16F877(void) {} //for the 8k 16F876/7
char dato;
int var, c = 0;
void main(){
   while(1){

      do {
         dato = getchar();
      } while(dato!='0' && dato!='1' && dato!='2' && dato!='3' && dato!='4' && dato!='5');

      if(dato == '0'){
         printf(" Todos los bits apagados \n\r");
         output_b(0x00);
      }

      if(dato == '1'){
         printf(" Todos los bits encendidos \n\r");
         output_b(0xFF);
      }

      if(dato == '2'){
         printf(" Corrimiento a la derecha \n\r");
         var = 0x80;
         c=0;
         do{
         	rotate_right(&var,1);
         	output_b(var);
         	delay_ms(1000);
            c++;
            if(c==10)
               break;
         }while(true);
      }

      if(dato == '3'){
         printf(" Corrimiento a la izquierda \n\r");
         var = 0x01;
         c=0;
         do{
         	rotate_left(&var,1);
	         output_b(var);
	         delay_ms(1000);
            c++;
            if(c==10)
               break;
         }while(true);
      }

      if(dato == '4'){
         printf(" Corrimiento a ambos lados \n\r");
         var = 0x80;
         c=0;
         while(true){      
            do{
            	rotate_right(&var,1);
            	output_b(var);
            	delay_ms(1000);
            }while(var!=0x01);
   
            do{
            	rotate_left(&var,1);
   	         output_b(var);
   	         delay_ms(1000);
            }while(var!=0x80);
            c++;
            if(c==10)
               break;  
         }
      }

      if(dato == '5'){
         printf(" Flasheo \n\r");
         c=0;
         while(true){
            output_b(0x00);
            delay_ms(1000);
            output_b(0xFF);
            delay_ms(1000);
            c++;
            if(c==10)
               break;
         }
      }
   }
}
