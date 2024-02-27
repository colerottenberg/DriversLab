# The Level

## Description
The level is a simple program that communicates with an on-board accelerometer and when the device is level, it will light up a green LED. When the device is not level, it will light up a red LED. The device communicates over I2C to the accelerometer and the LEDs are controlled by PIO.

## Building
To build the fisrt time, run the following command:

```bash
mkdir build
cd build
cmake -DPICO_BOARD=adafruit_feather_rp2040 ..
```

After a successful CMake run, you can build the project with:

```bash
make
```

## Flashing
To flash the program to the board, run the following command:

```bash
cp level.uf2 /media/$USER/RPI-RP2
```