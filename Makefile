asmsharp: src/main.cpp src/lexer.cpp src/error.cpp src/cpu.cpp
	g++ -o asmsharp src/main.cpp src/lexer.cpp src/error.cpp src/cpu.cpp

clean:
	rm asmsharp
