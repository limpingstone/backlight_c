# backlight_c
A mini tool written in C that changes the laptop backlight without using the RandR extension. 

Currently, the program is hardcoded with amdgpu configurations. This program mimics the functionality of Xbacklight yet eliminates the X server overhead by directly changeing the value in `/sys/class/amdgpu_bl0/backlight`. Any constructive feedback on the code itself and platform compatibility is welcome and appreciated. 

## Installation 
To install the program, simply input the commands: 
```
$ make 
$ sudo make install
```

## Usage
To run the program, input the following command:
```
$ backlight_c [OPTION] [VALUE]
```
The options include `inc` and `dec` that respectively increases or decreases the brightness by the indicated value.

