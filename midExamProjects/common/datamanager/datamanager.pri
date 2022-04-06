INCLUDEPATH += $$PWD

QT += sql

HEADERS +=  $$PWD/datamanager.h \
    $$PWD/Student.h \
    $$PWD/datamanagerdb.h \
			$$PWD/schoollisttablemodel.h \
			$$PWD/scoremanagemodel.h \
                        $$PWD/localstudenttablemodel.h \
                        $$PWD/initdb.h

			

SOURCES +=  $$PWD/datamanager.cpp \
			$$PWD/datamanagerdb.cpp \
			$$PWD/schoollisttablemodel.cpp \
			$$PWD/scoremanagemodel.cpp \
			$$PWD/localstudenttablemodel.cpp


