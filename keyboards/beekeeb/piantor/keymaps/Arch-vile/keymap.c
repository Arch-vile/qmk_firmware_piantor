// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Each layer gets a name for readability.
enum layer_names {
    BASE,
    SYMBOLS,
    SYMBOLS_2,
    TEXT,
    MOUSE,
    WINDOWS,
    NUMBERS,
};

//Tap Dance Declarations
enum {
  TD_ESC_CAPS,
  TD_AMPR_PIPE,
  TD_AT_DLR,
  TD_SLSH_PSLS,
  TD_DQUO_QUOT,
  TD_LT_GT,
  TD_EQL_MINS,
  TD_LPRN_RPRN,
  TD_LCBR_RCBR,
  TD_LBRC_RBRC,
  TD_SCLN_COLN,
  TD_W_Q,
  TD_X_Z,
  TD_DOT_QUES,
  TD_COMM_EXLM,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(WINDOWS, KC_ESC):
              if (!record->tap.count) {      // If holding.
                if (record->event.pressed) { // On hold press.
                  register_mods(MOD_LGUI);   // Hold LGUI.
                } else {                     // On hold release.
                  unregister_mods(MOD_LGUI); // Release LGUI.
                }
              }
              return true;  // Continue normal handling.
    }
    return true;
}

tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_B),
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    [TD_AMPR_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_AMPR, KC_PIPE),
    [TD_AT_DLR] = ACTION_TAP_DANCE_DOUBLE(KC_AT, KC_DLR),
    [TD_SLSH_PSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    [TD_DQUO_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_DQUO, KC_QUOT),
    [TD_LT_GT] = ACTION_TAP_DANCE_DOUBLE(KC_LT, KC_GT),
    [TD_EQL_MINS] = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_MINS),
    [TD_LPRN_RPRN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
    [TD_LCBR_RCBR] = ACTION_TAP_DANCE_DOUBLE(KC_LCBR, KC_RCBR),
    [TD_LBRC_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
    [TD_SCLN_COLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    [TD_W_Q] = ACTION_TAP_DANCE_DOUBLE(KC_W, KC_Q),
    [TD_X_Z] = ACTION_TAP_DANCE_DOUBLE(KC_X, KC_Z),
    [TD_DOT_QUES] = ACTION_TAP_DANCE_DOUBLE(KC_DOT, KC_QUES),
    [TD_COMM_EXLM] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_EXLM)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3(
        KC_NO,   KC_NO,    TD(TD_W_Q),    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_NO,    KC_NO,
        KC_NO, LCTL_T(KC_A),    LALT_T(KC_S),    LGUI_T(KC_D),    LSFT_T(KC_F),    KC_G,                               KC_H,    RSFT_T(KC_J),    RGUI_T(KC_K),    RALT_T(KC_L),    RCTL_T(KC_P), KC_NO,
        KC_NO, KC_NO,    TD(TD_X_Z),    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    TD(TD_COMM_EXLM), TD(TD_DOT_QUES),  KC_NO, KC_NO,
                                            LT(NUMBERS, KC_TAB), LT(SYMBOLS, KC_SPC),  LT(WINDOWS, KC_ESC),           LT(MOUSE, KC_ENT),  LT(TEXT, KC_BSPC),  RALT(KC_U)
    ),
    [SYMBOLS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS,KC_ASTR, KC_QUOT,   KC_UNDS,  KC_CIRC,         KC_AT,  KC_HASH, KC_DLR,  KC_AMPR,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_PIPE,KC_PLUS, KC_DQUO,   KC_EQL,   KC_SLSH,         KC_LT,  KC_LPRN, KC_LCBR,KC_LBRC,  KC_SCLN, KC_TRNS,
        KC_TRNS, KC_TILD,KC_PERC, KC_GRV,    KC_MINS,  KC_BSLS,         KC_GT,  KC_RPRN, KC_RCBR,KC_RBRC,  KC_COLN, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_RCTL, KC_RGUI, KC_RALT
    ),
    [SYMBOLS_2] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS,          KC_QUOT,        KC_AMPR,          KC_AT,            KC_CIRC,                         KC_UNDS,         KC_DLR,           KC_HASH,          KC_ASTR,          KC_TRNS,          KC_TRNS,
        KC_TRNS, TD(TD_AMPR_PIPE), TD(TD_AT_DLR),  TD(TD_SLSH_PSLS), TD(TD_DQUO_QUOT), TD(TD_LT_GT),                    TD(TD_EQL_MINS), TD(TD_LPRN_RPRN), TD(TD_LCBR_RCBR), TD(TD_LBRC_RBRC), TD(TD_SCLN_COLN), KC_TRNS,
        KC_TRNS, KC_TRNS,          KC_TILD,        KC_PLUS,          KC_GRV,           KC_CIRC,                         KC_UNDS,         KC_HASH,          KC_ASTR,          KC_PERC,          KC_TRNS,          KC_TRNS,
                                                   KC_TRNS,          KC_TRNS,          KC_TRNS,                         KC_RCTL,         KC_RGUI,          KC_RALT
    ),
    [TEXT] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS,                KC_TRNS,                   LALT(KC_LEFT),      LALT(KC_RIGHT),                 KC_TRNS,                        KC_TRNS,       KC_PGDN,             KC_PGUP,            KC_TRNS,               KC_TRNS,               KC_TRNS,
        KC_TRNS, LCTL_T(LGUI(KC_A)),     LALT_T(LGUI(KC_X)),        LGUI_T(KC_LEFT),    LSFT_T(KC_RIGHT),               SGUI(KC_Z),                     LGUI(KC_Z),    RSFT_T(KC_DOWN),     RGUI_T(KC_UP),      RALT_T(LGUI(KC_C)),    RCTL_T(LGUI(KC_V)),    KC_TRNS,
        KC_TRNS, KC_TRNS,                KC_TRNS,                   LGUI(KC_LEFT),            LGUI(KC_RIGHT),                         KC_TRNS,                        KC_TRNS,       KC_END,             KC_HOME,            KC_TRNS,               KC_TRNS,               KC_TRNS,
                                                                    KC_TRNS,            KC_LSFT,                        KC_TRNS,                        KC_TRNS,       KC_TRNS,             KC_TRNS
    ),
    [MOUSE] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS, LCTL_T(KC_TRNS),    LALT_T(KC_TRNS),    LGUI_T(KC_TRNS),    LSFT_T(KC_TRNS),    KC_TRNS,           KC_TRNS,    RSFT_T(KC_TRNS),    RGUI_T(KC_TRNS),    RALT_T(KC_TRNS),    RCTL_T(KC_TRNS),    KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                         KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [WINDOWS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS,   KC_TRNS,    KC_TRNS,       KC_TRNS,           KC_TRNS,           KC_TRNS,    KC_PLUS,          KC_MINS,        KC_TRNS,         KC_TRNS,    KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_GRV,     KC_LCBR,       KC_RCBR,           KC_TRNS,           KC_TRNS,    KC_TAB,           LSFT(KC_TAB),   LCAG(KC_ENT),    KC_TRNS,    KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_TRNS,    LCAG(KC_LEFT), LCAG(KC_RIGHT),    KC_TRNS,           KC_TRNS,    LCAG(KC_DOWN),    LCAG(KC_UP),    KC_TRNS,         KC_TRNS,    KC_TRNS,
                                        KC_TRNS,       KC_TRNS,           KC_TRNS,           KC_TRNS,    KC_TRNS,          KC_TRNS
    ),
    [NUMBERS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS,    KC_F1,    KC_F2,    KC_F3,    KC_F10,                                           KC_TRNS,    KC_1,    KC_2,    KC_3,    KC_TRNS,    KC_TRNS,
        KC_TRNS, LCTL_T(KC_TRNS),    LALT_T(KC_F4),    LGUI_T(KC_F5),    LSFT_T(KC_F6),    KC_F11,           KC_TRNS,    RSFT_T(KC_4),    RGUI_T(KC_5),    RALT_T(KC_6),    RCTL_T(KC_TRNS),    KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_F7,    KC_F8,    KC_F9,    KC_F12,                                           KC_TRNS,    KC_7,    KC_8,    KC_9,    KC_TRNS,    KC_TRNS,
                                         KC_TRNS,    KC_TRNS,    KC_TRNS,                                           KC_TRNS,    KC_0,    KC_TRNS
    ),
};
