


   #include "types.h"


   #define PREPHERAL_BIT_ALIAS_BASE              0x42000000
   #define BIT_BAND_REGION_BASE                  0x40000000

   #define SRAM_BIT_ALIAS_BASE                   0x22000000 
   #define BIT_BAND_REGION_BASE                  0x20000000      
        
        
        
   #define BIT_BANDING(ADDRESS, BIT_NUMBER)        (*(uint32*)(BIT_ALIAS_BASE + ((ADDRESS - BIT_BAND_REGION_BASE) * 32) + (BIT_NUMBER * 4)))


/* GPIO  Direction PORT base address  */
   #define GPIO_PORTA_APB_Base         (*((volatile uint32*)  0X40004000))
   #define GPIO_PORTA_AHB_Base         (*((volatile uint32*)  0X40058000))

   #define GPIO_PORTB_APB_Base         (*((volatile uint32*)  0X40005000))
   #define GPIO_PORTB_AHB_Base         (*((volatile uint32*)  0X40059000))

   #define GPIO_PORTC_APB_Base         (*((volatile uint32*)  0x40006000))
   #define GPIO_PORTC_AHB_Base         (*((volatile uint32*)  0x4005A000))

   #define GPIO_PORTD_APB_Base         (*((volatile uint32*)  0x40007000))
   #define GPIO_PORTD_AHB_Base         (*((volatile uint32*)  0x4005B000))

   #define GPIO_PORTE_APB_Base         (*((volatile uint32*)  0x40024000))
   #define GPIO_PORTE_AHB_Base         (*((volatile uint32*)  0x4005C000))

   #define GPIO_PORTF_APB_Base         (*((volatile uint32*)  0x40025000))
   #define GPIO_PORTF_AHB_Base         (*((volatile uint32*)  0x4005D000))
        
/******************************************/        

/* GPIO Register Map offset*/

   #define   GPIODATA_OFF        0x000//direction
   #define   GPIODIR_OFF         0x400                     //
   #define   GPIOAFSEL_OFF       0x420                     //
   #define   GPIODR2R_OFF        0x500                     //GPIO 2-mA Drive Select
   #define   GPIODR4R_OFF        0x504                     //GPIO 4-mA Drive Select
   #define   GPIODR8R_OFF        0x508                     //GPIO 8-mA Drive Select   
   #define   GPIOODR_OFF         0x50c                     //open drain
   #define   GPIOPUR_OFF         0x510                     //pull up
   #define   GPIOPDR_OFF         0x514                    //pull down
   #define   GPIOSLR_OFF         0x518
   #define   GPIODEN_OFF         0x51C
   #define   GPIOLOCK_OFF        0x520
   #define   GPIOCR_OFF          0x524
   #define   GPIOAMSEL_OFF       0x528
   #define   GPIOPCTL_OFF        0x52C


/* *************Interrupt addresses offset ******************************** -> */
   

   #define GPIO_IS_OFF                          0x404
   #define GPIO_IBE_OFF                         0x408
   #define GPIO_IEV_OFF                         0x40C
   #define GPIO_IM_OFF                          0x410
   #define GPIO_RIS_OFF                         0x414
   #define GPIO_MIS_OFF                         0x418
   #define GPIO_ICR_OFF                         0x41C


/* **************** ADC Addresses offset ********************************** -> */
    
    
    #define GPIO_ADCCTL_OFF                       0x530
    #define GPIO_DMACTL_OFF                       0x534

/* **************************************************************************** */
    
    #define GPIO_PeriphID4_OFF                    0xFD0
    #define GPIO_PeriphID5_OFF                    0xFD4
    #define GPIO_PeriphID6_OFF                    0xFD8
    #define GPIO_PeriphID7_OFF                    0xFDC
    #define GPIO_PeriphID0_OFF                    0xFE0
    #define GPIO_PeriphID1_OFF                    0xFE4
    #define GPIO_PeriphID2_OFF                    0xFE8
    #define GPIO_PeriphID3_OFF                    0xFEC
    #define GPIO_PCellID0_OFF                     0xFF0
    #define GPIO_PCellID1_OFF                     0xFF4
    #define GPIO_PCellID2_OFF                     0xFF8
    #define GPIO_PCellID3-OFF                     0xFFC
    
    /* ************************************************************************** */

