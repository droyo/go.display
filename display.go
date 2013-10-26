package display

/*
#include "display.h"
#include <stdlib.h>

#cgo darwin  LDFLAGS: -framework GLUT -framework OpenGL
#cgo linux   LDFLAGS: -lGL -lSDL2
#cgo windows LDFLAGS: -lopengl32 -lSDL2
*/
import "C"

import (
	"errors"
	"log"
	"runtime"
	"sync"
	"time"
	"unsafe"
)

var initialize sync.Once

func init() {
	runtime.LockOSThread()
}

// A Config is used to choose the settings of a
// window display. Different systems may support
// different configurations.
type Config map[string]string

//export goProcessEvent
func goProcessEvent(winP unsafe.Pointer, t C.EventType, p unsafe.Pointer) {
	win := (*Buffer)(winP)
	switch t {
	case C.EMouse:
		e := (*C.MouseEvent)(p)
		win.enqueue(Mouse{
			Btn:  Button(e.Down),
			Mod:  Modifier(e.Mod),
			When: time.Now(),
		})
	case C.ECursor:
		e := (*C.CursorEvent)(p)
		win.enqueue(Cursor{
			X:    int(e.X),
			Y:    int(e.Y),
			When: time.Now(),
		})
	case C.EText:
		e := (*C.TextEvent)(p)
		win.enqueue(Text{
			Text: C.GoString((*C.char)(*e)),
			When: time.Now(),
		})
	case C.EEdit:
		e := (*C.EditEvent)(p)
		win.enqueue(Text{
			Text: C.GoString((*C.char)(e.Text)),
			When: time.Now(),
		})
	case C.EKeyPress:
		e := (*C.KeyEvent)(p)
		win.enqueue(KeyPress{
			Mod:  Modifier(e.Mod),
			Code: Key(e.Code),
			Down: e.Down == 1,
			When: time.Now(),
		})
	case C.EResize:
		e := (*C.ResizeEvent)(p)
		win.enqueue(Resize{
			Width:  int(e.Width),
			Height: int(e.Height),
			When:   time.Now(),
		})
	case C.EFocus:
		e := (*C.FocusEvent)(p)
		win.enqueue(Focus{
			Focused: C.int(*e) == 1,
			When:    time.Now(),
		})
	case C.EScroll:
		e := (*C.ScrollEvent)(p)
		win.enqueue(Scroll{
			X:    int(e.X),
			Y:    int(e.Y),
			When: time.Now(),
		})
	case C.ERefresh:
		win.enqueue(Damage{When: time.Now()})
	case C.EClose:
		// May make a callback here
		win.Close()
	}
}

// This could be more sophisticated; some events are
// more important than others and should not be dropped
func (w Buffer) enqueue(e Event) {
	select {
	case w.event <- e:
	default:
	}
}

// A Buffer is an OpenGL canvas that can be displayed
// within an OS window. Buffers can receive user input,
// which can be accessed with the Subscribe() method.
type Buffer struct {
	ds    unsafe.Pointer
	Event <-chan Event
	event chan Event
	sync.Mutex
}

// Helper functions for pulling values from our C shim
func val(x C.RC) error {
	var err error
	if x.err != nil {
		err = errors.New(C.GoString(x.err))
		C.free(unsafe.Pointer(x.err))
	}
	return err
}

func valP(x C.RP) (unsafe.Pointer, error) {
	var err error
	if x.err != nil {
		err = errors.New(C.GoString(x.err))
		C.free(unsafe.Pointer(x.err))
	}
	return x.rp, err
}

func val2(x C.R2) (int, int, error) {
	var err error
	if x.err != nil {
		err = errors.New(C.GoString(x.err))
		C.free(unsafe.Pointer(x.err))
	}
	return int(x.X), int(x.Y), err
}

// Close() closes a window and releases any resources associated with it.
func (w *Buffer) Close() {
	if w == nil {
		return
	}
	if err := val(C.dsWinClose(w.ds)); err != nil {
		log.Print(err)
	}
	close(w.event)
}

// Title retrieves the current title of a window
func (w *Buffer) Title() string {
	if w == nil {
		return ""
	}
	w.Lock()
	defer w.Unlock()
	if s, err := valP(C.dsWinGetTitle(w.ds)); err != nil {
		return ""
	} else {
		return C.GoString((*C.char)(s))
	}
}

// SetTitle changes a window's title string to a new value. The maximum
// length of a window title is an unspecified value over 255 characters.
func (w *Buffer) SetTitle(title string) {
	if w == nil {
		return
	}
	w.Lock()
	defer w.Unlock()
	s := C.CString(title)
	if err := val(C.dsWinSetTitle(w.ds, s)); err != nil {
		log.Print(err)
	}
}

// Size returns the window's width and height in pixels
func (w *Buffer) Size() (width, height int) {
	var err error
	if w == nil {
		return -1, -1
	}
	width, height, err = val2(C.dsWinSize(w.ds))
	if err != nil {
		log.Print(err)
	}
	return width, height
}

// Resize changes the width and height of a window to the specified
// dimensions in pixels. Note that height and width are only suggestions;
// especially in fullscreen mode, window system or hardware restrictions
// may prevent the desired height and width from being set. The actual
// screen size may be retrieved with the Size() method.
func (w *Buffer) Resize(width, height int) error {
	return val(C.dsWinResize(
		w.ds,
		C.int(width),
		C.int(height)))
}

// Flip swaps the background buffer with the foregroud buffer.
// All drawing is done to the background buffer. The window's context
// must be set in the calling goroutine with TakeContext() before
// SwapBuffers, or any GL drawing functions, are called. By default,
// SwapBuffers will block until the screen is refreshed.
func (w *Buffer) Flip() {
	C.dsWinSwap(w.ds)
}

func buildArgv(cfg Config) ([]*C.char, error) {
	var argv []*C.char

	for key, val := range cfg {
		argv = append(argv, C.CString(key))
		argv = append(argv, C.CString(val))
	}

	argv = append(argv, nil)
	return argv, nil
}

func freeArgv(argv []*C.char) {
	for _, s := range argv {
		if s != nil {
			C.free(unsafe.Pointer(s))
		}
	}
}

// Open creates a new window.
func Open(c Config) (*Buffer, error) {
	var argv []*C.char
	var err error

	initialize.Do(func() {
		err = val(C.dsInit(0, nil))
	})
	if err != nil {
		return nil, err
	}

	buf := new(Buffer)
	buf.event = make(chan Event, 20)
	buf.Event = buf.event

	if argv, err = buildArgv(c); err != nil {
		return nil, err
	}

	buf.ds, err = valP(C.dsWinOpen(unsafe.Pointer(buf), C.int(len(argv)-1), &argv[0]))
	freeArgv(argv)
	if err != nil {
		return nil, err
	}
	return buf, nil
}

func (w *Buffer) CheckEvent() error {
	return val(C.dsWinCheckEvent(w.ds))
}

func (w *Buffer) WaitEvent() error {
	return val(C.dsWinWaitEvent(w.ds))
}
