CC = gcc
CFLAGS = -std=gnu11 -Werror -Wall -pedantic
LDFLAGS =

TARGET = top_secret
MODULES = utils.o bmp.o playfair.o
TEST_TARGET = tests/all_tests
TEST_MODULES = tests/test_utils.o tests/test_bmp.o tests/test_playfair.o

# Main tasks
.PHONY: all test clean

all: $(TARGET) $(TEST_TARGET)

test: $(TEST_TARGET)
	$< 

clean:
	-rm -f top_secret.o $(MODULES)
	-rm -f tests/all_tests.o $(TEST_MODULES)
	-rm -f $(TARGET)
	-rm -f $(TEST_TARGET)

# Dependencies
$(TARGET): top_secret.o $(MODULES)
top_secret.o: top_secret.c bmp.h playfair.h
bmp.o: bmp.c bmp.h utils.h
post.o: post.c post.h utils.h

$(TEST_TARGET): tests/all_tests.o $(TEST_MODULES) $(MODULES)
tests/test_utils.o: tests/test_utils.c tests/greatest.h utils.h
tests/test_post.o: tests/test_post.c tests/greatest.h post.h
tests/test_wall.o: tests/test_wall.c tests/greatest.h wall.h

# Machinery
%.o: %.c
	$(CC) -c -o $@ $(CFLAGS) $<
%: %.o
	$(CC) -o $@ $(LDFLAGS) $^
