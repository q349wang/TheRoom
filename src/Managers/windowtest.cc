#include "XWindowManager.h"
#include <unistd.h>

int main() {
    XWindowManager win;
    win.drawMazeTile(30, 30, 10);

    sleep(1000);
}