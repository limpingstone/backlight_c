# backlight_c
A mini tool written in C that changes the laptop backlight. Currently it is hardcoded with amdgpu configurations. This program mimics the functionality of Xbacklight yet eliminates the X server's randr overhead by directly changeing the value in /sys/class/amdgpu_bl0/backlight. Any constructive feedback on the code itself and platform compatibility is welcome and appreciated. 

## Installation 
To install the program, simply input the commands: 
```
$ make 
$ sudo make install
```

## Usage
To run the program, input the following command:
```
$ backlight [OPTION] [VALUE]
```
The options include `inc` and `dec` that respectively increases or decreases the brightness by the indicated value.

