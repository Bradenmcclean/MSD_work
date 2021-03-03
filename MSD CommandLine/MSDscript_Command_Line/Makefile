INCS = functions.hpp

UNCS=arithmetic.h

PNCS=parse.hpp

NNCS=randomTestGen.hpp

KNCS=exec.hpp

HNCS=val.hpp

OBJS = main.o functions.o arithmetic.o parse.o val.o

OBJSS =  exec.o randomTestGen.o 

CXXFLAGS = --std=c++14 -O2

msdscript: $(OBJS)
	$(CXX) $(CXXFLAGS) -o msdscript $(OBJS)

test_msdscript:$(OBJSS)
	$(CXX) $(CXXFLAGS) -o test_msdscript $(OBJSS)

.PHONY: test
test: msdscript
	./msdscript --test


main.o: main.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<
functions.o: functions.cpp $(INCS)
	$(CXX) $(CXXFLAGS) -c $<
arithmetic.o: arithmetic.cpp $(UNCS)
	$(CXX) $(CXXFLAGS) -c $<
Parse.o: parse.cpp $(PNCS)
	$(CXX) $(CXXFLAGS) -c $<
val.o: val.cpp $(HNCS)
	$(CXX) $(CXXFLAGS) -c $<

exec.o: exec.cpp $(KNCS)
	$(CXX) $(CXXFLAGS) -c $<

randomTestGen.o: randomTestGen.cpp $(NNCS)
	$(CXX) $(CXXFLAGS) -c $<


