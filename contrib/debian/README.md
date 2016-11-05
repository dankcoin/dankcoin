
Debian
====================
This directory contains files used to package dankcoind/dankcoin-qt
for Debian-based Linux systems. If you compile dankcoind/dankcoin-qt yourself, there are some useful files here.

## dankcoin: URI support ##


dankcoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dankcoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dankcoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/dankcoin128.png` to `/usr/share/pixmaps`

dankcoin-qt.protocol (KDE)

