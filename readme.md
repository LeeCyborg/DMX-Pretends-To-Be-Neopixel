# DMX >> NeoPixel

## Why
Do you want to pretend your giant DMX lamps are NeoPixels? Do you not want to think about DMX and just use your beloved neopixel patterns on your stage lighting or gigantic art? This code uses Adafruit Neopixel style structure so you can just copy/paste existing patterns onto DMX lights. 

It is helpful to be familiar with the Adafruit Neopixel library, because some of this only makes sense if you're trying to emulate it. 

## What You'll Need
This uses the [DF Robot DMX Shield](https://www.dfrobot.com/product-984.html) to control standard 4 or 8 channel [DMX lights](https://www.amazon.com/Lights-MFL-Lighting-Activated-Wedding/dp/B01CTU89N8/ref=sr_1_17?ie=UTF8&qid=1541910731&sr=8-17&keywords=RGBW+dmx) You'll also need an [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3) which the shield fits on top of. Note: You can't use Serial while using DMX lights. You'll need DMX cables as well. 

## What is going on? 
todo
### What and Why DMX
DMX is a standard lighting system understood by many control boards and existing systems. Its great for larger scale installations or interactive pieces that require more power than even the brightest WS2811 addressable LEDs or need to be controleld through existing stage lighting ect. 
### What are Channels ? 
An oversimplification, but all you really need to know, descripton of channels: A channel referes to an address of a piece of information. For our purposes, they refer to the R, G, B, W values on lights. Each channel contains a piece of data. Each light is assigned a channel, and the number of that channel is the first piece of data for that light. There are a maximum of 512 channels for a set of DMX lights, although more can be added as "Slave" mode.   
**In 4 channel mode this looks like:**    
Lamp 1 is set to channel 1 (Physically on the lamp)    
 Channel 1 is red on the first lamp   
 Channel 2 is green on the first lamp      
 Channel 3 is blue on the first lamp      
 Channel 4 is white on the first lamp      
 A total of 4 channels per lamp      
Lamp 2 is set to channel 5 (Physically on the lamp)   
 Channel 5 is red on second lamp      
 Channel 6 is green on second lamp      
 etc...    
    
Some lamps have 8 channels that have functions like strobe, color changing or dimming. The value of each channel will effect the attrubite of that channel. For this case, we want to stick to 4 channel mode, or, in the code settings (below) set it to effectively bypass the other 4 channels.   

### What are Slave Mode, and channel modes?
Setting your DMX lamp to slave mode means it will echo the lamp direclty preceeding it. You can set all of your lamps to slave and they will all do the same thing! Yay! Many lamps have a 4 or 8 channel mode. Its a good idea to check the settings of your specific lamp. 

## Software Setup
This program extends [Conceptinetics DMX library](https://sourceforge.net/p/dmxlibraryforar/wiki/Home/).  I have tested this on Arduino IDE 1.8.5. 

## Hardware Setup
Connect your DMX lights in series. All lights should be in 4 channel mode if possible. If they are in 8 channel mode, you'll need to make code modifications (See below). Some DMX lights have 8 channels. You have a maximum of 512 channels. Set the lights to . 
If you are in 4 channel mode   
Lamp 1 >> Channel 1     
Lamp 2 >> Channel 5    
Lamp 3 >> Channel 9    
... etc ...   
If you're in 8 channel mode   
Lamp 1 >> Channel 1    
Lamp 2 >> Channel 9    
Lamp 3 >> Channel 17    
... etc ...    
If you're not sure    
Lamp 1 >> Channel 10    
Lamp 2 >> Channel 20    
Lamp 3 >> Channel 30    
... etc ...   

You can test your by looping through the first 10 channels of your light and see how many channels there are. This turns each channel on and off so you can see what they do.   

```   
for (int i = 0; i < 10; i++) {   
 dmx_master.setChannelValue(i, 255 );   
 delay(1000);   
 dmx_master.setChannelValue(i, 255 );   
 delay(100);
}  
```

## Channel Spacing variable 
This indicates the amount of channels between each lamp. If you are sure you are using 4 channel lights, set channelSpacing to 4, and then physically set your lamp channels to incrments of 4 (1, 5, 9 etc). If you aren't sure, you can set channelSpacing to 10, and set each of your lamps to 10, 20, 30, 40 etc). In this case, many channels wont get used, but you're sure not to overlap on channels. 

## Style and buffers
There are two ways of using this code. The first is to directly assign a value to a lamp, and the second is "Neopixel style" where you add the code to the buffer and then show it. This mode exists so you can copy old neo pixel patterns taht are dependant on the buffer implimentation. 

### Direct control 
` set_rgb_value(lamp, red, green, blue, white);` 
` set_rgb_value(1, 255, 0, 0, 0);`
This will set the value of lamp 1 (lamps start at 1) to red (values between 0-255) immidately 

### Buffer control 
`setPixel(1, 0, 255, 0, 0);
showPixels(); ` 
The buffer method emualtes NeoPixels and requires the showPixels command. This can replace strip.show(); in your previous noe pixel examples, and setPixel() can replace strip.setPixelColor().   

## Code
todo

## Sequences 
I've translated a few peices of popular Neopixel code here in the Examples folder   
**Wave:** Sends running sin waves lights through the whole strip    
**Fade:** Pulses the whole strip with a breath like function    
**Fire:** Flame like effect    
**Twinkle:** Snowglobe twinkle    




###### Copyright (c) November 2018 Lee (Lindy) Wilkins <hello@leecyb.org> and Jane Hacker <Jhacker1@gmai.com>.  All right reserved. This library is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser General Public  License as published by the Free Software Foundation; either  version 3 of the License, or (at your option) any later version.  This library is distributed in the hope that it will be useful,  but WITHOUT ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU  Lesser General Public License for more details.
