/*--------------------------------------------------------------------*-

    task-car_wash_controller_lpc1769.c (Released 2019-04)

  --------------------------------------------------------------------

    Simple CAR WASH CONTROLLER task for LPC1769.
	[Read Input on LPCXpresso baseboard.]

    Simple car wash controller code.

    - See "Car Wash Cortroller.jpg" for details.

-*--------------------------------------------------------------------*/


// Project header
#include "task-Clean_Room_controller_lpc1769.h"

#include "../main/main.h"


// Task header


// ------ Public variable ------------------------------------------
// Sensors
extern uint32_t Em_switch_pressed_G;
extern uint32_t Door1_switch_pressed_G;
extern uint32_t Door2_switch_pressed_G;



// Actuators
extern uint32_t Lock1_led_required_G;
extern uint32_t Lock2_led_required_G;


// ------ Private constants ----------------------------------------
// All durations are in Seconds (short times here for demo)
#define MAX_STABLE_DURATION (200)



// ------ Private data type ----------------------------------------

// Possible system states
typedef enum {IDLE, DOOR_OPEN, TIMEOUT,EMERGENCY, FAULT} eSystem_state;

// ------ Private variable -----------------------------------------
static eSystem_state System_state_G;
static uint32_t Time_in_state_G;
uint32_t LogicOff_G=0,Time_in_em1_G,Time_in_em2_G;

/*------------------------------------------------------------------*-

    CLEAN_ROOM_CONTROLLER_Init()

    Prepare for CLEAN_ROOM_CONTROLLER_Update() function - see below.

-*------------------------------------------------------------------*/
void CLEAN_ROOM_CONTROLLER_Init(void)
{
	System_state_G = IDLE;

	// Lock1 is off
	Lock1_led_required_G = LOCK_OFF;

	//  Lock2 is off
	Lock2_led_required_G = LOCK_OFF;
}


/*------------------------------------------------------------------*-

    CAR_WASH_CONTROLLER_Update()

    Simple car wash controller code.

	If IDLE     && Em_switch_pressed_G is sensor on   => Emergency
	                                                    Time_in_state_G=0;
														Open_Door=0;
														LogicOff_G=TRUE;

			    && Door1_switch_pressed_G is sensor on  &&
	               Door2_switch_pressed_G is sensor off
	               OR
	               Door1_switch_pressed_G is sensor off &&
	               Door2_switch_pressed_G is sensor on    => DOOR_OPEN
	                                                       Lockx_led_required_G=LOCK_ON;

	If DOOR_OPEN && Em_switch_pressed_G is sensor on      => Emergency
	                                                         Time_in_state_G=0;
														     Open_Door=0;
														     LogicOff_G=TRUE;

			     && Door1_switch_pressed_G is sensor off &&
	                Door2_switch_pressed_G is sensor off    => TIMEOUT (Closed Door)
	                                                           Time_in_state_G=0;

	If TIMEOUT  && Em_switch_pressed_G is sensor on      => Emergency
	                                                         Time_in_state_G=0;
														     Open_Door=0;
														     LogicOff_G=TRUE;
	             && ++Time_in_state_G >= MAX_TIME    => IDLE
	             	 	 	 	 	 	 	 	 	 	Lockx_led_required_G=LOCK_OFF;


	If EMERGENCY  Door1_switch_pressed_G is sensor on &&
	              Door2_switch_pressed_G is sensor on
	              Door1_switch_pressed_G is sensor off &&
	              Door2_switch_pressed_G is sensor off     => IDLE

	If FAULT                                            	=>

    Must schedule every 1 mili second (soft deadline).

-*------------------------------------------------------------------*/
void CLEAN_ROOM_CONTROLLER_Update(void)
{

    static uint32_t Open_Door=false,RGEm=0,OUTEm=0;

	switch (System_state_G)
	{
		case IDLE:

			if (Em_switch_pressed_G == SENSOR_ON )
		    {
				System_state_G=EMERGENCY;
				Time_in_state_G=0;
				Open_Door=0;
				LogicOff_G=TRUE;

			}else{

				if ((Door1_switch_pressed_G == SENSOR_ON)&&(Door2_switch_pressed_G == SENSOR_OFF) )
				{   Open_Door=1;
					Lock2_led_required_G=LOCK_ON;
					System_state_G=DOOR_OPEN;

				}else{
					if ((Door1_switch_pressed_G == SENSOR_OFF)&&(Door2_switch_pressed_G == SENSOR_ON) )
					{   Open_Door=2;
						Lock1_led_required_G=LOCK_ON;
						System_state_G=DOOR_OPEN;
					}else{

						// FAULT

					}

				}

			}


			break;

		case DOOR_OPEN:

			if (Em_switch_pressed_G == SENSOR_ON )
			{
				System_state_G=EMERGENCY;
				Time_in_state_G=0;
				Open_Door=0;
				LogicOff_G=TRUE;


			}else{
				if ((Door1_switch_pressed_G == SENSOR_OFF) && (Door2_switch_pressed_G == SENSOR_OFF))
				{
					 Time_in_state_G = 0;
					 System_state_G = TIMEOUT;
				}

			}



			break;

		case TIMEOUT:


			if (Em_switch_pressed_G == SENSOR_ON )
			{
				System_state_G=EMERGENCY;
				Time_in_state_G=0;
				Open_Door=0;
				LogicOff_G=TRUE;


			}else{
				// Remain in this state the necessary time

				if (++Time_in_state_G >= MAX_STABLE_DURATION)
				{

					System_state_G = IDLE;
					if(Open_Door==2){
						Lock1_led_required_G=LOCK_OFF;

					}else{
						if(Open_Door==1)
							Lock2_led_required_G=LOCK_OFF;
					}
					Open_Door=0;
				}



			}




			break;

		case EMERGENCY:


			// Out condition for EM
			if((Door1_switch_pressed_G == SENSOR_ON)&&(Door2_switch_pressed_G == SENSOR_ON)){

				OUTEm=1;

			}else{
				if((Door1_switch_pressed_G == SENSOR_OFF)&&(Door2_switch_pressed_G == SENSOR_OFF)&&(OUTEm==1)){

					OUTEm=0;
					Time_in_state_G=0;
					System_state_G=IDLE;
					LogicOff_G=FALSE;
					Lock1_led_required_G=0;
					Lock2_led_required_G=0;

				}

			}


			break;

		case FAULT:



			break;
	}
}


/*------------------------------------------------------------------*-
  ---- END OF FILE -------------------------------------------------
-*------------------------------------------------------------------*/
