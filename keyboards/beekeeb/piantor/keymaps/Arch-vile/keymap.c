// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Each layer gets a name for readability.
enum layer_names {
    BASE,
    SYMBOLS,
    TEXT,
    MOUSE,
    WINDOWS,
    NUMBERS,
};

enum {
    CT_CLN,
    TD_ESC_CAPS,
};

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    tap_dance_action_t *action;

    switch (keycode) {
        // not working
        case TD(CT_CLN):  // list all tap dance keycodes with tap-hold configurations
            action = &tap_dance_actions[TD_INDEX(keycode)];
            if (!record->event.pressed && action->state.count && !action->state.finished) {
                tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
                tap_code16(tap_hold->tap);
            }
            return true;
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

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [CT_CLN] = ACTION_TAP_DANCE_TAP_HOLD(KC_BSPC, LM(WINDOWS,MOD_LGUI)),
    // Tap once for Escape, twice for Caps Lock
    [TD_ESC_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_A, KC_B),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT_split_3x6_3(
        KC_NO,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_NO,
        KC_NO, LCTL_T(KC_A),    LALT_T(KC_S),    LGUI_T(KC_D),    LSFT_T(KC_F),    KC_G,                               KC_H,    RSFT_T(KC_J),    RGUI_T(KC_K),    RALT_T(KC_L),    RCTL_T(KC_QUES), KC_NO,
        KC_NO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_EXLM, KC_NO,
                                            LT(NUMBERS, KC_TAB), LT(SYMBOLS, KC_SPC),  LT(WINDOWS, KC_ESC),           LT(MOUSE, KC_ENT),  LT(TEXT, KC_BSPC),  RALT(KC_U)
    ),
    [SYMBOLS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_QUOT, KC_AMPR, KC_AT,   KC_CIRC,          KC_UNDS, KC_DLR,  KC_HASH, KC_ASTR, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_PIPE, KC_DQUO, KC_LBRC, KC_RBRC, KC_BSLS,          KC_EQL,  KC_LPRN, KC_RPRN, KC_PLUS, KC_SCLN, KC_TRNS,
        KC_TRNS, KC_TILD, KC_GRV,  KC_LT,   KC_GT,   KC_SLSH,          KC_MINS, KC_LCBR, KC_RCBR, KC_PERC, KC_COLN, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS,          KC_RCTL, KC_RGUI, KC_RALT
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
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS, LCTL_T(KC_TRNS),    LALT_T(KC_TRNS),    LGUI_T(KC_TRNS),    LSFT_T(KC_TRNS),    KC_TRNS,           KC_TRNS,    RSFT_T(KC_TRNS),    RGUI_T(KC_TRNS),    RALT_T(KC_TRNS),    RCTL_T(KC_TRNS),    KC_TRNS,
        KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
                                         KC_TRNS,    KC_TRNS,    KC_TRNS,           KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
};
