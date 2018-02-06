#!/bin/sh
export QT5_LIBS=$(pwd)/lib
export QT_QPA_PLATFORM_PLUGIN_PATH=$(pwd)/plugins
export LD_LIBRARY_PATH=$QT5_LIBS:$QT_QPA_PLATFORM_PLUGIN_PATH/sqldrivers:$LD_LIBRARY_PATH
./DeviserEdit
exit
