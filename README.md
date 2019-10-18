# guitar-pedal
A dsPIC-based guitar pedal.

## Circuit

The circuit is designed using Altium Designer v17.1.5 Build 472. It is based around a breakout board for the dsPIC60F6014A-PF microcontroller designed and sold by Mikroelektronika (see Resources for documentation). Third party models sourced from [SnapEDA](https://www.snapeda.com/home/). All the project files (including the third party models) can be found in the `circuit` directory.

## Code

The code is written using Mikroelektronika mikroC PRO for dsPIC v7.1.0. The dsPIC is programmed using a USB programmer designed and sold by Mikroelektronika (see Resources for documentation). The template of the code is written in C and given in the `code` directory.

## Resources

[dsPIC30F6014A datasheet](http://ww1.microchip.com/downloads/en/devicedoc/70143e.pdf)

[Mikroelektronika dsPIC PRO4 MCU Card Manual](https://download.mikroe.com/documents/full-featured-boards/easy/dspicpro-v4/dspicpro4-mcu-cards-manual-v100.pdf)

[Mikroelektronika dsPIC Flash Programmer User Manual](http://www.rlx.sk/mikroelektronika/dspicflash_manual_v102.pdf)
