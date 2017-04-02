#!/bin/sh

glib-compile-resources mirage.gresource.xml

cp ../protocols/generated/* .

gcc -o maynard \
       maynard.c \
       shell-helper.c \
       shell-helper-protocol.c \
       panel.c \
       weston-desktop-shell-protocol.c \
       $(pkg-config --cflags --libs libweston-1 gtk+-3.0 wayland-client wayland-server pixman-1 libweston-1 wayland-server) -lm

gcc -fPIC -shared shell-helper.c shell-helper-protocol.c -o shell-helper $(pkg-config --libs --cflags pixman-1 libweston-2 wayland-server)
