/*
 * Pretend your DMX lights are neopixels using DFRobot shield and 4 channel
 * lights + DMX_master.ino library 
 * Lee Wilkins + Jane Hacker November 2018
 */

/*
  DMX_Master.ino - Example code for using the Conceptinetics DMX library
  Copyright (c) 2013 W.A. van der Meeren <danny@illogic.nl>.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 3 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/


#include <Conceptinetics.h>
//
// CTC-DRA-10-R2 ISOLATED DMX-RDM SHIELD JUMPER INSTRUCTIONS
//
// Set !EN (right hand side) when uploading
// Set EN (left hand side) when running
// Or no jummper altogether and you can do all the things (in master mode)*
//   and you will see the lights blink to the data being sent over the line!
//
// * This will only work if the RX-???? jummper is also unset.


//
// The number of channels the master will control
//


// The above depends on amount of memory you have avaliable
// Control data will always be sent to all 255 channels
// A default of the first 100 channels will fit on a typical UNO
// A minimum of 1 channel
//
// If you are controlling lights for example:
// Channel 1 is white
// Channel 2 is Red
// Channel 3 is Green
// Channel 4 is Blue
//
// A total of 4 channels!



#define DMX_MASTER_CHANNELS   170 // 10 channels for each light. maybe to be fixed
const int B = 4275;               // B value of the thermistor
const int R0 = 100000;            // R0 = 100k
#define RXEN_PIN  2
#define lamps 16
struct pixelBuffer {
  int lamp;
  int red;
  int green;
  int blue;
  int white;
};
pixelBuffer pBuff[lamps]; // array of buffer pieces the size of the amount of lamps
//
// A little macro that takes a percentage and chnages it to 0-255
//
#define MAX_VALUE 255
#define PER_TO_VAL(percent) ((MAX_VALUE/100) * percent)
typedef enum DmxCh {
  RED    = 0,
  GREEN  = 1,
  BLUE   = 2,
  WHITE  = 3

} DmxCh;

DMX_Master        dmx_master(DMX_MASTER_CHANNELS, RXEN_PIN);
void setup() {
  dmx_master.enable();
  int startChannel = 1;
  int endChannel   = DMX_MASTER_CHANNELS;
  int byteValue    = PER_TO_VAL(0);
  dmx_master.setChannelRange ( startChannel, endChannel, byteValue );
}

void loop() {
  //set_rgb_value(1, 255, 0, 0,0); // Old no buffer style setting a pixel
  sequenceOld(); // Old
  sequenceBuffer();
}

void setPixel(int lampNumber, int red, int green, int blue, int white) {
  pBuff[lampNumber].lamp = lampNumber;
  pBuff[lampNumber].red = red;
  pBuff[lampNumber].green = green;
  pBuff[lampNumber].blue = blue;
  pBuff[lampNumber].white = white;

}

void showPixels() {
  for (int i = 0; i < lamps; i++) {
    int channelNumber = pBuff[i].lamp * 10;
    // Set each of the colors
    dmx_master.setChannelValue(channelNumber + RED,   pBuff[i].red  );
    dmx_master.setChannelValue(channelNumber + GREEN, pBuff[i].green);
    dmx_master.setChannelValue(channelNumber + BLUE,  pBuff[i].blue );
    dmx_master.setChannelValue(channelNumber + WHITE, pBuff[i].white );
  }
  clearBuffer();
}

void clearBuffer() {
  for (int i = 0; i < lamps + 1; i++) {
    pBuff[i].lamp = i;
    pBuff[i].red = 0;
    pBuff[i].green = 0;
    pBuff[i].blue = 0;
    pBuff[i].white = 0;
  }
}

// Old function that does it without th ebuffer
void set_rgb_value(int lampNumber, int red, int green, int blue, int white) {
  int channelNumber = lampNumber * 10;
  // Set each of the colors
  dmx_master.setChannelValue(channelNumber + RED,   red  );
  dmx_master.setChannelValue(channelNumber + GREEN, green);
  dmx_master.setChannelValue(channelNumber + BLUE,  blue );
  dmx_master.setChannelValue(channelNumber + WHITE,  white );
}


void sequenceBuffer() {
  for (int i = 0; i < 255; i++) {
    for (int j = 0; j < lamps; j++) {
      setPixel(j, i, 255, 0, 0);
    }
    showPixels();
    delay(5);
  }
  for (int i = 255; i > 0; i--) {
    for (int j = 0; j < lamps; j++) {
      setPixel(j, i, 255, 0, 0);
    }
    showPixels();
    delay(5);
  }
}
void sequenceOld() { //  using old no buffer style
  for (int i = 0; i < 255; i++) {
    for (int j = 0; j < lamps; j++) {
      set_rgb_value(j, i, 255, 0, 0);
    }
    delay(5);
  }
  for (int i = 255; i > 0; i--) {
    for (int j = 0; j < lamps; j++) {
      set_rgb_value(j, i, 255, 0, 0);
    }
    delay(5);
  }
}

