




#TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#
#
PRJNAMETOOT = DrawCanvasDynamicly
DEFINES += "DRAWCANVASDYNAMICLY_API="
DEFINES += "DRAWCANVASDYNAMICLY_API(...)="
#
DEFINES += "UCLASS()=DRAWCANVASDYNAMICLY_API"
DEFINES += "UCLASS(...)=DRAWCANVASDYNAMICLY_API"
#
# this is true during development with unreal-editor...

DEFINES += "WITH_EDITORONLY_DATA=1"



INCLUDEPATH += ../Intermediate/Build/Win64/UnrealEditor/Inc/$$PRJNAMETOOT/UHT
#INCLUDEPATH += $$PRJNAMETOOT $$PRJNAMETOOT/Public $$PRJNAMETOOT/Private #don't use this,
# we should follow UE project struct to include files, start from prj.Build.cs folder
#
#  The Thirdparty libs
#    INCLUDEPATH += ../ThirdpartyLibs/FMOD/inc
#
#
include(defs.pri)
include(inc.pri)
#
#

DISTFILES += \
    DrawCanvasDynamicly.Target.cs \
    DrawCanvasDynamicly/DrawCanvasDynamicly.Build.cs \
    DrawCanvasDynamiclyEditor.Target.cs

HEADERS += \
    DrawCanvasDynamicly/DrawCanvans/DrawingCanvas.h \
    DrawCanvasDynamicly/DrawCanvasDynamicly.h \
    DrawCanvasDynamicly/Public/TootIntQueue.h

SOURCES += \
    DrawCanvasDynamicly/DrawCanvans/DrawingCanvas.cpp \
    DrawCanvasDynamicly/DrawCanvasDynamicly.cpp \
    DrawCanvasDynamicly/Private/TootIntQueue.cpp







