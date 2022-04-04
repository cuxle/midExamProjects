#-------------------------------------------------
#
# Project created by QtCreator 2021-09-22T17:33:59
#
#-------------------------------------------------

QT       += core gui multimedia network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = midExamFootBall
TEMPLATE = app

SHARED_PATH = ../common

include($$SHARED_PATH/common.pri)
#include(./libs/xlsx/qtxlsx.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += FOOTBALL
#DEFINES += TIAOSHENG

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    #algorithm/algorithmloadbase.cpp \
    #algorithm/volleyballinterface.cpp \
    #algorithm/volleyballworker.cpp \
    footballregin.cpp \
    lidar/godleilaser.cpp \
    lidar/godleilaserdifop.cpp \
    lidar/godleilasermsop.cpp \
    lidar/lidarAnalysis.cpp \
    lidarcloudwidget.cpp \
    qcustomplot.cpp \
    #    main.cpp \
    formfuncchoose.cpp \
    #socket/client.cpp \
    videowidget.cpp

HEADERS += \
    #algorithm/algorithmloadbase.h \
    #algorithm/volleyballinterface.h \
    #algorithm/volleyballworker.h \
    footballregin.h \
    lidar/godleilaser.h \
    lidar/godleilaserdifop.h \
    lidar/godleilasermsop.h \
    lidar/lidarAnalysis.h \
    lidarcloudwidget.h \
    qcustomplot.h \
    formfuncchoose.h \
    #socket/client.h \
    videowidget.h

FORMS += \
    formfuncchoose.ui

RESOURCES += \
    res.qrc

INCLUDEPATH += D:\ProgramData\PCL1.12.1\include\pcl-1.12
INCLUDEPATH += D:\ProgramData\PCL1.12.1\include\pcl-1.12\pcl
INCLUDEPATH += D:\ProgramData\PCL1.12.1\3rdParty\Boost\include\boost-1_78
INCLUDEPATH += D:\ProgramData\PCL1.12.1\3rdParty\Eigen\eigen3
INCLUDEPATH += D:\ProgramData\PCL1.12.1\3rdParty\FLANN\include
INCLUDEPATH += D:\ProgramData\PCL1.12.1\3rdParty\FLANN\include\flann
INCLUDEPATH += D:\ProgramData\PCL1.12.1\3rdParty\OpenNI2\Include
INCLUDEPATH += D:\ProgramData\PCL1.12.1\3rdParty\Qhull\include


