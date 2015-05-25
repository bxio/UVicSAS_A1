/*
 * test1.c
 *
 * Created: 16/05/2015 9:05:15 PM
 *  Author: Junnan Lu
 */


/*#include <avr/io.h>
#include <avr/interrupt.h>*/

#include "source.h"

#define P1_D0 PORTB = PORTB & (~(_BV(0)))
#define P1_D1 PORTB = PORTB | (_BV(0))

#define P2_D0 PORTB = PORTB & (~(_BV(1)))
#define P2_D1 PORTB = PORTB | (_BV(1))

#define P3_D0 PORTB = PORTB & (~(_BV(2)))
#define P3_D1 PORTB = PORTB | (_BV(2))

#define P4_D0 PORTB = PORTB & (~(_BV(3)))
#define P4_D1 PORTB = PORTB | (_BV(3))

#define P5_D0 PORTB = PORTB & (~(_BV(4)))
#define P5_D1 PORTB = PORTB | (_BV(4))

#define matchValue 2
#define paperValue 1
#define tobaccoValue 3

typedef enum {READY,RUNNING,SLEEP} Task_State;
typedef enum {SYS, PER, RND} Task_Level;

unsigned char forward[] = {0x89,0x00,0xF4,0x80,0x00};
unsigned char turn_left[] = {0x89,0x01,0x01,0x00,0x01};


typedef struct
{
	unsigned int stack_p;
	Task_State state;
	Task_Level level;
	int exeTime;
	int pid;
	int clock;
	int start;
	int started;
}task_struct;

typedef struct
{
	unsigned int stack_p;
	Task_State state;
	Task_Level level;
}sysTask;

task_struct Tasks[10];
task_struct RND_Task;
sysTask SYS_Task[10];
int counter;
int sysTaskNum;
int task_id;
int c_c;
int select;
int g_sp;
int getTaskSize;
int selected;
int tmp1;
int tmp2;
int match;
int paper;
int tobacco;
int sysSelect;
int sysSelected;
typedef void (*f)(void);
f FP;
unsigned int break_point;
unsigned char test[] = "A";
void go_forward(void);
void turn_around(void);
void send_cmd_232(unsigned char v);
void show_cursor1(char *v, int ss);
void show_cursor2(char *v, int ss);
void read_sig(void)
{
	if (PIA == 1)
	{
		turn_left();
	}
}



void initFork(void)
{
	fork1=1;
	fork2=1;
	fork3=1;
	fork4=1;
	fork5=1;
	sysTaskNum = 0;
	PORTA = 0b00011111;
}
void initsmoking(void)
{
	tmp1 = 0;
	tmp2 = 0;
	match=0;
	paper = 0;
	tobacco = 0;
	sysSelect = 0;
	sysSelected = 0;
}
void init_USART(void)
{
	UCSR0A = UCSR0A | (1<<U2X0);
	UBRR0 = 24;
	//UBRR0 = 143;
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	UCSR0C = (0<<USBS0) |(1<<UCSZ00) | (1<<UCSZ01);
}
void init_Roomba(void)
{
	while (!(UCSR0A & (1<<UDRE0)))
	{

	}
	UDR0 = 0x80;
	while (!(UCSR0A & (1<<UDRE0)))
	{

	}
	UDR0 = 0x82;
}



int main(void)
{
	c_c = 0;
	select = 0;
	selected = 0;
	g_sp = 16000;
	counter = 0;
	task_id = 0;
	PORTB = 0X00;
	DDRC = 0xFF;
	PORTC = 0X00;
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);

	init_USART();
	init_Roomba();
	init_lcd();
	for(;;)
	{
		go_forward();
		read_sig();
	}
}
