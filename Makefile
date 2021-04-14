.DEFAULT_GOAL := all

sistema.o: src/sistema.cpp include/sistema.hpp
	g++ src/sistema.cpp -c

executor.o: src/executor.cpp include/executor.hpp sistema.o
	g++ src/executor.cpp -c

usuario.o: src/usuario.cpp include/usuario.hpp
	g++ src/usuario.cpp -c

mensagem.o: src/mensagem.cpp include/mensagem.hpp
	g++ src/mensagem.cpp -c

canal.o: src/canal.cpp include/canal.hpp
	g++ src/canal.cpp -c

canalTexto.o: src/canalTexto.cpp canal.o
	g++ src/canalTexto.cpp -c

canalVoz.o: src/canalVoz.cpp canal.o
	g++ src/canalVoz.cpp -c

servidor.o: src/servidor.cpp mensagem.o canal.o canalTexto.o canalVoz.o include/servidor.hpp include/canal.hpp include/canalTexto.hpp include/canalVoz.hpp
	g++ src/servidor.cpp -c

objects: sistema.o executor.o usuario.o mensagem.o canal.o canalTexto.o canalVoz.o servidor.o

concordo: objects src/concordo.cpp
	g++ -Wall -fsanitize=address sistema.o executor.o usuario.o mensagem.o canal.o canalTexto.o canalVoz.o servidor.o src/concordo.cpp -o concordo

clean:
	rm *.o usuarios.txt servidores.txt concordo

all: concordo

run:
	./concordo
