#include QMK_KEYBOARD_H

enum custom_layers {
  //_GAME,
  //_JONMAK,
  //_JM_EXT,
  //_SYMBOL,
  //_MOUSE,
  //_FUNC
  _GAME,
  _BLAKEMAK_C,
  _BLAKEMAK_L,
  _BLAKEMAK_R,
  _MOUSE,
  _NUMBERS,
  _FUNC
};

// layer keys
//#define JONMAK  TG(_JONMAK)
//#define GJONMAK MO(_JONMAK)
//#define JM_EXT  MO(_JM_EXT)
//#define MOUSE   MO(_MOUSE)
//#define SYMBOL  MO(_SYMBOL)
//#define MOUSE   MO(_MOUSE)
//#define T_GAME  TO(_GAME)
#define FUNC    MO(_FUNC)
#define BM_L    MO(_BLAKEMAK_L)
#define BM_C    MO(_BLAKEMAK_C)
#define BM_R    MO(_BLAKEMAK_R)
#define NUMBE   MO(_NUMBERS)
#define T_GAME  TO(_GAME)
#define T_MOUSE TO(_MOUSE)
#define T_DEF   TO(_BLAKEMAK_C)

// alternate keys
#define L       KC_LEFT
#define D       KC_DOWN
#define U       KC_UP
#define R       KC_RIGHT

#define M_L     KC_MS_L
#define M_D     KC_MS_D
#define M_U     KC_MS_U
#define M_R     KC_MS_R

#define MW_L    KC_MS_WH_LEFT
#define MW_D    KC_MS_WH_DOWN
#define MW_U    KC_MS_WH_UP
#define MW_R    KC_MS_WH_RIGHT

//#define TERM    LCA(KC_T)
//#define PLUS    LSFT(KC_EQL)
//#define STAR    LSFT(KC_8)
//#define WS_L    G(KC_PGUP)
//#define WS_R    G(KC_PGDN)

// mod taps
//#define CTL_ENT CTL_T(KC_ENT)
#define MT_G    ALT_T(KC_G)
#define MT_H    SFT_T(KC_H)

#define MT_A    SFT_T(KC_A)
#define MT_S    CTL_T(KC_S)
#define MT_D    ALT_T(KC_D)
#define MT_F    SFT_T(KC_F)

#define MT_J    SFT_T(KC_J)
#define MT_K    CTL_T(KC_K)
#define MT_L    ALT_T(KC_L)
#define MT_SI   SFT_T(KC_SCLN)
//
//#define MTQ_A   SFT_T(KC_A)
//#define MTQ_S   CTL_T(KC_S)
//#define MTQ_D   ALT_T(KC_D)
//#define MTQ_F   SFT_T(KC_F)

// layer tap
//#define MO_TAB LT(MOUSE, KC_TAB)
//#define SY_GRV LT(SYMBOL, KC_GRV)

void keyboard_pre_init_user(void) { layer_move(_BLAKEMAK_C); }

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_GAME] = LAYOUT(
    KC_TAB , KC_1  , KC_2  , KC_3  ,
    KC_LSFT, KC_A  , KC_W  , KC_D  ,
    KC_LALT, KC_R  , KC_S  , KC_E  ,
             FUNC  ,KC_LCTL, KC_SPC
  ),

  [_BLAKEMAK_C] = LAYOUT(
    KC_ESC , KC_T  , KC_Y  , KC_DEL,
    KC_LSFT, MT_G  , MT_H  ,KC_BSPC,
    KC_BSLS, KC_B  , KC_N  , KC_SPC,
             FUNC  , BM_L  , BM_R
  ),

  [_BLAKEMAK_L] = LAYOUT(
    KC_Q   , KC_W  , KC_E  , KC_R,
    MT_A   , MT_S  , MT_D  , MT_F,
    KC_Z   , KC_X  , KC_C  , KC_V,
            _______,_______,_______
  ),

  [_BLAKEMAK_R] = LAYOUT(
    KC_U   , KC_I  , KC_O  , KC_P  ,
    MT_J   , MT_K  , MT_L  , MT_SI ,
    KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,
            _______, KC_ENT,_______
  ),

  [_MOUSE] = LAYOUT(
    MW_U   , MW_L  ,KC_LSFT, MW_R  ,
    MW_D   , M_L   , M_U   , M_R   ,
    KC_BTN3,KC_BTN1, M_D   ,KC_BTN2,
            FUNC   ,_______,_______
  ),

  [_NUMBERS] = LAYOUT(
    _______, KC_7  , KC_8  , KC_9  ,
    _______, KC_4  , KC_5  , KC_6  ,
    KC_0   , KC_1  , KC_2  , KC_3  ,
            _______,KC_LSFT,_______
  ),

  [_FUNC] = LAYOUT(
    QK_BOOT, T_GAME, T_DEF ,T_MOUSE,
    NUMBE  , L     , U     , R     ,
    KC_LALT, KC_TAB, D     ,KC_GRV,
            _______,_______,_______
  ),

};
