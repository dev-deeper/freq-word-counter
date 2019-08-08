BIN = bin/freq

all: build

build: clean
	@cmake -S . -B buildcmake -H. -Bbuild -DCMAKE_BUILD_TYPE=Release && cd build && make

test:
	@test -f $(BIN) || (echo "build project first" && exit 1)
	$(BIN) -i example/in.txt

clean:
	@rm -rf build/*
	@rm -rf bin/*

