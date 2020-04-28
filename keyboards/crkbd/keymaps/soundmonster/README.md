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
* This requires DFU support. You may want to change the bootloader back to `catarina` in `rules.mk`.
