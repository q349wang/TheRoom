#ifndef X_WINDOW_MANAGER_H_
#define X_WINDOW_MANAGER_H_

#include <X11/Xlib.h> /* defines common Xlib functions and structs. */
#include <X11/Xutil.h>

#include "../HelperClasses/Observer.h"
#include <string>

class XWindowManager : public Observer
{
    /* this variable will contain the pointer to the Display structure */
    /* returned when opening a connection.                             */
    Display *d;
    Window w;
    int s;
    GC gc;

    unsigned long colours[10];

    const static int fontCol = 1;
    const static int mazeCol = 2;
    const static int mazeTileSize = 20;
    const static std::string font;

public:
    XWindowManager(int width = 500, int height = 500);
    ~XWindowManager();
    XWindowManager(const XWindowManager &) = delete;
    XWindowManager &operator=(const XWindowManager &) = delete;

    enum
    {
        White = 0,
        Black,
        Red,
        Green,
        Blue
    };

    void drawFillRect(int x, int y, int w, int h, int col);
    void drawRect(int x, int y, int w, int h, int col);
    void drawString(int x, int y, std::string msg);

    void drawMazeTile(int x, int y, int content);
    void drawEntityInfo(int x, int y /* Add entity info */);

    void notify() override;
};

#endif