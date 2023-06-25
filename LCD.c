#include <SI_EFM8BB1_Register_Enums.h>

//Initialize my device
void InitDevice(void)
{
	//Disable Watchdog Timer
	//Disable Watchdog with key sequence
	WDTCN = 0xDE; //First key
	WDTCN = 0xAD; //Second key
	// [WDTCN – Watchdog Timer Control]$

	//Setup Defaults for P1
	P1MDOUT = P1MDOUT_B0__OPEN_DRAIN | P1MDOUT_B1__OPEN_DRAIN
	| P1MDOUT_B2__OPEN_DRAIN | P1MDOUT_B3__OPEN_DRAIN
	| P1MDOUT_B4__PUSH_PULL | P1MDOUT_B5__OPEN_DRAIN
	| P1MDOUT_B6__OPEN_DRAIN | P1MDOUT_B7__OPEN_DRAIN;

	//Enable Weak Pullups
	XBR2 = XBR2_WEAKPUD__PULL_UPS_ENABLED | XBR2_XBARE__ENABLED;

	//Disable Interrupts
	IE = IE_EA__DISABLED | IE_EX0__DISABLED | IE_EX1__DISABLED
	| IE_ESPI0__DISABLED | IE_ET0__DISABLED | IE_ET1__DISABLED
	| IE_ET2__ENABLED | IE_ES0__DISABLED;
}
//delay function
void delay (void){
	unsigned char a, b;
	for(a=0; a<0xFF; a++){
		for(b=0; b<0x70; b++){
		}
	}
}
//datawrite function
void LCD_Data_Write (unsigned char x){
	P1 = P1|(0x01); //RS = 1
	P1 = P1 &~ (0x01<<1); //RW = 0
	P0 = x;
	P1 = P1|(0x01<<2); //E = 1
	delay();
	P1 = P1 &~ (0x01<<2); //E = 0
}
//commanderite function
void LCD_Command_Write (unsigned char y){
	P1 = P1 &~ (0x01); //RS = 0
	P1 = P1 &~ (0x01<<1); //RW = 0
	P0 = y;
	P1 = P1|(0x01<<2); //E = 1
	delay();
	P1 = P1 &~ (0x01<<2); //E = 0
}
//main function
void main (void){
	while(1){
		InitDevice(); //call Initialization
		LCD_Command_Write(0x38); //8bit interface, 2 lines, 5x7 font
		LCD_Command_Write(0x0E); //autoincrement, no display shift
		LCD_Command_Write(0x01); //display on, cursor on, no blinking
		LCD_Command_Write(0x06); //clear display, set cursor to 0
		
		LCD_Data_Write(0x45); //E  ASCII hex from table
		LCD_Data_Write(0x56); //V           ^
		LCD_Data_Write(0x45); //E           ^
		LCD_Data_Write(0x52); //R           ^
		LCD_Data_Write(0x41); //A           ^
		LCD_Data_Write(0x52); //R           ^
		LCD_Data_Write(0x44); //D           ^
		LCD_Data_Write(0x4F); //O           ^
	}
}