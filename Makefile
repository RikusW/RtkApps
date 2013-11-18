
FLAGS = -DXLIB -Wall -g -lRtk
#FLAGS = -DXLIB -Wall -g -fpermissive -I/usr/X11/include -L/usr/X11/lib -lX11 -L../Rtk -lRtk  #required on some other platforms

#-Wl,-rpath,/home/rikus/Programming/Rtk
#LD_LIBRARY_PATH

all: app

clean:
	rm -fv *.o
	rm -fv *~
	rm -fv rex app caabb caabb_sisl.cpp str

libRtk: ../Rtk/libRtk.so

#=========================================================#

app_sisl.cpp: app.h ../Rtk/parse
	../Rtk/parse app.h > app_sisl.cpp


app: app.h app.cpp app_sisl.cpp libRtk
	g++ -o app app.cpp app_sisl.cpp $(FLAGS)
# -lefence
#-L/usr/X11R6/lib -lX11
#	-lefence

#=========================================================#

rex: rex.cpp libRtk
	g++ -o rex rex.cpp $(FLAGS)

#=========================================================#

cfg: cfg.cpp libRtk
	g++ -o cfg cfg.cpp $(FLAGS)

#=========================================================#

str: str.cpp libRtk
	g++ -o str str.cpp $(FLAGS)

#=========================================================#

prog_sisl.cpp: prog.h ../Rtk/parse
	../Rtk/parse prog.h > prog_sisl.cpp

prog: prog.h prog.cpp prog_sisl.cpp ../Rtk/libRtk.so
	g++ -o prog prog.cpp prog_sisl.cpp $(FLAGS)

#=========================================================#

caabb_sisl.cpp: CAaBb.h ../Rtk/parse
	../Rtk/parse CAaBb.h > caabb_sisl.cpp

caabb_sisl.o: caabb_sisl.cpp
	g++ $(FLAGS) -c -o caabb_sisl.o caabb_sisl.cpp

caabb: CAaBb.h CAaBb.cpp caabb_sisl.o ../Rtk/libRtk.so
	g++ $(FLAGS) -o caabb CAaBb.cpp caabb_sisl.o -L../Rtk/ -lRtk
# -lefence

#=========================================================#


