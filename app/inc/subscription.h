#ifndef SUBSCRIPTION_H_
#define SUBSCRIPTION_H_

#include <stdint.h>

#define TAILLE_TABLEAU 20

typedef struct subscribe_message_t
{
    uint8_t sem_id;       // Semaphore ID to use for publication
    uint32_t sensor_id;    // Awaited sensor ID
    uint8_t sensor_state; // Awaited sensor State
} subscribe_message_t;

typedef struct subscription
{
    uint8_t subscriptionNumber;
    subscribe_message_t subscribersList[TAILLE_TABLEAU];
} subscription;

void updateSubscription(subscription *subs, subscribe_message_t *msg, uint8_t counter);
void removeSubscription(subscription *subs, uint8_t sem_id);

#endif /* APP_INC_SUBSCRIPTION_H_ */
