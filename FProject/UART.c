#include"tm4c123gh6pm.h"
#include <stdbool.h>  //as there is no boolean type in C
#include "UART.h"
#include "Utilities.h"
// intialization of UART5(PORTE)
  void intUARTE(){
	SET(SYSCTL_RCGCUART_R,0x20);  //activate UART5
	SET(SYSCTL_RCGCGPIO_R,0x10);  // activate PORTE
	while (Read(SYSCTL_PRGPIO_R ,0x10)==0){};  //delay until PORTE is activated
	SET (UART5_CTL_R ,(UART5_CTL_R & 0xFFFFFF00)+0x00000011);  //disable the UART and enable TX&RX
	UART5_IBRD_R =208;   // assuming MC 16 MHZ & baud rate 9600 
	UART5_FBRD_R =21;
	UART5_LCRH_R= 0x70;  //enable FIFO & setting data in 8bits
	SET (UART5_CTL_R,0x301);  // enable UART
	GPIO_PORTE_LOCK_R =0x4C4F434B;
	SET (GPIO_PORTE_CR_R,0x30);  // enable change in pin 4&5
	SET(GPIO_PORTE_AMSEL_R,0x30);  // disable  analog mode for pins 4&5
	SET(GPIO_PORTE_AFSEL_R ,0x30);  //enable alternate fun. for pins 4&5
	SET(GPIO_PORTE_PCTL_R,0x00110000);  // enable UART in PORTE
	SET(GPIO_PORTE_DEN_R,0x30);  //enable digital ll pins 4&5
	SET(GPIO_PORTE_DIR_R,0x0E);  // ana sara7a m4 3arfa 23ml fyha eh 3mltha zy GPIO 3ade
	SET(GPIO_PORTE_PUR_R,0x11);
}
	//check if we can receive data ( whether FIFO fy RX empty or full)
  // if it returns 0 it means FIFO is empty and vice versa
 bool UARTR_Ready(){
	 return(Read(UART5_FR_R,0x10)==0) ? 1:0;
}
  //return data written in UART Data R(1byte=8 bits)
 char UART_Read(){
	 while((UARTR_Ready()!=1));
		 return (char)(Read(UART5_DR_R,0xFF));	 
	// else 3ayza 23ml 7aga t2ol 2no fady 2w action mfrod yta5d msln lsa m4 3arfa
	// mo3yda 3mla else y3ml delay by while bs bd2a code by while b2a
	// lono 27mr 34an lw md5l4 while hyrg3 eh? mfy4 return sa3tha
 }
 // send data (1byte=8 bits)
 bool UARTT_Ready(){
	  return(Read(UART5_FR_R,0x20)==0) ? 1:0;
 }
 
//fIGO is empty and we will begin writing on it
 void UARTT_Write( char data){
	 if ( UARTT_Ready()==1)
		 UART5_DR_R=data;
 } 
 