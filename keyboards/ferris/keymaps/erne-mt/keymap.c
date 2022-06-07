
#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum tap_dance_codes {
  DANCE_1,
  DANCE_2,
  DANCE_3,
  DANCE_21,
  DANCE_54,
  DANCE_55,
  DANCE_56,
  DANCE_57,
  DANCE_58,
  DANCE_59,
  DANCE_60,
  DANCE_63,
  BKSL_HME,
  PIPE_END,
  A_AE,
  U_UE,
  O_OE,
  S_SZ,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    KC_Q,	      KC_W,	KC_F,		KC_P,			KC_B,			  KC_J, 	 KC_L,		  	TD(U_UE),	    TD(DANCE_2),  KC_BSPC,
  //---------------------------------------------------------------------------------------    	  --------------------------------------------------------------------------------------
    TD(A_AE),	      KC_R,	TD(S_SZ),	KC_T,			KC_G,			  KC_M, 	 KC_N,			KC_E,		    KC_I,	  TD(O_OE),
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    KC_Y,	      KC_X,	KC_C,  		KC_D,			KC_V,			  KC_K, 	 KC_H,		  	TD(DANCE_3),	    TD(DANCE_1),  KC_Z,
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
		    				MT(MOD_MEH,KC_SPACE),	OSM(MOD_LSFT),		  OSM(MOD_RCTL), TO(1)
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
  ),

  [1] = LAYOUT(
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    KC_ESCAPE,	   DE_AT,	DE_HASH,	 DE_DLR,		DE_PERC,		  DE_CIRC,	DE_AMPR,	DE_ASTR,	TD(DANCE_21),		KC_BSPC,
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    KC_TAB,	   DE_EQL,	DE_ACUT,	 DE_GRV,		DE_QUOT,		  TD(BKSL_HME),	DE_LCBR,	DE_RCBR,	TD(PIPE_END),		KC_ENTER,
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    DE_TILD,	   DE_EURO,	DE_LABK,	 DE_RABK,		DE_DQUO,	          DE_LBRC,	DE_LPRN,	DE_RPRN,	DE_RBRC,		TO(3),
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
		    				 TO(0),			OSM(MOD_LSFT),		  KC_RALT,	TO(2) 
  ),

  [2] = LAYOUT(
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    KC_ESCAPE, LALT(KC_F4), LCTL(LALT(KC_DEL)),	 KC_F12,	       DE_UNDS,			  KC_PMNS,	KC_7,		KC_8,		KC_9,			KC_TRANSPARENT,
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    KC_TAB,    KC_NO,	    KC_NO,		 LSFT(KC_INS),	       KC_PPLS,   	 	  DE_EQL,	KC_4,		KC_5,		KC_6,			KC_ENTER,
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
    RESET,     DE_ASTR,	    KC_AUDIO_VOL_DOWN,   KC_AUDIO_VOL_UP,      KC_DOT,   	 	  KC_0,		KC_1,		KC_2, 		KC_3,			KC_TRANSPARENT,
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
	  						 TO(0),		      KC_LGUI,		  KC_RALT,	TO(1)
  ),

  [3] = LAYOUT(
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
      TD(DANCE_54),   KC_MS_WH_LEFT,  KC_MS_UP,       KC_MS_WH_RIGHT, TD(DANCE_55), 		  LGUI(KC_LBRACKET), LCTL(LSFT(KC_TAB)), RCTL(KC_TAB),   LGUI(KC_RBRACKET), KC_TRANSPARENT, 
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
      TD(DANCE_56),   KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    MT(MOD_LGUI,KC_DEL), 	  TD(DANCE_60), MT(MOD_RGUI,KC_DOWN), MT(MOD_RALT,KC_UP),TD(DANCE_63),      KC_ENTER,     
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
      TD(DANCE_58),   KC_MS_BTN2,     KC_MS_WH_UP,    KC_MS_WH_DOWN,  KC_INS,	 		  KC_MS_BTN1,   KC_MS_ACCEL0,	      KC_MS_ACCEL1,	 KC_MS_ACCEL2,      KC_NO, 
  //---------------------------------------------------------------------------------------       --------------------------------------------------------------------------------------
                        				TO(0),		KC_LGUI,		  KC_RALT,	TO(1)
  )
};



