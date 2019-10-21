# dspic-guitar-pedal
A dsPIC-based guitar pedal. It is built around a 16-bit DSP microprocessor. The project is designed to showcase some common practices in digital signal processing, PCB design and embedded programming. The A/D and D/A conversions are done using 12-bits, so the lowpass filters are designed to take away a lot of the higher frequencies, which results in a quite unique and dark sound of the pedal when it is on.

## Circuit

The circuit is designed using `Altium Designer v17.1.5 Build 472`. It is based around a [breakout board](https://download.mikroe.com/documents/full-featured-boards/easy/dspicpro-v4/dspicpro4-mcu-cards-manual-v100.pdf)) designed and sold by Mikroelektronika for the [dsPIC60F6014A-PF microcontroller](http://ww1.microchip.com/downloads/en/devicedoc/70143e.pdf). The circuit supports reprogramming of the microcontroller using the [Mikroelektronika dsPIC Flash Programmer](http://www.rlx.sk/mikroelektronika/dspicflash_manual_v102.pdf). The dsPIC has an in-built 12-bit A/D converter, so the only external module (apart from the LM324 OP-AMP) is an [MCP4921 12-bit D/A converter](http://ww1.microchip.com/downloads/en/devicedoc/21897b.pdf). Third party models sourced from [SnapEDA](https://www.snapeda.com/home/). All the project files (including the third party models) can be found in the `circuit` directory. The schematic of the circuit is given below.

![Schematic](circuit/figures/schematic.png)

The PCB is designed on a two-layer Eurocard. Industry-standard output files detailing the design of the PCB can be found in `circuit/Project Outputs for GuitarPedal`.

## Code

The code is written using Mikroelektronika `mikroC PRO for dsPIC v7.1.0`. The essential code (`template.c`) is written in C and given in the `code` directory, and shows how to initiate all the modules of the microcontroller needed, and how to interface the D/A Converter. An example of using that code to create a delay effect is given in `delay.c`.




