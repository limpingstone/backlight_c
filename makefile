all: 
	gcc src/backlight.c -o backlight_c

clean: 
	rm -rf backlight_c 

install: 
	cp backlight_c /usr/local/bin
	chmod u+s /usr/local/bin/backlight_c 
