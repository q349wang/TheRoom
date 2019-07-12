#include <X11/Xlib.h> /* defines common Xlib functions and structs. */
#include <X11/Xutil.h>
class XWindowManager {
    /* this variable will contain the pointer to the Display structure */
    /* returned when opening a connection.                             */
    Display* d;
    Window w;
    int s;
    GC gc;

    unsigned long colours[10];

   public:
    XWindowManager(int width = 500, int height = 500);
    ~XWindowManager();
    XWindowManager(const XWindowManager&) = delete;
    XWindowManager& operator=(const XWindowManager&) = delete;

    enum {White=0, Black, Red, Green, Blue};

    void drawFillRect(int x, int y, int w, int h, int col);
    void drawString(int x, int y, std::string msg);
};