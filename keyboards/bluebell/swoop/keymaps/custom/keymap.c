/* Copyright 2022 James White <jamesmnw@gmail.com>
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

#define TAPPING_TERM 200

enum layers {
    _BASE,
    _LAYER1,
    _LAYER2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * BASE
 * ,---------------------------------.     ,----------------------------------.
 * |  Q  |   W  |   E  |   R  |   T  |     |   Z  |   U  |   I  |   O  |   P  |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |  A  |   S  |   D  |   F  |   G  |     |   H  |   J  |   K  |   L  |   ;  |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |  Y  |   X  |   C  |   V  |   B  |     |   N  |   M  |   ,  |   .  |   /  |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              | Esc  | L1   | Tab  |     | Enter | Spc  | BSpc |
 *              `--------------------'     `--------------------'
 */
[_BASE] = LAYOUT_split_3x5_3(
    KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,   KC_S,    KC_D,    KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    MT(MOD_LSFT, KC_Z),   KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  MT(MOD_RSFT, KC_SLSH),
                       MT(MOD_LALT, KC_ESC),  KC_LGUI,  MT(MOD_LCTL, KC_TAB),      KC_ENT,  KC_SPC,  KC_BSPC
),

/*
 * LAYER 1
 * ,---------------------------------.     ,----------------------------------.
 * |  1  |   2  |   3  |   4  |   5  |     |   6  |   7  |   8  |   9  |   0  |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * |  `  |      |      |      |      |     | Left | Down |  Up  | Rght |  '   |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |     |      |      |      |      |     |   -  |   =  |   [  |   ]  |   \  |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              | TRNS | TRNS |      |     |      |      |      |
 *              `--------------------'     `--------------------'
 */
[_LAYER1] = LAYOUT_split_3x5_3(
    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_GRV, KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_QUOT,
    KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                       KC_TRNS, KC_TRNS, KC_NO,       KC_NO,   KC_NO,   KC_NO
),

/*
 * LAYER 2
 * ,---------------------------------.     ,----------------------------------.
 * | F1  |  F2  |  F3  |  F4  |  F5  |     |  F6  |  F7  |  F8  |  F9  |  F10 |
 * |-----+------+------+------+------|     |------+------+------+------+------|
 * | F11 |  F12 |      |      |      |     | MRWD | VOLD | VOLU | MFFD | MUTE |
 * |-----+------+------+------+------|     ,------+------+------+------+------|
 * |     |      |      |      |      |     |      |      |      |      |      |
 * `------------+------+------+------|     |------+------+------+-------------'
 *              |      |      |      |     |      |      |      |
 *              `--------------------'     `--------------------'
 */
[_LAYER2] = LAYOUT_split_3x5_3(
    KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
    KC_F11, KC_F12,  KC_NO,   KC_NO,   KC_NO,       KC_MRWD, KC_VOLD, KC_VOLU, KC_MFFD, KC_MUTE,
    RCS(KC_NO), KC_NO, KC_NO, KC_NO, KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                       KC_NO,    KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO
)
};
