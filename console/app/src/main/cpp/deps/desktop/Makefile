
BUILD_DIR := build


SRCS := raymob/qcpilot/ui/entry.cpp

OBJS := $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))

INCLUDES := -I./ -I../ -I../raylib/ -I../raymob/

# Desktop framework
desktop: build/desktop_app

build/desktop_app: build/desktop/main.o build/desktop/platform-desktop.o $(OBJS)
	mkdir -p build/desktop
	g++ $^ -L./lib -lraylib -o build/desktop_app

build/desktop/main.o: main.cpp $(OBJS)
	mkdir -p build/desktop
	g++ main.cpp -c $(INCLUDES) -o build/desktop/main.o

build/desktop/platform-desktop.o: platform-desktop.cpp $(OBJS)
	mkdir -p build/desktop
	g++ platform-desktop.cpp -c $(INCLUDES) -o build/desktop/platform-desktop.o

build/%.o: ../%.cpp
	mkdir -p $(dir $@)
	g++ $^ -c $(INCLUDES) -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: desktop clean
