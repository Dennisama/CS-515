CXX=g++

all: hello addUp results.txt

results.txt: addUp
	$ ./addUp < myNumbers > results.txt

addUp: addUp.cpp
	$(CXX)  addUp.cpp -o addUp

hello: hello.cpp
	$(CXX)  hello.cpp -o hello

clean:
	rm -f *.o hello
