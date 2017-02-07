//============================================================================
// Name        : Ex1.cpp
// Author      : 
// Version     :
// Copyright   : ASP Ltd.
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <atomic>
#include <cassert>
#include <chrono>
#include <iostream>
#include <thread>


std::atomic<bool> x,y;
std::atomic<int> z;

void write_x()
{
	x.store(true,std::memory_order_release);
}


void write_y()
{
	y.store(true,std::memory_order_release);
}


void read_x_then_y()
{
	while(!x.load(std::memory_order_acquire));
	if(y.load(std::memory_order_acquire))
		++z;
}


void read_y_then_x()
{
	while(!y.load(std::memory_order_acquire));
	if(x.load(std::memory_order_acquire))
		++z;
}


int do_main()
{
x=false;
y=false;
z=0;
std::thread a(write_x);
std::thread b(write_y);
std::thread c(read_x_then_y);
std::thread d(read_y_then_x);
a.join();
b.join();
c.join();
d.join();
assert(z.load()!=0);
return z;
}


int main()
{
	for (int i{0u}; i < 1'000; ++i)
		do_main();
	std::cout << "Bye bye\n";
}
