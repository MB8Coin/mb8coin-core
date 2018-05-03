
Debian
====================
This directory contains files used to package mb8coind/mb8coin-qt
for Debian-based Linux systems. If you compile mb8coind/mb8coin-qt yourself, there are some useful files here.

## mb8coin: URI support ##


mb8coin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install mb8coin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your mb8coin-qt binary to `/usr/bin`
and the `../../share/pixmaps/mb8coin128.png` to `/usr/share/pixmaps`

mb8coin-qt.protocol (KDE)

