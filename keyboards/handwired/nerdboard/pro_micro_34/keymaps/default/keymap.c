#include QMK_KEYBOARD_H

enum custom_layers {
    _GAME,
    _JONMAK,
    _QWERTY,
    _SYMBOL,
    _MOUSE,
    _FUNC//,
    //_FUNC_2
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
//#define FUNC_2  MO(_FUNC_2)

// alternate keys
#define L       KC_LEFT 
#define D       KC_DOWN
#define U       KC_UP 
#define R       KC_RIGHT 
#define TERM    LCA(KC_T)
#define PLUS    LSFT(KC_EQL)
#define STAR    LSFT(KC_8)
#define RUN_APP LSFT(KC_F10)
#define RST_APP LCTL(KC_F10)
#define WS_L    G(KC_PGUP)
#define WS_R    G(KC_PGDN)

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
  char     splash_screen[34] = "NerdBoard V5 34 Key\n\nBy: Jon Hull";
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
      //case _FUNC_2:
      //  oled_write("FUNCTION 2", false);
      //  break;
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
    KC_TAB , KC_1  , KC_2  , KC_3  , KC_4  ,       _______,KC_BTN3,_______,_______, JONMAK,
    KC_LALT, KC_Q  , KC_W  , KC_E  , KC_F  ,       _______,KC_BTN4,KC_BTN5,_______, SYMBOL,
    KC_LSFT, KC_A  , KC_S  , KC_D  , KC_R  ,       _______,KC_BTN1,KC_BTN2,SNIPING,DRGSCRL,
                    KC_ESC ,KC_LCTL, KC_SPC,       GJONMAK
  ),

  // decide on having KC_ENT or KC_ESC here
  [_JONMAK] = LAYOUT(
    KC_D   , KC_W  , KC_F  , KC_P  , KC_Q  ,       KC_COMM, KC_M  , KC_U  , KC_Y  ,KC_SCLN,
    MT_A   , MT_R  , MT_S  , MT_T  , KC_Z  ,       KC_SLSH, KC_N  , KC_E  , KC_I  , KC_O  ,
    KC_G   , KC_X  , KC_C  , KC_V  , KC_B  ,       KC_DOT , KC_H  , KC_J  , KC_K  , KC_L  ,
                    CTL_ENT, MO_TAB, KC_SPC,       SY_GRV
  ),

  [_QWERTY] = LAYOUT(
    KC_Q   , KC_W  , KC_E  , KC_R  , KC_T  ,       KC_Y   , KC_U  , KC_I  , KC_O  , KC_P  ,
    MTQ_A  , MTQ_S , MTQ_D , MTQ_F , KC_G  ,       KC_H   , KC_J  , KC_K  , KC_L  ,KC_SCLN,
    KC_Z   , KC_X  , KC_C  , KC_V  , KC_B  ,       KC_N   , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,
                    CTL_ENT, MO_TAB, KC_SPC,       SY_GRV
  ),

  [_SYMBOL] = LAYOUT(
    KC_BSLS, KC_7  , KC_8  , KC_9  ,KC_LCBR,       KC_RCBR,KC_MINS, PLUS  , STAR  ,KC_SLSH,
    KC_LSFT, KC_4  , KC_5  , KC_6  ,KC_LBRC,       KC_RBRC,KC_BSPC, KC_DEL,KC_QUOT,KC_DQUO,
    KC_0   , KC_1  , KC_2  , KC_3  ,KC_LPRN,       KC_RPRN, L     , D     , U     , R     ,
                    KC_EQL , FUNC  , KC_ESC,       _______
  ),

  [_MOUSE] = LAYOUT(
    _______,_______,_______,_______,_______,       _______,KC_BTN3,_______,_______, KC_D  ,
    FUNC   ,_______, WS_L  , WS_R  ,_______,       _______,KC_BTN4,KC_BTN5,KC_RCTL,_______,
    KC_LSFT,KC_LCTL,KC_LALT,KC_LGUI,_______,       _______,KC_BTN1,KC_BTN2,SNIPING,DRGSCRL,
                    _______,_______,_______,       FUNC  
  ),

  [_FUNC] = LAYOUT(
    QK_BOOT,KC_VOLU, KC_F5 ,G(KC_L), T_GAME,       _______,KC_INS ,KC_PSCR,TOG_DEF, T_GAME,
    KC_LSFT,KC_MUTE, KC_F11, TERM  ,_______,       _______,KC_LGUI,KC_MPRV,KC_MPLY,KC_MNXT,
    KC_LSFT,KC_VOLD,KC_HOME, KC_END,_______,       _______, G(L)  , G(D)  , G(U)  , G(R)  ,
                    _______,_______,_______,       _______
  )//,

  //[_FUNC_2] = LAYOUT(
  //  _______,_______,_______,G(KC_L), T_GAME,       _______,KC_INS ,KC_PSCR,TOG_DEF, T_GAME,
  //  KC_LSFT, KC_F5 ,RUN_APP,RST_APP,_______,       _______,KC_LGUI,KC_MPRV,KC_MPLY,KC_MNXT,
  //  KC_LSFT,_______,_______,_______,_______,       _______, G(L)  , G(D)  , G(U)  , G(R)  ,
  //                  _______,_______,_______,       _______
  //)
};