extern bool g_suspend_state;
#define GET_TAP_KC(dual_role_key) dual_role_key & 0xFF
uint16_t last_keycode = KC_NO;
uint8_t last_modifier = 0;

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state = {
    .is_press_action = true,
    .step = 0
};

void on_dance_a_ae(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_a_ae_dance_step(qk_tap_dance_state_t *state);
void dance_a_ae_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_a_ae_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_a_ae(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_A);
		tap_code16(KC_A);
		tap_code16(KC_A);
	}
	if(state->count > 3) {
		tap_code16(KC_A);
	}
}

uint8_t dance_a_ae_dance_step(qk_tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_a_ae_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_a_ae_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_A); break;
		case SINGLE_HOLD: register_code16(DE_ADIA); break;
		case DOUBLE_TAP: register_code16(KC_A); register_code16(KC_A); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_A); register_code16(KC_A);
	}
}

void dance_a_ae_reset(qk_tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_A); break;
		case SINGLE_HOLD: unregister_code16(DE_ADIA); break;
		case DOUBLE_TAP: unregister_code16(KC_A); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(DE_ADIA); break;
	}
	dance_state.step = 0;
}

void on_dance_u_ue(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_u_ue_dance_step(qk_tap_dance_state_t *state);
void dance_u_ue_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_u_ue_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_u_ue(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_U);
		tap_code16(KC_U);
		tap_code16(KC_U);
	}
	if(state->count > 3) {
		tap_code16(KC_U);
	}
}

uint8_t dance_u_ue_dance_step(qk_tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_u_ue_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_u_ue_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_U); break;
		case SINGLE_HOLD: register_code16(DE_UDIA); break;
		case DOUBLE_TAP: register_code16(KC_U); register_code16(KC_U); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_U); register_code16(KC_U);
	}
}

void dance_u_ue_reset(qk_tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_U); break;
		case SINGLE_HOLD: unregister_code16(DE_UDIA); break;
		case DOUBLE_TAP: unregister_code16(KC_U); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(DE_UDIA); break;
	}
	dance_state.step = 0;
}

