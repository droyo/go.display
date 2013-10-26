package display

// A modifier is a bitwise OR mask of all key modifiers which are
// currently held down. Valid modifiers are any combination of
// Alt, Shift, Control, or Super. Super may refer to the Windows
// key on Microsoft Windows, or the Command key on OSX.
type Modifier int

const (
	ModAlt Modifier = 1 << iota
	ModShift
	ModCtrl
	ModSuper
	ModHyper
)

// Keys are named after the character of the key on a standard US
// keyboard, and may not map to the user's actual keyboard layout.
type Key int

const (
	KeyUnknown Key = iota
	KeyA
	KeyB
	KeyC
	KeyD
	KeyE
	KeyF
	KeyG
	KeyH
	KeyI
	KeyJ
	KeyK
	KeyL
	KeyM
	KeyN
	KeyO
	KeyP
	KeyQ
	KeyR
	KeyS
	KeyT
	KeyU
	KeyV
	KeyW
	KeyX
	KeyY
	KeyZ
	Key1
	Key2
	Key3
	Key4
	Key5
	Key6
	Key7
	Key8
	Key9
	Key0
	KeyEnter
	KeyEscape
	KeyBackspace
	KeyTab
	KeySpace
	KeyMinus
	KeyEquals
	KeyLeftBracket
	KeyRightBracket
	KeyBackslash
	KeyNonUShash
	KeySemicolon
	KeyApostrophe
	KeyGrave
	KeyComma
	KeyPeriod
	KeySlash
	KeyCapsLock
	KeyF1
	KeyF2
	KeyF3
	KeyF4
	KeyF5
	KeyF6
	KeyF7
	KeyF8
	KeyF9
	KeyF10
	KeyF11
	KeyF12
	KeyPrintScreen
	KeyScrollLock
	KeyPause
	KeyInsert
	KeyHome
	KeyPageUp
	KeyDelete
	KeyEnd
	KeyPageDown
	KeyRight
	KeyLeft
	KeyDown
	KeyUp
	KeyNumLockClear
	KeyPadDivide
	KeyPadMultiply
	KeyPadMinus
	KeyPadPlus
	KeyPadEnter
	KeyPad1
	KeyPad2
	KeyPad3
	KeyPad4
	KeyPad5
	KeyPad6
	KeyPad7
	KeyPad8
	KeyPad9
	KeyPad0
	KeyPadPeriod
	KeyNonUSBackslash
	KeyApplication
	KeyPower
	KeyPadEquals
	KeyF13
	KeyF14
	KeyF15
	KeyF16
	KeyF17
	KeyF18
	KeyF19
	KeyF20
	KeyF21
	KeyF22
	KeyF23
	KeyF24
	KeyExecute
	KeyHelp
	KeyMenu
	KeySelect
	KeyStop
	KeyAgain
	KeyUndo
	KeyCut
	KeyCopy
	KeyPaste
	KeyFind
	KeyMute
	KeyVolumeUp
	KeyVolumeDown
	KeyLockingCapsLock
	KeyLockingNumLock
	KeyLockingScrollLock
	KeyPadComma
	KeyPadEqualsAs400
	KeyInternational1
	KeyInternational2
	KeyInternational3
	KeyInternational4
	KeyInternational5
	KeyInternational6
	KeyInternational7
	KeyInternational8
	KeyInternational9
	KeyLang1
	KeyLang2
	KeyLang3
	KeyLang4
	KeyLang5
	KeyLang6
	KeyLang7
	KeyLang8
	KeyLang9
	KeyAlterase
	KeySysreq
	KeyCancel
	KeyClear
	KeyPrior
	KeyReturn2
	KeySeparator
	KeyOut
	KeyOper
	KeyClearAgain
	KeyCrsel
	KeyExsel
	KeyPad00
	KeyPad000
	KeyThousandsSeparator
	KeyDecimalSeparator
	KeyCurrencyUnit
	KeyCurrencySubUnit
	KeyPadLeftParen
	KeyPadRightParen
	KeyPadLeftBrace
	KeyPadRightBrace
	KeyPadTab
	KeyPadBackspace
	KeyPadA
	KeyPadB
	KeyPadC
	KeyPadD
	KeyPadE
	KeyPadF
	KeyPadXOR
	KeyPadPower
	KeyPadPercent
	KeyPadLess
	KeyPadGreater
	KeyPadAmpersand
	KeyPadDblampersand
	KeyPadVerticalbar
	KeyPadDblverticalbar
	KeyPadColon
	KeyPadHash
	KeyPadSpace
	KeyPadAt
	KeyPadExclam
	KeyPadMemstore
	KeyPadMemrecall
	KeyPadMemclear
	KeyPadMemadd
	KeyPadMemsubtract
	KeyPadMemmultiply
	KeyPadMemdivide
	KeyPadPlusminus
	KeyPadClear
	KeyPadClearentry
	KeyPadBinary
	KeyPadOctal
	KeyPadDecimal
	KeyPadHexadecimal
	KeyLeftControl
	KeyLeftShift
	KeyLeftAlt
	KeyLeftSuper
	KeyRightControl
	KeyRightShift
	KeyRightAlt
	KeyRightSuper
	KeyMode
	KeyAudioNext
	KeyAudioPrev
	KeyAudioStop
	KeyAudioPlay
	KeyAudioMute
	KeyMediaSelect
	KeyWWW
	KeyMail
	KeyCalculator
	KeyComputer
	KeyACSearch
	KeyACHome
	KeyACBack
	KeyACForward
	KeyACStop
	KeyACRefresh
	KeyACBookmarks
	KeyBrightnessDown
	KeyBrightnessUp
	KeyDisplaySwitch
	KeyKbdIllumToggle
	KeyKbdIllumDown
	KeyKbdIllumUp
	KeyEject
	KeySleep
)

