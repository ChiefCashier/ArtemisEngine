#pragma once
#include <iostream>
#include <memory>

class MemoryTest
{
public:

	MemoryTest();
	~MemoryTest();

	void asd(std::shared_ptr<MemoryTest> ptr);

private:

};

MemoryTest::MemoryTest()
{
	std::cout << "ctor" << std::endl;
}

MemoryTest::~MemoryTest()
{
	std::cout << "dtor" << std::endl;
}

void MemoryTest::asd(std::shared_ptr<MemoryTest> ptr)
{
	std::cout << ptr.use_count() << std::endl;
}