void on_dance_o_oe(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_o_oe_dance_step(qk_tap_dance_state_t *state);
void dance_o_oe_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_o_oe_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_o_oe(qk_tap_dance_state_t *state, void *user_data) {
        if(state->count == 3) {
                tap_code16(KC_O);
                tap_code16(KC_O);
                tap_code16(KC_O);
        }
        if(state->count > 3) {
                tap_code16(KC_O);
        }
}

uint8_t dance_o_oe_dance_step(qk_tap_dance_state_t *state) {
        if (state->count == 1) {
                if (state->interrupted || !state->pressed) return SINGLE_TAP;
                else return SINGLE_HOLD;
        } else if (state->count == 2) {
                if (state->interrupted) return DOUBLE_SINGLE_TAP;
                else if (state->pressed) return DOUBLE_HOLD;
                else return DOUBLE_TAP;
        }
        return MORE_TAPS;
}
void dance_o_oe_finished(qk_tap_dance_state_t *state, void *user_data) {
        dance_state.step = dance_o_oe_dance_step(state);
        switch (dance_state.step) {
                case SINGLE_TAP: register_code16(KC_O); break;
                case SINGLE_HOLD: register_code16(DE_ODIA); break;
                case DOUBLE_TAP: register_code16(KC_O); register_code16(KC_O); break;
                case DOUBLE_SINGLE_TAP: tap_code16(KC_O); register_code16(KC_O);
        }
}

void dance_o_oe_reset(qk_tap_dance_state_t *state, void *user_data) {
        wait_ms(10);
        switch (dance_state.step) {
                case SINGLE_TAP: unregister_code16(KC_O); break;
                case SINGLE_HOLD: unregister_code16(DE_ODIA); break;
                case DOUBLE_TAP: unregister_code16(KC_O); break;
                case DOUBLE_SINGLE_TAP: unregister_code16(DE_ODIA); break;
        }
        dance_state.step = 0;
}

void on_dance_s_sz(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_s_sz_dance_step(qk_tap_dance_state_t *state);
void dance_s_sz_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_s_sz_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_s_sz(qk_tap_dance_state_t *state, void *user_data) {
        if(state->count == 3) {
                tap_code16(KC_S);
                tap_code16(KC_S);
                tap_code16(KC_S);
        }
        if(state->count > 3) {
                tap_code16(KC_S);
        }
}

uint8_t dance_s_sz_dance_step(qk_tap_dance_state_t *state) {
        if (state->count == 1) {
                if (state->interrupted || !state->pressed) return SINGLE_TAP;
                else return SINGLE_HOLD;
        } else if (state->count == 2) {
                if (state->interrupted) return DOUBLE_SINGLE_TAP;
                else if (state->pressed) return DOUBLE_HOLD;
                else return DOUBLE_TAP;
        }
        return MORE_TAPS;
}
void dance_s_sz_finished(qk_tap_dance_state_t *state, void *user_data) {
        dance_state.step = dance_s_sz_dance_step(state);
        switch (dance_state.step) {
                case SINGLE_TAP: register_code16(KC_S); break;
                case SINGLE_HOLD: register_code16(DE_SS); break;
                case DOUBLE_TAP: register_code16(KC_S); register_code16(KC_S); break;
                case DOUBLE_SINGLE_TAP: tap_code16(KC_S); register_code16(KC_S);
        }
}

void dance_s_sz_reset(qk_tap_dance_state_t *state, void *user_data) {
        wait_ms(10);
        switch (dance_state.step) {
                case SINGLE_TAP: unregister_code16(KC_S); break;
                case SINGLE_HOLD: unregister_code16(DE_SS); break;
                case DOUBLE_TAP: unregister_code16(KC_S); break;
                case DOUBLE_SINGLE_TAP: unregister_code16(DE_SS); break;
        }
        dance_state.step = 0;
}

void on_dance_2(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_2_dance_step(qk_tap_dance_state_t *state);
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_2(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_COMM);
		tap_code16(KC_COMM);
		tap_code16(KC_COMM);
	}
	if(state->count > 3) {
		tap_code16(KC_COMM);
	}
}

uint8_t dance_2_dance_step(qk_tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_2_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_COMM); break;
		case SINGLE_HOLD: register_code16(DE_MINS); break;
		case DOUBLE_TAP: register_code16(KC_COMM); register_code16(KC_COMM); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_COMM); register_code16(KC_COMM);
	}
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_COMM); break;
		case SINGLE_HOLD: unregister_code16(DE_MINS); break;
		case DOUBLE_TAP: unregister_code16(KC_COMM); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(DE_MINS); break;
	}
	dance_state.step = 0;
}

void on_dance_3(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_3_dance_step(qk_tap_dance_state_t *state);
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_3_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_3(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(DE_SLSH);
		tap_code16(DE_SLSH);
		tap_code16(DE_SLSH);
	}
	if(state->count > 3) {
		tap_code16(DE_SLSH);
	}
}

uint8_t dance_3_dance_step(qk_tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_3_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(DE_SLSH); break;
		case SINGLE_HOLD: register_code16(DE_UNDS); break;
		case DOUBLE_TAP: register_code16(DE_SLSH); register_code16(DE_SLSH); break;
		case DOUBLE_SINGLE_TAP: tap_code16(DE_SLSH); register_code16(DE_SLSH);
	}
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(DE_SLSH); break;
		case SINGLE_HOLD: unregister_code16(DE_UNDS); break;
		case DOUBLE_TAP: unregister_code16(DE_SLSH); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(DE_SLSH); break;
	}
	dance_state.step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_1_dance_step(qk_tap_dance_state_t *state);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_DOT);
		tap_code16(KC_DOT);
		tap_code16(KC_DOT);
	}
	if(state->count > 3) {
		tap_code16(KC_DOT);
	}
}

uint8_t dance_1_dance_step(qk_tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_1_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(KC_DOT); break;
		case SINGLE_HOLD: register_code16(KC_EXLM); break;
		case DOUBLE_TAP: register_code16(KC_DOT); register_code16(KC_DOT); break;
		case DOUBLE_SINGLE_TAP: tap_code16(KC_DOT); register_code16(KC_DOT);
	}
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(KC_DOT); break;
		case SINGLE_HOLD: unregister_code16(KC_EXLM); break;
		case DOUBLE_TAP: unregister_code16(KC_DOT); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(KC_DOT); break;
	}
	dance_state.step = 0;
}

