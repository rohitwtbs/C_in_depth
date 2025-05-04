CC=gcc
CFLAGS= -I "/System/Volumes/Data/opt/homebrew/Cellar/raylib/5.5/include"
LDFLAGS= -L "/System/Volumes/Data/opt/homebrew/Cellar/raylib/5.5/lib" -lraylib
TARGET=tictactoe
SOURCE=tictactoe.c

all: $(TARGET)

$(TARGET): $(SOURCE)
  $(CC)	$(CFLAGS)	$(LDFLAGS)	-o	$(TARGET)	$(SOURCE)

clean:
  rm -f $(TARGET)

run: $(TARGET)
  ./$(TARGET)
  @$(MAKE) clean



  gcc -I "/System/Volumes/Data/opt/homebrew/Cellar/raylib/5.5/include" -L "/System/Volumes/Data/opt/homebrew/Cellar/raylib/5.5/lib" -lraylib -o tictactoe tictactoe.c