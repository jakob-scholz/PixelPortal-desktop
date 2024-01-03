PixelPortalDesktop: Globals.o Level.o PixelPortal.o Player.o Portal.o Wall.o 
	g++ $(OBJS) -o PixelPortalDesktop $(LDFLAGS)
	./PixelPortalDesktop

$(OBJS): $(SRCS) 
	g++ -c $<


# Release builds:
release: Globals.o Level.o PixelPortal.o Player.o Portal.o Wall.o
	g++ $(OFLAGS) $(OBJS) -o PixelPortalDesktop $(LDFLAGS)


windows: Globals.o Level.o PixelPortal.o Player.o Portal.o Wall.o
	g++ $(OFLAGS) $(OBJS) -o PixelPortalDesktop.exe $(LDFLAGS)

OBJS = Globals.o Level.o PixelPortal.o Player.o Portal.o Wall.o
OOBJS = Globals.oo Level.oo PixelPortal.oo Player.oo Portal.oo Wall.oo
SRCS = Globals.cpp Level.cpp PixelPortal.cpp Player.cpp Portal.cpp Wall.cpp
CXXFLAGS = 
LDFLAGS = -lsfml-system -lsfml-graphics -lsfml-window 
OFLAGS = -O2 -s
JFLAGS = -L
.PHONY: clean release optimizedStage0 windows run

clean:
	@rm ./*.o
	@rm ./PixelPortalDesktop

run: PixelPortalDesktop
	./PixelPortalDesktop