void on_dance_21(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_21_dance_step(qk_tap_dance_state_t *state);
void dance_21_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_21_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_21(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(DE_SCLN);
		tap_code16(DE_SCLN);
		tap_code16(DE_SCLN);
	}
	if(state->count > 3) {
		tap_code16(DE_SCLN);
	}
}

uint8_t dance_21_dance_step(qk_tap_dance_state_t *state) {
	if (state->count == 1) {
		if (state->interrupted || !state->pressed) return SINGLE_TAP;
		else return SINGLE_HOLD;
	} else if (state->count == 2) {
		if (state->interrupted) return DOUBLE_SINGLE_TAP;
		else if (state->pressed) return DOUBLE_HOLD;
		else return DOUBLE_TAP;
	}
	return MORE_TAPS;
}
void dance_21_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state.step = dance_2_dance_step(state);
	switch (dance_state.step) {
		case SINGLE_TAP: register_code16(DE_SCLN); break;
		case SINGLE_HOLD: register_code16(DE_COLN); break;
		case DOUBLE_TAP: register_code16(DE_SCLN); register_code16(DE_SCLN); break;
		case DOUBLE_SINGLE_TAP: tap_code16(DE_SCLN); register_code16(DE_SCLN);
	}
}

void dance_21_reset(qk_tap_dance_state_t *state, void *user_data) {
	wait_ms(10);
	switch (dance_state.step) {
		case SINGLE_TAP: unregister_code16(DE_SCLN); break;
		case SINGLE_HOLD: unregister_code16(DE_COLN); break;
		case DOUBLE_TAP: unregister_code16(DE_SCLN); break;
		case DOUBLE_SINGLE_TAP: unregister_code16(DE_SCLN); break;
	}
	dance_state.step = 0;
}

void on_dance_54(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_54_dance_step(qk_tap_dance_state_t *state);
void dance_54_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_54_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_54(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
        tap_code16(KC_ESCAPE);
    }
    if(state->count > 3) {
        tap_code16(KC_ESCAPE);
    }
}

uint8_t dance_54_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_54_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_54_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_ESCAPE); break;
        case SINGLE_HOLD: register_code16(LALT(LGUI(KC_ESCAPE))); break;
        case DOUBLE_TAP: register_code16(KC_ESCAPE); register_code16(KC_ESCAPE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ESCAPE); register_code16(KC_ESCAPE);
    }
}

void dance_54_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
        case SINGLE_HOLD: unregister_code16(LALT(LGUI(KC_ESCAPE))); break;
        case DOUBLE_TAP: unregister_code16(KC_ESCAPE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ESCAPE); break;
    }
    dance_state.step = 0;
}
void on_dance_55(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_55_dance_step(qk_tap_dance_state_t *state);
void dance_55_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_55_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_55(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_Q);
        tap_code16(KC_Q);
        tap_code16(KC_Q);
    }
    if(state->count > 3) {
        tap_code16(KC_Q);
    }
}

uint8_t dance_55_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_55_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_55_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_Q); break;
        case SINGLE_HOLD: register_code16(KC_H); break;
        case DOUBLE_TAP: register_code16(KC_Q); register_code16(KC_Q); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_Q); register_code16(KC_Q);
    }
}

void dance_55_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_Q); break;
        case SINGLE_HOLD: unregister_code16(KC_H); break;
        case DOUBLE_TAP: unregister_code16(KC_Q); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_Q); break;
    }
    dance_state.step = 0;
}
void on_dance_56(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_56_dance_step(qk_tap_dance_state_t *state);
void dance_56_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_56_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_56(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
        tap_code16(KC_TAB);
    }
    if(state->count > 3) {
        tap_code16(KC_TAB);
    }
}

uint8_t dance_56_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_56_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_56_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_TAB); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_TAB)); break;
        case DOUBLE_TAP: register_code16(KC_TAB); register_code16(KC_TAB); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_TAB); register_code16(KC_TAB);
    }
}

