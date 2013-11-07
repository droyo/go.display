#include "display.h"
#include <SDL2/SDL.h>
#include <string.h>
#include <stdio.h>
#define nelem(x) ((sizeof x)/(sizeof *x))

typedef struct {
	Uint32 id;
	SDL_Window *W;
	SDL_GLContext C;
	void *data;
} Window;

typedef struct {
	int RSize;
	int GSize;
	int BSize;
	int Depth;
	int XPos, YPos;
	int Width, Height;
	int Flags;
	int SwapInterval;
	int OpenGLMajorVersion;
	int OpenGLMinorVersion;
	char *Title;
} Config;

KeyCode sdl2dsKey(SDL_Scancode k);
Modifier sdl2dsMod(Uint16 m);
MouseBtn sdl2dsBtn(Uint32 m);
int marshalEvent(void *param, SDL_Event *e);

KeyCode KeyLUT[] = {
	[SDL_SCANCODE_UNKNOWN]            = KeyUnknown,
	[SDL_SCANCODE_A]                  = KeyA,
	[SDL_SCANCODE_B]                  = KeyB,
	[SDL_SCANCODE_C]                  = KeyC,
	[SDL_SCANCODE_D]                  = KeyD,
	[SDL_SCANCODE_E]                  = KeyE,
	[SDL_SCANCODE_F]                  = KeyF,
	[SDL_SCANCODE_G]                  = KeyG,
	[SDL_SCANCODE_H]                  = KeyH,
	[SDL_SCANCODE_I]                  = KeyI,
	[SDL_SCANCODE_J]                  = KeyJ,
	[SDL_SCANCODE_K]                  = KeyK,
	[SDL_SCANCODE_L]                  = KeyL,
	[SDL_SCANCODE_M]                  = KeyM,
	[SDL_SCANCODE_N]                  = KeyN,
	[SDL_SCANCODE_O]                  = KeyO,
	[SDL_SCANCODE_P]                  = KeyP,
	[SDL_SCANCODE_Q]                  = KeyQ,
	[SDL_SCANCODE_R]                  = KeyR,
	[SDL_SCANCODE_S]                  = KeyS,
	[SDL_SCANCODE_T]                  = KeyT,
	[SDL_SCANCODE_U]                  = KeyU,
	[SDL_SCANCODE_V]                  = KeyV,
	[SDL_SCANCODE_W]                  = KeyW,
	[SDL_SCANCODE_X]                  = KeyX,
	[SDL_SCANCODE_Y]                  = KeyY,
	[SDL_SCANCODE_Z]                  = KeyZ,
	[SDL_SCANCODE_1]                  = Key1,
	[SDL_SCANCODE_2]                  = Key2,
	[SDL_SCANCODE_3]                  = Key3,
	[SDL_SCANCODE_4]                  = Key4,
	[SDL_SCANCODE_5]                  = Key5,
	[SDL_SCANCODE_6]                  = Key6,
	[SDL_SCANCODE_7]                  = Key7,
	[SDL_SCANCODE_8]                  = Key8,
	[SDL_SCANCODE_9]                  = Key9,
	[SDL_SCANCODE_0]                  = Key0,
	[SDL_SCANCODE_RETURN]             = KeyEnter,
	[SDL_SCANCODE_ESCAPE]             = KeyEscape,
	[SDL_SCANCODE_BACKSPACE]          = KeyBackspace,
	[SDL_SCANCODE_TAB]                = KeyTab,
	[SDL_SCANCODE_SPACE]              = KeySpace,
	[SDL_SCANCODE_MINUS]              = KeyMinus,
	[SDL_SCANCODE_EQUALS]             = KeyEquals,
	[SDL_SCANCODE_LEFTBRACKET]        = KeyLeftBracket,
	[SDL_SCANCODE_RIGHTBRACKET]       = KeyRightBracket,
	[SDL_SCANCODE_BACKSLASH]          = KeyBackslash,
	[SDL_SCANCODE_NONUSHASH]          = KeyNonUShash,
	[SDL_SCANCODE_SEMICOLON]          = KeySemicolon,
	[SDL_SCANCODE_APOSTROPHE]         = KeyApostrophe,
	[SDL_SCANCODE_GRAVE]              = KeyGrave,
	[SDL_SCANCODE_COMMA]              = KeyComma,
	[SDL_SCANCODE_PERIOD]             = KeyPeriod,
	[SDL_SCANCODE_SLASH]              = KeySlash,
	[SDL_SCANCODE_CAPSLOCK]           = KeyCapsLock,
	[SDL_SCANCODE_F1]                 = KeyF1,
	[SDL_SCANCODE_F2]                 = KeyF2,
	[SDL_SCANCODE_F3]                 = KeyF3,
	[SDL_SCANCODE_F4]                 = KeyF4,
	[SDL_SCANCODE_F5]                 = KeyF5,
	[SDL_SCANCODE_F6]                 = KeyF6,
	[SDL_SCANCODE_F7]                 = KeyF7,
	[SDL_SCANCODE_F8]                 = KeyF8,
	[SDL_SCANCODE_F9]                 = KeyF9,
	[SDL_SCANCODE_F10]                = KeyF10,
	[SDL_SCANCODE_F11]                = KeyF11,
	[SDL_SCANCODE_F12]                = KeyF12,
	[SDL_SCANCODE_PRINTSCREEN]        = KeyPrintScreen,
	[SDL_SCANCODE_SCROLLLOCK]         = KeyScrollLock,
	[SDL_SCANCODE_PAUSE]              = KeyPause,
	[SDL_SCANCODE_INSERT]             = KeyInsert,
	[SDL_SCANCODE_HOME]               = KeyHome,
	[SDL_SCANCODE_PAGEUP]             = KeyPageUp,
	[SDL_SCANCODE_DELETE]             = KeyDelete,
	[SDL_SCANCODE_END]                = KeyEnd,
	[SDL_SCANCODE_PAGEDOWN]           = KeyPageDown,
	[SDL_SCANCODE_RIGHT]              = KeyRight,
	[SDL_SCANCODE_LEFT]               = KeyLeft,
	[SDL_SCANCODE_DOWN]               = KeyDown,
	[SDL_SCANCODE_UP]                 = KeyUp,
	[SDL_SCANCODE_NUMLOCKCLEAR]       = KeyNumLockClear,
	[SDL_SCANCODE_KP_DIVIDE]          = KeyPadDivide,
	[SDL_SCANCODE_KP_MULTIPLY]        = KeyPadMultiply,
	[SDL_SCANCODE_KP_MINUS]           = KeyPadMinus,
	[SDL_SCANCODE_KP_PLUS]            = KeyPadPlus,
	[SDL_SCANCODE_KP_ENTER]           = KeyPadEnter,
	[SDL_SCANCODE_KP_1]               = KeyPad1,
	[SDL_SCANCODE_KP_2]               = KeyPad2,
	[SDL_SCANCODE_KP_3]               = KeyPad3,
	[SDL_SCANCODE_KP_4]               = KeyPad4,
	[SDL_SCANCODE_KP_5]               = KeyPad5,
	[SDL_SCANCODE_KP_6]               = KeyPad6,
	[SDL_SCANCODE_KP_7]               = KeyPad7,
	[SDL_SCANCODE_KP_8]               = KeyPad8,
	[SDL_SCANCODE_KP_9]               = KeyPad9,
	[SDL_SCANCODE_KP_0]               = KeyPad0,
	[SDL_SCANCODE_KP_PERIOD]          = KeyPadPeriod,
	[SDL_SCANCODE_NONUSBACKSLASH]     = KeyNonUSBackslash,
	[SDL_SCANCODE_APPLICATION]        = KeyApplication,
	[SDL_SCANCODE_POWER]              = KeyPower,
	[SDL_SCANCODE_KP_EQUALS]          = KeyPadEquals,
	[SDL_SCANCODE_F13]                = KeyF13,
	[SDL_SCANCODE_F14]                = KeyF14,
	[SDL_SCANCODE_F15]                = KeyF15,
	[SDL_SCANCODE_F16]                = KeyF16,
	[SDL_SCANCODE_F17]                = KeyF17,
	[SDL_SCANCODE_F18]                = KeyF18,
	[SDL_SCANCODE_F19]                = KeyF19,
	[SDL_SCANCODE_F20]                = KeyF20,
	[SDL_SCANCODE_F21]                = KeyF21,
	[SDL_SCANCODE_F22]                = KeyF22,
	[SDL_SCANCODE_F23]                = KeyF23,
	[SDL_SCANCODE_F24]                = KeyF24,
	[SDL_SCANCODE_EXECUTE]            = KeyExecute,
	[SDL_SCANCODE_HELP]               = KeyHelp,
	[SDL_SCANCODE_MENU]               = KeyMenu,
	[SDL_SCANCODE_SELECT]             = KeySelect,
	[SDL_SCANCODE_STOP]               = KeyStop,
	[SDL_SCANCODE_AGAIN]              = KeyAgain,
	[SDL_SCANCODE_UNDO]               = KeyUndo,
	[SDL_SCANCODE_CUT]                = KeyCut,
	[SDL_SCANCODE_COPY]               = KeyCopy,
	[SDL_SCANCODE_PASTE]              = KeyPaste,
	[SDL_SCANCODE_FIND]               = KeyFind,
	[SDL_SCANCODE_MUTE]               = KeyMute,
	[SDL_SCANCODE_VOLUMEUP]           = KeyVolumeUp,
	[SDL_SCANCODE_VOLUMEDOWN]         = KeyVolumeDown,
//	[SDL_SCANCODE_LOCKINGCAPSLOCK]    = KeyLockingCapsLock,
//	[SDL_SCANCODE_LOCKINGNUMLOCK]     = KeyLockingNumLock,
//	[SDL_SCANCODE_LOCKINGSCROLLLOCK]  = KeyLockingScrollLock,
	[SDL_SCANCODE_KP_COMMA]           = KeyPadComma,
	[SDL_SCANCODE_KP_EQUALSAS400]     = KeyPadEqualsAs400,
	[SDL_SCANCODE_INTERNATIONAL1]     = KeyInternational1,
	[SDL_SCANCODE_INTERNATIONAL2]     = KeyInternational2,
	[SDL_SCANCODE_INTERNATIONAL3]     = KeyInternational3,
	[SDL_SCANCODE_INTERNATIONAL4]     = KeyInternational4,
	[SDL_SCANCODE_INTERNATIONAL5]     = KeyInternational5,
	[SDL_SCANCODE_INTERNATIONAL6]     = KeyInternational6,
	[SDL_SCANCODE_INTERNATIONAL7]     = KeyInternational7,
	[SDL_SCANCODE_INTERNATIONAL8]     = KeyInternational8,
	[SDL_SCANCODE_INTERNATIONAL9]     = KeyInternational9,
	[SDL_SCANCODE_LANG1]              = KeyLang1,
	[SDL_SCANCODE_LANG2]              = KeyLang2,
	[SDL_SCANCODE_LANG3]              = KeyLang3,
	[SDL_SCANCODE_LANG4]              = KeyLang4,
	[SDL_SCANCODE_LANG5]              = KeyLang5,
	[SDL_SCANCODE_LANG6]              = KeyLang6,
	[SDL_SCANCODE_LANG7]              = KeyLang7,
	[SDL_SCANCODE_LANG8]              = KeyLang8,
	[SDL_SCANCODE_LANG9]              = KeyLang9,
	[SDL_SCANCODE_ALTERASE]           = KeyAlterase,
	[SDL_SCANCODE_SYSREQ]             = KeySysreq,
	[SDL_SCANCODE_CANCEL]             = KeyCancel,
	[SDL_SCANCODE_CLEAR]              = KeyClear,
	[SDL_SCANCODE_PRIOR]              = KeyPrior,
	[SDL_SCANCODE_RETURN2]            = KeyReturn2,
	[SDL_SCANCODE_SEPARATOR]          = KeySeparator,
	[SDL_SCANCODE_OUT]                = KeyOut,
	[SDL_SCANCODE_OPER]               = KeyOper,
	[SDL_SCANCODE_CLEARAGAIN]         = KeyClearAgain,
	[SDL_SCANCODE_CRSEL]              = KeyCrsel,
	[SDL_SCANCODE_EXSEL]              = KeyExsel,
	[SDL_SCANCODE_KP_00]              = KeyPad00,
	[SDL_SCANCODE_KP_000]             = KeyPad000,
	[SDL_SCANCODE_THOUSANDSSEPARATOR] = KeyThousandsSeparator,
	[SDL_SCANCODE_DECIMALSEPARATOR]   = KeyDecimalSeparator,
	[SDL_SCANCODE_CURRENCYUNIT]       = KeyCurrencyUnit,
	[SDL_SCANCODE_CURRENCYSUBUNIT]    = KeyCurrencySubUnit,
	[SDL_SCANCODE_KP_LEFTPAREN]       = KeyPadLeftParen,
	[SDL_SCANCODE_KP_RIGHTPAREN]      = KeyPadRightParen,
	[SDL_SCANCODE_KP_LEFTBRACE]       = KeyPadLeftBrace,
	[SDL_SCANCODE_KP_RIGHTBRACE]      = KeyPadRightBrace,
	[SDL_SCANCODE_KP_TAB]             = KeyPadTab,
	[SDL_SCANCODE_KP_BACKSPACE]       = KeyPadBackspace,
	[SDL_SCANCODE_KP_A]               = KeyPadA,
	[SDL_SCANCODE_KP_B]               = KeyPadB,
	[SDL_SCANCODE_KP_C]               = KeyPadC,
	[SDL_SCANCODE_KP_D]               = KeyPadD,
	[SDL_SCANCODE_KP_E]               = KeyPadE,
	[SDL_SCANCODE_KP_F]               = KeyPadF,
	[SDL_SCANCODE_KP_XOR]             = KeyPadXOR,
	[SDL_SCANCODE_KP_POWER]           = KeyPadPower,
	[SDL_SCANCODE_KP_PERCENT]         = KeyPadPercent,
	[SDL_SCANCODE_KP_LESS]            = KeyPadLess,
	[SDL_SCANCODE_KP_GREATER]         = KeyPadGreater,
	[SDL_SCANCODE_KP_AMPERSAND]       = KeyPadAmpersand,
	[SDL_SCANCODE_KP_DBLAMPERSAND]    = KeyPadDblampersand,
	[SDL_SCANCODE_KP_VERTICALBAR]     = KeyPadVerticalbar,
	[SDL_SCANCODE_KP_DBLVERTICALBAR]  = KeyPadDblverticalbar,
	[SDL_SCANCODE_KP_COLON]           = KeyPadColon,
	[SDL_SCANCODE_KP_HASH]            = KeyPadHash,
	[SDL_SCANCODE_KP_SPACE]           = KeyPadSpace,
	[SDL_SCANCODE_KP_AT]              = KeyPadAt,
	[SDL_SCANCODE_KP_EXCLAM]          = KeyPadExclam,
	[SDL_SCANCODE_KP_MEMSTORE]        = KeyPadMemstore,
	[SDL_SCANCODE_KP_MEMRECALL]       = KeyPadMemrecall,
	[SDL_SCANCODE_KP_MEMCLEAR]        = KeyPadMemclear,
	[SDL_SCANCODE_KP_MEMADD]          = KeyPadMemadd,
	[SDL_SCANCODE_KP_MEMSUBTRACT]     = KeyPadMemsubtract,
	[SDL_SCANCODE_KP_MEMMULTIPLY]     = KeyPadMemmultiply,
	[SDL_SCANCODE_KP_MEMDIVIDE]       = KeyPadMemdivide,
	[SDL_SCANCODE_KP_PLUSMINUS]       = KeyPadPlusminus,
	[SDL_SCANCODE_KP_CLEAR]           = KeyPadClear,
	[SDL_SCANCODE_KP_CLEARENTRY]      = KeyPadClearentry,
	[SDL_SCANCODE_KP_BINARY]          = KeyPadBinary,
	[SDL_SCANCODE_KP_OCTAL]           = KeyPadOctal,
	[SDL_SCANCODE_KP_DECIMAL]         = KeyPadDecimal,
	[SDL_SCANCODE_KP_HEXADECIMAL]     = KeyPadHexadecimal,
	[SDL_SCANCODE_LCTRL]              = KeyLeftControl,
	[SDL_SCANCODE_LSHIFT]             = KeyLeftShift,
	[SDL_SCANCODE_LALT]               = KeyLeftAlt,
	[SDL_SCANCODE_LGUI]               = KeyLeftSuper,
	[SDL_SCANCODE_RCTRL]              = KeyRightControl,
	[SDL_SCANCODE_RSHIFT]             = KeyRightShift,
	[SDL_SCANCODE_RALT]               = KeyRightAlt,
	[SDL_SCANCODE_RGUI]               = KeyRightSuper,
	[SDL_SCANCODE_MODE]               = KeyMode,
	[SDL_SCANCODE_AUDIONEXT]          = KeyAudioNext,
	[SDL_SCANCODE_AUDIOPREV]          = KeyAudioPrev,
	[SDL_SCANCODE_AUDIOSTOP]          = KeyAudioStop,
	[SDL_SCANCODE_AUDIOPLAY]          = KeyAudioPlay,
	[SDL_SCANCODE_AUDIOMUTE]          = KeyAudioMute,
	[SDL_SCANCODE_MEDIASELECT]        = KeyMediaSelect,
	[SDL_SCANCODE_WWW]                = KeyWWW,
	[SDL_SCANCODE_MAIL]               = KeyMail,
	[SDL_SCANCODE_CALCULATOR]         = KeyCalculator,
	[SDL_SCANCODE_COMPUTER]           = KeyComputer,
	[SDL_SCANCODE_AC_SEARCH]          = KeyACSearch,
	[SDL_SCANCODE_AC_HOME]            = KeyACHome,
	[SDL_SCANCODE_AC_BACK]            = KeyACBack,
	[SDL_SCANCODE_AC_FORWARD]         = KeyACForward,
	[SDL_SCANCODE_AC_STOP]            = KeyACStop,
	[SDL_SCANCODE_AC_REFRESH]         = KeyACRefresh,
	[SDL_SCANCODE_AC_BOOKMARKS]       = KeyACBookmarks,
	[SDL_SCANCODE_BRIGHTNESSDOWN]     = KeyBrightnessDown,
	[SDL_SCANCODE_BRIGHTNESSUP]       = KeyBrightnessUp,
	[SDL_SCANCODE_DISPLAYSWITCH]      = KeyDisplaySwitch,
	[SDL_SCANCODE_KBDILLUMTOGGLE]     = KeyKbdIllumToggle,
	[SDL_SCANCODE_KBDILLUMDOWN]       = KeyKbdIllumDown,
	[SDL_SCANCODE_KBDILLUMUP]         = KeyKbdIllumUp,
	[SDL_SCANCODE_EJECT]              = KeyEject,
	[SDL_SCANCODE_SLEEP]              = KeySleep,
};

