all: music

CXX = g++
CPPFLAGS = -g -Wall

music: RhythmGame.h RhythmGame.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

.phony: clean music

clean:
	rm -rf music