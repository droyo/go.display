#include "display.h"
#include <GLUT/glut.h>
#include <string.h>
#include <stdio.h>

KeyCode glut2dsChr(unsigned char c);
KeyCode glut2dsKey(int k);
int glut2dsMod(int m);
int glut2dsBtn(int b);

#define nelem(x) ((sizeof(x))/(sizeof(*x)))

/* GLUT only allows for one window. We will use this limitation to
   make our code a bit simpler and save some memory. */
struct {
	int      eventOccured;
	int      window;
	int      width, height;
	int      cursor;
	void*    data;
	char*    title;
	Event    event;
	MouseBtn mouseState;
	int warp;
} G;

typedef struct {
	char *Title;
	int Width, Height;
	int XPos, YPos;
	int Mode;
	int Fullscreen;
	int WarpMouse;
} Config;

/* Lookup tables for conversion */
KeyCode glut2dsChr(unsigned char c) {
	KeyCode LUT[] = {
		KeyUnknown,      // (0) ASCII Null
		KeyUnknown,      // (1) Start of Header
		KeyUnknown,      // (2) Start of Text
		KeyUnknown,      // (3) End of Text
		KeyUnknown,      // (4) End of Transmission (EOT)
		KeyUnknown,      // (5) Enquiry
		KeyUnknown,      // (6) ACK
		KeyUnknown,      // (7) Bell
		KeyBackspace,    // (8) Backspace
		KeyTab,          // (9) Tab
		KeyEnter,        // (10) New line
		KeyUnknown,      // (11) Vertical tab
		KeyUnknown,      // (12) Form feed
		KeyEnter,        // (13) Carriage return
		KeyUnknown,      // (14) Shift out
		KeyUnknown,      // (15) Shift In
		KeyUnknown,      // (16) Data Link Escape
		KeyUnknown,      // (17) Device Conrol 01
		KeyUnknown,      // (18) Device Conrol 02
		KeyUnknown,      // (19) Device Conrol 03
		KeyUnknown,      // (20) Device Conrol 04
		KeyUnknown,      // (21) NAK
		KeyUnknown,      // (22) Synchronous idle
		KeyUnknown,      // (23) End of Transmission Block
		KeyUnknown,      // (24) Cancel
		KeyUnknown,      // (25) End of Medium
		KeyUnknown,      // (26) Substitute
		KeyEscape,       // (27) Escape
		KeyUnknown,      // (28) File separator
		KeyUnknown,      // (29) Group separator
		KeyUnknown,      // (30) Record separator
		KeyUnknown,      // (31) Unit separator
		KeySpace,        // (32) Space
		Key1,            // (33) '!':
		KeyApostrophe,   // (34) '"':
		Key3,            // (35) '#':
		Key4,            // (36) '$':
		Key5,            // (37) '%':
		Key7,            // (38) '&':
		KeyApostrophe,   // (39) ''':
		Key9,            // (40) '(':
		Key0,            // (41) ')':
		Key8,            // (42) '*':
		KeyEquals,       // (43) '+':
		KeyComma,        // (44) ',':
		KeyMinus,        // (45) '-':
		KeyPeriod,       // (46) '.':
		KeySlash,        // (47) '/':
		Key0,            // (48) '0':
		Key1,            // (49) '1':
		Key2,            // (50) '2':
		Key3,            // (51) '3':
		Key4,            // (52) '4':
		Key5,            // (53) '5':
		Key6,            // (54) '6':
		Key7,            // (55) '7':
		Key8,            // (56) '8':
		Key9,            // (57) '9':
		KeySemicolon,    // (58) ':':
		KeySemicolon,    // (59) ';':
		KeyComma,        // (60) '<':
		KeyEquals,       // (61) '=':
		KeyPeriod,       // (62) '>':
		KeySlash,        // (63) '?':
		Key2,            // (64) '@':
		KeyA,            // (65) 'A':
		KeyB,            // (66) 'B':
		KeyC,            // (67) 'C':
		KeyD,            // (68) 'D':
		KeyE,            // (69) 'E':
		KeyF,            // (70) 'F':
		KeyG,            // (71) 'G':
		KeyH,            // (72) 'H':
		KeyI,            // (73) 'I':
		KeyJ,            // (74) 'J':
		KeyK,            // (75) 'K':
		KeyL,            // (76) 'L':
		KeyM,            // (77) 'M':
		KeyN,            // (78) 'N':
		KeyO,            // (79) 'O':
		KeyP,            // (80) 'P':
		KeyQ,            // (81) 'Q':
		KeyR,            // (82) 'R':
		KeyS,            // (83) 'S':
		KeyT,            // (84) 'T':
		KeyU,            // (85) 'U':
		KeyV,            // (86) 'V':
		KeyW,            // (87) 'W':
		KeyX,            // (88) 'X':
		KeyY,            // (89) 'Y':
		KeyZ,            // (90) 'Z':
		KeyLeftBracket,  // (91) '[':
		KeyBackslash,    // (92) '\':
		KeyRightBracket, // (93) ']':
		Key6,            // (94) '^':
		KeyMinus,        // (95) '_':
		KeyGrave,        // (96) '`':
		KeyA,            // (97) 'a':
		KeyB,            // (98) 'b':
		KeyC,            // (99) 'c':
		KeyD,            // (100) 'd':
		KeyE,            // (101) 'e':
		KeyF,            // (102) 'f':
		KeyG,            // (103) 'g':
		KeyH,            // (104) 'h':
		KeyI,            // (105) 'i':
		KeyJ,            // (106) 'j':
		KeyK,            // (107) 'k':
		KeyL,            // (108) 'l':
		KeyM,            // (109) 'm':
		KeyN,            // (110) 'n':
		KeyO,            // (111) 'o':
		KeyP,            // (112) 'p':
		KeyQ,            // (113) 'q':
		KeyR,            // (114) 'r':
		KeyS,            // (115) 's':
		KeyT,            // (116) 't':
		KeyU,            // (117) 'u':
		KeyV,            // (118) 'v':
		KeyW,            // (119) 'w':
		KeyX,            // (120) 'x':
		KeyY,            // (121) 'y':
		KeyZ,            // (122) 'z':
		KeyLeftBracket,  // (123) '{':
		KeyBackslash,    // (124) '|':
		KeyRightBracket, // (125) '}':
		KeyGrave,        // (126) '~':
		KeyDelete,       // (127) DEL:
	};
	return (c > nelem(LUT)) ? KeyUnknown : LUT[c];
}

