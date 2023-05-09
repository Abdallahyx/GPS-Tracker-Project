#ifndef UART.h
#define UART.h
#include <stdbool.h>  //as there is no boolean type in C


// intialization of UART5(PORTE)
void intUARTE();
// if it returns 0 it means FIFO is empty and vice versa
 bool UARTR_Ready();
	//return data written in UART Data R(1byte=8 bits)
 char UART_Read();
 // send data (1byte=8 bits)
 bool UARTT_Ready();
 //fIGO is empty and we will begin writing on it
 void UARTT_Write( char data);
 
 #endif