# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-lattestation

CONFIG += sailfishapp

SOURCES += src/LAttestation.cpp \
    src/appsettings.cpp \
    src/attestationmanager.cpp \
    src/generator.cpp \
    libqrencode/qrencode.c \
    libqrencode/qrinput.c \
    libqrencode/split.c \
    libqrencode/rsecc.c \
    libqrencode/qrspec.c \
    libqrencode/bitstream.c \
    libqrencode/mqrspec.c \
    libqrencode/mmask.c \
    libqrencode/mask.c \
    src/generatorimageprovider.cpp

DISTFILES += qml/LAttestation.qml \
    qml/cover/CoverPage.qml \
    qml/pages/Access.qml \
    qml/pages/Generate.qml \
    qml/pages/HomePage.qml \
    qml/pages/Preview.qml \
    qml/pages/SettingsPage.qml \
    rpm/harbour-lattestation.changes.in \
    rpm/harbour-lattestation.changes.run.in \
    rpm/harbour-lattestation.spec \
    rpm/harbour-lattestation.yaml \
    translations/*.ts \
    LAttestation.desktop

resources.files += resources/*
resources.path += /usr/share/$$TARGET/resources

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

DEFINES += STATIC_IN_RELEASE= \
        MAJOR_VERSION=4 \
        MINOR_VERSION=1 \
        MICRO_VERSION=1 \
        HAVE_CONFIG_H

INCLUDEPATH += src

LIBS += -lpoppler-qt5

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/harbour-lattestation-fr.ts

INSTALLS += resources

# This part is to circumvent harbour limitations.
QMAKE_RPATHDIR = $$DEPLOYMENT_PATH/lib

HEADERS += \
    src/appsettings.h \
    src/attestationmanager.h \
    src/config.h \
    src/generator.h \
    src/generatorimageprovider.h