var keyNames = [...]string{
	KeyUnknown:            "Unknown",
	KeyA:                  "A",
	KeyB:                  "B",
	KeyC:                  "C",
	KeyD:                  "D",
	KeyE:                  "E",
	KeyF:                  "F",
	KeyG:                  "G",
	KeyH:                  "H",
	KeyI:                  "I",
	KeyJ:                  "J",
	KeyK:                  "K",
	KeyL:                  "L",
	KeyM:                  "M",
	KeyN:                  "N",
	KeyO:                  "O",
	KeyP:                  "P",
	KeyQ:                  "Q",
	KeyR:                  "R",
	KeyS:                  "S",
	KeyT:                  "T",
	KeyU:                  "U",
	KeyV:                  "V",
	KeyW:                  "W",
	KeyX:                  "X",
	KeyY:                  "Y",
	KeyZ:                  "Z",
	Key1:                  "1",
	Key2:                  "2",
	Key3:                  "3",
	Key4:                  "4",
	Key5:                  "5",
	Key6:                  "6",
	Key7:                  "7",
	Key8:                  "8",
	Key9:                  "9",
	Key0:                  "0",
	KeyEnter:              "Enter",
	KeyEscape:             "Escape",
	KeyBackspace:          "Backspace",
	KeyTab:                "Tab",
	KeySpace:              "Space",
	KeyMinus:              "Minus",
	KeyEquals:             "Equals",
	KeyLeftBracket:        "LeftBracket",
	KeyRightBracket:       "RightBracket",
	KeyBackslash:          "Backslash",
	KeyNonUShash:          "NonUShash",
	KeySemicolon:          "Semicolon",
	KeyApostrophe:         "Apostrophe",
	KeyGrave:              "Grave",
	KeyComma:              "Comma",
	KeyPeriod:             "Period",
	KeySlash:              "Slash",
	KeyCapsLock:           "CapsLock",
	KeyF1:                 "F1",
	KeyF2:                 "F2",
	KeyF3:                 "F3",
	KeyF4:                 "F4",
	KeyF5:                 "F5",
	KeyF6:                 "F6",
	KeyF7:                 "F7",
	KeyF8:                 "F8",
	KeyF9:                 "F9",
	KeyF10:                "F10",
	KeyF11:                "F11",
	KeyF12:                "F12",
	KeyPrintScreen:        "PrintScreen",
	KeyScrollLock:         "ScrollLock",
	KeyPause:              "Pause",
	KeyInsert:             "Insert",
	KeyHome:               "Home",
	KeyPageUp:             "Pageup",
	KeyDelete:             "Delete",
	KeyEnd:                "End",
	KeyPageDown:           "Pagedown",
	KeyRight:              "Right",
	KeyLeft:               "Left",
	KeyDown:               "Down",
	KeyUp:                 "Up",
	KeyNumLockClear:       "NumLockClear",
	KeyPadDivide:          "PadDivide",
	KeyPadMultiply:        "PadMultiply",
	KeyPadMinus:           "PadMinus",
	KeyPadPlus:            "PadPlus",
	KeyPadEnter:           "PadEnter",
	KeyPad1:               "Pad1",
	KeyPad2:               "Pad2",
	KeyPad3:               "Pad3",
	KeyPad4:               "Pad4",
	KeyPad5:               "Pad5",
	KeyPad6:               "Pad6",
	KeyPad7:               "Pad7",
	KeyPad8:               "Pad8",
	KeyPad9:               "Pad9",
	KeyPad0:               "Pad0",
	KeyPadPeriod:          "PadPeriod",
	KeyNonUSBackslash:     "NonUSBackslash",
	KeyApplication:        "Application",
	KeyPower:              "Power",
	KeyPadEquals:          "PadEquals",
	KeyF13:                "F13",
	KeyF14:                "F14",
	KeyF15:                "F15",
	KeyF16:                "F16",
	KeyF17:                "F17",
	KeyF18:                "F18",
	KeyF19:                "F19",
	KeyF20:                "F20",
	KeyF21:                "F21",
	KeyF22:                "F22",
	KeyF23:                "F23",
	KeyF24:                "F24",
	KeyExecute:            "Execute",
	KeyHelp:               "Help",
	KeyMenu:               "Menu",
	KeySelect:             "Select",
	KeyStop:               "Stop",
	KeyAgain:              "Again",
	KeyUndo:               "Undo",
	KeyCut:                "Cut",
	KeyCopy:               "Copy",
	KeyPaste:              "Paste",
	KeyFind:               "Find",
	KeyMute:               "Mute",
	KeyVolumeUp:           "VolumeUp",
	KeyVolumeDown:         "VolumeDown",
	KeyLockingCapsLock:    "LockingCapsLock",
	KeyLockingNumLock:     "LockingNumLock",
	KeyLockingScrollLock:  "LockingScrollLock",
	KeyPadComma:           "PadComma",
	KeyPadEqualsAs400:     "PadEqualsAs400",
	KeyInternational1:     "International1",
	KeyInternational2:     "International2",
	KeyInternational3:     "International3",
	KeyInternational4:     "International4",
	KeyInternational5:     "International5",
	KeyInternational6:     "International6",
	KeyInternational7:     "International7",
	KeyInternational8:     "International8",
	KeyInternational9:     "International9",
	KeyLang1:              "Lang1",
	KeyLang2:              "Lang2",
	KeyLang3:              "Lang3",
	KeyLang4:              "Lang4",
	KeyLang5:              "Lang5",
	KeyLang6:              "Lang6",
	KeyLang7:              "Lang7",
	KeyLang8:              "Lang8",
	KeyLang9:              "Lang9",
	KeyAlterase:           "Alterase",
	KeySysreq:             "Sysreq",
	KeyCancel:             "Cancel",
	KeyClear:              "Clear",
	KeyPrior:              "Prior",
	KeyReturn2:            "Return2",
	KeySeparator:          "Separator",
	KeyOut:                "Out",
	KeyOper:               "Oper",
	KeyClearAgain:         "ClearAgain",
	KeyCrsel:              "Crsel",
	KeyExsel:              "Exsel",
	KeyPad00:              "Pad00",
	KeyPad000:             "Pad000",
	KeyThousandsSeparator: "ThousandsSeparator",
	KeyDecimalSeparator:   "DecimalSeparator",
	KeyCurrencyUnit:       "CurrencyUnit",
	KeyCurrencySubUnit:    "CurrencySubUnit",
	KeyPadLeftParen:       "PadLeftParen",
	KeyPadRightParen:      "PadRightParen",
	KeyPadLeftBrace:       "PadLeftBrace",
	KeyPadRightBrace:      "PadRightBrace",
	KeyPadTab:             "PadTab",
	KeyPadBackspace:       "PadBackspace",
	KeyPadA:               "PadA",
	KeyPadB:               "PadB",
	KeyPadC:               "PadC",
	KeyPadD:               "PadD",
	KeyPadE:               "PadE",
	KeyPadF:               "PadF",
	KeyPadXOR:             "PadXOR",
	KeyPadPower:           "PadPower",
	KeyPadPercent:         "PadPercent",
	KeyPadLess:            "PadLess",
	KeyPadGreater:         "PadGreater",
	KeyPadAmpersand:       "PadAmpersand",
	KeyPadDblampersand:    "PadDblampersand",
	KeyPadVerticalbar:     "PadVerticalbar",
	KeyPadDblverticalbar:  "PadDblverticalbar",
	KeyPadColon:           "PadColon",
	KeyPadHash:            "PadHash",
	KeyPadSpace:           "PadSpace",
	KeyPadAt:              "PadAt",
	KeyPadExclam:          "PadExclam",
	KeyPadMemstore:        "PadMemstore",
	KeyPadMemrecall:       "PadMemrecall",
	KeyPadMemclear:        "PadMemclear",
	KeyPadMemadd:          "PadMemadd",
	KeyPadMemsubtract:     "PadMemsubtract",
	KeyPadMemmultiply:     "PadMemmultiply",
	KeyPadMemdivide:       "PadMemdivide",
	KeyPadPlusminus:       "PadPlusminus",
	KeyPadClear:           "PadClear",
	KeyPadClearentry:      "PadClearentry",
	KeyPadBinary:          "PadBinary",
	KeyPadOctal:           "PadOctal",
	KeyPadDecimal:         "PadDecimal",
	KeyPadHexadecimal:     "PadHexadecimal",
	KeyLeftControl:        "LeftControl",
	KeyLeftShift:          "LeftShift",
	KeyLeftAlt:            "LeftAlt",
	KeyLeftSuper:          "LeftSuper",
	KeyRightControl:       "RightControl",
	KeyRightShift:         "RightShift",
	KeyRightAlt:           "RightAlt",
	KeyRightSuper:         "RightSuper",
	KeyMode:               "Mode",
	KeyAudioNext:          "AudioNext",
	KeyAudioPrev:          "AudioPrev",
	KeyAudioStop:          "AudioStop",
	KeyAudioPlay:          "AudioPlay",
	KeyAudioMute:          "AudioMute",
	KeyMediaSelect:        "MediaSelect",
	KeyWWW:                "WWW",
	KeyMail:               "Mail",
	KeyCalculator:         "Calculator",
	KeyComputer:           "Computer",
	KeyACSearch:           "ACSearch",
	KeyACHome:             "ACHome",
	KeyACBack:             "ACBack",
	KeyACForward:          "ACForward",
	KeyACStop:             "ACStop",
	KeyACRefresh:          "ACRefresh",
	KeyACBookmarks:        "ACBookmarks",
	KeyBrightnessDown:     "BrightnessDown",
	KeyBrightnessUp:       "BrightnessUp",
	KeyDisplaySwitch:      "DisplaySwitch",
	KeyKbdIllumToggle:     "KbdIllumToggle",
	KeyKbdIllumDown:       "KbdIllumDown",
	KeyKbdIllumUp:         "KbdIllumUp",
	KeyEject:              "Eject",
	KeySleep:              "Sleep",
}

func (k Key) String() string {
	if int(k) > len(keyNames) || int(k) < 0 {
		return keyNames[KeyUnknown]
	}
	return keyNames[k]
}
