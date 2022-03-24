INCLUDEPATH += $$PWD

HEADERS += $$PWD/videocaptureworker.h \
			$$PWD/mat2qtformatmethod.h

SOURCES += $$PWD/videocaptureworker.cpp \
			$$PWD/mat2qtformatmethod.cpp


INCLUDEPATH += $$PWD/../../libs/videoWrite/FFmpeg/include
INCLUDEPATH += $$PWD/../../libs/videoWrite

LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lavcodec
LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lavdevice
LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lavfilter
LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lavformat
LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lavutil
LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lpostproc
LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lswresample
LIBS += -L$$PWD/../../libs/videoWrite/FFmpeg/lib -lswscale
LIBS += -L$$PWD/../../libs/videoWrite -lmatch2
