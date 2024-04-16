RC_ICONS = IDI_ICON1.ico
# work-around for QTBUG-13496
CONFIG += no_batch

QT += core gui \
    widgets

LIBS += -lwtsapi32
LIBS += -luser32


HEADERS += \
    fuzzyClockWindow.h \
	fuzzyClock.h

SOURCES += \
    fuzzyClockWindow.cpp \
	fuzzyClock.cpp \
    main.cpp

DISTFILES += \
    style.css