KeyCode sdl2dsKey(SDL_Scancode k) {
	if (k > nelem(KeyLUT) || k < 0) {
		return KeyUnknown;
	}
	return KeyLUT[k];
}

MouseBtn sdl2dsBtn(Uint32 m) {
	MouseBtn r = 0;
	r |= ((m & SDL_BUTTON(1))>0) * Mouse1;
	r |= ((m & SDL_BUTTON(2))>0) * Mouse2;
	r |= ((m & SDL_BUTTON(3))>0) * Mouse3;
	return r;
}

Modifier sdl2dsMod(Uint16 m) {
	Modifier r = 0;
	r |= ((m & (KMOD_RSHIFT|KMOD_LSHIFT))>0) * Shift;
	r |= ((m & (KMOD_RALT  |KMOD_LALT  ))>0) * Alt;
	r |= ((m & (KMOD_RCTRL |KMOD_LCTRL ))>0) * Ctrl;
	r |= ((m & (KMOD_RGUI  |KMOD_LGUI  ))>0) * Super;
	return r;
}

RC dsInit(int argc, char **argv) {
	RC v;
	v.err = NULL;
	v.rc = 0;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		v.rc = -1;
		v.err = strdup(SDL_GetError());
		SDL_ClearError();
	}
	return v;
}