/* *****************GLOBAL DATA TYPES AND STRUCTURES***************************** */
    
    
    /*Enum that desscribes the functionality of a pin*/
    typedef enum {GPIO,PERIPHERAL} GPIO_PIN_MODE;
    
    typedef enum{INPUT,OUTPUT} GPIO_PIN_DDR;
    
    
    /*Enum that describes whether pin is digital or analog */
    typedef enum{ANALOG, DIGITAL} GPIO_PIN_DIGITAL_ENABLE;

    /*Enum that describes the status of the internal resistance of the pin*/
    typedef enum{NO_RES,PULLUP,PULLDOWN} GPIO_PIN_INTERNAL_ATTACH;

    /*Enum that describes the output configuration of the pin*/
    typedef enum{ OPENDRAIN_OFF,OPENDRAIN_ON} GPIO_OUTPUT_CONFIG;


    /*enum that describes the output current drive */
    typedef enum {D_0mA=0,D_2mA=1, D_4mA=2,D_8mA=3} GPIO_PIN_OUTPUT_CURRENT;

    /*Enum that states if a pin is used as dma of adc trigger*/
    typedef enum {NO_TRIGGER,ADC,UDMA} GPIO_PIN_TRIGGER;

    /*Interrupt */
    /*Enum that states if the interrupt of a pin is enabled*/
    typedef enum {DISABLE_INTERRUPT,ENABLE_INTERRUPT} GPIO_INT_ENABLE;

    /*Enum that describes interrupt sense */
    typedef enum{EDGE_TRIGGERED,LEVEL_TRIGGER} GPIO_INT_SENSE;

    /*Enum that describes the trigger of the interrupt pin*/
    typedef enum {BOTH_EDGES,FALLING_EDGE,RISING_EDGE} GPIO_INT_TRIGGER;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*Struct describing the configuration of the enum*/
    typedef struct 
    {
        GPIO_INT_SENSE sense;
        GPIO_INT_TRIGGER trigger;

    } GPIO_INT_CONFIG;

    /*Struct that describes the configuration of a GPIO pin */
    typedef struct 
    {
        GPIO_PIN_DDR              direction;
        GPIO_PIN_MODE             pinMode;
        GPIO_PIN_DIGITAL_ENABLE   digitalEnable;
        GPIO_PIN_INTERNAL_ATTACH  internalResistance;
        GPIO_OUTPUT_CONFIG        outputConfig;
        GPIO_PIN_OUTPUT_CURRENT   currentDrive;
        GPIO_PIN_TRIGGER          pinTrigger;
        GPIO_INT_ENABLE           interruptEnable;
        GPIO_INT_CONFIG           interruptConfig;

    }GPIO_PIN_CONFIG;


    /*Struct that describes the configuration of an interrupt pin */
    typedef struct{
        GPIO_INT_SENSE     interruptSense;
        GPIO_INT_TRIGGER   interruptTrigger;
    }GPIO_INT_PIN_CONFIG;

  /* ********************GLOBAL FUNCTION PROTOTYPES************************** */

        void GPIO_enablePortClock(uint32 port);

        /* Function that initializes a GPIO pin
        parameters:
            -configuration: the configuration of the pin
            -port:  port to be configured
            -pin: number of pin ro be configured
        */
        void GPIO_intit(GPIO_pinConfig *configuration,uint32 port,uint8 pin);

        /* Function that clears the interrupt Mask interrupt status and raw interrupt status by setting ICR bit
        parameters:
            -port: port of the interrupt pin
            -pin: the interrupt pin
        */
        void GPIO_clearInterrupt(uint32 port,uint8 pin);



