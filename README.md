# Pulse-Oximeter
Handheld, battery powered device for measuring heart BPM and blood-oxygen content with full custom PCB design, interface design and housing.

![PCB CAD Design](/img/cad_design.png)

## Introduction
It was created as a team project for a microprocessor controllers class at our university. The goal was to create a device that utilizes microcontrollers and at least 3 built-in interfaces.

## Parameters
* 3.3V power, by using two CR2032 coin cell batteries
* ATMega328p-AU with internal 8MHz clock
* MAX30102 I2C Sensor for measuring bpms and blood-oxygen levels
* 0.96" OLED SPI Display

## Working principles (and design choices)

![Electrical schematic](/img/schematic.png)

### Power
Device is powered by two 3V CR2032 batteries connected in series. To sustain 3.3V the batteries were connected to LD1117-3.3 fixed voltage reagulator.

### Bootloader
Due to 3.3V power supply and according to the documentation the chips oscillator had to be lowered from 16Mhz to 8Mhz. To save space on the PCB and also lower the cost of the device we choose to flash a new bootlader that enabled the internal 8Mhz oscillator.

### BPM measurement
To achieve fast readouts and not compromise accuracy we chose to increase the amount of samples (used to calculate the moving average) with time. This gives us very fast printout of the first readings and increases accuracy with the time of measurement.

### Splash screen animation
To add some life to our interface we decided to add a splash screen animation that plays everytime the device is turned on. Each frame of the animation is stored as a bitmap. Unfortunately loading all frames from program memory caused long boot time after the device was turned off for a while (week).

### PCB
![Assembled PCB](/img/assembled_pcb.png)

It wasn't in the requirements for the project but we decided to create a pcb for the device which allowed us to use SMD components and minify the size of the product. It was designed using Altium Designer and home-etched using B327 eatching solution. Toner transfer, before etching, was done using a solution of 70% rubbing alcohol and 30% acetone. To avoid solder briding and shorts uv curable solder mask was also put on.

### Enclousure
![Housing](/img/cad_housing.png)

Enclousure was designed in Fusion 360 and 3D printed using white PLA fillament. It was desinged around CAD files of the pcb.

## Team
<table>
<td align="center"><a href="https://github.com/ae-michu"><img src="https://avatars.githubusercontent.com/u/72276028?v=4" width="100px;" alt=""/><br /><sub><b>Michał Pękal</b></sub></a><br /><p style="font-size:12px">Electronics Design<br> Firmware</p></td>

<td align="center"><a href="https://github.com/olafka0"><img src="https://avatars.githubusercontent.com/u/82404928?v=4" width="100px;" alt=""/><br /><sub><b>Oliwia Wawrzyniak</b></sub></a><br /><p style="font-size:12px">UX/UI Design<br><br></p></td>

<td align="center"><a href="https://github.com/pablithone"><img src="https://avatars.githubusercontent.com/u/81630270?v=4" width="100px;" alt=""/><br /><sub><b>Paweł Lewandowski</b></sub></a><br /><p style="font-size:12px">Enclousure Design<br><br></p></td>
</table>

<br>
<br>
<br>

### Legal note
THE SOFTWARE, HARDWARE DESIGN ARE PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE AND HARDWARE DESIGN OR THE USE OR OTHER DEALINGS IN THE SOFTWARE AND HARDWARE DESIGN.