#/opt/arduino/hardware/tools/avrdude -C/opt/arduino/hardware/tools/avrdude.conf -q -q -patmega168 -carduino -P usb -b19200 -D -Uflash:w:/tmp/build9193052523845434398.tmp/src.cpp.hex:i


#!/bin/bash


/opt/arduino/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega168 -DF_CPU=8000000L -DARDUINO=152 -I/opt/arduino/hardware/arduino/avr/cores/arduino -I/opt/arduino/hardware/arduino/avr/variants/standard /tmp/build6903474054884972233.tmp/src.cpp -o /tmp/build6903474054884972233.tmp/src.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega168 -DF_CPU=8000000L -DARDUINO=152 -I/opt/arduino/hardware/arduino/avr/cores/arduino -I/opt/arduino/hardware/arduino/avr/variants/standard /tmp/build6903474054884972233.tmp/serialComm.cpp -o /tmp/build6903474054884972233.tmp/serialComm.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-g++ -c -g -Os -w -fno-exceptions -ffunction-sections -fdata-sections -MMD -mmcu=atmega168 -DF_CPU=8000000L -DARDUINO=152 -I/opt/arduino/hardware/arduino/avr/cores/arduino -I/opt/arduino/hardware/arduino/avr/variants/standard /tmp/build6903474054884972233.tmp/brushless.cpp -o /tmp/build6903474054884972233.tmp/brushless.cpp.o 
  
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/WInterrupts.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/wiring_pulse.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/wiring_digital.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/wiring.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/hooks.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/wiring_analog.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/malloc.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/wiring_shift.c.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/IPAddress.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/main.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/USBCore.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/CDC.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/WMath.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/HardwareSerial.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/WString.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/Tone.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/new.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/Print.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/Stream.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-ar rcs /tmp/build6903474054884972233.tmp/core.a /tmp/build6903474054884972233.tmp/HID.cpp.o 
/opt/arduino/hardware/tools/avr/bin/avr-gcc -Os -Wl,--gc-sections -mmcu=atmega168 -o /tmp/build6903474054884972233.tmp/src.cpp.elf /tmp/build6903474054884972233.tmp/src.cpp.o /tmp/build6903474054884972233.tmp/serialComm.cpp.o /tmp/build6903474054884972233.tmp/brushless.cpp.o /tmp/build6903474054884972233.tmp/core.a -L/tmp/build6903474054884972233.tmp -lm 
/opt/arduino/hardware/tools/avr/bin/avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 /tmp/build6903474054884972233.tmp/src.cpp.elf /tmp/build6903474054884972233.tmp/src.cpp.eep 
/opt/arduino/hardware/tools/avr/bin/avr-objcopy -O ihex -R .eeprom /tmp/build6903474054884972233.tmp/src.cpp.elf /tmp/build6903474054884972233.tmp/src.cpp.hex 

