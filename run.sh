#!/bin/bash

cd models

make

cd patient/bin
./main 1 50 100 180 &

sleep 0.5

cd ../../insulin_pump/bin
./main &

cd ../../environment/bin
./main &

cd ../../../InsulinePumpDisplay
./insulinePumpDisplay

wait

cd ../models/monitors/bin
./main