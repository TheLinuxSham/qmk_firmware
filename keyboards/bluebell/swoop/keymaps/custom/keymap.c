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

// Add TapDance feature for layer switches and recognition
// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    SPC_LAYR1, // Our custom tap dance key; add any other tap dance keys to this enum
    ENT_LAYR2,
    SUPER
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(tap_dance_state_t *state);

// Functions associated with individual tap dances
void layer1_toggle(tap_dance_state_t *state, void *user_data);
void layer1_reset(tap_dance_state_t *state, void *user_data);

// Define Layouts
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Base Layer
 * ,---------------------------------.     ,----------------------------------.
 * |  Q  |  W  |  E  |  R  |  T  |        |  Z  |  U  |  I  |  O  |  P  |
 * |-----+-----+-----+-----+------|       |-----+-----+-----+-----+-----|
 * |  A  |  S  |  D  |  F  |  G  |        |  H  |  J  |  K  |  L  |  ;  |
 * |-----+-----+-----+-----+------|       |-----+-----+-----+-----+-----|
 * |  Y  |  X  |  C  |  V  |  B  |        |  N  |  M  |  ,  |  .  |  /  |
 * `-----------+-----+-----+------|       |-----+-----+-----+------------'
 *             | Ctrl | BSPC| Esc |       | Enter| SPC | Alt |
 *             `-------------------'       `-----------------'
 */
[_BASE] = LAYOUT_split_3x5_3(
    KC_Q, KC_W, KC_E, KC_R, KC_T,    KC_Y, KC_U, KC_I, KC_O, KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G,    KC_H, KC_J, KC_K, KC_L, KC_SCLN,
    MT(MOD_LSFT, KC_Z), KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_LSFT, KC_SLSH),
                       MT(MOD_LALT, KC_ESC),  KC_LGUI,  MT(MOD_LCTL, KC_TAB),      TD(SPC_LAYR1), TD(ENT_LAYR2),  KC_BSPC
),

/* Layer 1
 * ,---------------------------------.     ,----------------------------------.
 * |  1  |  2  |  3  |  4  |  5  |        |  6  |  7  |  8  |  9  |  0  |
 * |-----+-----+-----+-----+------|       |-----+-----+-----+-----+-----|
 * |  `  | End | PgUp| PgDn| Home |        |    |  -  |  =  |  [  |  ]  |
 * |-----+-----+-----+-----+------|       |-----+-----+-----+-----+-----|
 * | \|  |AltR |  @  |     |     |        |     |     |     |     |INT3 |
 * `-----------+-----+-----+------|       |-----+-----+-----+------------'
 *             | TRNS | TRNS| TRNS|       |  TD1| TRNS| TRNS|
 *             `-------------------'       `-----------------'
 */
[_LAYER1] = LAYOUT_split_3x5_3(
    KC_1, KC_2, KC_3, KC_4, KC_5,                           KC_6, KC_7, KC_8, KC_9, KC_0,
    KC_GRV, KC_END, KC_PGUP, KC_PGDN,KC_HOME,               KC_QUOT, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,
    MT(MOD_LSFT, KC_NUBS), KC_RALT, KC_AT, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO, KC_NO, MT(MOD_LSFT, KC_INT3),
                  KC_TRNS, KC_TRNS, KC_TRNS,                TD(SPC_LAYR1), KC_TRNS, KC_TRNS
),

/* Layer 2
 * ,---------------------------------.     ,----------------------------------.
 * | F1  | F2  | F3  | F4  | F5  |        | F6  | F7  | F8  | F9  | F10 |
 * |-----+-----+-----+-----+------|       |-----+-----+-----+-----+-----|
 * | F11 | F12 |BrUp |BrDn |PSCR |        |LEFT |DOWN | UP  |RGHT |     |
 * |-----+-----+-----+-----+------|       |-----+-----+-----+-----+-----|
 * |Shift|     |     |     |     |        |Prev |Vol- |Vol+ |Next |Mute |
 * `-----------+-----+-----+------|       |-----+-----+-----+------------'
 *             | TRNS | TRNS| TRNS|       | TRNS|  TD2| TRNS|
 *             `-------------------'       `-----------------'
 */
[_LAYER2] = LAYOUT_split_3x5_3(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,    KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
    KC_F11, KC_F12, KC_BRIU, KC_BRID, KC_PSCR, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_NO,
    KC_LSFT, KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MUTE,
                  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD(ENT_LAYR2), KC_TRNS
    )
};

// Define Tapdance behavior
// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) {
            return TD_SINGLE_TAP;
        } else {
            return TD_SINGLE_HOLD;
        }
    } else if (state->count == 2) {
        // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        // keystrokes of the key, and not the 'double tap' action/macro.
        if (!state->pressed) {
            return TD_DOUBLE_TAP;
        } else {
            return TD_DOUBLE_HOLD;
        }
    } else {
        return TD_UNKNOWN;
    }
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void layer1_toggle(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_ENT);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_LAYER1);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_LAYER1)) {
                // If already set, then switch it off
                layer_off(_LAYER1);
            } else {
                // If not already set, then switch the layer on
                layer_on(_LAYER1);
            }
            break;
        default:
            break;
    }
}

void layer1_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_LAYER1);
    }
    ql_tap_state.state = TD_NONE;
}

void layer2_toggle(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_LAYER2);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_LAYER2)) {
                // If already set, then switch it off
                layer_off(_LAYER2);
            } else {
                // If not already set, then switch the layer on
                layer_on(_LAYER2);
            }
            break;
        default:
            break;
    }
}

void layer2_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(_LAYER2);
    }
    ql_tap_state.state = TD_NONE;
}

void super_toggle(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_HOLD:
            tap_code(KC_LGUI);
            break;
        case TD_DOUBLE_HOLD:
            tap_code(MOD_MASK_SG);
            break;
        default:
            break;
    }
}

void super_reset(tap_dance_state_t *state, void *user_data) {
    if (ql_tap_state.state == TD_DOUBLE_HOLD) {
        unregister_code(KC_LGUI);
        unregister_code(KC_LSFT);
    }
    ql_tap_state.state = TD_NONE;
}
// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [SPC_LAYR1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layer1_toggle, layer1_reset),
    [ENT_LAYR2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, layer2_toggle, layer2_reset),
    [SUPER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, super_toggle, super_reset)
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}
