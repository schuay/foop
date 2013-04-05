bake:
	mkdir -p build
	cd build; cmake -DCMAKE_BUILD_TYPE="Debug" -DQT_QMAKE_EXECUTABLE=qmake-qt4 .. && make -j6 && make test ARGS="-V"

clean:
	rm -r build


