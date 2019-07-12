#include "XWindowManager.h"
using namespce std;

XWindowManager::XWindowManager() {
    /* open the connection to the display "simey:0". */
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        fprintf(stderr, "Cannot connect to X server %s\n", "simey:0");
        exit(-1);
    }:
}

XWindowManager::~XWindowManager() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}