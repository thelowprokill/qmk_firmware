#include QMK_KEYBOARD_H

enum custom_layers {
    _GAME,
    _JONMAK,
    _QWERTY,
    _SYMBOL,
    _MOUSE
};

// layer keys
#define JONMAK  TG(_JONMAK)
#define GJONMAK MO(_JONMAK)
#define MOUSE   MO(_MOUSE)
#define SYMBOL  MO(_SYMBOL)
#define MOUSE   MO(_MOUSE)
#define T_GAME  TO(_GAME)
#define GAME    MO(_GAME)
#define TOG_DEF TG(_QWERTY)

// alternate keys
#define L       KC_LEFT 
#define D       KC_DOWN
#define U       KC_UP 
#define R       KC_RIGHT 
#define ALT_TAB LALT(KC_TAB)

// mod taps
#define SFT_ESC SFT_T(KC_ESC)
#define CTL_BSP CTL_T(KC_BSPC)
#define ALT_SPC ALT_T(KC_SPC)
#define SFT_ENT SFT_T(KC_ENT)
#define SUP_BSP GUI_T(KC_BSPC)
#define ALT_BSP LALT_T(KC_BSPC)
#define CTL_ENT CTL_T(KC_ENT)
#define CTL_BSL CTL_T(KC_BSLS)
#define LSA_A   LSA(KC_A)

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
#define LW_GRV LT(SYMBOL, KC_GRV)

#ifdef OLED_ENABLE
  //char     splash_screen[27] = "NerdBoard V4\n\nBy: Jon Hull";
  char     splash_screen[27] = "NerdBoard V2\n\nBy: Jon Hull";
  uint32_t timer             = 0;
  uint8_t  show_splash       = 1;
  
  //static void render_logo(void) {
  //    static const char PROGMEM qmk_logo[] = {
  //        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
  //        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
  //        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
  //    };
  //
  //    oled_write_P(qmk_logo, false);
  //}
  
  static void regular_use(void) {
    oled_clear();
    oled_set_cursor(0, 0);
  
    oled_write("Layer: ", false);
    switch (get_highest_layer(layer_state)) {
      case _JONMAK:
        oled_write("Jon MAC", false);
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
  
  void keyboard_pre_init_user(void) { layer_move(_JONMAK); }
  
  //oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  //  return OLED_ROTATION_1;
  //}

#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_GAME] = LAYOUT(
    KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  ,                       KC_Y   ,KC_LALT, KC_TAB, KC_GRV, SYMBOL,
    KC_LSFT, KC_A  , KC_S  , KC_D  , KC_F  ,                       KC_H   ,KC_BTN1,KC_BTN2,SNIPING,KC_WH_U,
    KC_LALT, KC_Z  , KC_X  , KC_C  , KC_V  ,                       KC_N   , KC_M  ,DRGSCRL,KC_BTN3,KC_WH_D,
    _______,KC_LBRC,KC_RBRC,                                                       _______, JONMAK,_______,
                             KC_E   ,KC_ESC ,                              KC_3   ,
                             KC_LCTL,KC_SPC ,                              GJONMAK,
             KC_G   ,KC_LSFT,                                                       KC_1   , KC_2
  ),

  [_JONMAK] = LAYOUT(
    KC_Q   , KC_W  , KC_F  , KC_P  , KC_Z  ,                       KC_COMM, KC_M  , KC_U  , KC_Y  ,KC_SCLN,
    MT_A   , MT_R  , MT_S  , MT_T  , KC_D  ,                       KC_DOT , KC_N  , KC_E  , KC_I  , KC_O  ,
    KC_G   , KC_X  , KC_C  , KC_V  , KC_B  ,                       KC_SLSH, KC_H  , KC_J  , KC_K  , KC_L  ,
    _______,KC_LBRC,KC_RBRC,                                                       KC_MINS, KC_EQL,_______,
            //                KC_ENT , KC_ESC,                               CTL_BSL,
            //                _______, KC_SPC,                               SYMBOL ,
            //_______, MO_TAB,                                                       KC_GRV , KC_GRV
                            KC_ENT , KC_SPC,                               CTL_BSL,
                            _______, MO_TAB,                               SYMBOL ,
            _______, KC_ESC,                                                       KC_GRV , KC_GRV
  ),

  [_QWERTY] = LAYOUT(
    KC_Q   , KC_W  , KC_E  , KC_R  , KC_T  ,                       KC_Y   , KC_U  , KC_I  , KC_O  , KC_P  ,
    MTQ_A  , MTQ_S , MTQ_D , MTQ_F , KC_G  ,                       KC_H   , KC_J  , KC_K  , KC_L  ,KC_SCLN,
    KC_Z   , KC_X  , KC_C  , KC_V  , KC_B  ,                       KC_N   , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,
    _______,KC_LBRC,KC_RBRC,                                                       KC_MINS, KC_EQL,_______,
                            KC_ENT , KC_SPC,                               CTL_BSL,
                            _______, MO_TAB,                               SYMBOL ,
            _______, KC_ESC,                                                       KC_GRV , KC_GRV
  ),

  [_SYMBOL] = LAYOUT(
    KC_VOLU, KC_7  , KC_8  , KC_9  ,KC_LBRC,                       KC_RBRC,KC_MPLY,KC_MPRV,KC_MNXT, T_GAME,
    KC_LSFT, KC_4  , KC_5  , KC_6  ,KC_LPRN,                       KC_RPRN,KC_BSPC,KC_DEL ,KC_INS ,KC_DQUO,
    KC_VOLD, KC_1  , KC_2  , KC_3  ,G(KC_T),                       KC_QUOT, L     , D     , U     , R     ,
    _______,_______, KC_0  ,                                                       KC_HOME,KC_END ,_______,
                            _______,_______,                               _______,
                            _______,_______,                               _______,
            _______,KC_CAPS,                                                       _______,_______

  ),

  [_MOUSE] = LAYOUT(
    KC_MPLY,KC_WH_L,KC_WH_R, KC_F11,ALT_TAB,                       _______,KC_BTN1,KC_BTN2,KC_BTN3,TOG_DEF,
    KC_LSFT,KC_BTN1,KC_BTN2,KC_BTN3,KC_WH_U,                       KC_LGUI,KC_RSFT,DRGSCRL,SNIPING,KC_RCTL,
    G(KC_L),_______,DRGSCRL,SNIPING,KC_WH_D,                       _______, G(L)  , G(D)  , G(U)  , G(R)  ,
    _______,KC_BTN4,KC_BTN5,                                                       KC_LPRN,KC_RPRN,_______,
                            _______,_______,                               _______,
                            _______,_______,                               KC_LSFT,
            _______,_______,                                                       KC_BTN1,KC_BTN2
  )
};
