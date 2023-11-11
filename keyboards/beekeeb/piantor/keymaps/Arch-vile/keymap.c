// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// QMK SUPER ALT TAB
bool is_cmd_tab_active = false; // ADD this near the beginning of keymap.c
uint16_t cmd_tab_timer = 0;     // we will be using them soon.

enum custom_keycodes {          // Make sure have the awesome keycode ready
  CMD_TAB = SAFE_RANGE,
};

// Each layer gets a name for readability.
enum layer_names {
    BASE,
    SFT,
    SYM,
    SYM_2,
    NAV,
    MOUSE,
    WIN,
    NUM,
};

//const uint16_t PROGMEM shiftL_combo[] = {LGUI_T(KC_D), LSFT_T(KC_F), COMBO_END};
//const uint16_t PROGMEM shiftR_combo[] = {LSFT_T(KC_J), RGUI_T(KC_K), COMBO_END};
//const uint16_t PROGMEM shift_combo[] = {LT(NUM, KC_SPC), MO(SYM), COMBO_END};
const uint16_t PROGMEM ent_combo[] = {LSFT_T(KC_J), RGUI_T(KC_K), COMBO_END};
//const uint16_t PROGMEM bspc_combo[] = {RGUI_T(KC_K), RALT_T(KC_L), COMBO_END};
combo_t key_combos[] = {
//    COMBO(shiftL_combo, OSM(MOD_LSFT)),
//    COMBO(shift_combo, OSM(MOD_LSFT)),
//    COMBO(shiftR_combo, OSM(MOD_LSFT)),
//    COMBO(bspc_combo, KC_BSPC),
    COMBO(ent_combo, KC_ENT),
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
        case LT(WIN, KC_ESC):
              if (!record->tap.count) {      // If holding.
                if (record->event.pressed) { // On hold press.
                  register_mods(MOD_LGUI);   // Hold LGUI.
                } else {                     // On hold release.
                  unregister_mods(MOD_LGUI); // Release LGUI.
                }
              }
              return true;  // Continue normal handling.
        case CMD_TAB:
              if (record->event.pressed) {
                if (!is_cmd_tab_active) {
                  is_cmd_tab_active = true;
                  register_code(KC_LGUI);
                }
                cmd_tab_timer = timer_read();
                register_code(KC_TAB);
              } else {
                unregister_code(KC_TAB);
              }
              return true;
    }
    return true;
}

