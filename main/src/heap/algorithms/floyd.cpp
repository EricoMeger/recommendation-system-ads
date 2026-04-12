#include "../../../include/heap/algorithms/floyd.hpp"

#include <stdexcept>
#include <utility>

Floyd::Floyd(const std::vector<ItemScore>& values)
{
	buildHeap(values);
}

void Floyd::buildHeap(const std::vector<ItemScore>& values)
{
	data = values;

	for (size_t i = data.size() / 2; i > 0; --i) {
		heapifyDown(i - 1);
	}
}

void Floyd::push(ItemScore value)
{
	data.push_back(value);
	heapifyUp(data.size() - 1);
}

void Floyd::pop()
{
	if (data.empty()) {
		return;
	}

	data[0] = data.back();
	data.pop_back();

	if (!data.empty()) {
		heapifyDown(0);
	}
}

ItemScore Floyd::top() const
{
	if (data.empty()) {
		throw std::out_of_range("Heap is empty");
	}
 
	return data[0];
}

bool Floyd::empty() const
{
	return data.empty();
}

size_t Floyd::size() const
{
	return data.size();
}

std::string Floyd::getName() const
{
	return "Floyd";
}

void Floyd::heapifyUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (data[parent] >= data[index]) break;  
        std::swap(data[parent], data[index]);
        index = parent;
    }
}

void Floyd::heapifyDown(size_t index) {
    while (true) {
        size_t left    = 2 * index + 1;
        size_t right   = left + 1;
        size_t largest = index;

        if (left  < data.size() && data[left]  > data[largest]) largest = left;
        if (right < data.size() && data[right] > data[largest]) largest = right;

        if (largest == index) break;
        std::swap(data[index], data[largest]);
        index = largest;
    }
}

std::vector<ItemScore> Floyd::topK(int k) {
    Floyd copy = *this;
    std::vector<ItemScore> result;
    for (int i = 0; i < k && !copy.empty(); i++) {
        result.push_back(copy.top());
        copy.pop();
    }
    return result;
}