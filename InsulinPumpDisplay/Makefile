con2redis_OBJ=$(wildcard ../con2redis/obj/*.o)
con2redis_incl=../con2redis/src
all:	
	g++ -o insulinPumpDisplay insulinPumpDisplay.cpp `pkg-config gtkmm-3.0 --cflags --libs` -I$(con2redis_incl) $(con2redis_OBJ) -lhiredis

.PHONY: clean

clean:
	rm -f *.o *~ insulinPumpDisplay