/**                             _____________
 *              /\      /\     /             \
 *             //\\____//\\   |   MAUUUU!!    |
 *            /     '      \   \  ___________/
 *           /   /\ '  /\    \ /_/			      / /  ___    / __\ |__   __ _| |_ 
 *          |    == o ==      |       /|	     / /  / _ \  / /  | '_ \ / _` | __|
 *           \      '        /       | |	    / /__|  __/ / /___| | | | (_| | |_ 
 *             \           /         \ \	    \____/\___| \____/|_| |_|\__,_|\__|
 *             /----<o>---- \         / /
 *             |            ' \       \ \
 *             |    |    | '   '\      \ \
 *  _________  | ´´ |  ' |     '  \    / /
 *  |  MAYA  | |  ' |    | '       |__/ /
 *   \______/   \__/ \__/ \_______/____/
 * 
 * @file MC33HB2001.h
 * @author Alejandro Gomez Molina (@Alejo2312)
 * @brief 
 * @version 0.1
 * @date Mar 28, 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef TPL_MC33HB2001_C_DRIVER_MC33HB2001_H_
#define TPL_MC33HB2001_C_DRIVER_MC33HB2001_H_


/************************************************************************
	INCLUDES
************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/************************************************************************
	DEFINES AND TYPES
************************************************************************/

#define MC33HB2001_ERROR    -1
#define MC33HB2001_OK        0

#define MC33HB2001_WRITE_OP (0b01 << 15)
#define MC33HB2001_READ_OP  (0b00 << 15)
#define MC33HB2001_OP_MSK   0x1FFFU
#define MC33HB2001_REG_SIZE 2U
#define MC33HB2001_MSB      0U
#define MC33HB2001_LSB      1U


#define MC33HB2001_IS_ERROR( error ) ((error) < MC33HB2001_ERROR)

/**
 * @brief Error type.
 */
typedef int MC33HB2001_Error_t;

/**
 * @brief  MC33HB2001 register definition.
 */
typedef enum
{
    MC33HB2001_REG_ID       = (0b00 << 13U), /**< Device Identification (Reserved) */
    MC33HB2001_REG_STATUS   = (0b01 << 13U), /**< Status */
    MC33HB2001_REG_FAULT    = (0b10 << 13U), /**< Fault Status Mask */
    MC33HB2001_REG_CONTROL  = (0b11 << 13U)  /**< Configuration and Control */
}MC33HB2001_Reg_t;

/**
 * @brief Status bits description
 */
typedef enum
{
    MC33HB2001_STATUS_FRM   = (0b01 << 11U),    /**< SPI framing error */
    MC33HB2001_STATUS_CP_U  = (0b01 << 10U),    /**< Charge pump undervoltage */
    MC33HB2001_STATUS_UV    = (0b01 <<  9U),    /**< VPWR undervoltage */
    MC33HB2001_STATUS_OV    = (0b01 <<  8U),    /**< VPWR overvoltage */
    MC33HB2001_STATUS_SCP2  = (0b01 <<  7U),    /**< Short-circuit to power output 2 */
    MC33HB2001_STATUS_SCP1  = (0b01 <<  6U),    /**< Short-circuit to power output 1 */
    MC33HB2001_STATUS_SCG2  = (0b01 <<  5U),    /**< Short-circuit to ground output 2 */
    MC33HB2001_STATUS_SCG1  = (0b01 <<  4U),    /**< Short-circuit to ground output 1 */
    MC33HB2001_STATUS_OL    = (0b01 <<  3U),    /**< Open load */
    MC33HB2001_STATUS_OC    = (0b01 <<  2U),    /**< Overcurrent - current limit has been activated */
    MC33HB2001_STATUS_TW    = (0b01 <<  1U),    /**< Thermal warning */
    MC33HB2001_STATUS_OT    = (0b01 <<  0U),    /**< Overtemperature shutdown */
}MC33HB2001_Status_t;


/**
 * @brief Configuration and control bits description
 */
