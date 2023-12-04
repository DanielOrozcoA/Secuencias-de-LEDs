#INCLUDE <18f4550.h>
#FUSES NOPROTECT, NOWDT, NOLVP, HSPLL, PLL5, CPUDIV2
#USE delay(clock = 48M, crystal = 20M)

#BYTE TRISB = 0xF93
#BYTE PORTB = 0xF81

#BYTE TRISD = 0xF95
#BIT B1 = 0xF83.2
#BIT B2 = 0xF83.3
#BIT STOP = 0xF83.4
#BIT START = 0xF83.5

//Secuencias_LEDs
int Sec1[9] = {0x80,0xA0,0xA8,0xAA,0xAB,0xAF,0xBF,0xFF,0x00};
int Sec2[9] = {0x10,0x18,0x1C,0x1E,0x1F,0x3F,0x7F,0xFF,0x00};
int Sec3[9] = {0x80,0xC0,0xC8,0xCC,0xEC,0xFC,0xFE,0xFF,0x00};
int Sec4[9] = {0x01,0x03,0x07,0x0F,0x1F,0x3F,0x7F,0xFF,0x00};

void main(){

   //Boton_1_2_Banderas_1_2_3_4
   int PB1 = 0,PB2 = 0,Band1 = 0,Band2 = 0, Band3 = 0;
   int16 temp = 0;
   
   TRISB = 0x00;
   TRISD = 0xFF;
   
   PORTB = 0x00;
   
 //////////////////////////////////////  
   while(true){
      while(Band1 == 0){
         if(B1) PB1 = 1;
         else if(B2) PB2 = 1;
         else if(START) Band1 = 1;
      }
      Band1 = 0;
/////////////////Selector de secuencias
//////////////////////////////////////////////////////
      while(Band2 == 0){
      //Seleccion de secuencia 1
         if(PB1 == 0 && PB2 == 0){
            while(Band3 < 9){
               //Encencido de LED_X
               PORTB = Sec1[Band3];
               if(STOP) break;
               //Delay de 500 ms
               for(temp = 1;temp < 501;temp++){
                  delay_ms(1);
                  if(STOP){Band3 = 9; break;}
               }
               if(Band3 == 8) Band3 = 0;
               else Band3++;
            }
            //LEDs OFF_Reinicio de variables
            PORTB = 0x00; PB1 = 0; PB2 = 0; Band2 = 1;
         }
         //Seleccion de secuencia 2
         else if(PB1 == 1 && PB2 == 0){
            while(Band3 < 9){
               PORTB = Sec2[Band3];
               if(STOP) break;
               for(temp = 1;temp < 501;temp++){
                  delay_ms(1);
                  if(STOP){Band3 = 9; break;}
               }
               if(Band3 == 8) Band3 = 0;
               else Band3++;
            }
            PORTB = 0x00; PB1 = 0; PB2 = 0; Band2 = 1;
         }
         //Seleccion de secuencia 3
         else if(PB1 == 0 && PB2 == 1){
            while(Band3 < 9){
               PORTB = Sec3[Band3];
               if(STOP) break;
               for(temp = 1;temp < 501;temp++){
                  delay_ms(1);
                  if(STOP){Band3 = 9; break;}
               }
               if(Band3 == 8) Band3 = 0;
               else Band3++;
            }
            PORTB = 0x00; PB1 = 0; PB2 = 0; Band2 = 1;
         }
         //Seleccion de secuencia 4
         else{
           while(Band3 < 9){
               PORTB = Sec4[Band3];
               if(STOP) break;
               for(temp = 1;temp < 501;temp++){
                  delay_ms(1);
                  if(STOP){Band3 = 9; break;}
               }
               if(Band3 == 8) Band3 = 0;
               else Band3++;
            }
            PORTB = 0x00; PB1 = 0; PB2 = 0; Band2 = 1;
         }
      }
      Band2 = 0;
      Band3 = 0;
      //Reinicio de variables
   }
}
/////////////////////////////////Reproductor de secuencias
