typedef enum {
	Mouse1 = 1<<0,
	Mouse2 = 1<<1,
	Mouse3 = 1<<2,
	Mouse4 = 1<<3,
	Mouse5 = 1<<4,
	Mouse6 = 1<<5,
	Mouse7 = 1<<6,
	Mouse8 = 1<<7
} MouseBtn;

typedef enum {
	KeyUnknown = 0,
	KeyA,
	KeyB,
	KeyC,
	KeyD,
	KeyE,
	KeyF,
	KeyG,
	KeyH,
	KeyI,
	KeyJ,
	KeyK,
	KeyL,
	KeyM,
	KeyN,
	KeyO,
	KeyP,
	KeyQ,
	KeyR,
	KeyS,
	KeyT,
	KeyU,
	KeyV,
	KeyW,
	KeyX,
	KeyY,
	KeyZ,
	Key1,
	Key2,
	Key3,
	Key4,
	Key5,
	Key6,
	Key7,
	Key8,
	Key9,
	Key0,
	KeyEnter,
	KeyEscape,
	KeyBackspace,
	KeyTab,
	KeySpace,
	KeyMinus,
	KeyEquals,
	KeyLeftBracket,
	KeyRightBracket,
	KeyBackslash,
	KeyNonUShash,
	KeySemicolon,
	KeyApostrophe,
	KeyGrave,
	KeyComma,
	KeyPeriod,
	KeySlash,
	KeyCapsLock,
	KeyF1,
	KeyF2,
	KeyF3,
	KeyF4,
	KeyF5,
	KeyF6,
	KeyF7,
	KeyF8,
	KeyF9,
	KeyF10,
	KeyF11,
	KeyF12,
	KeyPrintScreen,
	KeyScrollLock,
	KeyPause,
	KeyInsert,
	KeyHome,
	KeyPageUp,
	KeyDelete,
	KeyEnd,
	KeyPageDown,
	KeyRight,
	KeyLeft,
	KeyDown,
	KeyUp,
	KeyNumLockClear,
	KeyPadDivide,
	KeyPadMultiply,
	KeyPadMinus,
	KeyPadPlus,
	KeyPadEnter,
	KeyPad1,
	KeyPad2,
	KeyPad3,
	KeyPad4,
	KeyPad5,
	KeyPad6,
	KeyPad7,
	KeyPad8,
	KeyPad9,
	KeyPad0,
	KeyPadPeriod,
	KeyNonUSBackslash,
	KeyApplication,
	KeyPower,
	KeyPadEquals,
	KeyF13,
	KeyF14,
	KeyF15,
	KeyF16,
	KeyF17,
	KeyF18,
	KeyF19,
	KeyF20,
	KeyF21,
	KeyF22,
	KeyF23,
	KeyF24,
	KeyExecute,
	KeyHelp,
	KeyMenu,
	KeySelect,
	KeyStop,
	KeyAgain,
	KeyUndo,
	KeyCut,
	KeyCopy,
	KeyPaste,
	KeyFind,
	KeyMute,
	KeyVolumeUp,
	KeyVolumeDown,
	KeyLockingCapsLock,
	KeyLockingNumLock,
	KeyLockingScrollLock,
	KeyPadComma,
	KeyPadEqualsAs400,
	KeyInternational1,
	KeyInternational2,
	KeyInternational3,
	KeyInternational4,
	KeyInternational5,
	KeyInternational6,
	KeyInternational7,
	KeyInternational8,
	KeyInternational9,
	KeyLang1,
	KeyLang2,
	KeyLang3,
	KeyLang4,
	KeyLang5,
	KeyLang6,
	KeyLang7,
	KeyLang8,
	KeyLang9,
	KeyAlterase,
	KeySysreq,
	KeyCancel,
	KeyClear,
	KeyPrior,
	KeyReturn2,
	KeySeparator,
	KeyOut,
	KeyOper,
	KeyClearAgain,
	KeyCrsel,
	KeyExsel,
	KeyPad00,
	KeyPad000,
	KeyThousandsSeparator,
	KeyDecimalSeparator,
	KeyCurrencyUnit,
	KeyCurrencySubUnit,
	KeyPadLeftParen,
	KeyPadRightParen,
	KeyPadLeftBrace,
	KeyPadRightBrace,
	KeyPadTab,
	KeyPadBackspace,
	KeyPadA,
	KeyPadB,
	KeyPadC,
	KeyPadD,
	KeyPadE,
	KeyPadF,
	KeyPadXOR,
	KeyPadPower,
	KeyPadPercent,
	KeyPadLess,
	KeyPadGreater,
	KeyPadAmpersand,
	KeyPadDblampersand,
	KeyPadVerticalbar,
	KeyPadDblverticalbar,
	KeyPadColon,
	KeyPadHash,
	KeyPadSpace,
	KeyPadAt,
	KeyPadExclam,
	KeyPadMemstore,
	KeyPadMemrecall,
	KeyPadMemclear,
	KeyPadMemadd,
	KeyPadMemsubtract,
	KeyPadMemmultiply,
	KeyPadMemdivide,
	KeyPadPlusminus,
	KeyPadClear,
	KeyPadClearentry,
	KeyPadBinary,
	KeyPadOctal,
	KeyPadDecimal,
	KeyPadHexadecimal,
	KeyLeftControl,
	KeyLeftShift,
	KeyLeftAlt,
	KeyLeftSuper,
	KeyRightControl,
	KeyRightShift,
	KeyRightAlt,
	KeyRightSuper,
	KeyMode,
	KeyAudioNext,
	KeyAudioPrev,
	KeyAudioStop,
	KeyAudioPlay,
	KeyAudioMute,
	KeyMediaSelect,
	KeyWWW,
	KeyMail,
	KeyCalculator,
	KeyComputer,
	KeyACSearch,
	KeyACHome,
	KeyACBack,
	KeyACForward,
	KeyACStop,
	KeyACRefresh,
	KeyACBookmarks,
	KeyBrightnessDown,
	KeyBrightnessUp,
	KeyDisplaySwitch,
	KeyKbdIllumToggle,
	KeyKbdIllumDown,
	KeyKbdIllumUp,
	KeyEject,
	KeySleep
} KeyCode;