typedef enum
{
    MC33HB2001_CONTOL_CL    = (0b01 << 12U),    /**< Check for open load. = Enabled on transition from Standby to Normal mode  */
    MC33HB2001_CONTOL_TM    = (0b01 << 11U),    /**< Thermal Management mode. Enable change of current limit
                                                     frequency by control of tB when OTW state */
    MC33HB2001_CONTOL_AL    = (0b01 << 10U),    /**< Enable active current limit when overcurrent ILIM threshold has been exceeded */
    MC33HB2001_CONTOL_ILIM1 = (0b01 <<  9U),    /**< ILIM Bit 1 */
    MC33HB2001_CONTOL_ILIM0 = (0b01 <<  8U),    /**< ILIM Bit 0 */
    MC33HB2001_CONTOL_SR2   = (0b01 <<  7U),    /**< Slew Rate Bit 2 */
    MC33HB2001_CONTOL_SR1   = (0b01 <<  6U),    /**< Slew Rate Bit 1 */
    MC33HB2001_CONTOL_SR0   = (0b01 <<  5U),    /**< Slew Rate Bit 0 */
    MC33HB2001_CONTOL_EN    = (0b01 <<  4U),    /**< Disable Outputs. ENABLE output control when ENBL pin is high and DIS pin is low  */
    MC33HB2001_CONTOL_MODE  = (0b01 <<  3U),    /**< Input Control mode */
    MC33HB2001_CONTOL_INPUT = (0b01 <<  2U),    /**< Active INPUT Control mode.SPI control of outputs by way of VIN1 and VIN2, IN1 pin
                                                     and IN2 pin are disabled */
    MC33HB2001_CONTOL_VIN2  = (0b01 <<  1U),    /**< Virtual Input 2 (SPI equivalent of IN2) */
    MC33HB2001_CONTOL_VIN1  = (0b01 <<  0U),    /**< Virtual Input 1 (SPI equivalent of IN1) */
}MC33HB2001_Control_t;

/**
 * @brief Input Control mode
 */
typedef enum
{
    MC33HB2001_MODE_HALF_BRIDGE = 0b0,  /**< H-bridge control mode */
    MC33HB2001_MODE_FULL_BRIDGE = 0b1,  /**<  Half-bridge control mode */
}MC33HB2001_Mode_t;

/**
 * @brief Virtual Input
 */
typedef enum
{
    MC33HB2001_VIN1,/**< Virtual Input 2 (SPI equivalent of IN2) */
    MC33HB2001_VIN2,/**< Virtual Input 1 (SPI equivalent of IN1) */
}MC33HB2001_VirtualInput_t;

/**
 * @brief OUTx rising and falling slew rate, from 10 % to 90 % of VPWR.
 */
typedef enum
{
    MC33HB2001_SR_0 = (0b000 << 5U),    /**<  bypass   */
    MC33HB2001_SR_1 = (0b001 << 5U),    /**<   16 V/us */
    MC33HB2001_SR_2 = (0b010 << 5U),    /**<    8 V/us */
    MC33HB2001_SR_3 = (0b011 << 5U),    /**<    4 V/us */
    MC33HB2001_SR_4 = (0b100 << 5U),    /**<    2 V/us (default) */
    MC33HB2001_SR_5 = (0b101 << 5U),    /**<    1 V/us */
    MC33HB2001_SR_6 = (0b110 << 5U),    /**<  0.5 V/us */
    MC33HB2001_SR_7 = (0b111 << 5U),    /**< 0.25 V/us */
    MC33HB2001_SR_MSK = (0b111 << 5U)
}MC33HB2001_SR_t;

/**
 * @brief Current limit threshold current
 *
 */
typedef enum
{
    MC33HB2001_ILIM_1 = (0b00 << 8U),   /**<  5.4 A */
    MC33HB2001_ILIM_2 = (0b01 << 8U),   /**<  7.0 A (default) */
    MC33HB2001_ILIM_3 = (0b10 << 8U),   /**<  8.8 A */
    MC33HB2001_ILIM_4 = (0b11 << 8U),   /**< 10.7 A */
    MC33HB2001_ILIM_MSK = (0b11 << 8U)
}MC33HB2001_ILIM_t;


/************************************************************************
	FUNCTIONS
************************************************************************/

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_Init( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_DeviceID( uint16_t* devID );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_GetStatus( uint16_t* status );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_CheckOpenLoad( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_EnableThermalManagement( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_DisableThermalManagement( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_EnableCurrentLimit( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_DisableCurrentLimit( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_SetCurrentLimit( MC33HB2001_ILIM_t iLimit );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_SetSlewRate( MC33HB2001_SR_t sr );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_SetMode(MC33HB2001_Mode_t mode );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_EnableOutput( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_DisableOutput( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_EnableVirturalInput( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_DisableVirturalInput( void );

/**
  See "MC33HB2001.c" for details of how to use this function.
 */
MC33HB2001_Error_t MC33HB2001_SetVirturalInput( MC33HB2001_VirtualInput_t vin, uint8_t value );

#endif /* TPL_MC33HB2001_C_DRIVER_MC33HB2001_H_ */
