# What is this?
This is a basic kernel. It can display text to the screen via VGA.
![Image of kernel](images/screenshot.png)

# Installation
## Setup

Ensure you are in a linux/WSL envionment.
Also ensure you have the dependencies installed:

Debain/Ubuntu:

`sudo apt install build-essential mtools xorriso grub-pc grub-efi-amd64`

Fedora:

`sudo dnf install @development-tools mtools xorriso grub2 grub2-efi-x64`

Arch:

`sudo pacman -S base-devel mtools xorriso grub`

## Install

Open a terminal in a preferably empty directory.
Run the following:

```sh
git clone https://github.com/Advaith-Hello/KernelProject.git/
cd KernelProject/
make```

There should now be a `bin` folder, inside of which you'll find a `kernel.bin` and `myos.iso`.

## Running
The best way to run this is to emulate/virtualize with qemu.
To do this, first install `qemu-system-x86_64`

Then, just run:
`./run.sh`

It should open up a window for you with the OS.

