// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD

// TAPPING_TERM is also used by the tap dance. So though we could set it long, because permissive hold,
// the tap dance would feel sluggish as it would wait long time for the second tap.
#define TAPPING_TERM 200
// This is a must have setting for getting home row mods to work reliably
// With LSFT_T(KC_F) given the sequence executed faster then TAPPING_TERM: F down, J down, J up, F up
// would emit 'j' instead of 'J'
#define PERMISSIVE_HOLD

#define ONESHOT_TAP_TOGGLE 2