RC dsTerminate(void) {
	RC v = { 0, NULL };
	SDL_Quit();
	return v;
}

void parse_config(Config *cfg, int argc, char **argv) {
	int i;
	char *key, *val;
	SDL_Rect scr;

	cfg->RSize = 5;
	cfg->GSize = 5;
	cfg->BSize = 5;
	cfg->Depth = 16;
	cfg->XPos = 0;
	cfg->YPos = 0;
	cfg->Width = 640;
	cfg->Height = 480;
	if (SDL_GetDisplayBounds(0, &scr) == 0) {
		cfg->XPos = scr.x;
		cfg->YPos = scr.y;
		cfg->Width = scr.w;
		cfg->Height = scr.h;
	}
	cfg->Flags = SDL_WINDOW_OPENGL |
		SDL_WINDOW_RESIZABLE |
		SDL_WINDOW_INPUT_FOCUS |
		SDL_WINDOW_MOUSE_FOCUS;
	cfg->OpenGLMajorVersion = 0;
	cfg->OpenGLMinorVersion = 0;
	cfg->SwapInterval = 1;
	cfg->Title = "SDL Window";
	
	for (i = 0; i < argc; i += 2) {
		key = argv[i];
		val = argv[i+1];
		
		if(!strcmp(key, "OpenGL Version")) {
			sscanf(val, "%d.%d", 
				&(cfg->OpenGLMajorVersion),
				&(cfg->OpenGLMinorVersion));
		} else if(!strcmp(key, "Geometry")) {
			sscanf(val, "%dx%d@%d,%d",
				&(cfg->Width), &(cfg->Height),
				&(cfg->XPos), &(cfg->YPos));
		} else if(!strcmp(key, "Red Buffer")) {
			cfg->RSize = strtol(val, NULL, 10);
		} else if(!strcmp(key, "Green Buffer")) {
			cfg->GSize = strtol(val, NULL, 10);
		} else if(!strcmp(key, "Blue Buffer")) {
			cfg->BSize = strtol(val, NULL, 10);
		} else if(!strcmp(key, "Depth Buffer")) {
			cfg->Depth = strtol(val, NULL, 10);
		} else if(!strcmp(key, "Title")) {
			cfg->Title = val;
		} else if(!strcmp(key, "Fullscreen")) {
			if (!strcmp(val, "True")) {
				cfg->Flags |= SDL_WINDOW_FULLSCREEN;
			}
		} else if(!strcmp(key, "Grab Mouse")) {
			if (!strcmp(val, "True")) {
				cfg->Flags |= SDL_WINDOW_INPUT_GRABBED;
			}
		} else if(!strcmp(key, "Border")) {
			if (!strcmp(val, "False")) {
				cfg->Flags |= SDL_WINDOW_BORDERLESS;
			}
		} else if(!strcmp(key, "Hide")) {
			if (!strcmp(val, "True")) {
				cfg->Flags |= SDL_WINDOW_HIDDEN;
				cfg->Flags &= ~SDL_WINDOW_SHOWN;
			}
		} else if(!strcmp(key, "Resize")) {
			if (!strcmp(val, "False")) {
				cfg->Flags &= ~SDL_WINDOW_RESIZABLE;
			}
		} else if(!strcmp(key, "Swap Interval")) {
			cfg->SwapInterval = strtol(val, NULL, 10);
		}
	}
}

