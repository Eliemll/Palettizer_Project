#include "myTasks.h"
#include "factory_io.h"
#include "semphr.h"
#include "queue.h"

xQueueHandle xSubscribeQueue;
subscription subs = {0};

xQueueHandle xWritingQueue;

#define XSEM_TABLE_SIZE 3
xSemaphoreHandle xSemTable[XSEM_TABLE_SIZE];
xSemaphoreHandle xSem1 = NULL;
xSemaphoreHandle xSem2 = NULL;
xSemaphoreHandle xSem3 = NULL;

xTaskHandle ClampReady;
xTaskHandle StackContinue;

static uint32_t command = 0;
uint32_t free_heap_size = 0;

void sendSubscription(subscribe_message_t subMsg, uint8_t semId, uint32_t sensorId, uint8_t sensorState)
{
    subMsg.sem_id = semId;
    subMsg.sensor_id = sensorId;
    subMsg.sensor_state = sensorState;
    xQueueSend(xSubscribeQueue, &subMsg, portMAX_DELAY);
}

void InitTasks()
{
    xSem1 = xSemaphoreCreateBinary();
    xSem2 = xSemaphoreCreateBinary();
    xSem3 = xSemaphoreCreateBinary();

    xSemTable[0] = xSem1;
    xSemTable[1] = xSem2;
    xSemTable[2] = xSem3;

    xSubscribeQueue = xQueueCreate(10, sizeof(subscribe_message_t));
    xWritingQueue = xQueueCreate(10, sizeof(uint32_t));

    xTaskCreate(CardboardSenderTask, "CardboardbSender", 128, NULL, 1, NULL);
    xTaskCreate(CardboardLoaderIntoPalettizer, "CardBoardLoader", 128, NULL, 1, NULL);
    xTaskCreate(CardBoardStackerTask, "CbStacker", 128, NULL, 1, &ClampReady);
    xTaskCreate(PaletteSenderTask, "PaletteSender", 128, NULL, 1, &StackContinue);
    xTaskCreate(TaskSubscribe, "Subscriber", 128, NULL, 2, NULL);
    xTaskCreate(TaskPublisher, "Publisher", 128, NULL, 2, NULL);
}

void TaskSubscribe(void *params)
{
    portTickType xLastWakeTime = xTaskGetTickCount();
    uint8_t counter = 0;
    subscribe_message_t msg;

    while (1)
    {
        if (xQueueReceive(xSubscribeQueue, &msg, 0) == pdPASS)
        {
            updateSubscription(&subs, &msg, counter);
        }

        for (uint8_t i = 0; i < subs.subscriptionNumber; i++)
        {

            uint8_t expected = subs.subscribersList[i].sensor_state;
            uint32_t sid = subs.subscribersList[i].sensor_id;
            uint8_t id = subs.subscribersList[i].sem_id;

            if (FACTORY_IO_Sensors_Get(sid) == expected)
            {
                xSemaphoreGive(xSemTable[id - 1]);
                removeSubscription(&subs, id);
            }
        }
        vTaskDelayUntil(&xLastWakeTime, (200 / portTICK_RATE_MS));
    }
}

void TaskPublisher(void *params)
{
    uint32_t cmd;

    while (1)
    {
        xQueueReceive(xWritingQueue, &cmd, portMAX_DELAY);
        FACTORY_IO_Actuators_Set(cmd);

        vTaskDelay(200 / portTICK_RATE_MS);
    }
}

void CardboardSenderTask(void *params)
{
    portTickType xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();

    command |= (ActivateFirstConveyor_Msk | ActivateConveyor2_Msk);
    xQueueSend(xWritingQueue, &command, 0);

    while (1)
    {
        command |= SendCardboard_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(500));

        command &= ~SendCardboard_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(4500));

        free_heap_size = xPortGetFreeHeapSize();
    }
}

