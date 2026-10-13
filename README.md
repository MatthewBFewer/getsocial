# - getsocial -
C program for Linux systems that streamlines copying frequently used URLs to your clipboard. Supports both Wayland and x11.

## Build Instructions

Safe build command:
    gcc -std=c11 -Wall -Wextra -O2 getsocial.c -o getsocial

## Usage Instructions/Notes:

This must be either wayland or x11: 
    echo "$XDG_SESSION_TYPE"

OS: Only tested on Ubuntu 26.04, but will probably work on many other similar Linux distributions

Dependencies:
    sudo apt install build-essential wl-clipboard xclip

#### Optional but recommended (add getsocial to your binaries folder):
  sudo install -m 755 getsocial /usr/local/bin/getsocial
