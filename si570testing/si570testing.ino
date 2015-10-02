/*
*  A lean version of the Si570 sketch to test an si570 
*  Wiring details on http://blog.riyas.org
* 
* Modified from Radiono - The Minima's Main Arduino Sketch (from : http://github.com/afarhan/radiono )
* Copyright (C) 2013 Ashar Farhan
*
* This program is free software: you can redistribute it and/or modify it
* under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option)
* any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License along with
* this program. If not, see <http://www.gnu.org/licenses/>.
*/
#define __ASSERT_USE_STDERR
#include <assert.h>
/*
* Wire is only used from the Si570 module but we need to list it here so that
* the Arduino environment knows we need it.
*/
#include <Wire.h>
#include <avr/io.h>
#include "Si570.h"
#include "debug.h"
#define SI570_I2C_ADDRESS 0x55
Si570 *vfo;
int count = 0;
char b[20], c[20], printBuff[32];
void setup() {
    // Initialize the Serial port so that we can use it for debugging
    Serial.begin(115200);
    Serial.println("Initialising!");
    // The library automatically reads the factory calibration settings of your Si570
    // but it needs to know for what frequency it was calibrated for.
    // Looks like most HAM Si570 are calibrated for 56.320 Mhz.
    // If yours was calibrated for another frequency, you need to change that here
    vfo = new Si570(SI570_I2C_ADDRESS, 56320000);
    if (vfo->status == SI570_ERROR) {
        // The Si570 is unreachable. Show an error for 3 seconds and continue.
        Serial.println("Si570 comm error");
        delay(3000);
    }
    // This will print some debugging info to the serial console.
    vfo->debugSi570();
    //set the initial frequency
    vfo->setFrequency(26150000L);//start frequency at 26MHZ!
}
void loop(){
    //vfo->setFrequency(14497000l);//fixed signal
    //Below will sweep slowly arounf 144.97MHZ
    for (int foff = 1; foff < 1000; foff++) {
        vfo->setFrequency(14497000l+foff*10);
        delay(100);
    }
}
