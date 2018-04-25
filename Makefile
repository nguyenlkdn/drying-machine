IDIR =-I/usr/local/include/modbus/
CC=gcc
#CFLAGS=$(IDIR) -pthread $(pkg-config --libs gtk+-3.0)

ODIR=./
LDIR =/usr/local/lib/

LIBS=-lm -lpthread `pkg-config --libs gtk+-3.0` -export-dynamic

_DEPS = config.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

CFLAGS=-g -Wall -Wextra `pkg-config --cflags gtk+-3.0`
LDFLAGS=`pkg-config --libs gtk+-3.0`

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm server

install:
	cp server /usr/local/bin
