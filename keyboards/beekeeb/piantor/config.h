// Copyright 2022 beekeeb
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// TAPPING_TERM is also used by the tap dance. So though we could set it long, because permissive hold,
// the tap dance would feel sluggish as it would wait long time for the second tap.
#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
