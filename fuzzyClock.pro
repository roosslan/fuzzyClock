RC_ICONS = IDI_ICON1.ico
# work-around for QTBUG-13496
CONFIG += no_batch \
          precompile_header

QT += \
    core gui \
    widgets

LIBS += \
        -lwtsapi32 \
        -luser32

# PRECOMPILED_HEADER = stable.h

#INCLUDEPATH += \
#        rxqt\include \
#        rxqt\rxcpp

HEADERS += \
        fuzzyHelper.h \
        fuzzyClockWindow.h \
        fuzzyClock.h


SOURCES += \
        fuzzyHelper.cpp \
        fuzzyClockWindow.cpp \
	fuzzyClock.cpp \
        main.cpp

DISTFILES += \
        style.css

