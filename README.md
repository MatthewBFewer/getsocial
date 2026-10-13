# - getsocial -
### Ever grow tired of having to open a bunch of websites to paste in URLs to your socials when filling out a job application? Here is my simple but effective solution...
- C program for Linux systems that streamlines copying frequently used URLs to your clipboard. Supported on Wayland and x11.

- A binary (`getsocial`) is included in this repository, but you must build it yourself if you want to change the links and specify what you want the flags to do. dependencies will need to be installed as defined below.

## Example usage
```
~$ getsocial
Usage: getsocial [-g | -l]
  -g  Copy GitHub profile link
  -l  Copy LinkedIn profile link
~$ getsocial -l
LinkedIn link copied to clipboard!
```

## Build Instructions

Safe build command:\
    gcc -std=c11 -Wall -Wextra -O2 getsocial.c -o getsocial

## Usage Instructions/Notes:

This must be either wayland or x11, otherwise the program will likely throw an error:\
    echo "$XDG_SESSION_TYPE"

OS: Only tested on Ubuntu 26.04, but will probably work on many other similar Linux distributions

Dependencies:\
    sudo apt install build-essential wl-clipboard xclip

#### Optional but recommended (add getsocial to your binaries folder):\
  sudo install -m 755 getsocial /usr/local/bin/getsocial
