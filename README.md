# mouse-stick

```bash
brew install dfu-programmer
```

```bash

tar -xvf arduino-firmware

# make arduino mouse
sudo dfu-programmer atmega16u2 flash --debug 1 arduino-firmware/Arduino-mouse-0.1.hex

# clear bootloader
sudo dfu-programmer atmega16u2 erase

# make arduino programmable
sudo dfu-programmer atmega16u2 flash --debug 1 arduino-firmware/Arduino-usbserial-uno.hex
```
