#include "XWindowManager.h"
#include "../HelperClasses/GameException.h"
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

XWindowManager::XWindowManager(int width, int height)
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
	else {

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

	XSetForeground(d, gc, colours[Black]);

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
void XWindowManager::drawFillRect(int x, int y, int width, int height, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XFillRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

void XWindowManager::drawRect(int x, int y, int width, int height, int colour)
{
	XSetForeground(d, gc, colours[colour]);
	XDrawRectangle(d, w, gc, x, y, width, height);
	XFlush(d);
}

void XWindowManager::drawString(int x, int y, string msg)
{
	XDrawString(d, w, DefaultGC(d, s), x, y, msg.c_str(), msg.length());
	XFlush(d);
}

void XWindowManager::drawMazeTile(int x, int y, int content)
{
	drawRect(x, y, mazeTileSize, mazeTileSize, mazeCol);
	drawFillRect(x, y, mazeTileSize, mazeTileSize, mazeCol);
	XSetForeground(d, gc, colours[fontCol]);
	drawString(x, y + 10, to_string(content)); // Fix this
}
void XWindowManager::drawEntityInfo(int x, int y /* Add entity info */)
{
	XSetForeground(d, gc, colours[fontCol]);
}

void XWindowManager::notify()
{
	return;
}
