#
# Mandelzoom Makefile
# Based on the Unity Project Example Makefile
#

#We try to detect the OS we are running on, and adjust commands as needed
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
elseifeq ($(OSTYPE),msys)
  CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.exe
elseifeq ($(OS),Windows_NT)
	CLEANUP = del /F /Q
	MKDIR = mkdir
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

# Unity C test harness is in the unity/ subdirectory
UNITY_ROOT=unity
C_COMPILER=clang

CFLAGS=-std=c99
CFLAGS += -Wall
CFLAGS += -Werror
#CFLAGS += -Wpointer-arith
#CFLAGS += -Wcast-align
#CFLAGS += -Wwrite-strings
#CFLAGS += -Wswitch-default
CFLAGS += -Wunreachable-code
#CFLAGS += -Winit-self
CFLAGS += -Wmissing-field-initializers
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -Wstrict-prototypes
#CFLAGS += -Wundef
CFLAGS += -Wold-style-definition
CFLAGS += -pedantic

TARGET_BASE1=vector
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
SRC_FILES1=$(UNITY_ROOT)/src/unity.c src/vector.c  test/test_vector.c  test/test_runners/test_vector_runner.c
INC_DIRS=-Isrc -I$(UNITY_ROOT)/src
SYMBOLS=-DTEST

.PHONY: all test clean

all: clean test

test:
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb test/test_vector.c  test/test_runners/test_vector_runner.c
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o test/$(TARGET1)
	./test/$(TARGET1)

clean:
	(cd src;  $(CLEANUP) *.o *.out *.out.stackdump)
	(cd test; $(CLEANUP) *.o *.out *.out.stackdump test_runners/*.c)
