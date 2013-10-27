TARGET=RainbowAttack

normal: $(TARGET)

RainbowAttack: src/RainbowAttack.cpp main.cpp src/bitsetFunctions.cpp
		g++ -Wall -o RainbowPoneys main.cpp src/RainbowAttack.cpp src/bitsetFunctions.cpp -I/usr/include/cryptopp -L/usr/lib -lcryptopp

