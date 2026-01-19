#include "subscription.h"

void updateSubscription(subscription *subs, subscribe_message_t *msg, uint8_t counter)
{
    for (uint8_t i = 0; i < subs->subscriptionNumber; i++)
    {
        if (subs->subscribersList[i].sem_id == msg->sem_id &&
            subs->subscribersList[i].sensor_id == msg->sensor_id &&
            subs->subscribersList[i].sensor_state == msg->sensor_state)
        {
            return;
        }
    }

    if (subs->subscriptionNumber < TAILLE_TABLEAU)
    {
        uint8_t nextIndex = subs->subscriptionNumber;

        subs->subscribersList[nextIndex].sem_id = msg->sem_id;
        subs->subscribersList[nextIndex].sensor_id = msg->sensor_id;
        subs->subscribersList[nextIndex].sensor_state = msg->sensor_state;

        subs->subscriptionNumber++;
    }
}

void removeSubscription(subscription *subs, uint8_t sem_id)
{
    for (uint8_t i = 0; i < subs->subscriptionNumber; i++)
    {
        if (subs->subscribersList[i].sem_id == sem_id)
        {
            for (uint8_t j = i; j < subs->subscriptionNumber - 1; j++)
            {
                subs->subscribersList[j] = subs->subscribersList[j + 1];
            }

            uint8_t lastIndex = subs->subscriptionNumber - 1;
            subs->subscribersList[lastIndex].sem_id = 0;
            subs->subscribersList[lastIndex].sensor_id = 0;
            subs->subscribersList[lastIndex].sensor_state = 0;

            subs->subscriptionNumber--;

            return;
        }
    }
}
