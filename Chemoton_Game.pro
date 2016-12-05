TEMPLATE = app
#CONFIG += console
CONFIG -= qt
CONFIG += c++11
CONFIG += static

#DEFINES += GLEW_STATIC
DEFINES += SFML_STATIC
DEFINES += UNICODE


SOURCES += main.cpp \
    mvc/rgapplication.cpp \
    mvc/controller.cpp \
    chemoton/rk4engine.cpp \
    chemoton/reakcionbase.cpp \
    chemoton/polimerization.cpp \
    chemoton/membranegrowthreaction.cpp \
    chemoton/fixedratereaction.cpp \
    chemoton/concdependentreaction.cpp \
    chemoton/chemotonbf.cpp \
    display/plot.cpp \
    display/datashowbase.cpp \
    display/curve.cpp \
    gui/interfaces/sizeable.cpp \
    gui/interfaces/guibase.cpp \
    gui/textbutton.cpp \
    gui/layer.cpp \
    gui/label.cpp \
    gui/guimanager.cpp \
    observer/eventdispatcher.cpp \
    observer/event.cpp \
    gui/interfaces/clickable.cpp \
    gui/toggletextbutton.cpp \
    chemoton/rungekuttaengine.cpp \
    gui/knob.cpp

INCLUDEPATH += D:\CPPLibraries\SFML-master\SFML-master\include

DEPENDPATH += D:\CPPLibraries\SFML-master\SFML-master\include

LIBS += -LD:\CPPLibraries\SFML-master\SFML-master\extlibs\libs-mingw\x86

LIBS += -LD:\CPPLibraries\SFML-master\SFML-master-static-build\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio-s -lsfml-graphics-s -lsfml-network-s -lsfml-main -lsfml-window-s -lsfml-system-s

CONFIG(debug, debug|release): LIBS += -lsfml-audio-s-d -lsfml-graphics-s-d -lsfml-network-s-d -lsfml-main-d -lsfml-window-s-d -lsfml-system-s-d

#CONFIG(release, debug|release): LIBS += -lsfml-audio-2 -lsfml-graphics-2 -lsfml-network-2 -lsfml-window-2 -lsfml-system-2

#CONFIG(debug, debug|release): LIBS += -lsfml-audio-d-2 -lsfml-graphics-d-2 -lsfml-network-d-2 -lsfml-window-d-2 -lsfml-system-d-2

LIBS += -lwinmm -lgdi32 -lws2_32 -lglew -lopengl32 -lfreetype -ljpeg -lopenal32 -lsndfile


HEADERS += \
    mvc/rgapplication.h \
    mvc/controller.h \
    chemoton/rk4engine.h \
    chemoton/reakcionbase.h \
    chemoton/polimerization.h \
    chemoton/membranegrowthreaction.h \
    chemoton/fixedratereaction.h \
    chemoton/concdependentreaction.h \
    chemoton/chemotonbf.h \
    display/plot.h \
    display/datashowbase.h \
    display/curve.h \
    gui/interfaces/sizeable.h \
    gui/interfaces/guibase.h \
    gui/textbutton.h \
    gui/layer.h \
    gui/label.h \
    gui/guimanager.h \
    observer/eventdispatcher.h \
    observer/event.h \
    gui/interfaces/clickable.h \
    gui/toggletextbutton.h \
    chemoton/rungekuttaengine.h \
    gui/knob.h \
    chemoton/diffusion_simulator.h