void dance_56_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_TAB); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_TAB)); break;
        case DOUBLE_TAP: unregister_code16(KC_TAB); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_TAB); break;
    }
    dance_state.step = 0;
}
void on_dance_57(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_57_dance_step(qk_tap_dance_state_t *state);
void dance_57_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_57_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_57(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_DELETE);
        tap_code16(KC_DELETE);
        tap_code16(KC_DELETE);
    }
    if(state->count > 3) {
        tap_code16(KC_DELETE);
    }
}

uint8_t dance_57_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_57_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_57_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_DELETE); break;
        case SINGLE_HOLD: register_code16(LCTL(KC_K)); break;
        case DOUBLE_TAP: register_code16(KC_DELETE); register_code16(KC_DELETE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_DELETE); register_code16(KC_DELETE);
    }
}

void dance_57_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_DELETE); break;
        case SINGLE_HOLD: unregister_code16(LCTL(KC_K)); break;
        case DOUBLE_TAP: unregister_code16(KC_DELETE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_DELETE); break;
    }
    dance_state.step = 0;
}
void on_dance_58(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_58_dance_step(qk_tap_dance_state_t *state);
void dance_58_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_58_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_58(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
        tap_code16(KC_GRAVE);
    }
    if(state->count > 3) {
        tap_code16(KC_GRAVE);
    }
}

uint8_t dance_58_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_58_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_58_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_GRAVE); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_GRAVE)); break;
        case DOUBLE_TAP: register_code16(KC_GRAVE); register_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_GRAVE); register_code16(KC_GRAVE);
    }
}

void dance_58_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_GRAVE); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_GRAVE)); break;
        case DOUBLE_TAP: unregister_code16(KC_GRAVE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_GRAVE); break;
    }
    dance_state.step = 0;
}
void on_dance_59(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_59_dance_step(qk_tap_dance_state_t *state);
void dance_59_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_59_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_59(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
        tap_code16(KC_SPACE);
    }
    if(state->count > 3) {
        tap_code16(KC_SPACE);
    }
}

uint8_t dance_59_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_59_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_59_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_SPACE); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_O)); break;
        case DOUBLE_TAP: register_code16(KC_SPACE); register_code16(KC_SPACE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_SPACE); register_code16(KC_SPACE);
    }
}

void dance_59_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_SPACE); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_O)); break;
        case DOUBLE_TAP: unregister_code16(KC_SPACE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_SPACE); break;
    }
    dance_state.step = 0;
}
void on_dance_60(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_60_dance_step(qk_tap_dance_state_t *state);
void dance_60_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_60_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_60(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
        tap_code16(KC_LEFT);
    }
    if(state->count > 3) {
        tap_code16(KC_LEFT);
    }
}

uint8_t dance_60_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_60_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_60_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_LEFT); break;
        case SINGLE_HOLD: register_code16(LALT(KC_LEFT)); break;
        case DOUBLE_TAP: register_code16(KC_LEFT); register_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_LEFT); register_code16(KC_LEFT);
    }
}

void dance_60_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_LEFT); break;
        case SINGLE_HOLD: unregister_code16(LGUI(KC_LEFT)); break;
        case DOUBLE_TAP: unregister_code16(KC_LEFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_LEFT); break;
    }
    dance_state.step = 0;
}
void on_dance_63(qk_tap_dance_state_t *state, void *user_data);
uint8_t dance_63_dance_step(qk_tap_dance_state_t *state);
void dance_63_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_63_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_63(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
        tap_code16(KC_RIGHT);
    }
    if(state->count > 3) {
        tap_code16(KC_RIGHT);
    }
}

uint8_t dance_63_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void dance_63_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = dance_63_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(KC_RIGHT); break;
        case SINGLE_HOLD: register_code16(LGUI(KC_RIGHT)); break;
        case DOUBLE_TAP: register_code16(KC_RIGHT); register_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_RIGHT); register_code16(KC_RIGHT);
    }
}

void dance_63_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(KC_RIGHT); break;
        case SINGLE_HOLD: unregister_code16(LALT(KC_RIGHT)); break;
        case DOUBLE_TAP: unregister_code16(KC_RIGHT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_RIGHT); break;
    }
    dance_state.step = 0;
}

