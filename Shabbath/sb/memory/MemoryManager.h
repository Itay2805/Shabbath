#pragma once

#include <type_traits>
#include <Windows.h>
#include <stack>

class MemoryManager {
public:
	static MemoryManager* Get() {
		static MemoryManager manager;
		return &manager;
	}

private:
	
	// simple, just goes forward
	char* staticMemory;
	char* staticMemoryBase;
	int staticMemorySize;
	int staticMemorySizeHighest = 0;

	// like static memory but has a stack which you can push and pop
	char* randomMemoryBase;
	char* randomMemory;
	int randomMemorySize;
	int randomMemorySizeHighest = 0;
	std::stack<void*> addresses;

	// if set to true it will get more memory when needed
	// on static and random objects
	bool expandingMode;

public:

	MemoryManager(bool expandingMode = false) {
		staticMemorySize = 4 * 1024 * 1024; // 4MB static
		staticMemoryBase = staticMemory = (char*)VirtualAlloc(0, staticMemorySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

		randomMemorySize = 1 * 1024 * 1024 * 1024; // 1GB random
		randomMemoryBase = randomMemory = (char*)VirtualAlloc(0, randomMemorySize, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	}

	void Push() {
		addresses.push(randomMemory);
	}

	void Pop() {
		if(!addresses.empty()) addresses.pop();
	}

	template<class T, typename ... Args>
	T* AllocateRandom(Args... params) {
		if (((randomMemory + sizeof(T)) - randomMemoryBase) > randomMemorySize) {
			throw std::runtime_error("not enough memory!");
		}
		T* t = new (randomMemory) T(std::forward<Args>(params)...);
		randomMemory += sizeof(T);
		if ((randomMemory - randomMemoryBase) > randomMemorySizeHighest) {
			randomMemorySizeHighest = (randomMemory - randomMemoryBase);
		}
		return t;
	}

	template<class T, typename ... Args>
	T* AllocateStatic(Args... params) {
		if (((staticMemory + sizeof(T)) - staticMemoryBase) > staticMemorySize) {
			throw std::runtime_error("not enough memory!");
		}
		T* t = new (staticMemory) T(std::forward<Args>(params)...);
		staticMemory += sizeof(T);
		if ((staticMemory - staticMemoryBase) > staticMemorySizeHighest) {
			staticMemorySizeHighest = (staticMemory - staticMemoryBase);
		}
		return t;
	}

	template<class T>
	T* AllocateStaticArray(int count) {
		if (((staticMemory + sizeof(T) * count) - staticMemoryBase) > staticMemorySize) {
			throw std::runtime_error("not enough memory!");
		}
		T* t = new (staticMemory) T[count];
		staticMemory += sizeof(T) * count;
		if ((staticMemory - staticMemoryBase) > staticMemorySizeHighest) {
			staticMemorySizeHighest = (staticMemory - staticMemoryBase);
		}
		return t;
	}

};