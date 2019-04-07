TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    calculate_matrix_sum.h \
    test_runner.h \
    paginator.h

LIBS += -pthread
