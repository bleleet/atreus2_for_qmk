/* Copyright 2020 Bleleet <bleleet@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

enum atreus_layers {
    _QWERTY,
    _LOWER,
    _UPPER
};

#define QWERTY TO(_QWERTY)
#define LOWER MO(_LOWER)
#define UPPER TO(_UPPER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_GRV,  KC_BSLS, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_ESC,  KC_TAB,  KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  LOWER,   KC_MINS, KC_QUOT, KC_ENT
  ),

  [_LOWER] = LAYOUT(
    KC_EXLM, KC_AT,   KC_UP,   KC_DLR,  KC_PERC,                   KC_PGUP, KC_7,    KC_8,    KC_9,    KC_BSPC,
    KC_LPRN, KC_LEFT, KC_DOWN, KC_RGHT, KC_RPRN,                   KC_PGDN, KC_4,    KC_5,    KC_6,    KC_NO,
    KC_LBRC, KC_RBRC, KC_HASH, KC_LCBR, KC_RCBR, KC_CIRC, KC_AMPR, KC_ASTR, KC_1,    KC_2,    KC_3,    KC_PLUS,
    UPPER,   KC_INS,  KC_LGUI, KC_LSFT, KC_BSPC, KC_LCTL, KC_LALT, KC_SPC,  _______, KC_DOT,  KC_0,    KC_EQL
    ),

  [_UPPER] = LAYOUT(
    KC_INS,  KC_HOME, KC_UP,   KC_END,  KC_PGUP,                   KC_UP,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_DEL,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                   KC_DOWN, KC_F4,   KC_F5,   KC_F6,   KC_F11,
    KC_NO,   KC_VOLU, KC_NO,   KC_NO,   _______, _______, _______, KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F12,
    QWERTY,  KC_VOLD, _______, _______, _______, _______, _______, _______, QWERTY,  KC_PSCR, KC_SLCK, KC_MPLY
    )
};
