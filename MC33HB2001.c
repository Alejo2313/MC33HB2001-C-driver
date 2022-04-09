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
 * @file MC33HB2001.c
 * @author Alejandro Gomez Molina (@Alejo2312)
 * @brief 
 * @version 0.1
 * @date Mar 28, 2022
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/************************************************************************
	INCLUDES
************************************************************************/
#include "MC33HB2001.h"
#include "MC33HB2001_port.h"

/************************************************************************
 	DEFINES AND TYPES
************************************************************************/


/************************************************************************
	DECLARATIONS
************************************************************************/
static bool MC33HB2001_isInitialized = false;

/************************************************************************
	FUNCTIONS
************************************************************************/

/**
 * @brief
 *
 * @param bit
 * @param regAddress
 * @return
 */
static MC33HB2001_Error_t  MC33HB2001_SetRegBit( uint16_t bit, MC33HB2001_Reg_t regAddress )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;
    uint16_t reg = 0;

    /* Set write operation and register number */
    reg = (MC33HB2001_READ_OP | regAddress);
    /* Read current register value */
    error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    if( !MC33HB2001_IS_ERROR(error) )
    {
        /* Set flag */
        reg = ( reg | bit) & MC33HB2001_OP_MSK;
        /* Set operation */
        reg |= (MC33HB2001_WRITE_OP | regAddress);
        error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    }

    return error;
}

/**
 * @brief
 *
 * @param bit
 * @param regAddress
 * @return
 */
static MC33HB2001_Error_t  MC33HB2001_ResetRegBit( uint16_t bit, MC33HB2001_Reg_t regAddress )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;
    uint16_t reg = 0;

    /* Set write operation and register number */
    reg = (MC33HB2001_READ_OP | regAddress);
    /* Read current register value */
    error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    if( !MC33HB2001_IS_ERROR(error) )
    {
        /* Set flag */

        reg &= ((~reg) & MC33HB2001_OP_MSK);
        /* Set operation */
        reg |= (MC33HB2001_WRITE_OP | regAddress);
        error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    }

    return error;
}


/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_Init( void )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;

    if( !MC33HB2001_isInitialized )
    {
        MC33HB2001_PORT_Init();
        MC33HB2001_isInitialized = true;
        error = MC33HB2001_OK;
    }
}

/**
 * @brief
 *
 * @param devID
 * @return
 */
MC33HB2001_Error_t MC33HB2001_DeviceID( uint16_t* devID )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;
    uint16_t reg = 0;
    uint8_t buffer[MC33HB2001_REG_SIZE];

    if( devID != NULL )
    {
        reg = (MC33HB2001_READ_OP | MC33HB2001_REG_ID);

        error = MC33HB2001_PORT_ReadWriteSPI(&reg);
        if( !MC33HB2001_IS_ERROR(error) )
        {
            *devID = reg;
        }

    }
    return error;
}

/**
 * @brief
 *
 * @param status
 * @return
 */
