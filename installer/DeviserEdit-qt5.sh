#!/bin/sh
export QT5_LIBS=$(pwd)/qt5
export LD_LIBRARY_PATH=$QT5_LIBS:$LD_LIBRARY_PATH
export QT_QPA_PLATFORM_PLUGIN_PATH=$QT5_LIBS
# echo $LD_LIBRARY_PATH
./DeviserEdit
exit
