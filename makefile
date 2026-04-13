CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./main/include

SRC = ./main/src/main.cpp \
      ./main/src/factory/factory.cpp \
      ./main/src/recommender.cpp \
      ./main/src/cuckoo/cuckoo_filter.cpp \
      ./main/src/hash/algorithms/fnv1a.cpp \
      ./main/src/hash/algorithms/murmurhash.cpp \
      ./main/src/hash/hash_table.cpp \
      ./main/src/hash/item_score_table.cpp \
      ./main/src/heap/algorithms/floyd.cpp \
      ./main/src/rng/engines/algorithms/acorn.cpp \
      ./main/src/rng/engines/algorithms/xorshift.cpp

TARGET = recsys

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) --seed 42 --users 100 --items 50 --ratings 1000 --topk 5

run-cuckoo: $(TARGET)
	./$(TARGET) --seed 42 --users 100 --items 50 --ratings 1000 --topk 5 --cuckoo

clean:
	rm -f $(TARGET)

.PHONY: all run run-cuckoo clean