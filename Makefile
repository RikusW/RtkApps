
CXXFLAGS += -DXLIB -Wall -g -lRtk-base -lRtk-gui -I../

all: app

clean:
	rm -fv *.o
	rm -fv *~
	rm -fv app rex str CAaBb *_sisl.cpp

#=========================================================#
#Keep Rtk-parse output
.PRECIOUS: %_sisl.cpp

%_sisl.cpp: %.h
	../Rtk-gui/Rtk-parse $< > $@

#=========================================================#

app: app.o app_sisl.o
	g++ -o $@ $^ $(CXXFLAGS)
# -lefence

#=========================================================#

rex: rex.cpp
	g++ -o $@ $^ $(CXXFLAGS)

#=========================================================#

str: str.cpp
	g++ -o $@ $^ $(CXXFLAGS)

#=========================================================#

CAaBb: CAaBb.cpp CAaBb_sisl.o
	g++ -o $@ $^ $(CXXFLAGS)

#=========================================================#


