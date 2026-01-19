/*
 * factory_io.h
 *
 *  Created on: 5 d�c. 2020
 *      Author: Laurent
 */

#ifndef BSP_INC_FACTORY_IO_H_
#define BSP_INC_FACTORY_IO_H_


#define	FRAME_LENGTH		14
#define FRAME_LENGTH_ACT	7
#define FRAME_LENGTH_SENS	7

#define	TAG_SENSORS			0xA8
#define	TAG_ACTUATORS		0xAD
#define TAG_UPDATE			0xA3

// ACTUATORS
// 0b1<<7 doesnt correspond to anything.
// To reach the 7th Sensor you have to write 0b1<<8
#define Test_Msk 							 0b1<<16

#define SendCardboard_Msk                   (0b1)
#define ActivateFirstConveyor_Msk           (0b1<<1)
#define BlockPalletizerEntry_Msk            (0b1<<2)
#define OpenDoor_Msk                        (0b1<<3)
#define Pusher_Msk                          (0b1<<4)
#define Clamp_Msk                           (0b1<<5)
#define LiftUpElevator_Msk                  (0b1<<6)
// This line has no effects                 (0b1<<7)
#define LiftDownElevator_Msk                (0b1<<8)
#define ElevatorToLimit_Msk                 (0b1<<9)
#define SendPalette_Msk                     (0b1<<10)
#define LoadPalette_Msk                     (0b1<<11)
#define ActivateConveyor2_Msk               (0b1<<12)
#define TurnCardboard_Msk                   (0b1<<13)
// This line either doesn't do anything     (0b1 << 14)
#define UnloadPalettizer_Msk                (0b1<<15)
#define LoadPalettizer_Msk                  (0b1<<16)
#define UnloadPalette_Msk                   (0b1<<17)
#define ActivateSecondPaletteConveyor_Msk   (0b1<<18)
#define ActivateFisrtPaletteConveyor_Msk    (0b1<<19)
#define ActivatePaletteOutConveyor_Msk      (0b1<<20)
#define RemovePalette_Msk                   (0b1<<21)

// SENSORS
#define CardoboardDistibuted_Msk             0b1
#define CardboardSent_Msk                   (0b1<<1)
#define CardboardArrivedToPalletizer_Msk    (0b1<<2)
#define DoorOpenred_Msk                     (0b1<<3)
#define PushLimit_Msk                       (0b1<<4) 
#define CardBoardsClamped_Msk               (0b1<<5)
#define ElevatorIsDown_Msk                  (0b1<<6)
// This line has no effects                 (0b1<<7)
#define ElevatorIsAtFirstStage_Msk          (0b1<<8)
#define ElevatorIsAtSecondStage_Msk         (0b1<<9)
#define PaletteIsOut_Msk                    (0b1<<10)
#define DoorLimit_Msk                       (0b1<<11)
#define ElevatorIsMooving_Msk               (0b1<<12)
#define PaletteIn_Msk                       (0b1<<13)

    /*
     * Global variables
     */

    /*
     * Receiving buffer from Factory I/O Python bridge
     *
     * Works with DMA in circular mode, therefore nothing special has to be done
     * to retrieve latest states. One should simply read the content of rx_dma_buffer[]
     *
     * 7 bytes for sensors
     * [0]  -> 0xA8	Sensors tag
     * [1]  -> 7-bit data byte #1 [  0 ->  6 ]
     * [2]  -> 7-bit data byte #2 [  7 -> 13 ]
     * [3]  -> 7-bit data byte #3 [ 14 -> 20 ]
     * [4]  -> 7-bit data byte #4 [ 21 -> 27 ]
     * [5]  -> CRC
     * [6]  -> '\n'
     *
     * 7 bytes for Actuators
     * [7]  -> 0xAD	Actuators tag
     * [8]  -> 7-bit data byte #1 [  0 ->  6 ]
     * [9]  -> 7-bit data byte #2 [  7 -> 13 ]
     * [10] -> 7-bit data byte #3 [ 14 -> 20 ]
     * [11] -> 7-bit data byte #4 [ 21 -> 27 ]
     * [12] -> CRC
     * [13] -> '\n'
     *
     */

    extern uint8_t rx_dma_buffer[FRAME_LENGTH];


/*
 * Public functions
 */


/*
 * FACTORY_IO_Actuators_Set
 *
 * Sets Factory IO scene all actuators based on a 32-bit states parameter
 *
 *            -------------------------------------------------------------------------------------------------
 * cmd bit    |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
 *            -------------------------------------------------------------------------------------------------
 * Actuator @ |##|27|26|25|24|23|22|21|##|20|19|18|17|16|15|14|##|13|12|11|10| 9| 8| 7|##| 6| 5| 4| 3| 2| 1| 0|
 *            -------------------------------------------------------------------------------------------------
 *
 * Note : only 7-bit representation is used to allow special tags to be specified when MSB is set
 *
 */
void FACTORY_IO_Actuators_Set (uint32_t cmd);


/*
 * FACTORY_IO_Sensors_Get
 *
 * Get Factory IO scene single-sensor state based on a 32-bit mask
 *
 *           -------------------------------------------------------------------------------------------------
 * bit       |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0|
 *           -------------------------------------------------------------------------------------------------
 * Sensor @  |##|27|26|25|24|23|22|21|##|20|19|18|17|16|15|14|##|13|12|11|10| 9| 8| 7|##| 6| 5| 4| 3| 2| 1| 0|
 *           -------------------------------------------------------------------------------------------------
 *
 * Note : only 7-bit representation is used to allow special tags to be specified when MSB is set
 *
 */
uint8_t	FACTORY_IO_Sensors_Get (uint32_t msk);


/*
 * Force Factory IO scene to send sensors and actuators states
 *
 * These are automatically received in the rx_dma_buffer[] array
 */
void FACTORY_IO_update (void);


#endif /* BSP_INC_FACTORY_IO_H_ */