typedef enum {
	Alt   = 1<<0,
	Shift = 1<<1,
	Ctrl  = 1<<2,
	Super = 1<<3,
	Hyper = 1<<4
} Modifier;

typedef unsigned char Bool;
typedef unsigned long Device;

typedef enum {
	EIgnore,
	EEdit,
	EText,
	EKeyPress,
	EResize,
	EFocus,
	EScroll,
	EMouse,
	ECursor,
	ERefresh,
	EClose
} EventType;

typedef struct {
	int X, Y;
} CursorEvent;

typedef struct {
	MouseBtn Down;
	Modifier Mod;
} MouseEvent;

typedef struct {
	char *Text;
	int Dot;
} EditEvent;

typedef struct {
	int Width, Height;
} ResizeEvent;

typedef struct {
	KeyCode Code;
	Modifier Mod;
	Bool Down;
} KeyEvent;

typedef struct {
	int X, Y;
} ScrollEvent;

typedef char *TextEvent;
typedef Bool FocusEvent;

typedef struct {
	EventType Type;
	Device Dev;
	union {
		CursorEvent Cursor;
		MouseEvent Mouse;
		EditEvent Edit;
		ResizeEvent Resize;
		KeyEvent KeyPress;
		ScrollEvent Scroll;
		TextEvent Text;
		FocusEvent Focus;
	};
} Event;

/* Helper functions for implementors */
/* TODO */

typedef struct {
	int rc;
	char *err;
} RC;

typedef struct {
	void *rp;
	char *err;
} RP;

typedef struct {
	int X,Y;
	char *err;
} R2;

typedef struct {
	EventType Type;
	void *data;
	char *err;
} RE;

/* 
Implementations must provide the following functions. WinOpen should
block until a window is closed. All functions execute on the main
thread, except for dsSendCmd
*/
RC dsInit(int argc, char **argv);    /* Init windowing system */
RC dsTerminate(void);                /* Shutdown window system */
RP dsWinOpen(void*,int,char**);      /* Open window */
RC dsWinClose(void*);                /* Close window */
R2 dsWinSize(void*);                 /* Get the window size */
RP dsWinGetTitle(void*);             /* Get the window title */
RC dsWinSetTitle(void*, char*);      /* Set the window title */
RC dsWinResize(void*, int, int);     /* Change the window size */
RC dsWinCheckEvent(void *);          /* Run through events */
RC dsWinWaitEvent(void *);           /* Wait for next event */
RC dsWinGrabMouse(void *);           /* Grab the mouse when focused */
RC dsWinReleaseMouse(void *);        /* Release, unhide cursor */
RC dsWinMouseWarp(void *, int, int); /* Move cursor to new location */
void dsWinSwap(void*);               /* SwapBuffers */

/* This callback should be called for every event */
void goProcessEvent(void *data, EventType typ, void *event);
