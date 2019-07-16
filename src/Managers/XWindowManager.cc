#include "XWindowManager.h"
#include "../HelperClasses/GameException.h"
#include "../ADTs/Entity/Entity.h"
#include "../ADTs/Entity/Player.h"
#include "../ADTs/Map/Tile.h"
#include "../ADTs/Map/Map.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

XWindowManager::~XWindowManager()
{
	XFreeGC(d, gc);
	XCloseDisplay(d);
}

const string XWindowManager::font = "-*-clean-*-*-*-*-*-*-100-100-*-*-*-*";

XWindowManager::XWindowManager(shared_ptr<Map> map, int width, int height) : gameMap{map}
{
	d = XOpenDisplay(NULL);
	if (d == NULL)
	{
		cerr << "Cannot open display" << endl;
		throw GameException{"Cannot open display"};
	}

	s = DefaultScreen(d);
	w = XCreateSimpleWindow(
		d, RootWindow(d, s), 10, 10, width, height,
		1, BlackPixel(d, s), WhitePixel(d, s));

	XSelectInput(d, w, ExposureMask | KeyPressMask);

	Pixmap pix = XCreatePixmap(
		d, w, width, height,
		DefaultDepth(d, DefaultScreen(d)));

	gc = XCreateGC(d, pix, 0, 0);

	// Set up font

	XFontStruct *font_info;
	font_info = XLoadQueryFont(d, font.c_str());
	if (!font_info)
	{
		cerr << "Could not find " << font << ". Using default font" << endl;
	}
	else
	{

		XSetFont(d, gc, font_info->fid);
	}

	// Set up colours.
	XColor xcolour;
	Colormap cmap;

	const size_t numColours = 5;
	char color_vals[numColours][10] = {
		"white", "black", "red",
		"green", "blue"};

	cmap = DefaultColormap(d, DefaultScreen(d));

	for (unsigned int i = 0; i < numColours; ++i)
	{
		XParseColor(d, cmap, color_vals[i], &xcolour);
		XAllocColor(d, cmap, &xcolour);
		colours[i] = xcolour.pixel;
	}

	XSetForeground(d, gc, colours[GameColours::Black]);

	// Make window non-resizeable.
	XSizeHints hints;
	hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
	hints.height = hints.base_height = hints.min_height = hints.max_height = height;
	hints.width = hints.base_width = hints.min_width = hints.max_width = width;
	XSetNormalHints(d, w, &hints);

	// map window and flush
	XMapRaised(d, w);
	XFlush(d);

	// wait 1 second for setup
	sleep(1);
}

// Fills in rectangle
void XWindowManager::drawFillRect(int x, int y, int width, int height, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

// Draws outline of a rectangle
void XWindowManager::drawRect(int x, int y, int width, int height, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XDrawRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

// Draws a string of text
void XWindowManager::drawString(int x, int y, string msg)
{
	XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
	XFlush(d);
}

// Draws a map tile
void XWindowManager::drawMapTile(int x, int y, int col)
{
	drawRect(x, y, mapTileSize, mapTileSize, col);
	drawFillRect(x, y, mapTileSize, mapTileSize, col);
	XSetForeground(d, gc, colours[fontCol]);
}

// Draws a nameplate displaying entity info
void XWindowManager::drawEntityInfo(int x, int y, const shared_ptr<Entity> &entity)
{
	drawRect(x, y, mapTileSize, mapTileSize, col);
	drawFillRect(x, y, mapTileSize, mapTileSize, col);
	XSetForeground(d, gc, colours[fontCol]);
}

// Draws info box regarding ability cooldown
void XWindowManager::drawAbilityCD(const shared_ptr<Player> &p)
{
	bool abilityReady = p->getCooldown() == 0;
	drawRect(x, y, mapTileSize, mapTileSize, col);
	drawFillRect(x, y, mapTileSize, mapTileSize, col);
	string cd = "Ability: " + abilityReady
					? "READY!"
					: p->getCooldown() + " turns until ready...";
	XSetForeground(d, gc, colours[fontCol]);
	drawString(x, y, cd);
}

// Redraws battle scene
void XWindowManager::redrawBattle()
{
	XClearWindow(d, w);
	if (auto mp = gameMap.lock())
	{
	}
}

// Draws all the map tiles
void XWindowManager::drawMapStruct(const vector<vector<shared_ptr<Tile>>> &mapArr)
{
	for (int row = 0; row < mapArr.size(); row++)
	{
		for (int col = 0; col < mapArr[row].size(); col++)
		{
			drawMapTile(col * mapTileSize, row * mapTileSize, mapArr[row][col]->getColour());
		}
	}
}

// Redraws map scene
void XWindowManager::redrawMap()
{
	XClearWindow(d, w);
	if (auto mp = gameMap.lock())
	{
	}
}

// Redraws correct scene based on current game state
void XWindowManager::notify()
{

	return;
}