CONFIG(debug,debug|release){
    LIBS += -LD:\ProgramData\PCL1.12.1\lib\
    #        -lpcl_apps_debug\
            -lpcl_common_debug\
            -lpcl_features_debug\
            -lpcl_filters_debug\
            -lpcl_io_debug\
            -lpcl_io_ply_debug\
            -lpcl_kdtree_debug\
            -lpcl_keypoints_debug\
            -lpcl_ml_debug\
            -lpcl_octree_debug\
            -lpcl_outofcore_debug\
            -lpcl_people_debug\
            -lpcl_recognition_debug\
            -lpcl_registration_debug\
            -lpcl_sample_consensus_debug\
            -lpcl_search_debug\
            -lpcl_segmentation_debug\
    #        -lpcl_simulation_debug\
            -lpcl_stereo_debug\
            -lpcl_surface_debug\
            -lpcl_tracking_debug\
            -lpcl_visualization_debug

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\Boost\lib\
            -llibboost_atomic-vc142-mt-x64-gd-x64-1_78\
            -llibboost_chrono-vc142-mt-x64-gd-x64-1_78\
            -llibboost_container-vc142-mt-x64-gd-x64-1_78\
            -llibboost_context-vc142-mt-x64-gd-x64-1_78\
            -llibboost_coroutine-vc142-mt-x64-gd-x64-1_78\
            -llibboost_date_time-vc142-mt-x64-gd-x64-1_78\
            -llibboost_exception-vc142-mt-x64-gd-x64-1_78\
            -llibboost_filesystem-vc142-mt-x64-gd-x64-1_78\
            -llibboost_graph-vc142-mt-x64-gd-x64-1_78\
            -llibboost_iostreams-vc142-mt-x64-gd-x64-1_78\
            -llibboost_locale-vc142-mt-x64-gd-x64-1_78\
            -llibboost_log-vc142-mt-x64-gd-x64-1_78\
            -llibboost_log_setup-vc142-mt-x64-gd-x64-1_78\
            -llibboost_math_c99-vc142-mt-x64-gd-x64-1_78\
            -llibboost_math_c99f-vc142-mt-x64-gd-x64-1_78\
            -llibboost_math_c99l-vc142-mt-x64-gd-x64-1_78\
            -llibboost_math_tr1-vc142-mt-x64-gd-x64-1_78\
            -llibboost_math_tr1f-vc142-mt-x64-gd-x64-1_78\
            -llibboost_math_tr1l-vc142-mt-x64-gd-x64-1_78\
            -llibboost_mpi-vc142-mt-x64-gd-x64-1_78\
            -llibboost_prg_exec_monitor-vc142-mt-x64-gd-x64-1_78\
            -llibboost_program_options-vc142-mt-x64-gd-x64-1_78\
            -llibboost_random-vc142-mt-x64-gd-x64-1_78\
            -llibboost_regex-vc142-mt-x64-gd-x64-1_78\
            -llibboost_serialization-vc142-mt-x64-gd-x64-1_78\
            -llibboost_signals-vc142-mt-x64-gd-x64-1_78\
            -llibboost_system-vc142-mt-x64-gd-x64-1_78\
            -llibboost_test_exec_monitor-vc142-mt-x64-gd-x64-1_78\
            -llibboost_thread-vc142-mt-x64-gd-x64-1_78\
            -llibboost_timer-vc142-mt-x64-gd-x64-1_78\
            -llibboost_unit_test_framework-vc142-mt-x64-gd-x64-1_78\
            -llibboost_wave-vc142-mt-x64-gd-x64-1_78\
            -llibboost_wserialization-vc142-mt-x64-gd-x64-1_78

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\FLANN\lib\
            -lflann-gd\
            -lflann_cpp_s-gd\
            -lflann_s-gd

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\OpenNI2\Lib\
            -lOpenNI2

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\Qhull\lib\
     #       -lqhull-gd\
            -lqhullcpp-gd\
            -lqhullstatic-gd\
            -lqhullstatic_r-gd\
            -lqhull_p-gd\
            -lqhull_r-gd

} else {
    LIBS += -LD:\ProgramData\PCL1.12.1\lib\
    #        -lpcl_apps\
            -lpcl_common\
            -lpcl_features\
            -lpcl_filters\
            -lpcl_io\
            -lpcl_io_ply\
            -lpcl_kdtree\
            -lpcl_keypoints\
            -lpcl_ml\
            -lpcl_octree\
            -lpcl_outofcore\
            -lpcl_people\
            -lpcl_recognition\
            -lpcl_registration\
            -lpcl_sample_consensus\
            -lpcl_search\
            -lpcl_segmentation\
    #        -lpcl_simulation\
            -lpcl_stereo\
            -lpcl_surface\
            -lpcl_tracking\
            -lpcl_visualization

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\Boost\lib\
            -llibboost_atomic-vc142-mt-x64-1_78\
            -llibboost_chrono-vc142-mt-x64-1_78\
            -llibboost_container-vc142-mt-x64-1_78\
            -llibboost_context-vc142-mt-x64-1_78\
            -llibboost_coroutine-vc142-mt-x64-1_78\
            -llibboost_date_time-vc142-mt-x64-1_78\
            -llibboost_exception-vc142-mt-x64-1_78\
            -llibboost_filesystem-vc142-mt-x64-1_78\
            -llibboost_graph-vc142-mt-x64-1_78\
            -llibboost_iostreams-vc142-mt-x64-1_78\
            -llibboost_locale-vc142-mt-x64-1_78\
            -llibboost_log-vc142-mt-x64-1_78\
            -llibboost_log_setup-vc142-mt-x64-1_78\
            -llibboost_math_c99-vc142-mt-x64-1_78\
            -llibboost_math_c99f-vc142-mt-x64-1_78\
            -llibboost_math_c99l-vc142-mt-x64-1_78\
            -llibboost_math_tr1-vc142-mt-x64-1_78\
            -llibboost_math_tr1f-vc142-mt-x64-1_78\
            -llibboost_math_tr1l-vc142-mt-x64-1_78\
            -llibboost_mpi-vc142-mt-x64-1_78\
            -llibboost_prg_exec_monitor-vc142-mt-x64-1_78\
            -llibboost_program_options-vc142-mt-x64-1_78\
            -llibboost_random-vc142-mt-x64-1_78\
            -llibboost_regex-vc142-mt-x64-1_78\
            -llibboost_serialization-vc142-mt-x64-1_78\
            #-llibboost_signals-vc142-mt-x64-1_78\
            -llibboost_system-vc142-mt-x64-1_78\
            -llibboost_test_exec_monitor-vc142-mt-x64-1_78\
            -llibboost_thread-vc142-mt-x64-1_78\
            -llibboost_timer-vc142-mt-x64-1_78\
            -llibboost_unit_test_framework-vc142-mt-x64-1_78\
            -llibboost_wave-vc142-mt-x64-1_78\
            -llibboost_wserialization-vc142-mt-x64-1_78

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\FLANN\lib\
            -lflann\
            -lflann_cpp_s
    #        -lflann_s

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\OpenNI2\Lib\
            -lOpenNI2

    LIBS += -LD:\ProgramData\PCL1.12.1\3rdParty\Qhull\lib\
            #-lqhull\
            -lqhullcpp\
            -lqhullstatic\
            -lqhullstatic_r\
            #-lqhull_p\
            -lqhull_r
}


