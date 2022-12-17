INCLUDEPATH += $$PWD

QT += sql

HEADERS +=  $$PWD/datamanager.h \
    $$PWD/Student.h \
    $$PWD/datamanagerdb.h \
    $$PWD/mysortfilterproxymodel.h \
    $$PWD/schoollisttablemodel.h \
    $$PWD/scoremanagemodel.h \
    $$PWD/localstudenttablemodel.h \
    $$PWD/scoremanagerform.h \
    $$PWD/initdb.h

			

SOURCES +=  $$PWD/datamanager.cpp \
            $$PWD/datamanagerdb.cpp \
            $$PWD/mysortfilterproxymodel.cpp \
            $$PWD/schoollisttablemodel.cpp \
            $$PWD/scoremanagemodel.cpp \
            $$PWD/scoremanagerform.cpp \
            $$PWD/localstudenttablemodel.cpp

FORMS += $$PWD/scoremanagerform.ui
