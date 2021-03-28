.DEFAULT_GOAL := all

sistema.o: src/sistema.cpp include/sistema.hpp
	g++ src/sistema.cpp -c

executor.o: src/executor.cpp include/executor.hpp sistema.o
	g++ src/executor.cpp -c

usuario.o: src/usuario.cpp include/usuario.hpp
	g++ src/usuario.cpp -c

servidor.o: src/servidor.cpp include/servidor.hpp
	g++ src/servidor.cpp -c

objects: sistema.o executor.o usuario.o servidor.o

concordo: objects src/concordo.cpp
	g++ -Wall -fsanitize=address sistema.o executor.o usuario.o servidor.o src/concordo.cpp -o concordo

clean:
	rm *.o concordo

all: concordo

run:
	./concordo
