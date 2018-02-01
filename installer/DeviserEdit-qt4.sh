#!/bin/bash
CURRENT_DIR=$(cd `dirname $0` && pwd)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CURRENT_DIR:$CURRENT_DIR/qt4


#if [ ! -f $HOME/.deviser_config.xml ]
#then

#export PYTHON_EXECUTABLE=`which python`
#export DEVISER_DIR=$CURRENT_DIR/deviser
#export SBMLPKSPEC_DIR=$CURRENT_DIR/sbmlpkgspec

#cat $CURRENT_DIR/default_config.xml | sed -e "s@PYTHON_EXECUTABLE@$PYTHON_EXECUTABLE@;s@DEVISER_DIR@$DEVISER_DIR@;s@SBMLPKSPEC_DIR@$SBMLPKSPEC_DIR@" > $HOME/.deviser_config.xml

#fi

if ! $CURRENT_DIR/DeviserEdit --version; then
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$CURRENT_DIR/qt4
fi

$CURRENT_DIR/DeviserEdit $*