RP dsWinOpen(void *data, int argc, char **argv) {
	RP v;
	Window *w;
	SDL_Window *win;
	Config cfg;
	SDL_GLContext c;
	
	v.err = NULL;

	parse_config(&cfg, argc, argv);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetSwapInterval(cfg.SwapInterval);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, cfg.RSize);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, cfg.GSize);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, cfg.BSize);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, cfg.Depth);
	if (cfg.OpenGLMajorVersion) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, cfg.OpenGLMajorVersion);
	}
	if (cfg.OpenGLMinorVersion) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, cfg.OpenGLMinorVersion);
	}
	win = SDL_CreateWindow(
		cfg.Title,
		cfg.XPos,  cfg.YPos,
		cfg.Width, cfg.Height,
		cfg.Flags
	);
	if (win == NULL) {
		goto fail_createwindow;
	}
	c = SDL_GL_CreateContext(win);
	if (c == NULL) {
		goto fail_createcontext;
	}
	if ((w = malloc(sizeof *w)) == NULL) {
		v.err = strdup("Cannot allocate memory for window object");
		goto fail_allocwinstruct;
	}
	memset(w, 0, sizeof *w);
	w->W = win;
	w->C = c;
	w->data = data;
	SDL_SetEventFilter(marshalEvent, w);
	v.rp = w;
	return v;

