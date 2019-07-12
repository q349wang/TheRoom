#include <X11/Xlib.h> /* defines common Xlib functions and structs. */

class XWindowManager {
    /* this variable will contain the pointer to the Display structure */
    /* returned when opening a connection.                             */
    Display* d;

   public:
    XWindowManager();
    ~XWindowManager();
}