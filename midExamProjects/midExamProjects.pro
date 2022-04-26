TEMPLATE = subdirs

INCLUDEPATH += $$PWD/libs/zmq/libzmq/include
DEPENDPATH += $$PWD/libs/zmq/libzmq/include

SUBDIRS += midExamFootBall \
          midExamYwqz \
          midExamYtxs \
          midExamPaiQiu \
          midExamTiaoSheng \
          midExamBasketball \
          machineCodeProducer \
          licenseGenerator \
          skipRopeServer


#SUBDIRS += midExamTiaoSheng \
#        midExamYwqz \
#        midExamYtxs \
#        midExamPaiQiu \
#        midExamFootBall
# SUBDIRS += $$PWD/midExamTiaoSheng/midExamTiaoSheng.pro
# SUBDIRS += $$PWD/midExamYwqz/midExamYwqz.pro
# SUBDIRS += $$PWD/midExamYtxs/midExamYtxs.pro
# SUBDIRS += $$PWD/midExamPaiQiu/midExamPaiQiu.pro
# SUBDIRS += $$PWD/midExamFootBall/midExamFootBall.pro

EXAMPLE_PATH += $$PWD/common/
