#include "./include/Vector.h"
#include "./include/Stack.h"
#include "./include/Deque.h"
#include <iostream>
using namespace MyTinySTL;

int count = 0;

class A
{
public:
	A(int aa = 0):a(aa){}
	void show()
	{
		std::cout << "A::show()" << std::endl;
	}
	~A()
	{
		std::cout << "~A()\t";
		count++;
		std::cout << "count = " << count << std::endl;
	}
private:
	int a;
};

int main()
{
	deque<A> dp;
	A a(100);
	dp.push_front(a);
	for (int i = 0; i < 65; i++) {
		A aa(i);
		dp.push_back(aa);
	}
	return 0;
}