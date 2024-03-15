#!/bin/bash


cd models

cd patient/bin
./main 1 50 100 180 &

sleep 0.5

cd ../../insulin_pump/bin
./main &

cd ../../environment/bin
./main &

wait

cd ../../monitors/bin
./main