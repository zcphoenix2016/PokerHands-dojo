UTLIB = googletest/build/googlemock/libgmock_main.a\
        googletest/build/googlemock/libgmock.a\
        googletest/build/googlemock/gtest/libgtest.a

UTINC = -isystem googletest/googlemock/include\
       -isystem googletest/googletest/include\

UTFLAG = -g -pthread -DUNIT_TEST -Wno-write-strings

all:
	g++ -std=c++14 -pthread Source/*.cpp -o PokerHands.exe -g

ut:
	g++ -std=c++14 ${UTFLAG} ${UTINC} ${UTLIB} Source/*.cpp Test_modules/*.cpp -o ut_PokerHands.exe

clean:
	rm -rf *.o
	rm -rf Test_modules/*.o
	rm -rf *.exe