void on_bksl_hme(qk_tap_dance_state_t *state, void *user_data);
uint8_t bksl_hme_dance_step(qk_tap_dance_state_t *state);
void bksl_hme_finished(qk_tap_dance_state_t *state, void *user_data);
void bksl_hme_reset(qk_tap_dance_state_t *state, void *user_data);

void on_bksl_hme(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(DE_BSLS);
        tap_code16(DE_BSLS);
        tap_code16(DE_BSLS);
    }
    if(state->count > 3) {
        tap_code16(DE_BSLS);
    }
}

uint8_t bksl_hme_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void bksl_hme_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = bksl_hme_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(DE_BSLS); break;
        case SINGLE_HOLD: register_code16(KC_HOME); break;
        case DOUBLE_TAP: register_code16(DE_BSLS); register_code16(DE_BSLS); break;
        case DOUBLE_SINGLE_TAP: tap_code16(DE_BSLS); register_code16(DE_BSLS);
    }
}

void bksl_hme_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(DE_BSLS); break;
        case SINGLE_HOLD: unregister_code16(KC_HOME); break;
        case DOUBLE_TAP: unregister_code16(DE_BSLS); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(DE_BSLS); break;
    }
    dance_state.step = 0;
}

void on_pipe_end(qk_tap_dance_state_t *state, void *user_data);
uint8_t pipe_end_dance_step(qk_tap_dance_state_t *state);
void pipe_end_finished(qk_tap_dance_state_t *state, void *user_data);
void pipe_end_reset(qk_tap_dance_state_t *state, void *user_data);

void on_pipe_end(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(DE_PIPE);
        tap_code16(DE_PIPE);
        tap_code16(DE_PIPE);
    }
    if(state->count > 3) {
        tap_code16(DE_PIPE);
    }
}

uint8_t pipe_end_dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}
void pipe_end_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state.step = pipe_end_dance_step(state);
    switch (dance_state.step) {
        case SINGLE_TAP: register_code16(DE_PIPE); break;
        case SINGLE_HOLD: register_code16(KC_END); break;
        case DOUBLE_TAP: register_code16(DE_PIPE); register_code16(DE_PIPE); break;
        case DOUBLE_SINGLE_TAP: tap_code16(DE_PIPE); register_code16(DE_PIPE);
    }
}

void pipe_end_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state.step) {
        case SINGLE_TAP: unregister_code16(DE_PIPE); break;
        case SINGLE_HOLD: unregister_code16(KC_END); break;
        case DOUBLE_TAP: unregister_code16(DE_PIPE); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(DE_PIPE); break;
    }
    dance_state.step = 0;
}
qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_2, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_3, dance_3_finished, dance_3_reset),
        [DANCE_21] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_21, dance_21_finished, dance_21_reset),
        [DANCE_54] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_54, dance_54_finished, dance_54_reset),
        [DANCE_55] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_55, dance_55_finished, dance_55_reset),
        [DANCE_56] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_56, dance_56_finished, dance_56_reset),
        [DANCE_57] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_57, dance_57_finished, dance_57_reset),
        [DANCE_58] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_58, dance_58_finished, dance_58_reset),
        [DANCE_59] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_59, dance_59_finished, dance_59_reset),
        [DANCE_60] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_60, dance_60_finished, dance_60_reset),
        [DANCE_63] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_63, dance_63_finished, dance_63_reset),
        [BKSL_HME] = ACTION_TAP_DANCE_FN_ADVANCED(on_bksl_hme, bksl_hme_finished, bksl_hme_reset),
        [PIPE_END] = ACTION_TAP_DANCE_FN_ADVANCED(on_pipe_end, pipe_end_finished, pipe_end_reset),
        [A_AE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_a_ae, dance_a_ae_finished, dance_a_ae_reset),
        [U_UE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_u_ue, dance_u_ue_finished, dance_u_ue_reset),
        [O_OE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_o_oe, dance_o_oe_finished, dance_o_oe_reset),
        [S_SZ] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_s_sz, dance_s_sz_finished, dance_s_sz_reset),
};
