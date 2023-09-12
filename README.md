# Krokodil

Simple language that looks like Pascal.

Krokodil means crocodile.

## Quick start

This project must be cross platform, but I'm prefer program inside Linux.

To build project for Windows on Linux I use
[msvc-wine](https://github.com/mstorsjo/msvc-wine/)

For Arch Linux install this dependencies:

    sudo pacman -Sy wine samba python msitools python-simplejson python-six \
        ca-certificates libwbclient base-devel cmake clang

For Debian:

    apt-get update
    apt-get install -y wine64-development python3 msitools python3-simplejson \
        python3-six ca-certificates winbind build-essential cmake clang

To build project for Linux:

    ./configure
    make linux

To build project for Windows:

    ./configure
    make windows

After that all executable files can be found inside `build` and `build-msvc`.