MC33HB2001_Error_t MC33HB2001_GetStatus( uint16_t* status )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;
    uint16_t reg = 0;
    uint8_t buffer[MC33HB2001_REG_SIZE];

    if( status != NULL )
    {
        reg = (MC33HB2001_READ_OP | MC33HB2001_REG_STATUS);

        error = MC33HB2001_PORT_ReadWriteSPI(&reg);
        if( !MC33HB2001_IS_ERROR(error) )
        {
            *status = reg;
        }
    }
    return error;
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_CheckOpenLoad( void )
{
    return MC33HB2001_SetRegBit(MC33HB2001_CONTOL_CL, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_EnableThermalManagement( void )
{
    return MC33HB2001_SetRegBit(MC33HB2001_CONTOL_TM, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_DisableThermalManagement( void )
{
    return MC33HB2001_ResetRegBit(MC33HB2001_CONTOL_TM, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_EnableCurrentLimit( void )
{
    return MC33HB2001_SetRegBit(MC33HB2001_CONTOL_AL, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_DisableCurrentLimit( void )
{
    return MC33HB2001_ResetRegBit(MC33HB2001_CONTOL_AL, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @param iLimit
 * @return
 */
MC33HB2001_Error_t MC33HB2001_SetCurrentLimit( MC33HB2001_ILIM_t iLimit )
{

    MC33HB2001_Error_t error = MC33HB2001_ERROR;
    uint16_t reg = 0;

    /* Set write operation and register number */
    reg = (MC33HB2001_READ_OP | MC33HB2001_REG_CONTROL);
    /* Read current register value */
    error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    if( !MC33HB2001_IS_ERROR(error) )
    {
        /* Clear previous value */
        reg &= ~(MC33HB2001_ILIM_MSK);
        /* Set flag */
        reg = ( reg | ( iLimit & MC33HB2001_ILIM_MSK) ) & MC33HB2001_OP_MSK;
        /* Set operation */
        reg |= (MC33HB2001_WRITE_OP | MC33HB2001_REG_CONTROL);
        error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    }

    return error;
}

/**
 * @brief
 *
 * @param sr
 * @return
 */
MC33HB2001_Error_t MC33HB2001_SetSlewRate( MC33HB2001_SR_t sr )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;
    uint16_t reg = 0;

    /* Set write operation and register number */
    reg = (MC33HB2001_READ_OP | MC33HB2001_REG_CONTROL);
    /* Read current register value */
    error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    if( !MC33HB2001_IS_ERROR(error) )
    {
        /* Clear previous value */
        reg &= ~(MC33HB2001_SR_MSK);
        /* Set flag */
        reg = ( reg | (sr & MC33HB2001_SR_MSK) ) & MC33HB2001_OP_MSK;
        /* Set operation */
        reg |= (MC33HB2001_WRITE_OP | MC33HB2001_REG_CONTROL);
        error = MC33HB2001_PORT_ReadWriteSPI(&reg);
    }

    return error;
}

/**
 * @brief
 *
 * @param mode
 * @return
 */
MC33HB2001_Error_t MC33HB2001_SetMode(MC33HB2001_Mode_t mode )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;

    if( mode == MC33HB2001_MODE_FULL_BRIDGE )
    {
        error = MC33HB2001_SetRegBit(MC33HB2001_CONTOL_MODE, MC33HB2001_REG_CONTROL);
    }
    else if ( mode == MC33HB2001_MODE_HALF_BRIDGE )
    {
        error = MC33HB2001_ResetRegBit(MC33HB2001_CONTOL_EN, MC33HB2001_REG_CONTROL);
    }
    return error;
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_EnableOutput( void )
{
    return MC33HB2001_SetRegBit(MC33HB2001_CONTOL_EN, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_DisableOutput( void )
{
    return MC33HB2001_ResetRegBit(MC33HB2001_CONTOL_EN, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_EnableVirturalInput( void )
{
    return MC33HB2001_SetRegBit(MC33HB2001_CONTOL_INPUT, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @return
 */
MC33HB2001_Error_t MC33HB2001_DisableVirturalInput( void )
{
    return MC33HB2001_ResetRegBit(MC33HB2001_CONTOL_INPUT, MC33HB2001_REG_CONTROL);
}

/**
 * @brief
 *
 * @param vin
 * @param value
 * @return
 */
MC33HB2001_Error_t MC33HB2001_SetVirturalInput( MC33HB2001_VirtualInput_t vin, uint8_t value )
{
    MC33HB2001_Error_t error = MC33HB2001_ERROR;

    if( vin == MC33HB2001_VIN1 )
    {
        if( value > 0 )
        {
            error = MC33HB2001_SetRegBit(MC33HB2001_CONTOL_VIN1, MC33HB2001_REG_CONTROL);
        }
        else
        {
            error = MC33HB2001_ResetRegBit(MC33HB2001_CONTOL_VIN1, MC33HB2001_REG_CONTROL);
        }
    }
    else if( vin == MC33HB2001_VIN1 )
    {
        if( value > 0 )
        {
            error = MC33HB2001_SetRegBit(MC33HB2001_CONTOL_VIN2, MC33HB2001_REG_CONTROL);
        }
        else
        {
            error = MC33HB2001_ResetRegBit(MC33HB2001_CONTOL_VIN2, MC33HB2001_REG_CONTROL);
        }
    }

    return error;
}