// The timer for the CMD_TAB
void matrix_scan_user(void) {
  if (is_cmd_tab_active) {
    if (timer_elapsed(cmd_tab_timer) > 800) {
      unregister_code(KC_LGUI);
      is_cmd_tab_active = false;
    }
  }
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
        KC_NO,          KC_Q,               KC_W,               KC_E,               KC_R,               KC_T,                   /**/            KC_Y,               KC_U,               KC_I,               KC_O,               KC_EXLM,          KC_NO,
        KC_NO,          LCTL_T(KC_A),       LALT_T(KC_S),       LGUI_T(KC_D),       LSFT_T(KC_F),       KC_G,                   /**/            KC_H,               LSFT_T(KC_J),       RGUI_T(KC_K),       RALT_T(KC_L),       RCTL_T(KC_P),   KC_NO,
        KC_NO,          KC_Z,               KC_X,               KC_C,               KC_V,               KC_B,                   /**/            KC_N,               KC_M,               KC_COMM,            KC_DOT,             KC_QUES,          KC_NO,
                                                                LT(WIN, KC_ESC),    LT(NUM, KC_SPC),    LT(NAV, KC_TAB),        /**/            KC_LSFT,            MO(SYM),            MT(MOUSE,RALT(KC_U) )
    ),
    [SFT] = LAYOUT_split_3x6_3(
        KC_NO,          LSFT(KC_Q),         LSFT(KC_W),         LSFT(KC_E),         LSFT(KC_R),       LSFT(KC_T),                   /**/            LSFT(KC_Y),               LSFT(KC_U),       LSFT(KC_I),        LSFT(KC_O),       KC_NO,         KC_NO,
        KC_NO,          LSFT(KC_A),         LSFT(KC_S),         LSFT(KC_D),         LSFT(KC_F),       LSFT(KC_G),                   /**/            LSFT(KC_H),               LSFT(KC_J),       LSFT(KC_K),        LSFT(KC_L),       LSFT(KC_P),    KC_NO,
        KC_NO,          LSFT(KC_Z),         LSFT(KC_X),         LSFT(KC_C),         LSFT(KC_V),       LSFT(KC_B),                   /**/            LSFT(KC_N),               LSFT(KC_M),       KC_EXLM,           KC_QUES,          KC_NO,         KC_NO,
                                                                KC_NO,              KC_TAB,           RALT(KC_U),                   /**/            KC_NO,                    KC_NO,            KC_NO
    ),
    [SYM] = LAYOUT_split_3x6_3(
        KC_NO,    KC_NO,      KC_PERC,    KC_QUOT,    KC_UNDS,    KC_HASH,   /**/     KC_AT,      KC_AMPR,    KC_DLR,     KC_TRNS,    KC_NO,      KC_NO,
        KC_NO,    KC_PIPE,    KC_PLUS,    KC_DQUO,    KC_EQL,     KC_SLSH,   /**/     KC_LT,      KC_LPRN,    KC_LCBR,    KC_LBRC,    KC_SCLN,    KC_NO,
        KC_NO,    KC_TILD,    KC_ASTR,    KC_GRV,     KC_MINS,    KC_BSLS,   /**/     KC_GT,      KC_RPRN,    KC_RCBR,    KC_RBRC,    KC_COLN,    KC_NO,
                                          KC_NO,      KC_BSPC,      KC_NO,     /**/     KC_NO,      KC_NO,      KC_NO
    ),
    [NAV] = LAYOUT_split_3x6_3(
        KC_TRNS,    KC_TRNS,    KC_TRNS,    LALT(KC_LEFT),      LALT(KC_RIGHT),     KC_TRNS,        /**/    KC_TRNS,        KC_PGDN,    KC_PGUP,    KC_TRNS,        KC_TRNS,        KC_TRNS,
        KC_TRNS,    LGUI(KC_A), LGUI(KC_X), KC_LEFT,            KC_RIGHT,           SGUI(KC_Z),     /**/    LGUI(KC_Z),     KC_DOWN,    KC_UP,      LGUI(KC_C),     LGUI(KC_V),     KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    LGUI(KC_LEFT),      LGUI(KC_RIGHT),     KC_TRNS,        /**/    KC_TRNS,        KC_END,     KC_HOME,    KC_TRNS,        KC_TRNS,        KC_TRNS,
                                            KC_LSFT,            KC_LCTL,            KC_LALT,        /**/    KC_TRNS,        KC_TRNS,    KC_TRNS
    ),
    [MOUSE] = LAYOUT_split_3x6_3(
        KC_TRNS,    KC_TRNS,            KC_TRNS,                KC_TRNS,            KC_TRNS,            KC_TRNS,           /**/     KC_TRNS,    KC_TRNS,             KC_TRNS,                KC_TRNS,                KC_TRNS,            KC_TRNS,
        KC_TRNS,    LCTL_T(KC_TRNS),    LALT_T(KC_TRNS),        LGUI_T(KC_TRNS),    LSFT_T(KC_TRNS),    KC_TRNS,           /**/     KC_TRNS,    RSFT_T(KC_TRNS),     RGUI_T(KC_TRNS),        RALT_T(KC_TRNS),        RCTL_T(KC_TRNS),    KC_TRNS,
        KC_TRNS,    KC_TRNS,            KC_TRNS,                KC_TRNS,            KC_TRNS,            KC_TRNS,           /**/     KC_TRNS,    KC_TRNS,             KC_TRNS,                KC_TRNS,                KC_TRNS,            KC_TRNS,
                                                                KC_TRNS,            KC_TRNS,            KC_TRNS,           /**/     KC_TRNS,    KC_TRNS,             KC_TRNS
    ),
    [WIN] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO,           KC_NO,      KC_NO,            KC_NO,           KC_NO,             /**/   KC_NO,           KC_NO,          KC_NO,          KC_NO,      KC_NO,  KC_NO,
        KC_NO, LGUI(KC_GRV),    KC_NO,      LGUI(KC_RCBR),    CMD_TAB,         KC_NO,             /**/   LGUI(KC_PLUS),   LCAG(KC_DOWN),  LCAG(KC_UP),    KC_NO,      KC_NO,  KC_NO,
        KC_NO, KC_NO,           KC_NO,      LGUI(KC_LCBR),    LSFT_T(CMD_TAB), KC_NO,             /**/   LGUI(KC_MINS),   KC_NO,          KC_NO,          KC_NO,      KC_NO,  KC_NO,
                                             KC_NO,           KC_NO,           KC_NO,             /**/   LCAG(KC_LEFT),   LCAG(KC_ENT),   LCAG(KC_RIGHT)
    ),
    [NUM] = LAYOUT_split_3x6_3(
        KC_NO, KC_NO,   KC_F1,  KC_F2,  KC_F3,  KC_F11,    /**/        KC_NO,   KC_1,   KC_2,   KC_3,   KC_NO,  KC_NO,
        KC_NO, KC_NO,   KC_F4,  KC_F5,  KC_F6,  KC_F10,    /**/        KC_0,    KC_4,   KC_5,   KC_6,   KC_NO,  KC_NO,
        KC_NO, KC_NO,   KC_F7,  KC_F8,  KC_F9,  KC_F12,    /**/        KC_NO,   KC_7,   KC_8,   KC_9,   KC_NO,  KC_NO,
                                KC_NO,  KC_NO,  KC_NO,     /**/        KC_NO,   KC_NO,  KC_NO
    ),
};
