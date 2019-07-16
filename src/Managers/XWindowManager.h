#ifndef X_WINDOW_MANAGER_H_
#define X_WINDOW_MANAGER_H_

#include <X11/Xlib.h> /* defines common Xlib functions and structs. */
#include <X11/Xutil.h>

#include "../HelperClasses/Observer.h"
#include "../HelperClasses/GameConstants.h"
#include <string>
#include <vector>
#include <memory>

class Tile;
class Entity;
class Player;
class Map;

class XWindowManager : public Observer
{
    /* this variable will contain the pointer to the Display structure */
    /* returned when opening a connection.                             */
    Display *d;
    Window w;
    int s;
    GC gc;
    std::weak_ptr<Map> gameMap;
    unsigned long colours[10];

    static const int fontCol = GameColours::Black;
    static const int mapBorderColour = GameColours::White;
    static const int mapTileSize = 20;
    static const int namePlateBorderColour = GameColours::Black;
    static const int namePlateColour = GameColours::White;
    static const std::string font;

public:
    XWindowManager(std::shared_ptr<Map> gameMap, int width = 500, int height = 500);
    ~XWindowManager();
    XWindowManager(const XWindowManager &) = delete;
    XWindowManager &operator=(const XWindowManager &) = delete;

    void drawFillRect(int x, int y, int w, int h, int col);
    void drawRect(int x, int y, int w, int h, int col);
    void drawString(int x, int y, std::string msg);

    void drawMapTile(int x, int y, int content);
    void drawMapStruct(const std::vector<std::vector<std::shared_ptr<Tile>>>&);
    void drawEntityInfo(int x, int y, const std::shared_ptr<Entity>&);
    void drawAbilityCD(const std::shared_ptr<Player>&);

    void redrawMap();
    void redrawBattle();
    void notify() override;
};

#endif