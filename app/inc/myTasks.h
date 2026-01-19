#ifndef MY_TASKS_H
#define MY_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "subscription.h"

void InitTasks();

void TaskSubscribe(void *params); 
void TaskPublisher(void *params);

void CardboardSenderTask(void *params);
void CardboardLoaderIntoPalettizer(void *params);
void CardBoardStackerTask(void *params);
void PaletteSenderTask(void *params);

void vApplicationIdleHook(void *);

#endif
