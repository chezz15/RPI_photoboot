#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T16:24:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RPI_Photobooth
target.path = /home/pi
INSTALLS += target

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        button_lib.cpp \
    raspicam.cpp \
    private/fake_mmal_dependencies.cpp \
    private/private_impl.cpp \
    private/threadcondition.cpp \
    private_still/private_still_impl.cpp \
    raspicam_still.cpp

HEADERS  += mainwindow.h\
         button_lib.h\
         wiringPi.h \
    raspicam.h \
    raspicamtypes.h \
    build-RPI_Photobooth-RPI_Qt-Debug/ui_mainwindow.h \
    private/exceptions.h \
    private/private_impl.h \
    private/private_types.h \
    private/threadcondition.h \
    private_still/private_still_impl.h \
    raspicam_still.h \
    scaler.h \
    mmal/core/mmal_buffer_private.h \
    mmal/core/mmal_clock_private.h \
    mmal/core/mmal_component_private.h \
    mmal/core/mmal_core_private.h \
    mmal/core/mmal_events_private.h \
    mmal/core/mmal_port_private.h \
    mmal/util/mmal_component_wrapper.h \
    mmal/util/mmal_connection.h \
    mmal/util/mmal_default_components.h \
    mmal/util/mmal_graph.h \
    mmal/util/mmal_il.h \
    mmal/util/mmal_list.h \
    mmal/util/mmal_param_convert.h \
    mmal/util/mmal_util.h \
    mmal/util/mmal_util_params.h \
    mmal/util/mmal_util_rational.h \
    mmal/vc/mmal_vc_api.h \
    mmal/vc/mmal_vc_api_drm.h \
    mmal/vc/mmal_vc_client_priv.h \
    mmal/vc/mmal_vc_msgnames.h \
    mmal/vc/mmal_vc_msgs.h \
    mmal/vc/mmal_vc_opaque_alloc.h \
    mmal/vc/mmal_vc_shm.h \
    mmal/mmal.h \
    mmal/mmal_buffer.h \
    mmal/mmal_clock.h \
    mmal/mmal_common.h \
    mmal/mmal_component.h \
    mmal/mmal_encodings.h \
    mmal/mmal_events.h \
    mmal/mmal_format.h \
    mmal/mmal_logging.h \
    mmal/mmal_metadata.h \
    mmal/mmal_parameters.h \
    mmal/mmal_parameters_audio.h \
    mmal/mmal_parameters_camera.h \
    mmal/mmal_parameters_clock.h \
    mmal/mmal_parameters_common.h \
    mmal/mmal_parameters_video.h \
    mmal/mmal_pool.h \
    mmal/mmal_port.h \
    mmal/mmal_queue.h \
    mmal/mmal_types.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$PWD/../libs/ -lwiringPi

CONFIG += c++11

INCLUDEPATH += $$PWD/../libs
DEPENDPATH += $$PWD/../libs
