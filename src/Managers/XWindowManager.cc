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

XWindowManager::XWindowManager(shared_ptr<Map> map, int width, int height)
	: gameMap{map},
	  width{width},
	  height{height}
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

	const size_t numColours = 9;
	char color_vals[numColours][10] = {
		"white", "black", "red", "orangered",
		"green", "blue", "darkgreen", "purple",
		"yellow"};

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

// Fills in circle
void XWindowManager::drawFillCirc(int x, int y, int width, int height, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XFillArc(d, w, gc, x, y, width, height, 0, 360 * 64);
	XFlush(d);
}

// Draws outline of a circle
void XWindowManager::drawCirc(int x, int y, int width, int height, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XDrawArc(d, w, gc, x, y, width, height, 0, 360 * 64);
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
	drawFillRect(x, y, mapTileSize, mapTileSize, col);
	drawRect(x, y, mapTileSize, mapTileSize, mapBorderColour);
	XSetForeground(d, gc, colours[fontCol]);
}

// Draws a nameplate displaying entity info
void XWindowManager::drawEntityInfo(int x, int y, const shared_ptr<Entity> &entity)
{
	drawRect(x, y, mapTileSize, mapTileSize, namePlateBorderColour);
	drawFillRect(x, y, mapTileSize, mapTileSize, namePlateColour);
	XSetForeground(d, gc, colours[fontCol]);
	drawString(x, y, entity->getName());
	string health = "H: " + to_string(entity->getHealth());
	drawString(x, y, health);
	string energy = "E: " + to_string(entity->getEnergy());
	drawString(x, y, energy);
	string armor = "A: " + to_string(entity->getArmour());
	drawString(x, y, armor);
}

// Draws info box regarding ability cooldown
void XWindowManager::drawAbilityCD(const shared_ptr<Player> &p)
{
	int cdX = 10;
	int cdY = 10;
	bool abilityReady = p->getCooldown() == 0;
	drawRect(cdX, cdY, mapTileSize, mapTileSize, namePlateBorderColour);
	drawFillRect(cdY, cdX, mapTileSize, mapTileSize, namePlateColour);
	string cd = "Ability: " + abilityReady
					? "READY!"
					: p->getCooldown() + " turns until ready...";
	XSetForeground(d, gc, colours[fontCol]);
	drawString(cdX, cdY, cd);
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
void XWindowManager::drawMapStruct(const shared_ptr<Entity> &p,
								   const vector<vector<shared_ptr<Tile>>> &mapArr)
{
	pair<int, int> coords = p->getPosition();
	int xOffset = coords.first;
	int yOffset = coords.second;
	for (unsigned int row = 0; row < mapArr.size(); row++)
	{
		for (unsigned int col = 0; col < mapArr[row].size(); col++)
		{
			drawMapTile(centerX((col - xOffset) * mapTileSize),
						centerY((row - yOffset) * mapTileSize),
						mapArr[row][col]->getColour());
		}
	}
}

// Redraws map scene
void XWindowManager::redrawMap()
{
	XClearWindow(d, w);
	if (auto mp = gameMap.lock())
	{
		drawMapStruct(mp->getPlayer(), mp->getMap());
		drawEntityOnMap(mp->getPlayer());
	}
}

// Redraws correct scene based on current game state
void XWindowManager::notify()
{

	return;
}

void XWindowManager::drawEntityOnMap(const shared_ptr<Entity> &p)
{
	drawFillCirc(centerX(0) + mapTileSize / 2 - entityDiameter / 2,
				 centerY(0) + mapTileSize / 2 - entityDiameter / 2,
				 entityDiameter, entityDiameter, p->getColour());
}

int XWindowManager::centerX(int x)
{
	return x + width / 2 - entityDiameter / 2;
}

int XWindowManager::centerY(int y)
{
	return y + height / 2 - entityDiameter / 2;
}
