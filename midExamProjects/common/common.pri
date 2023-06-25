include($$PWD/networkServer/networkserver.pri)
include($$PWD/camera/camera.pri)
include($$PWD/log/log.pri)
include($$PWD/videocapture/videocapture.pri)
include($$PWD/config/appconfig.pri)
include($$PWD/datamanager/datamanager.pri)
include($$PWD/videoreplay/videoreplay.pri)
include($$PWD/settingdialog/settingdialog.pri)
include($$PWD/utils/utils.pri)
include($$PWD/login/login.pri)
include($$PWD/license/license.pri)
#include($$PWD/xlsx/qtxlsx.pri)
#include($$PWD/testcase/testcase.pri)

# include log4qt lib
LIBS += -L$$PWD/../libs/log/ -llog4qt

win32:CONFIG(release, debug|release): LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world3410
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world3410d
else:unix: LIBS += -LD:/opencv/build/x64/vc15/lib/ -lopencv_world3410

INCLUDEPATH += D:/opencv/build/include
DEPENDPATH += D:/opencv/build/include

