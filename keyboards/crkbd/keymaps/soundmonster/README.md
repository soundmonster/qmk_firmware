# Soundmonster's layout for Corne

### Features

* Modern OLED support (many thanks to @drashna):
  * Proper orientation
  * Graphic layer indicator ↑ ↓
  * Graphic modifier indicator ⌘ ⇧ ⌥  ⌃
* Similar enough to the default keymap so you can easily port your custom keymap to it
* Mac-friendly (Command and Option on the thumbs)
* Vim-friendly (Esc, `:` and Ctrl on the thumbs)
* Full per-key RGB Matrix support out of the box (you still have to go through the nightmare of soldering yourself though 😉)

### Build instructions

* `make crkbd:soundmonster:dfu` to build and flash the left half
* `make crkbd:soundmonster:dfu RGB_MATRIX_SPLIT_RIGHT=yes` to build and flash the right half
* This keymap expects a DFU bootloader on the promicros in your Corne. While DFU is supposedly better, you may just as well stick to the Catarina bootloader that is installed on most promicros by default: change the `BOOTLADER` setting to `catarina` in `rules.mk`.
