asmsharp: src/main.cpp src/lexer.cpp src/error.cpp
	g++ -o asmsharp src/main.cpp src/lexer.cpp src/error.cpp

clean:
	rm asmsharp
