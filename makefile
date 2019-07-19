all:
	g++ -c timber.cpp -ISFML/include
	g++ timber.o -o timber-sfml -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
run: all
	export LD_LIBRARY_PATH=SFML/lib && ./timber-sfml
clean:
	rm -f timber.o timber-sfml