void CardboardLoaderIntoPalettizer(void *params)
{
    subscribe_message_t subMsg;
    uint8_t counter = 0;
    uint8_t semId = 1;

    subMsg.sem_id = semId;
    subMsg.sensor_id = CardboardArrivedToPalletizer_Msk;
    subMsg.sensor_state = 0;

    command |= BlockPalletizerEntry_Msk;
    xQueueSend(xWritingQueue, &command, 0);

    while (1)
    {
        xQueueSend(xSubscribeQueue, &subMsg, portMAX_DELAY);
        xSemaphoreTake(xSemTable[0], portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(1000));

        xQueueSend(xSubscribeQueue, &subMsg, portMAX_DELAY);
        xSemaphoreTake(xSemTable[0], portMAX_DELAY);

        command &= ~BlockPalletizerEntry_Msk;
        command |= LoadPalettizer_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelay(pdMS_TO_TICKS(2500));

        command |= BlockPalletizerEntry_Msk;
        command |= Pusher_Msk;
        command &= ~LoadPalettizer_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelay(pdMS_TO_TICKS(1300));

        command &= ~Pusher_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        counter++;

        if (counter == 3)
        {
            xTaskNotifyGive(ClampReady);
            counter = 0;
        }
        
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void CardBoardStackerTask(void *params)
{
    subscribe_message_t subMsg;
    uint8_t semId = 2;

    while (1)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        command |= Clamp_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        sendSubscription(subMsg, semId, CardBoardsClamped_Msk, 1);
        xSemaphoreTake(xSemTable[semId - 1], portMAX_DELAY);

        command |= OpenDoor_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelay(pdMS_TO_TICKS(1000));

        xTaskNotifyGive(StackContinue);

        vTaskDelay(pdMS_TO_TICKS(2000));

        command &= ~Clamp_Msk;
        command &= ~OpenDoor_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        command |= Clamp_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        sendSubscription(subMsg, semId, CardBoardsClamped_Msk, 1);
        xSemaphoreTake(xSemTable[semId - 1], portMAX_DELAY);

        command |= OpenDoor_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelay(pdMS_TO_TICKS(1000));

        xTaskNotifyGive(StackContinue);

        vTaskDelay(pdMS_TO_TICKS(2000));

        command &= ~Clamp_Msk;
        command &= ~OpenDoor_Msk;
        xQueueSend(xWritingQueue, &command, 0);
    }
}

void PaletteSenderTask(void *params)
{
    subscribe_message_t subMsg;
    uint8_t semId = 3;

    command |= RemovePalette_Msk;

    while (1)
    {
        command |= (SendPalette_Msk | ActivateFisrtPaletteConveyor_Msk | ActivateSecondPaletteConveyor_Msk | LoadPalette_Msk);
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelay(pdMS_TO_TICKS(500));

        command &= ~SendPalette_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        sendSubscription(subMsg, semId, PaletteIn_Msk, 1);
        xSemaphoreTake(xSemTable[semId - 1], portMAX_DELAY);

        vTaskDelay(pdMS_TO_TICKS(2100));

        command &= ~(ActivatePaletteOutConveyor_Msk | ActivateSecondPaletteConveyor_Msk | LoadPalette_Msk);
        command |= LiftUpElevator_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelay(pdMS_TO_TICKS(500));

        command |= ElevatorToLimit_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        sendSubscription(subMsg, semId, ElevatorIsAtFirstStage_Msk, 1);
        xSemaphoreTake(xSemTable[semId - 1], portMAX_DELAY);

        command &= ~ElevatorToLimit_Msk;
        command &= ~LiftUpElevator_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        command |= LiftDownElevator_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        sendSubscription(subMsg, semId, ElevatorIsAtFirstStage_Msk, 0);
        xSemaphoreTake(xSemTable[semId - 1], portMAX_DELAY);

        command &= ~LiftDownElevator_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        command |= LiftDownElevator_Msk;
        command |= ElevatorToLimit_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        sendSubscription(subMsg, semId, ElevatorIsDown_Msk, 1);
        xSemaphoreTake(xSemTable[semId - 1], portMAX_DELAY);

        command &= ~LiftDownElevator_Msk;
        command &= ~ElevatorToLimit_Msk;
        command |= LoadPalette_Msk;
        command |= ActivatePaletteOutConveyor_Msk;
        xQueueSend(xWritingQueue, &command, 0);

        vTaskDelay(pdMS_TO_TICKS(3000));

        command &= ~LoadPalette_Msk;
        xQueueSend(xWritingQueue, &command, 0);
    }
}

void vApplicationIdleHook(void *nothing)
{
    __WFI();
}