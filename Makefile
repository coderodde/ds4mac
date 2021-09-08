all: DirectoryTagEntry.cpp DirectoryTagEntryList.cpp main.cpp
	g++ -std=c++17 -Wall -Werror -pedantic -o ds_engine DirectoryTagEntry.cpp DirectoryTagEntryList.cpp main.cpp

install:
	sh installer.sh

all: ds_engine

SOURCES = DirectoryTagEntry.cpp DirectoryTagEntryList.cpp main.cpp
HEADERS = DirectoryTagEntry.h DirectoryTagEntryList.h

ds_engine: $(SOURCES) $(HEADERS)
	g++ -std=c++17 -Wall -Werror -pedantic -o $@ $(SOURCES)