fail_allocwinstruct:
	SDL_GL_DeleteContext(c);
fail_createcontext:
	SDL_DestroyWindow(win);
fail_createwindow:
	v.rp = NULL;
	v.err = v.err ? v.err : strdup(SDL_GetError());
	SDL_ClearError();
	return v;
}

RC dsWinClose(void *obj) {
	RC v = { 0, NULL };
	Window *w = obj;
	if (w == NULL) {
		v.rc = -1;
		v.err = strdup("Null window object");
		return v;
	}
	if (w->C == NULL) {
		v.rc = -1;
		v.err = strdup("Null GL context");
	} else {
		SDL_GL_DeleteContext(w->C);
	}
	if (w->W == NULL) {
		v.rc = -1;
		v.err = strdup("Null SDL Window");
	} else {
		SDL_DestroyWindow(w->W);
	}
	free(w);
	return v;
}

RP dsWinGetTitle(void *obj) {
	RP v;
	const char *p;
	Window *win = obj;
	
	if (win == NULL || win->W == NULL) {
		v.err = strdup("Null window object");
	} else if ((p = SDL_GetWindowTitle(win->W)) == NULL) {
		v.err = strdup(SDL_GetError());
		SDL_ClearError();
	} else {
		v.err = NULL;
		v.rp = strdup(p);
	}
	return v;
}

