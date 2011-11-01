GXX=g++
INCLUDES=-Iinclude/fuzzyone
GXXFLAGS=-c -Wall $(INCLUDES)
OBJECTS=FuzzyOne.o Term.o LVar.o Hedge.o
LIB=fuzzyone
PROGRAM=lib$(LIB).so

all: debug test

debug:
	$(MAKE) GXXFLAGS="$(GXXFLAGS) -g -fPIC" $(PROGRAM)

release:
	$(MAKE) GXXFLAGS="$(GXXFLAGS) -O2 -fPIC -DNDEBUG" $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(GXX) $(LFLAGS) --shared $(OBJECTS) -o $@

test: src/test.cpp
	$(GXX) -Wall $(INCLUDES) -g -L. -l$(LIB) $< -Wl,-rpath,. -o test

%.o: src/%.cpp
	$(GXX) $(GXXFLAGS) $<

.PHONY: clean

clean:
	rm *.o

rebuild: clean all
