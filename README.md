# guessing-game-gadget

a guessing game written in C for the RP2040 Raspberry Pi Pico microcontroller.

![image](https://github.com/user-attachments/assets/0de8bc71-132b-4a88-9972-bd7118f8f7ea)

## required hardware

- Raspberry Pi Pico
- 1x breadboard
- 1x I2C LCD screen
- 2x LEDs (1 green, 1 red)
- 2x micro buttons
- 4x 220 ohm resistors
- 2x 10K ohm resistors
- cables

## required software

- CMake
- pico-sdk
- arm-none-eabi cross compiler (gcc preferred, clang works)

## setting up

wire your components like the picture as shown at the top.

if you change your pins, edit `guess.h` appropriately.

## building

```
// English
cmake -B build && cmake --build build -- -j4

// Turkish
cmake -B build -DLOCALE=1 && cmake --build build -- -j4 
```

## flashing

```
cp ./build/guessing_game.uf2 /<the mount place of pico>
```

## license

Copyright (c) 2024 Hakan Candar
All rights reserved.

This source code is licensed under the BSD 2-Clause License found in the
LICENSE file in the root directory of this source tree.