KeyCode glut2dsKey(int k) {
	switch (k) {
		case GLUT_KEY_F1:       return KeyF1;
		case GLUT_KEY_F2:       return KeyF2;
		case GLUT_KEY_F3:       return KeyF3;
		case GLUT_KEY_F4:       return KeyF4;
		case GLUT_KEY_F5:       return KeyF5;
		case GLUT_KEY_F6:       return KeyF6;
		case GLUT_KEY_F7:       return KeyF7;
		case GLUT_KEY_F8:       return KeyF8;
		case GLUT_KEY_F9:       return KeyF9;
		case GLUT_KEY_F10:      return KeyF10;
		case GLUT_KEY_F11:      return KeyF11;
		case GLUT_KEY_F12:      return KeyF12;
		case GLUT_KEY_UP:       return KeyUp;
		case GLUT_KEY_LEFT:     return KeyLeft;
		case GLUT_KEY_RIGHT:    return KeyRight;
		case GLUT_KEY_DOWN:     return KeyDown;
		case GLUT_KEY_PAGE_UP:  return KeyPageUp;
		case GLUT_KEY_PAGE_DOWN:return KeyPageDown;
		case GLUT_KEY_HOME:     return KeyHome;
		case GLUT_KEY_END:      return KeyEnd;
		case GLUT_KEY_INSERT:   return KeyInsert;
	}
	return KeyUnknown;
}

int glut2dsMod(int m) {
	/*
	 SHIFT = 1<<0
	 CTRL  = 1<<1
	 ALT   = 1<<2
	*/
	int LUT[] = {
		0,             /* 000 */
		Shift,         /* 001 */
		Ctrl,          /* 010 */
		Shift|Ctrl,    /* 011 */
		Alt,           /* 100 */
		Alt|Shift,     /* 101 */
		Alt|Ctrl,      /* 110 */
		Alt|Ctrl|Shift /* 111 */
	};
	return (m < 0 || m > 7) ? 0 : LUT[m];
}

int glut2dsBtn(int b) {
	switch (b) {
	case GLUT_LEFT_BUTTON:
		return Mouse1;
	case GLUT_RIGHT_BUTTON:
		return Mouse2;
	case GLUT_MIDDLE_BUTTON:
		return Mouse3;
	}
	return 0;
}

/* Caller ensures this doesn't get called twice */
RC dsInit(int ignore1, char **ignore2) {
	RC v = {0, NULL};
	int argc = 0;
	char *argv[] = {NULL};
	G.mouseState = 0;
	memset(&G, 0, sizeof G);
	glutInit(&argc, argv);
	return v;
}

RC dsTerminate(void) {
	RC v = {0, NULL};
	return v;
}

