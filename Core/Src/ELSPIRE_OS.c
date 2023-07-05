/*
  ******************************************************************************
  * @file    ELSPIRE_OS.c
  * @version 1.0
  * @author  Agapov Aleksandr
  * @brief   Task Manager.
  *          This file provides firmware functions to manage the following
  * 			operating system kernel
  * 			timing function
  * 			function start and stop tasks
  * 			function to put the task to sleep
  * 			delay function
  *
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020 Agapov Aleksandr.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
*/

/* Includes ------------------------------------------------------------------*/
#include "ELSPIRE_OS.h"

/* Private function prototypes -----------------------------------------------*/
void ELSPIRE_OS_KERNEL(void);
void ELSPIRE_OS_TIMER(void);
void sleep(unsigned int ms);
void Task_STOP(unsigned char task_num);
void Task_RUN(unsigned char task_num, unsigned int del);
void delay_ms(unsigned int ms);
void TaskAsigner(void (*f)(void), unsigned char num);

/* Private variables ---------------------------------------------------------*/
unsigned int tasks_timer[num_of_tasks];
unsigned char current_task = 0;
unsigned int delay_count = 0;
void (*task[num_of_tasks])(void);
struct ElspireOS ELSPIRE = {ELSPIRE_OS_KERNEL, ELSPIRE_OS_TIMER, sleep, Task_STOP, Task_RUN, delay_ms, TaskAsigner};

/* Task manager --------------------------------------------------------------*/
void ELSPIRE_OS_KERNEL(void)
{
	while(1)
	{
		MX_TouchGFX_Process();
		if(!tasks_timer[current_task])task[current_task]();
		if(++current_task==num_of_tasks)
		{
			// You can add sleep MCU function here
			current_task=0;
		}
	}
}

/* Timing function ------------------------------------------------------------*/
void ELSPIRE_OS_TIMER(void)
{
	unsigned char i = 0;
	for(i=0;i<num_of_tasks;i++)
	{
		if(tasks_timer[i]>0)
		{
			if(tasks_timer[i]!=0xFFFF) tasks_timer[i]--;
		}
	}
	if (delay_count > 0)
	{ delay_count--; }
}

/* Sleep function -------------------------------------------------------------*/
void sleep(unsigned int ms)
{
	tasks_timer[current_task] = ms;
}

/* Stop function --------------------------------------------------------------*/
void Task_STOP(unsigned char task_num)
{
	tasks_timer[task_num]=0xFFFF;
}

/* Run function ---------------------------------------------------------------*/
void Task_RUN(unsigned char task_num, unsigned int del)
{
	tasks_timer[task_num] = del;
}

/* Delay function --------------------------------------------------------------*/
void delay_ms(unsigned int ms)
{
	delay_count = ms;
	while (delay_count){}
}

/* Assign task function --------------------------------------------------------*/
void TaskAsigner(void (*f)(void), unsigned char num)
{
	task[num] = f;
}





uint8_t Battery(uint8_t Percent)
{
	uint8_t res = (uint8_t)(Percent/14);
	if(res>7)res=7;
	return res;
}


