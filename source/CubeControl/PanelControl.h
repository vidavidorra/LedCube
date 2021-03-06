/*******************************************************************************
 * Begin of file PanelControl.h
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
 * A PanelControl PCB holds three LED Sink Drivers.
 * 
 ******************************************************************************/

#ifndef PANELCONTROL_H
#define PANELCONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Switches
 ******************************************************************************/
#define PC_ENABLE_SELF_TEST_NO

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <xc.h>
#include "Debug.h"
#include "LedDriver.h"
#include "CubeControlData.h"
#ifdef PC_ENABLE_SELF_TEST_YES
#include "Delay.h"
#endif /* PC_ENABLE_SELF_TEST_YES */

/*******************************************************************************
 * Defines
 ******************************************************************************/
/** Number of LedDrivers on a PanelControl PCB */
#define N_LEDDRIVERS    3

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
/**
 * Initialize everything needed for a PanelControl PCB.
 * 
 * @note    This initializes a LED Sink Driver using @ref LedDriver_init.
 */
void
PanelControl_init(void);

/**
 * Update the outputs of a PanelControl PCB by calling @ref LedDriver_update
 * three times.
 * 
 * @param   _pCubeControlData Pointer to @ref CubeControlData structure.
 * @param   _pCubeData Pointer to the first element of a CubeData structure
 * array.
 * @param   _layer The layer to update.
 * @param   _panel The panel to update.
 * @param   _bamRound The BAM-round to update.
 */
void
PanelControl_update(const pCubeControlData_t _pCubeControlData,
                    const pCubeData_t _pCubeData,
                    const uint8_t _layer,
                    const Panels_t _panel,
                    const uint8_t _bamRound);

/**
 * Turn all the LEDs of a PanelControl PCB off using @ref LedDriver_allOff.
 */
void
PanelControl_allOff(void);

/**
 * Turn all the LEDs of a PanelControl PCB on using @ref LedDriver_allOn.
 */
void
PanelControl_allOn(void);

#ifdef PC_ENABLE_SELF_TEST_YES
/**
 * Run a self test on a PanelControl PCB. I.e. test a PanelControl PCB.
 * Loops through all the outputs of a PanelControl PCB by putting on one output
 * at a time.
 * 
 * @param   void
 * @return  void
 * @Example <code>PanelControl_selfTest();</code>
 */
void
PanelControl_selfTest(void);
#endif /* PC_ENABLE_SELF_TEST_YES */

#ifdef __cplusplus
}
#endif

#endif /* PANELCONTROL_H */
/* End of file PanelControl.h */
