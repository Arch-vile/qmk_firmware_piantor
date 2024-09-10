# Piantor

Here are the files you are looking for:
keymaps/Arch-vile/keymap.c

To build the firmware:

```bash
qmk compile
# Compiling keymap with gmake --jobs=1 beekeeb/piantor:Arch-vile
```

Should get the firmware file:
`beekeeb_piantor_Arch-vile.uf2`

To install the firmware:
Repeat the following steps for each half of the keyboard:
1. Keep the `BOOTSEL` button pressed
2. Plug in the USB cable
3. Drag and drop the firmware file to the USB drive that appears

# Original README

![Piantor](https://i.imgur.com/xIF754Qh.jpg)

Piantor is a Cantor fork with Raspberry Pi Pico, hybrid hotswap socket and soldered-in switches support, and a breakable column.

* Keyboard Maintainer: [beekeeb](https://github.com/beekeeb)
* Hardware Supported: RP2040
* Hardware Availability: https://shop.beekeeb.com

Make example for this keyboard (after setting up your build environment):

    make beekeeb/piantor:default

Flashing example for this keyboard:

    make beekeeb/piantor:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Hold the `BOOTSEL` button on the PCB while plugin in the usb cable.
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
