package display

import (
	"time"
	"fmt"
	"strings"
)

var devicePool chan Device

func init() {
	devicePool = make(chan Device, 1)
	devicePool <- 101
}

// All user and system events satisfy the Event interface, which must
// provide a unique device identifier and an event time.
type Event interface {
	Src() Device
	Time() time.Time
}

// An Edit event occurs when a user begins inputting candidate text. This
// is most notably used when the user is using an input method to input
// characters that require multiple key presses. The string Text contains
// the non-commited text the user has typed so far.
type Edit struct {
	Text string
	When time.Time
}

// Text events contain a string of UTF-8 encoded text that the user has
// input, either directly by pressing a keyboard key, or indirectly
// by commiting candidate text through an input method.
type Text struct {
	Text string
	When time.Time
}

// KeyPress events occur when a user presses or releases a keyboard key.
// Mod is the bitwise OR mask of all pressed modifiers.
type KeyPress struct {
	Mod  Modifier
	Code Key
	Down bool
	When time.Time
}

// Resize events occur when a window is resized. Width and Height
// represent the new size of the window, in pixels.
type Resize struct {
	Width, Height int
	When          time.Time
}

// A Focus event occurs when a window receives or loses focus. In most
// window systems, a single active window is in focus, and will
// receive user input.
type Focus struct {
	Focused bool
	When    time.Time
}

// A Scroll event occurs when a user scrolls the window, using a mouse
// wheel, track pad or otherwise. X and Y represent the relative
// horizontal and vertical scroll, respectively. Scrolling down and to
// the right produces positive offsets on both axes.
type Scroll struct {
	X, Y int
	When time.Time
}

// Mouse events occur when a mouse button is pressed or released.
// Btn is the bitwise OR mask of all pressed mouse buttons.
// Like a KeyPress, mouse presses may be associated with Modifiers.
type Mouse struct {
	Btn  Button
	Mod  Modifier
	When time.Time
}

// A Cursor event occurs when the cursor position, usually controlled
// by the mouse, is changed. Cursor events contain the X and Y position
// of the cursor in pixels, where the origin is the top left corner of
// the screen.
type Cursor struct {
	X, Y int
	When time.Time
}

// Damage events occur when the window needs to be redisplayed. This
// can happen when part of the window is covered by another and the
// window system does not restore it.
type Damage struct {
	When time.Time
}

// All input events must have a globally unique device identifier
// number, which can be retrieved from an Event throught the Src()
// method. Note that the underlying window system may not be able to
// distinguish between individual keyboards or mice. Events from
// a single device are guaranteed to arrive in chronological order.
// The window package reserves device ids 0-100 for use by system
// devices. By convention, the device id 0 is used when the origin
// device is not important.
type Device uint32

// The GenDevice function may be used to generate a unique device
// identifier. If the pool of device identifiers has been exhausted,
// the device identifier will be zero.
func GenDevice() Device {
	var next Device
	d := <-devicePool
	if d == 0 {
		next = 0
	} else {
		next = d + 1
	}
	devicePool <- next
	return d
}

// Our backing libraries do not support multiple mice/keyboards,
// so we will just fake it in our API. Hopefully we'll find support
// in the future.
const (
	anyDevice Device = iota
	defaultMouseDevice
	defaultKeyboardDevice
	systemDevice
)

// A Button is a bitwise OR mask of all pressed mouse buttons.
// This format makes it easy to compare mouse state between sequential
// events with bitwise operations:
//
// 	var (
// 		prev = Mouse1 | Mouse2 | Mouse5
// 		next = Mouse2 | Mouse3
// 	)
// 	pressed := (prev ^ next) & next // => Mouse3
// 	released := (prev ^ next) & prev // => Mouse1 | Mouse5
// 	holding := prev & next // => Mouse2
type Button int

const (
	Mouse1 Button = 1 << iota
	Mouse2
	Mouse3
	Mouse4
	Mouse5
	Mouse6
	Mouse7
	Mouse8
)

func (e Resize) Time() time.Time   { return e.When }
func (e Focus) Time() time.Time    { return e.When }
func (e Damage) Time() time.Time   { return e.When }
func (e KeyPress) Time() time.Time { return e.When }
func (e Edit) Time() time.Time     { return e.When }
func (e Text) Time() time.Time     { return e.When }
func (e Scroll) Time() time.Time   { return e.When }
func (e Mouse) Time() time.Time    { return e.When }
func (e Cursor) Time() time.Time   { return e.When }

func (Resize) Src() Device   { return systemDevice }
func (Focus) Src() Device    { return systemDevice }
func (Damage) Src() Device   { return systemDevice }
func (KeyPress) Src() Device { return defaultKeyboardDevice }
func (Edit) Src() Device     { return defaultKeyboardDevice }
func (Text) Src() Device     { return defaultKeyboardDevice }
func (Scroll) Src() Device   { return defaultMouseDevice }
func (Mouse) Src() Device    { return defaultMouseDevice }
func (Cursor) Src() Device   { return defaultMouseDevice }

func (mod Modifier) String() string {
	s := make([]string, 0, 4)
	if mod&ModAlt > 0 {
		s = append(s, "Alt")
	}
	if mod&ModShift > 0 {
		s = append(s, "Shift")
	}
	if mod&ModCtrl > 0 {
		s = append(s, "Control")
	}
	if mod&ModSuper > 0 {
		s = append(s, "Super")
	}
	return strings.Join(s, " + ")
}

func (btn Button) String() string {
	b := make([]string, 0, 8)
	if btn&Mouse1 > 0 {
		b = append(b, "M1")
	}
	if btn&Mouse2 > 0 {
		b = append(b, "M2")
	}
	if btn&Mouse3 > 0 {
		b = append(b, "M3")
	}
	if btn&Mouse4 > 0 {
		b = append(b, "M4")
	}
	if btn&Mouse5 > 0 {
		b = append(b, "M5")
	}
	return strings.Join(b, ",")
}

func (key KeyPress) String() string {
	var action string
	combo := make([]string, 0, 2)
	mod := key.Mod.String()

	if len(mod) > 0 {
		combo = append(combo, mod)
	}
	combo = append(combo, key.Code.String())

	if key.Down {
		action = "Press "
	} else {
		action = "Release "
	}
	return fmt.Sprint(action, strings.Join(combo, " + "))
}

func (r Resize) String() string {
	return fmt.Sprintf("Resize window %dx%d", r.Width, r.Height)
}

func (s Scroll) String() string {
	return fmt.Sprintf("Scroll %+d,%+d", s.X, s.Y)
}

func (t Text) String() string {
	return t.Text
}

func (t Edit) String() string {
	return t.Text
}

func (m Mouse) String() string {
	combo := make([]string, 0, 2)
	mod := m.Mod.String()
	btn := m.Btn.String()
	if len(mod) > 0 {
		combo = append(combo, mod)
	}
	if len(btn) > 0 {
		combo = append(combo, btn)
	}
	return strings.Join(combo, " + ")
}

func (m Cursor) String() string {
	return fmt.Sprintf("Cursor (%d,%d)", m.X, m.Y)
}
