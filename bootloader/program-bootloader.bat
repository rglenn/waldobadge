avrdude -c usbtiny -p m328 -U lock:w:0x3F:m
avrdude -c usbtiny -p m328 -U lfuse:w:0xFF:m -U hfuse:w:0xd0:m -U efuse:w:0x06:m
avrdude -c usbtiny -p m328 -U flash:w:protrinket_12mhz.hex 
avrdude -c usbtiny -p m328 -U lock:w:0x2F:m