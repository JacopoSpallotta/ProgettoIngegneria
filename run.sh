#!/bin/bash

SEX=1
AGE=50
WEIGHT=80
HEIGHT=180

cd models

cd patient/bin
./main $SEX $AGE $WEIGHT $HEIGHT &

sleep 0.5

cd ../../insulin_pump/bin
./main &

cd ../../environment/bin
./main &

wait

cd ../../monitors/bin
./main