INCLUDEPATH += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\include"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkcgns-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkChartsCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonColor-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonComputationalGeometry-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonDataModel-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonExecutionModel-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonMath-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonMisc-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonSystem-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkCommonTransforms-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkDICOMParser-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkDomainsChemistry-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkDomainsChemistryOpenGL2-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkdoubleconversion-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkexodusII-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkexpat-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersAMR-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersExtraction-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersFlowPaths-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersGeneral-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersGeneric-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersGeometry-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersHybrid-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersHyperTree-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersImaging-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersModeling-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersParallel-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersParallelImaging-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersPoints-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersProgrammable-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersSelection-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersSMP-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersSources-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersStatistics-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersTexture-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersTopology-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkFiltersVerdict-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkfmt-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkfreetype-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkGeovisCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkgl2ps-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkglew-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkGUISupportQt-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkGUISupportQtQuick-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkGUISupportQtSQL-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkhdf5-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkhdf5_hl-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingColor-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingFourier-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingGeneral-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingHybrid-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingMath-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingMorphological-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingSources-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingStatistics-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkImagingStencil-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkInfovisCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkInfovisLayout-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkInteractionImage-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkInteractionStyle-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkInteractionWidgets-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOAMR-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOAsynchronous-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOCGNSReader-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOChemistry-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOCityGML-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOCONVERGECFD-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOEnSight-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOExodus-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOExport-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOExportGL2PS-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOExportPDF-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOGeometry-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOHDF-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOImage-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOImport-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOInfovis-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOIOSS-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOLegacy-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOLSDyna-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOMINC-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOMotionFX-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOMovie-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIONetCDF-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOOggTheora-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOParallel-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOParallelXML-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOPLY-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOSegY-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOSQL-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkioss-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOTecplotTable-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOVeraOut-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOVideo-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOXML-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkIOXMLParser-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkjpeg-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkjsoncpp-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkkissfft-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtklibharu-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtklibproj-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtklibxml2-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkloguru-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtklz4-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtklzma-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkmetaio-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtknetcdf-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkogg-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkParallelCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkParallelDIY-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkpng-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkpugixml-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingAnnotation-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingContext2D-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingContextOpenGL2-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingFreeType-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingGL2PSOpenGL2-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingImage-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingLabel-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingLOD-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingOpenGL2-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingQt-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingSceneGraph-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingUI-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingVolume-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingVolumeOpenGL2-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkRenderingVtkJS-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtksqlite-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtksys-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkTestingRendering-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtktheora-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtktiff-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkverdict-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkViewsContext2D-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkViewsCore-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkViewsInfovis-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkViewsQt-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkWrappingTools-9.1.lib"
LIBS += "D:\Program Files\PCL 1.12.1\3rdParty\VTK\lib\vtkzlib-9.1.lib"


