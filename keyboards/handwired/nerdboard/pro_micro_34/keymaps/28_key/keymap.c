#include QMK_KEYBOARD_H

enum custom_layers {
    _GAME,
    _JONMAK,
    _JM_EXT,
    _SYMBOL,
    _MOUSE,
    _FUNC
};

// layer keys
#define JONMAK  TG(_JONMAK)
#define GJONMAK MO(_JONMAK)
#define JM_EXT  MO(_JM_EXT)
#define MOUSE   MO(_MOUSE)
#define SYMBOL  MO(_SYMBOL)
#define MOUSE   MO(_MOUSE)
#define T_GAME  TO(_GAME)
#define FUNC    MO(_FUNC)

// mod keys
#define CTL_Z LCTL(KC_Z)
#define CTL_R LCTL(KC_R)

// alternate keys
#define L       KC_LEFT 
#define D       KC_DOWN
#define U       KC_UP 
#define R       KC_RIGHT 

// mod taps
#define CTL_ENT CTL_T(KC_ENT)
#define MT_A    SFT_T(KC_A)
#define MT_R    CTL_T(KC_R)
#define MT_S    ALT_T(KC_S)
#define MT_T    SFT_T(KC_T)

#define MTQ_A   SFT_T(KC_A)
#define MTQ_S   CTL_T(KC_S)
#define MTQ_D   ALT_T(KC_D)
#define MTQ_F   SFT_T(KC_F)

// layer tap
#define MO_TAB LT(MOUSE, KC_TAB)
#define SY_GRV LT(SYMBOL, KC_GRV)
#define JM_ENT LT(JM_EXT, KC_ENT)

#ifdef OLED_ENABLE
  char     splash_screen[34] = "NerdBoard V5 28 Key\n\nBy: Jon Hull";
  uint32_t timer             = 0;
  uint8_t  show_splash       = 1;
  
  
  static void regular_use(void) {
    oled_clear();
    oled_set_cursor(0, 0);
  
    oled_write("Layer: ", false);
    switch (get_highest_layer(layer_state)) {
      case _GAME:
        oled_write("GAME", false);
        break;
      case _JONMAK:
        oled_write("Jon MAC 28", false);
        break;
      case _JM_EXT:
        oled_write("Jon MAC Cont.", false);
        break;
      case _SYMBOL:
        oled_write("SYMBOLS", false);
        break;
      case _MOUSE:
        oled_write("MOUSE", false);
        break;
      case _FUNC:
        oled_write("FUNCTION", false);
        break;
    }
  
    led_t led_state = host_keyboard_led_state();
    oled_write("\n\nMods:", false);
  
    uint8_t mod = get_mods();
  
    if (led_state.caps_lock)  { oled_write(" CAP", false); }
    if (mod & MOD_MASK_SHIFT) { oled_write(" SFT", false); }
    if (mod & MOD_MASK_CTRL)  { oled_write(" CTL", false); }
    if (mod & MOD_MASK_ALT)   { oled_write(" ALT", false); }
    if (mod & MOD_MASK_GUI)   { oled_write(" GUI", false); }
  
    return;
  }
  
  bool oled_task_user() {
    if (timer > 100) { regular_use(); }
    else { timer += 1; oled_write(splash_screen, false); }
    return false;
  }

#endif

void keyboard_pre_init_user(void) { layer_move(_JONMAK); }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_GAME] = LAYOUT(
    KC_TAB , KC_1  , KC_2  , KC_3  ,_______,       _______,_______,KC_BTN3,_______, JONMAK,
    KC_LALT, KC_Q  , KC_W  , KC_E  ,_______,       _______,KC_BTN4,KC_BTN5, KC_R  , SYMBOL,
    KC_LSFT, KC_A  , KC_S  , KC_D  ,_______,       _______,KC_BTN1,KC_BTN2,SNIPING,DRGSCRL,
                    KC_ESC ,KC_LCTL, KC_SPC,       GJONMAK
  ),

  // decide on having KC_ENT or KC_ESC here
  [_JONMAK] = LAYOUT(
    KC_D   , KC_W  , KC_F  , KC_P  , CTL_Z ,       KC_BTN3, KC_M  , KC_U  , KC_Y  ,KC_SCLN,
    MT_A   , MT_R  , MT_S  , MT_T  , CTL_R ,       KC_BTN2, KC_N  , KC_E  , KC_I  , KC_O  ,
    KC_G   , KC_X  , KC_C  , KC_V  , CTL_R ,       KC_BTN1, KC_H  , KC_J  , KC_K  , KC_L  ,
                     JM_ENT, MO_TAB, KC_SPC,       SY_GRV
  ),

  [_JM_EXT] = LAYOUT(
     CTL_Z , CTL_R ,KC_HOME,KC_LBRC,_______,       _______,KC_RBRC, KC_END,_______,_______,
    _______,_______,KC_BSLS,KC_LCBR,_______,       _______,KC_RCBR,_______,_______,_______,
     KC_Z  , KC_Q  , KC_B  ,KC_LPRN,_______,       _______,KC_RPRN,KC_COMM, KC_DOT,KC_SLSH,
                    _______,_______,_______,       _______
  ),

  [_SYMBOL] = LAYOUT(
    _______, KC_7  , KC_8  , KC_9  ,_______,       KC_DOT ,KC_MINS,KC_PPLS,KC_PAST,KC_PSLS,
    KC_LSFT, KC_4  , KC_5  , KC_6  ,_______,       _______,KC_BSPC, KC_DEL,KC_QUOT,KC_DQUO,
    KC_0   , KC_1  , KC_2  , KC_3  ,_______,       KC_COMM,L      , D     , U     , R     ,
                    KC_PEQL, FUNC  , KC_ESC,       FUNC
  ),

  [_MOUSE] = LAYOUT(
    FUNC   ,_______,_______,_______,_______,       _______,KC_BTN3,_______,_______,_______,
    _______,_______,_______,_______,_______,       _______,KC_BTN4,KC_BTN5,_______,KC_RCTL,
    KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI,_______,       _______,KC_BTN1,KC_BTN2,SNIPING,DRGSCRL,
                    _______, FUNC  ,_______,       FUNC  
  ),

  [_FUNC] = LAYOUT(
    QK_BOOT,KC_VOLU, KC_F5 ,G(KC_L),_______,       _______,KC_INS ,_______,_______, T_GAME,
    KC_LSFT,KC_MUTE, KC_F11,G(KC_T),_______,       _______,KC_LGUI,KC_MPRV,KC_MPLY,KC_MNXT,
    _______,KC_VOLD,KC_HOME, KC_END,_______,       _______, G(L)  , G(D)  , G(U)  , G(R)  ,
                    _______,_______,_______,       _______
  )
};
