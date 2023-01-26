all:
	cd tests && make
	g++ cppp/src/linux/main.cpp -Icppp/include
