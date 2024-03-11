#!/bin/bash

cd models

make

cd patient/bin
./main 1 50 100 180 &

sleep 1

cd ../../insulin_pump/bin
./main &

cd ../../environment/bin
./main &

cd ../../monitors/bin
./main &

wait