RC dsWinSetTitle(void *obj, char *title) {
	RC v;
	Window *win = obj;
	
	if (win == NULL || win->W == NULL) {
		v.err = strdup("Null window object");
	} else {
		SDL_SetWindowTitle(win->W, title);
	}
	free(title);
	return v;
}

R2 dsWinSize(void *obj) {
	R2 v;
	
	Window *win = obj;
	v.err = NULL;
	
	if (win == NULL || win->W == NULL) {
		v.err = strdup("Null window object");
		return v;
	}
	SDL_GetWindowSize(win->W, &v.X, &v.Y);
	return v;
}

RC dsWinResize(void *obj, int w, int h) {
	RC v;
	
	Window *win = obj;
	v.err = NULL;
	SDL_SetWindowSize(win->W, w, h);
	return v;
}

RC dsWinCheckEvent(void *obj) {
	RC v = { 0, NULL };
	SDL_PumpEvents();
	return v;
}

RC dsWinWaitEvent(void *obj) {
	RC v;
	v.rc = SDL_WaitEvent(NULL);
	if (v.rc != 1) {
		v.err = strdup(SDL_GetError());
		SDL_ClearError();
	}
	return v;
}

RC dsWinGrabMouse(void *obj) {
	RC v;
	Window *w = obj;
	v.rc = SDL_SetRelativeMouseMode(SDL_TRUE);
	if (v.rc) {
		v.err = strdup(SDL_GetError());
		SDL_ClearError();
		return v;
	}
	v.err = NULL;
	return v;
}

