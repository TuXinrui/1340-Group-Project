FLAGS = -lsupc++ -pedantic-errors -std=c++11

support.o: support.cpp support.h attack.h
	g++ $(FLAGS) -c $<

initMap.o: initMap.cpp support.h
	g++ $(FLAGS) -c $<

attack.o: attack.cpp attack.h support.h enemy_ai.h
	g++ $(FLAGS) -c $<

enemy_ai.o: enemy_ai.cpp enemy_ai.h attack.h support.h
	g++ $(FLAGS) -c $<

inputtransform.o: inputtransform.cpp inputtransform.h attack.h support.h output.h
	g++ $(FLAGS) -c $<

output.o: output.cpp output.h support.h
	g++ $(FLAGS) -c $<

Main.o: Main.cpp attack.h support.h inputtransform.h enemy_ai.h initMap.h output.h
	g++ $(FLAGS) -c $<

naval_battle: support.o initMap.o attack.o enemy_ai.o inputtransform.o output.o Main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f *.o naval_battle

.PHONY: clean
