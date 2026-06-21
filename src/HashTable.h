#pragma once
#include <vector>
#include <list>
#include <string>
#include <stdexcept>
#include <optional>
#include <iostream>

constexpr double fill_factor = 0.75;

template <typename K, typename V>
class HashTable {
	struct Item {
		K key;
		V value;
		Item(const K& k, const V& v) : key(k), value(v) {};
	};
	std::vector<std::list<Item>> table;
	size_t capacity;
	size_t size;

	unsigned long hash(const K& key, size_t cap) const {
		std::hash<K> hasher;
		return hasher(key) % cap;
	}
	unsigned long hash(const K& key) const {
		return hash(key, capacity);
	}
public:
	HashTable(size_t cap = 32) : capacity(cap), size(0) {
		if (capacity == 0) {
			throw std::runtime_error("capacity cannot be 0!");
		}
		table.resize(capacity);
	}
	void insert(const K& key, const V& value) {
		size_t index = hash(key);
		for (auto& entry : table[index]) {
			if (entry.key == key) {
				entry.value = value;
				return;
			}
		}
		table[index].emplace_back(key, value);
		size++;
		if (size > capacity * fill_factor) {
			rehash();
		}
	}

	std::optional<V> find(const K& key) const {
		auto hashed = hash(key);
		for (const auto& entry : table[hashed]) {
			if (entry.key == key) {
				return entry.value;
			}
		}
		return std::nullopt;
	}

	bool contains(const K& key) const {
		auto hashed = hash(key);
		for (const auto& entry : table[hashed]) {
			if (entry.key == key) {
				return true;
			}
		}
		return false;
	}

	bool remove(const K& key) {
		auto hashed = hash(key);
		for (auto it = table[hashed].begin(); it != table[hashed].end(); ++it) {
			if (it->key == key) {
				table[hashed].erase(it);
				size--;
				return true;
			}
		}
		return false;
	}

	void rehash() {
		auto new_capacity = capacity * 2;
		if (new_capacity <= capacity) {
			throw std::runtime_error("new capacity less than old");
		}
		std::vector<std::list<Item>> new_table(new_capacity);
		for (const auto& bucket : table) {
			for (const auto& entry : bucket) {
				auto new_index = hash(entry.key, new_capacity);
				new_table[new_index].push_back(entry);
			}
		}
		capacity = new_capacity;
		table = std::move(new_table);
	}

	void statistics() const {
		if (size == 0) {
			std::cout << "table is empty!" << std::endl;
			return;
		}
		size_t sum = 0, max = 0, collision = 0, non_empty = 0;
		for (const auto& bucket : table) {
			if (!bucket.empty()) {
				sum += bucket.size();
				non_empty++;
				if (max < bucket.size()) {
					max = bucket.size();
				}
				if (bucket.size() > 1) {
					collision += bucket.size() - 1;
				}
			}

		}

		double average = static_cast<double>(sum) / non_empty;
		std::cout << "average size of chains: " << average << std::endl;
		std::cout << "max size of chains: " << max << std::endl;
		std::cout << "collisions in chains: " << collision << std::endl;

	}

	size_t getSize() const { return size; }
	bool isEmpty() const { return size == 0; }
};