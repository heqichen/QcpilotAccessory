
BUILD_DIR := build


INCLUDES := -I./ -I ../raylib/

# Desktop framework
desktop: build/desktop_app

build/desktop_app: build/desktop/main.o $(RAYLIB_OBJS)
	mkdir -p build/desktop
	g++ $^ -L./lib -lraylib -o build/desktop_app

build/desktop/main.o: main.cpp
	mkdir -p build/desktop
	g++ main.cpp -c $(INCLUDES) -o build/desktop/main.o

clean:
	rm -rf $(BUILD_DIR)

.PHONY: desktop clean
