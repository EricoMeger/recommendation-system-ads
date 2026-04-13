CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I..

TEST_RNG    = test_rng
TEST_HASH   = test_hash
TEST_HEAP   = test_heap
TEST_CUCKOO = test_cuckoo

TEST_SRC_RNG = test_rng.cpp \
               ../src/rng/engines/algorithms/acorn.cpp \
               ../src/rng/engines/algorithms/xorshift.cpp

TEST_SRC_HASH = test_hash.cpp \
                ../src/hash/hash_table.cpp \
                ../src/hash/item_score_table.cpp \
                ../src/hash/algorithms/fnv1a.cpp \
                ../src/hash/algorithms/murmurhash.cpp

TEST_SRC_HEAP = test_heap.cpp \
                ../src/heap/algorithms/floyd.cpp

TEST_SRC_CUCKOO = test_cuckoo.cpp \
                  ../src/cuckoo/cuckoo_filter.cpp \
                  ../src/hash/algorithms/fnv1a.cpp \
                  ../src/hash/algorithms/murmurhash.cpp

all: $(TEST_RNG) $(TEST_HASH) $(TEST_HEAP) $(TEST_CUCKOO)

$(TEST_RNG): $(TEST_SRC_RNG)
	$(CXX) $(CXXFLAGS) $(TEST_SRC_RNG) -o $(TEST_RNG)

$(TEST_HASH): $(TEST_SRC_HASH)
	$(CXX) $(CXXFLAGS) $(TEST_SRC_HASH) -o $(TEST_HASH)

$(TEST_HEAP): $(TEST_SRC_HEAP)
	$(CXX) $(CXXFLAGS) $(TEST_SRC_HEAP) -o $(TEST_HEAP)

$(TEST_CUCKOO): $(TEST_SRC_CUCKOO)
	$(CXX) $(CXXFLAGS) $(TEST_SRC_CUCKOO) -o $(TEST_CUCKOO)

run: all
	./$(TEST_RNG)
	./$(TEST_HASH)
	./$(TEST_HEAP)
	./$(TEST_CUCKOO)

clean:
	rm -f $(TEST_RNG) $(TEST_HASH) $(TEST_HEAP) $(TEST_CUCKOO)

.PHONY: all run clean
