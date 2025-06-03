## This repository contains some code that can run on a Nucleo-F446RE board, and blinks an led.

The following describes the entire build process:

### Clone the repository, compile the files, and flash them onto the microcontroller:
```
git clone git@github.com:osu-esdc/Nucleo-F446RE-LED.git
cd Nucleo-F446RE-LED/src
make
make flash
```
-> should now see the green LED on the Nucleo-F446RE board flash!  

###### For debugging, you can open a server and client window:
For server:
```
make load
```

###### To open a folder from WSL in VScode, just cd into that folder and use the command: `code .`

For client (either in other WSL terminal or in VSCode terminal):  

```
make client
```
```
(gdb) start
```
-> should now see the green LED on the Nucleo-F446RE board flash!  

