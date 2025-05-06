
BUILD_DIR := build


SRCS := raymob/qcpilot/ui/entry.cpp

OBJS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

INCLUDES := -I./ -I../ -I../raylib/ -I../raymob/

# Desktop framework
desktop: build/desktop_app

build/desktop_app: build/desktop/main.o build/desktop/platform-desktop.o $(OBJS)
	mkdir -p build/desktop
	g++ -std=c++17 $^ -L./lib -lraylib -o build/desktop_app

build/desktop/main.o: main.cpp $(OBJS)
	mkdir -p build/desktop
	g++ -std=c++17 main.cpp -c $(INCLUDES) -o build/desktop/main.o

build/desktop/platform-desktop.o: platform-desktop.cpp $(OBJS)
	mkdir -p build/desktop
	g++ -std=c++17 platform-desktop.cpp -c $(INCLUDES) -o build/desktop/platform-desktop.o

build/%.o: ../%.cpp
	mkdir -p $(dir $@)
	g++ -std=c++17 $^ -c $(INCLUDES) -o $@

clean:
	rm -rf $(BUILD_DIR)

run: build/desktop_app
	./build/desktop_app

.PHONY: desktop clean