RC dsWinClose(void *win) {
	RC v;
	int id;
	
	v.err = NULL;
	if (win == NULL) {
		v.err = strdup("No window open");
		v.rc = -1;
		return v;
	}
	id = *((int*)win);
	if (id < 1) {
		asprintf(&v.err, "Invalid window id %d", id);
		v.rc = -1;
		return v;
	} 
	glutDestroyWindow(id);
	memset(&G, 0, sizeof G);
	free(G.title);
	v.rc = 0;
	v.err = NULL;
	return v;
}

void marshalRefreshEvent(void) {
	G.eventOccured = 1;
	G.event.Type = ERefresh;
	goProcessEvent(G.data, G.event.Type, &G.event);
}

void marshalReshapeEvent(int width, int height) {
	G.eventOccured = 1;
	G.event.Type = EResize;
	G.event.Resize.Width = width;
	G.event.Resize.Height = height;
	G.width = width;
	G.height = height;
	goProcessEvent(G.data, G.event.Type, &G.event.Resize);
}

/* Glut does not support IME input. Gotta work on
   that Cocoa backend :) */
void marshalKeyboardEvent(unsigned char c, int x, int y) {
	char strbuf[2];
	G.eventOccured = 1;
	G.event.Type = EKeyPress;
	G.event.KeyPress.Code = glut2dsChr(c);
	G.event.KeyPress.Mod = glut2dsMod(glutGetModifiers());
	G.event.KeyPress.Down = 1;
	goProcessEvent(G.data, G.event.Type, &G.event.KeyPress);
	
	strbuf[0] = c;
	strbuf[1] = 0;
	G.event.Type = EText;
	G.event.Text = strbuf;
	goProcessEvent(G.data, G.event.Type, &G.event.Text);
}

void marshalKeyboardUpEvent(unsigned char c, int x, int y) {
	G.eventOccured = 1;
	char strbuf[2];
	G.event.Type = EKeyPress;
	G.event.KeyPress.Mod  = glut2dsMod(glutGetModifiers());
	G.event.KeyPress.Code = glut2dsChr(c);
	G.event.KeyPress.Down = 0;
	goProcessEvent(G.data, G.event.Type, &G.event.KeyPress);
}

void marshalMouseEvent(int btn, int state, int x, int y) {
	G.eventOccured = 1;
	G.event.Type = ECursor;
	G.event.Cursor.X = x;
	G.event.Cursor.Y = y;
	goProcessEvent(G.data, G.event.Type, &G.event.Cursor);
	
	/* We're trusting GLUT here to report mouse presses and
	   releases reliably */
	G.mouseState ^= glut2dsBtn(btn);
	G.event.Type = EMouse;
	G.event.Mouse.Down = G.mouseState;
	G.event.Mouse.Mod = glut2dsMod(glutGetModifiers());
	goProcessEvent(G.data, G.event.Type, &G.event.Mouse);
}

void marshalMotionEvent(int x, int y) {
	G.eventOccured = 1;
	G.event.Type = ECursor;
	G.event.Cursor.X = x;
	G.event.Cursor.Y = y;
	if (G.warp) {
		glutWarpPointer(G.width/2, G.height/2);
	}
	goProcessEvent(G.data, G.event.Type, &G.event.Cursor);
}

void marshalVisibleEvent(int state) {
	G.eventOccured = 1;
	if (state == GLUT_VISIBLE) {
		G.event.Type = ERefresh;
		goProcessEvent(G.data, G.event.Type, &G.event);
	}
	G.event.Type = EFocus;
	G.event.Focus = (state == GLUT_VISIBLE) ? 1 : 0;
	goProcessEvent(G.data, G.event.Type, &G.event.Focus);
}

void marshalFocusEvent(int state) {
	G.eventOccured = 1;
	G.event.Type = EFocus;
	G.event.Focus = (state == GLUT_LEFT) ? 0 : 1;
	goProcessEvent(G.data, G.event.Type, &G.event.Focus);
}

void marshalSpecialEvent(int k, int x, int y) {
	G.eventOccured = 1;
	G.event.Type = EKeyPress;
	G.event.KeyPress.Down = 1;
	G.event.KeyPress.Code = glut2dsKey(k);
	G.event.KeyPress.Mod = glut2dsMod(glutGetModifiers());
	goProcessEvent(G.data, G.event.Type, &G.event.KeyPress);
}

void marshalSpecialUpEvent(int k, int x, int y) {
	G.eventOccured = 1;
	G.event.Type = EKeyPress;
	G.event.KeyPress.Down = 0;
	G.event.KeyPress.Code = glut2dsKey(k);
	G.event.KeyPress.Mod = glut2dsMod(glutGetModifiers());
	goProcessEvent(G.data, G.event.Type, &G.event.KeyPress);
}

void marshalCloseEvent(void) {
	G.eventOccured = 1;
	G.event.Type = EClose;
	goProcessEvent(G.data, G.event.Type, &G.event);
}

