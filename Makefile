all: myhttpd client
LIBS = -lpthread #-lsocket
# httpd: httpd.c
# 	gcc -g -W -Wall $(LIBS) -o $@ $<

myhttpd: myhttpd.c
	gcc -g -W -Wall $(LIBS) -o $@ $<

client: simpleclient.c
	gcc -W -Wall -o $@ $<
clean:
	rm myhttpd
