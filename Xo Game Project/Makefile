CC=gcc
CFLAGS=-D.
DEPS = xogame.h 
DESTDIR1 ?=/usr/bin
DESTDIR2 ?=/usr/share
PREFIX ?= 
COPY_FILES = code/xml/schema/schema.xsd config.txt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

xogame: xogame.c engine.c
	$(CC) -DGUI -rdynamic `pkg-config --cflags gtk+-3.0` -o xogame xogame.c engine.c `pkg-config --libs gtk+-3.0`


install: xogame
	install -m 0755 -d $(DESTDIR1)$(PREFIX)
	install -m 0755 xogame $(DESTDIR1)$(PREFIX)
	mkdir $(DESTDIR2)$(PREFIX)/XOGame
	cp -R resources $(DESTDIR2)$(PREFIX)/XOGame
	install -m 0755 -d $(DESTDIR2)$(PREFIX)/XOGame
	install -m 0755 xogame.glade $(DESTDIR2)$(PREFIX)/XOGame
	cp xogame.desktop $(DESTDIR2)$(PREFIX)/applications