#! /bin/sh

cd app/libs
protoc --cpp_out=. --python_out=. --lua_out=. scheduler.proto
mkdir -p ../../tftphome
mkdir -p ../../tftphome/app
mkdir -p ../../tftphome/app/lib
cp *.lua ../../tftphome/app/lib/
mv -f scheduler.pb.cc source
mkdir -p include
mv -f scheduler.pb.h include
cd -
