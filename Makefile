TARGET = cmdserver
SOURCES = main.c shell.c subroutines.c
HEADERS = shell.h subroutines.h

all: $(TARGET)
.PHONY: all

$(TARGET): $(HEADERS) $(SOURCES)
	cc -o $(TARGET) $(SOURCES) -g3 -lreadline

clean:
	rm -f $(TARGET)
.PHONY: clean