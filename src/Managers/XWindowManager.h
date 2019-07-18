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
    GameManager *gameManager;

    int width;
    int height;

    unsigned long colours[10];

    static const int fontCol = GameColours::Black;
    static const int mapBorderColour = GameColours::White;
    static const int mapTileSize = 50;
    static const int namePlateBorderColour = GameColours::Black;
    static const int namePlateColour = GameColours::White;

    static const int entityDiameter = 25;
    static const std::string font;

    int centerX(int x);
    int centerY(int y);

public:
    XWindowManager(GameManager *gameManager,
                   std::shared_ptr<Map> gameMap,
                   int width = 500,
                   int height = 500);
    ~XWindowManager();
    XWindowManager(const XWindowManager &) = delete;
    XWindowManager &operator=(const XWindowManager &) = delete;

    void drawFillRect(int x, int y, int w, int h, int col);
    void drawRect(int x, int y, int w, int h, int col);

    void drawFillCirc(int x, int y, int w, int h, int col);
    void drawCirc(int x, int y, int w, int h, int col);

    void drawString(int x, int y, std::string msg);

    void drawMapTile(int x, int y, int content);
    void drawMapStruct(const std::shared_ptr<Entity> &, const std::vector<std::vector<std::shared_ptr<Tile>>> &);
    void drawEntityInfo(int x, int y, const std::shared_ptr<Entity> &);
    void drawAbilityCD(const std::shared_ptr<Player> &);

    void drawEntityOnMap(const std::shared_ptr<Entity> &);

    void redrawMap();
    void redrawBattle();
    void notify(std::string) override;
};

#endif