RC dsWinReleaseMouse(void *obj) {
	RC v;
	Window *w = obj;
	v.rc = SDL_SetRelativeMouseMode(SDL_FALSE);
	if (v.rc) {
		v.err = strdup(SDL_GetError());
		SDL_ClearError();
		return v;
	}
	v.err = NULL;
	return v;
}

RC dsWinMouseWarp(void *obj, int x, int y) {
	RC v = {0, NULL};
	Window *w = obj;
	SDL_WarpMouseInWindow(w->W, x, y);
	return v;
}

int marshalEvent(void *param, SDL_Event *e) {
	Event send;
	Window *w = param;
	void *event = NULL;
	send.Type = EIgnore;
	
	switch(e->type) {
	case SDL_QUIT:
	case SDL_APP_TERMINATING:
	case SDL_APP_LOWMEMORY:
	case SDL_APP_WILLENTERBACKGROUND:
	case SDL_APP_WILLENTERFOREGROUND:
	case SDL_APP_DIDENTERFOREGROUND:
	case SDL_SYSWMEVENT:
		break;
	case SDL_WINDOWEVENT:
		switch(e->window.event) {
		case SDL_WINDOWEVENT_SHOWN:
		case SDL_WINDOWEVENT_HIDDEN:
		case SDL_WINDOWEVENT_EXPOSED:
			send.Type = ERefresh;
			event = &send;
			break;
		case SDL_WINDOWEVENT_MOVED:
		case SDL_WINDOWEVENT_RESIZED:
			send.Type = EResize;
			send.Resize.Width = e->window.data1;
			send.Resize.Height = e->window.data2;
			event = &send.Resize;
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
		case SDL_WINDOWEVENT_MAXIMIZED:
		case SDL_WINDOWEVENT_RESTORED:
		case SDL_WINDOWEVENT_ENTER:
		case SDL_WINDOWEVENT_LEAVE:
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			send.Type = EFocus;
			send.Focus = 1;
			event = &send;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			send.Type = EFocus;
			send.Focus = 0;
			event = &send;
			break;
		case SDL_WINDOWEVENT_CLOSE:
			send.Type = EClose;
			event = &send;
			break;
		}
		break;
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		send.Type = EKeyPress;
		send.KeyPress.Down = (e->type == SDL_KEYDOWN);
		send.KeyPress.Code = sdl2dsKey(e->key.keysym.scancode);
		send.KeyPress.Mod = sdl2dsMod(e->key.keysym.mod);
		event = &send.KeyPress;
		break;
	case SDL_TEXTEDITING:
		send.Type = EEdit;
		send.Edit.Text = e->edit.text;
		send.Edit.Dot = e->edit.start;
		event = &send.Edit;
		break;
	case SDL_TEXTINPUT:
		send.Type = EText;
		send.Text = e->text.text;
		event = &send.Text;
		break;
	case SDL_MOUSEMOTION:
		send.Type = ECursor;
		send.Dev = e->motion.which;
		send.Cursor.X = e->motion.x;
		send.Cursor.Y = e->motion.y;
		event = &send.Cursor;
		break;
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		send.Type = EMouse;
		send.Dev = e->button.which;
		send.Mouse.Down = (e->button.state == SDL_PRESSED);
		send.Mouse.Down = sdl2dsBtn(SDL_GetMouseState(NULL,NULL));
		send.Mouse.Mod = sdl2dsMod(SDL_GetModState());
		event = &send.Mouse;
		break;
	case SDL_MOUSEWHEEL:
		send.Type = EScroll;
		send.Dev = e->wheel.which;
		send.Scroll.X = e->wheel.x;
		send.Scroll.Y = e->wheel.y;
		event = &send.Scroll;
		break;
	case SDL_JOYAXISMOTION:
	case SDL_JOYHATMOTION:
	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
	case SDL_JOYDEVICEADDED:
	case SDL_JOYDEVICEREMOVED:
	case SDL_CONTROLLERAXISMOTION:
	case SDL_CONTROLLERBUTTONDOWN:
	case SDL_CONTROLLERBUTTONUP:
	case SDL_CONTROLLERDEVICEADDED:
	case SDL_CONTROLLERDEVICEREMOVED:
	case SDL_CONTROLLERDEVICEREMAPPED:
	case SDL_FINGERDOWN:
	case SDL_FINGERUP:
	case SDL_FINGERMOTION:
	case SDL_DOLLARGESTURE:
	case SDL_DOLLARRECORD:
	case SDL_MULTIGESTURE:
	case SDL_CLIPBOARDUPDATE:
	case SDL_DROPFILE:
		break;
	}
	goProcessEvent(w->data, send.Type, event);
	return (e->type == SDL_QUIT) ? 1 : 0;
}

void dsWinSwap(void *obj) {
	SDL_GL_SwapWindow(((Window*)obj)->W);
}