RC dsWinCheckEvent(void *obj) {
	RC v = {0, NULL};
	glutCheckLoop();
	return v;
}

RC dsWinWaitEvent(void *obj) {
	RC v = {0, NULL};
	while (G.eventOccured == 0) {
		glutCheckLoop();
	}
	G.eventOccured = 0;
	return v;
}

RC dsWinGrabMouse(void *obj) {
	RC v = {0, NULL};
	G.warp = 1;
	G.cursor = glutGet(GLUT_WINDOW_CURSOR);
	glutSetCursor(GLUT_CURSOR_NONE);
	return v;
}

RC dsWinReleaseMouse(void *obj) {
	RC v = {0, NULL};
	G.warp = 0;
	glutSetCursor(G.cursor);
	return v;
}

RC dsWinMouseWarp(void *obj, int x, int y) {
	RC v = {0, NULL};
	glutWarpPointer(x, y);
	return v;
}

RP dsWinGetTitle(void *obj) {
	RP v;
	v.rp = G.title;
	v.err = NULL;
	return v;
}

RC dsWinSetTitle(void *obj, char *s) {
	RC v = {0, NULL};
	glutSetWindowTitle(s);
}

R2 dsWinSize(void *obj) {
	R2 v;
	v.err = NULL;
	v.X = glutGet(GLUT_WINDOW_WIDTH);
	v.Y = glutGet(GLUT_WINDOW_HEIGHT);
	return v;
}

RC dsWinResize(void *obj, int width, int height) {
	RC v = {0, NULL};
	glutReshapeWindow(width, height);
	return v;
}

void dsWinSwap(void *obj) {
	glutSwapBuffers();
}

void parse_config(Config *cfg, int argc, char **argv) {
	int i;
	char *key, *val;
	
	cfg->Width = 640;
	cfg->Height = 480;
	cfg->XPos = 0;
	cfg->YPos = 0;
	cfg->Mode = GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH;
	cfg->Fullscreen = 0;
	cfg->WarpMouse = 0;
	
	for(i = 0; i < argc; i += 2) {
		key = argv[i];
		val = argv[i+1];
		
		if(!strcmp(key, "Geometry")) {
			sscanf(val, "%dx%d@%d,%d",
				&(cfg->Width), &(cfg->Height),
				&(cfg->XPos), &(cfg->YPos));
		} else if(!strcmp(key, "Fullscreen")) {
			if (!strcmp(val, "True")) {
				cfg->Fullscreen = 1;
			}
		} else if(!strcmp(key, "Grab Mouse")) {
			if (!strcmp(val, "True")) {
				cfg->WarpMouse = 1;
			}
		} else if(!strcmp(key, "Title")) {
			cfg->Title = val;
		} else if(!strcmp(key, "OpenGL Version")) {
			if (!strcmp(val, "3.2")) {
				cfg->Mode |= GLUT_3_2_CORE_PROFILE;
			}
		}
	}
}

RP dsWinOpen(void *data, int argc, char **argv) {
	RP v;
	Config cfg;
	
	parse_config(&cfg, argc, argv);
	if (glutGetWindow() > 0) {
		v.err = strdup("Multiple windows unsupported");
		v.rp = NULL;
		return v;
	}
	G.data = data;
	glutInitDisplayMode(cfg.Mode);
	glutInitWindowSize(cfg.Width, cfg.Height);
	glutInitWindowPosition(cfg.XPos, cfg.YPos);
	
	int id = glutCreateWindow(cfg.Title);
	if (id < 1) {
		v.err = strdup("Could not create glut window");
		v.rp = NULL;
		return v;
	}
	G.title = strdup(cfg.Title);
	G.window = id;
	G.warp = cfg.WarpMouse;
	G.width = cfg.Width;
	G.height = cfg.Height;
	if (G.warp) {
		G.cursor = glutGet(GLUT_WINDOW_CURSOR);
		glutSetCursor(GLUT_CURSOR_NONE);
	}
	glutDisplayFunc(marshalRefreshEvent);
	glutReshapeFunc(marshalReshapeEvent);
	glutKeyboardFunc(marshalKeyboardEvent);
	glutKeyboardUpFunc(marshalKeyboardUpEvent);
	glutMouseFunc(marshalMouseEvent);
	glutMotionFunc(marshalMotionEvent);
	glutPassiveMotionFunc(marshalMotionEvent);
	glutVisibilityFunc(marshalVisibleEvent);
	glutEntryFunc(marshalFocusEvent);
	glutSpecialFunc(marshalSpecialEvent);
	glutSpecialUpFunc(marshalSpecialUpEvent);
	glutWMCloseFunc(marshalCloseEvent);
	
	v.rp = &G.window;
	v.err = NULL;
	return v;
}
