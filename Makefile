CFLAGS := -Wall -Wextra -Wno-missing-field-initializers -ggdb -DPLATFORM_DESKTOP -std=c++17 -I/usr/local/include/raylib #-O3
LDFLAGS := -L/usr/local/lib/raylib -l:libraylib.a

rayquad: src/*.cpp
	g++ $(CFLAGS) -o rayquad src/*.cpp $(LDFLAGS)

demo: rayquad
	./rayquad

clean:
	rm -f rayquad
