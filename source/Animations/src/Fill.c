/*******************************************************************************
 * Begin of file Fill.c
 * Author: jdebruijn
 * Created on November 8, 2015, 12:29 PM
 * 
 *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
 * 
 * Copyright (c) 2015 Jeroen de Bruijn <vidavidorra@gmail.com>
 * 
 * This file is part of LedCube which is released under The MIT License (MIT).
 * For full license details see file "main.c" or "LICENSE.md" or go to
 * https://opensource.org/licenses/MIT
 * 
 ******************************************************************************/
 /** @file 
 * @brief Animations to fill a row, layer or whole LED cube.
 * 
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "Fill.h"

/*******************************************************************************
 * Functions
 ******************************************************************************/
void
FillRowAtOnceWithSingleColour( uint8_t _x, uint8_t _z,
        uint8_t _red, uint8_t _green, uint8_t _blue ) {
    DEBUG_PRINTF_FUNCTION_CALL("%u, %u, %u, %u, %u", _x, _z,
            _red, _green, _blue);
    
    uint8_t y;
    for(y = 0; y < CUBEDATA_MAX_Y_C; y++) {
        LedCube_setPixel(_x, y, _z, _red, _green, _blue);
    }

    return;
}

void
FillRowWithSingleColour( uint8_t _x, uint8_t _z,
        uint8_t _red, uint8_t _green, uint8_t _blue ) {
    DEBUG_PRINTF_FUNCTION_CALL("%u, %u, %u, %u, %u", _x, _z,
            _red, _green, _blue);
    
    uint8_t y;
    for(y = 0; y < CUBEDATA_MAX_Y_C; y++) {
        LedCube_setPixel(_x, y, _z, _red, _green, _blue);
        LedCube_updateUsingCopy();
        Delay_ms(100);
    }
    
    return;
}

void
FillLayerAtOnceWithSingleColour( uint8_t _z,
        uint8_t _red, uint8_t _green, uint8_t _blue ) {  
    DEBUG_PRINTF_FUNCTION_CALL("%u, %u, %u, %u", _z, _red, _green, _blue);
    
    uint8_t x;
    for(x = 0; x < CUBEDATA_MAX_X_C; x++) {
        FillRowAtOnceWithSingleColour(x, _z, _red, _green, _blue);
    }
    
    return;
}

void
FillLayerWithSingleColour( uint8_t _z,
        uint8_t _red, uint8_t _green, uint8_t _blue ) {
    DEBUG_PRINTF_FUNCTION_CALL("%u, %u, %u, %u", _z, _red, _green, _blue);
    
    uint8_t x;
    for(x = 0; x < CUBEDATA_MAX_X_C; x++) {
        FillRowWithSingleColour(x, _z, _red, _green, _blue);
    }
    
    return;
}

/* End of file Fill.c */
