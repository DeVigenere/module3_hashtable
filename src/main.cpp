#include "HashTable.h"

int main() {
	HashTable<std::string, int> ht;
	ht.insert("a", 1);
	ht.insert("b", 2);
	ht.insert("c", 3);
	ht.contains("a");
	ht.remove("b");
	ht.find("c");
	ht.rehash();
	ht.statistics();
	std::cout << std::endl;

	HashTable<std::string, int> ht5;
	for (int i = 0; i < 10000; ++i) {
		std::string key = "element_" + std::to_string(i);
		ht5.insert(key, i * 2);
	}
	ht5.statistics();
}
