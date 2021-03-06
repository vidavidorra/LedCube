/*******************************************************************************
 * Begin of file PanelControl.c
 * Author: jdebruijn
 * Created on July 12, 2015, 11:50 AM
 * 
 *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*
 * 
 * This file is part of LedCube.
 * 
 * Copyright (c) 2015  Jeroen de Bruijn  <vidavidorra@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 *~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~**/
/** @file
 * @brief Controls a single PanelControl PCB.
 * 
 ******************************************************************************/

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "PanelControl.h"

/*******************************************************************************
 * Functions
 ******************************************************************************/
void
PanelControl_init(void)
{
    LedDriver_init();

    DEBUG_PRINTF_FUNCTION_INITIALIZE_COMPLETE;
    return;
}

void
PanelControl_update(const pCubeControlData_t _pCubeControlData,
                    const pCubeData_t _pCubeData,
                    const uint8_t _layer,
                    const Panels_t _panel,
                    const uint8_t _bamRound)
{
    DEBUG_PRINTF_FUNCTION_CALL("%p, %p, %u, %d, %u", _pCubeControlData, \
            _pCubeData, _layer, _panel, _bamRound);

    /* Update in reverse order (BRG instead of RGB), because the Led Sink
     * Drivers shift the data through. So the data for the first Led Sink Driver
     * needs to be send last.
     */
    LedDriver_update(
        ((((_pCubeData + _layer * CUBEDATA_MAX_Z_C + _panel + 1)->blue         &
        _pCubeControlData->BamRoundMask[_bamRound]) >>
        _pCubeControlData->BamRoundShift[_bamRound]) << 8)                     |
        (((_pCubeData + _layer * CUBEDATA_MAX_Z_C + _panel)->blue              &
        _pCubeControlData->BamRoundMask[_bamRound]) >>
        _pCubeControlData->BamRoundShift[_bamRound]));
    LedDriver_update(
        ((((_pCubeData + _layer * CUBEDATA_MAX_Z_C + _panel + 1)->green        &
        _pCubeControlData->BamRoundMask[_bamRound]) >>
        _pCubeControlData->BamRoundShift[_bamRound]) << 8)                     |
        (((_pCubeData + _layer * CUBEDATA_MAX_Z_C + _panel)->green             &
        _pCubeControlData->BamRoundMask[_bamRound]) >>
        _pCubeControlData->BamRoundShift[_bamRound]));
    LedDriver_update(
        ((((_pCubeData + _layer * CUBEDATA_MAX_Z_C + _panel + 1)->red          &
        _pCubeControlData->BamRoundMask[_bamRound]) >>
        _pCubeControlData->BamRoundShift[_bamRound]) << 8)                     |
        (((_pCubeData + _layer * CUBEDATA_MAX_Z_C + _panel)->red               &
        _pCubeControlData->BamRoundMask[_bamRound]) >>
        _pCubeControlData->BamRoundShift[_bamRound]));

    return;
}

void
PanelControl_allOff(void)
{
    DEBUG_PRINTF_FUNCTION_CALL();

    uint8_t i;
    for (i = 0; i < N_LEDDRIVERS; i++) {
        LedDriver_allOff();
    }

    return;
}

void
PanelControl_allOn(void)
{
    DEBUG_PRINTF_FUNCTION_CALL();

    uint8_t i;
    for (i = 0; i < N_LEDDRIVERS; i++) {
        LedDriver_allOn();
    }

    return;
}

#ifdef PC_ENABLE_SELF_TEST_YES

/**
 * Self test using the update function by shifting a 64-bit value and extracting
 * the RGB values from it.
 * 
 * @param void
 * @return void
 */
void
PanelControl_selfTest(void)
{
    DEBUG_PRINTF_FUNCTION_CALL();

    PanelControlData_t data = {0, 0, 0, 0, 0, 0};
    pPanelControlData_t pPanelData = &data;

    uint64_t panelData = 1;
    uint8_t led;

    // Loop to 49 instead of 48 so all the outputs are '0' in the end.
    for (led = 0; led < 49; led++) {
        pPanelData->red_1 = (uint8_t) (panelData & 0x00000000000000FF);
        pPanelData->red_2 = (uint8_t) ((panelData & 0x000000000000FF00) >> 8);
        pPanelData->green_1 = (uint8_t) ((panelData & 0x0000000000FF0000) >> 16);
        pPanelData->green_2 = (uint8_t) ((panelData & 0x00000000FF000000) >> 24);
        pPanelData->blue_1 = (uint8_t) ((panelData & 0x000000FF00000000) >> 32);
        pPanelData->blue_2 = (uint8_t) ((panelData & 0x0000FF0000000000) >> 40);

        PanelControl_update(pPanelData);

        Delay_ms(1000);
        if (0 == (led + 1) % 8) {
            Delay_ms(2000);
        }
        panelData <<= 1; // Prepare the panelData for the next iteration.
    }

    SPI1_WaitTillTxBufferEmpty();

    return;
}
#endif /* PC_ENABLE_SELF_TEST_YES */
/* End of file PanelControl.c */
