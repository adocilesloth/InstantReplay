#-#-#MODIFY THESE TO MATCH YOUR SYSTEM AND INSTALLATION#-#-#
ifndef OBS_INCLUDE
OBS_INCLUDE = /usr/include/obs
endif
ifndef OBS_API_INCLUDE
OBS_API_INCLUDE = ./obs-frontend-api
endif
ifndef OBS_LIB
OBS_LIB = /usr/lib
endif
ifndef OBS_SHARE
OBS_SHARE = /usr/share/obs
endif
ifndef QT_INCLUDE
QT_INCLUDE = $(HOME)/Qt/5.9.1/gcc_64/include
endif
ifndef QT_LIB
QT_LIB = $(HOME)/Qt/5.9.1/gcc_64/lib
endif
#-#-#END MODIFY#-#-#

CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -fPIC -DQT_NO_VERSION_TAGGING

INCLUDE = -I$(OBS_INCLUDE) -I$(OBS_API_INCLUDE) -I$(QT_INCLUDE)
LDFLAGS = -L$(OBS_LIB) -L$(QT_LIB)
LDLIBS_LIB   = -lobs -lQt5Widgets -lQt5Gui -lQt5Core

LIB = InstantReplay.so
LIB_OBJ = module-entrance.o InstantReplay.o InstantReplay_callout.o ui_InstantReplay_callout.o audio_io_state.o
SRC = module-entrance.cpp InstantReplay.cpp InstantReplay_callout.cpp moc_InstantReplay_callout.cpp audio_io_state.cpp

all: $(LIB)

#$(LIB): module-entrance.o InstantReplay.o InstantReplay_callout.o ui_InstantReplay_callout.o#$(LIB_OBJ)
$(LIB): $(LIB_OBJ)
	$(CXX) -shared $(LDFLAGS) $(LDLIBS_LIB) -o $@ $^

module-entrance.o: module-entrance.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

InstantReplay.o: InstantReplay.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

InstantReplay_callout.o: InstantReplay_callout.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

ui_InstantReplay_callout.o: moc_InstantReplay_callout.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

audio_io_state.o: audio_io_state.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<


.PHONY: install
install:
	cp -f $(LIB) $(OBS_LIB)/obs-plugins/
	mkdir -p /usr/share/obs/obs-plugins/InstantReplay
	mkdir -p /usr/share/obs/obs-plugins/InstantReplay/locale
	cp -f en-US.ini /usr/share/obs/obs-plugins/InstantReplay/locale/

.PHONY: clean
clean:
	rm ./$(LIB_OBJ)
	rm ./$(LIB)

.PHONY: uninstall
uninstall:
	rm $(OBS_LIB)/obs-plugins/$(LIB)
	rm -r /usr/share/obs/obs-plugins/InstantReplay