#For Release
INCLUDEPATH += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\include\vtk-9.1"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkcgns-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkChartsCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonColor-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonComputationalGeometry-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonDataModel-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonExecutionModel-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonMath-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonMisc-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonSystem-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkCommonTransforms-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkDICOMParser-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkDomainsChemistry-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkDomainsChemistryOpenGL2-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkdoubleconversion-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkexodusII-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkexpat-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersAMR-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersExtraction-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersFlowPaths-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersGeneral-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersGeneric-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersGeometry-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersHybrid-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersHyperTree-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersImaging-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersModeling-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersParallel-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersParallelImaging-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersPoints-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersProgrammable-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersSelection-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersSMP-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersSources-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersStatistics-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersTexture-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersTopology-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkFiltersVerdict-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkfmt-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkfreetype-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkGeovisCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkgl2ps-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkglew-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkGUISupportQt-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkGUISupportQtQuick-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkGUISupportQtSQL-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkhdf5-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkhdf5_hl-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingColor-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingFourier-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingGeneral-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingHybrid-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingMath-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingMorphological-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingSources-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingStatistics-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkImagingStencil-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkInfovisCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkInfovisLayout-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkInteractionImage-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkInteractionStyle-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkInteractionWidgets-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOAMR-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOAsynchronous-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOCGNSReader-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOChemistry-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOCityGML-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOCONVERGECFD-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOEnSight-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOExodus-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOExport-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOExportGL2PS-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOExportPDF-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOGeometry-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOHDF-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOImage-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOImport-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOInfovis-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOIOSS-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOLegacy-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOLSDyna-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOMINC-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOMotionFX-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOMovie-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIONetCDF-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOOggTheora-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOParallel-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOParallelXML-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOPLY-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOSegY-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOSQL-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkioss-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOTecplotTable-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOVeraOut-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOVideo-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOXML-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkIOXMLParser-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkjpeg-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkjsoncpp-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkkissfft-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtklibharu-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtklibproj-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtklibxml2-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkloguru-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtklz4-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtklzma-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkmetaio-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtknetcdf-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkogg-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkParallelCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkParallelDIY-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkpng-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkpugixml-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingAnnotation-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingContext2D-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingContextOpenGL2-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingFreeType-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingGL2PSOpenGL2-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingImage-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingLabel-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingLOD-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingOpenGL2-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingQt-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingSceneGraph-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingUI-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingVolume-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingVolumeOpenGL2-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkRenderingVtkJS-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtksqlite-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtksys-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkTestingRendering-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtktheora-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtktiff-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkverdict-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkViewsContext2D-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkViewsCore-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkViewsInfovis-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkViewsQt-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkWrappingTools-9.1.lib"
LIBS += "D:\ProgramData\PCL1.12.1\3rdParty\VTK\lib\vtkzlib-9.1.lib"

DISTFILES += \
    logo.rc


RC_FILE += logo.rc

