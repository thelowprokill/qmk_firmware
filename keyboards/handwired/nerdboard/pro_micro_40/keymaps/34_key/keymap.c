#include QMK_KEYBOARD_H

enum custom_layers {
    _GAME,
    _JONMAK,
    _QWERTY,
    _SYMBOL,
    _MOUSE,
    _FUNC
};

// layer keys
#define JONMAK  TG(_JONMAK)
#define GJONMAK MO(_JONMAK)
#define MOUSE   MO(_MOUSE)
#define SYMBOL  MO(_SYMBOL)
#define MOUSE   MO(_MOUSE)
#define T_GAME  TO(_GAME)
#define TOG_DEF TG(_QWERTY)
#define FUNC    MO(_FUNC)

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

#ifdef OLED_ENABLE
  #ifdef VERSION_1
    char     splash_screen[30] = "NerdBoard V1 34\n\nBy: Jon Hull";
  #endif
  #ifdef VERSION_2
    char     splash_screen[30] = "NerdBoard V2 34\n\nBy: Jon Hull";
  #endif

  uint32_t timer             = 0;
  uint8_t  show_splash       = 1;
  
  static void regular_use(void) {
    oled_clear();
    oled_set_cursor(0, 0);
  
    oled_write("Layer: ", false);
    switch (get_highest_layer(layer_state)) {
      case _JONMAK:
        oled_write("Jon MAC 34", false);
        break;
      case _GAME:
        oled_write("GAME", false);
        break;
      case _QWERTY:
        oled_write("QWERTY", false);
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
  
  //oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  //  return OLED_ROTATION_1;
  //}

#endif

void keyboard_pre_init_user(void) { layer_move(_JONMAK); }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_GAME] = LAYOUT(
    KC_TAB , KC_1  , KC_2  , KC_3  , KC_4  ,                       _______,_______,KC_BTN3,_______, JONMAK,
    KC_LSFT, KC_A  , KC_W  , KC_D  , KC_R  ,                       _______,KC_BTN1,KC_BTN2,SNIPING, SYMBOL,
    KC_LALT, KC_Q  , KC_S  , KC_E  , KC_F  ,                       _______,KC_BTN4,KC_BTN5,DRGSCRL,_______,
            _______,_______,                                                       _______,_______,        
                  #ifdef VERSION_1
                            KC_ENT ,KC_SPC ,                               _______,
                                    KC_LCTL,                               GJONMAK,
                    _______,                                                        _______   
                  #endif
                  #ifdef VERSION_2
                            _______,KC_ENT ,                               _______,
                                    KC_SPC ,                               GJONMAK,
                    KC_LCTL,                                                        _______   
                  #endif
  ),
  [_JONMAK] = LAYOUT(
    KC_Q   , KC_W  , KC_F  , KC_P  , KC_Z  ,                       KC_COMM, KC_M  , KC_U  , KC_Y  ,KC_SCLN,
    MT_A   , MT_R  , MT_S  , MT_T  , KC_D  ,                       KC_DOT , KC_N  , KC_E  , KC_I  , KC_O  ,
    KC_G   , KC_X  , KC_C  , KC_V  , KC_B  ,                       KC_SLSH, KC_H  , KC_J  , KC_K  , KC_L  ,
            _______,_______,                                                       _______,_______,        
                  #ifdef VERSION_1
                            _______,CTL_ENT,                               _______,
                                    KC_SPC ,                               SY_GRV ,
                    MO_TAB ,                                                       _______
                  #endif
                  #ifdef VERSION_2
                            CTL_ENT,KC_SPC ,                               _______,
                                    MO_TAB ,                               SY_GRV ,
                    _______,                                                       _______
                  #endif
  ),
  [_QWERTY] = LAYOUT(
    KC_Q   , KC_W  , KC_E  , KC_R  , KC_T  ,                       KC_Y   , KC_U  , KC_I  , KC_O  , KC_P  ,
    MTQ_A  , MTQ_S , MTQ_D , MTQ_F , KC_G  ,                       KC_H   , KC_J  , KC_K  , KC_L  ,KC_SCLN,
    KC_Z   , KC_X  , KC_C  , KC_V  , KC_B  ,                       KC_N   , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,
            _______,_______,                                                       _______,_______,        
                  #ifdef VERSION_1
                            _______,CTL_ENT,                               _______,
                                    KC_SPC ,                               SY_GRV ,
                    MO_TAB ,                                                       _______
                  #endif
                  #ifdef VERSION_2
                            CTL_ENT,KC_SPC ,                               _______,
                                    MO_TAB ,                               SY_GRV ,
                    _______,                                                       _______
                  #endif
  ),
  [_SYMBOL] = LAYOUT(
    _______, KC_7  , KC_8  , KC_9  ,KC_LBRC,                       KC_RBRC,KC_MINS,KC_PPLS,KC_PAST,KC_PSLS,
    KC_LSFT, KC_4  , KC_5  , KC_6  ,KC_LPRN,                       KC_RPRN,KC_BSPC, KC_DEL,KC_QUOT,KC_DQUO,
    KC_0   , KC_1  , KC_2  , KC_3  ,KC_BSLS,                       KC_PEQL, L     , D     , U     , R     ,
            _______,_______,                                                       _______,_______,        
                  #ifdef VERSION_1
                            _______,KC_EQL ,                               _______,
                                    KC_ESC ,                               FUNC   ,
                    FUNC   ,                                                       _______
                  #endif
                  #ifdef VERSION_2
                            KC_EQL , KC_ESC,                               _______,
                                    FUNC   ,                               FUNC   ,
                    _______,                                                       _______
                  #endif
  ),
  [_MOUSE] = LAYOUT(
    _______,_______,_______,_______,_______,                       _______,_______,KC_BTN3,_______,_______,
    KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI,_______,                       _______,KC_BTN1,KC_BTN2,SNIPING,KC_RCTL,
    FUNC   ,_______,_______,_______,_______,                       _______,KC_BTN4,KC_BTN5,DRGSCRL,_______,
            _______,_______,                                                       _______,_______,        
                  #ifdef VERSION_1
                            _______,_______,                               _______,
                                    _______,                               FUNC   ,
                    FUNC   ,                                                        _______
                  #endif
                  #ifdef VERSION_2
                            _______,_______,                               _______,
                                    FUNC   ,                               FUNC   ,
                    _______,                                                       _______
                  #endif
  ),
  [_FUNC] = LAYOUT(
    QK_BOOT,KC_VOLU, KC_F5 ,G(KC_L), T_GAME,                       _______,KC_INS ,_______,TOG_DEF, T_GAME,
    KC_LSFT,KC_MUTE, KC_F11,G(KC_T),KC_HOME,                       KC_END ,KC_LGUI,KC_MPRV,KC_MPLY,KC_MNXT,
    _______,KC_VOLD,KC_HOME, KC_END,_______,                       _______, G(L)  , G(D)  , G(U)  , G(R)  ,
            _______,_______,                                                       _______,_______,        
                            _______,_______,                               _______,
                                    _______,                               _______,
                    _______,                                                       _______
  )
};
