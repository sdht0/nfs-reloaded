# NFS Reloaded

## About

This is a simple car racing game in which you have to save your car from the
oncoming cars. This was created as a school project using the historical 
TurboC++ compiler and uses headers such as graphics.h, conio.h and dos.h.

## How to run

I got this running on Linux using dosbox.

* Download [TurboC++](https://www.developerinsider.in/download-turbo-c-for-windows-7-8-8-1-and-windows-10-32-64-bit-full-screen) and unzip it into the `~/TURBOC3` directory. The directory path is important as search paths are harcoded into TurboC++. 
* Copy `nfsreloaded.cpp` inside `~/TURBOC3`.
* Install [Dosbox](https://www.dosbox.com).
* Execute the following commands inside `dosbox`:
```bash
mount c ~
C:
cd TURBOC3/BIN
tc
```
* TurboC++ is now running. Open `nfsreloaded.cpp` using `File -> Open...` and run the program using `Run -> Run...`. This compiles the program and executes it.
* The game should now be running. Enjoy!

## License
GNU GPLv3
