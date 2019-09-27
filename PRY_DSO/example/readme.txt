c-tds-project-4a example using Co-operative - Time Driven System - Project for LPC1769

Example description
Required_SystemCoreClock => 100MHz
SysTick_RateHz => 1000 ticks per second (1mS)

Car Clean Room Controller
    Simple controller code 

task-Door1_switch_lpc1769
    Simple switch interface code, with software debounce.

task-Door2_switch_lpc1769
    Simple switch interface code, with software debounce.

task-Emergency_switch_lpc1769
    Simple switch interface code, with software debounce.

task-LockDoor1_led_lpc1769
    Simple lock & led interface code.

task-LockDoor2_led_lpc1769
    Simple lock & led interface code.

task-heartbeat_lpc1769
    If everything is OK, flashes at 0.5 Hz
    If there is a fault code active, this is displayed.

task-watchdog_lpc1769
    Simple Watchdog Timer interface.

Special connection requirements
There are no special connection requirements for this example.

Build procedures:
Visit the LPCOpen quickstart guide at "http://www.lpcware.com/content/project/lpcopen-platform-nxp-lpc-microcontrollers/lpcopen-v200-quickstart-guides"
to get started building LPCOpen projects.
