CC = g++
CFLAGS = -Wall -std=c++11 -O3 -Iinclude

SRCDIR = src
INCDIR = include
OBJDIR = obj
BUILDDIR = build

SOURCES = $(SRCDIR)/ppm.cpp \
          $(SRCDIR)/raycast.cpp \
          $(SRCDIR)/renderer.cpp \
          $(SRCDIR)/scene.cpp \
          $(SRCDIR)/v3math.c

OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
OBJECTS := $(OBJECTS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

TARGET = $(BUILDDIR)/raycast

all: $(OBJDIR) $(BUILDDIR) $(TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BUILDDIR):
	mkdir -p $(BUILDDIR)


$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BUILDDIR)