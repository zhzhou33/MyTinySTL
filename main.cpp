/*
 * @Author: zhzhou33
 * @Date: 2022-08-25 13:03:40
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-08-27 19:01:14
 */
#include "./include/Vector.h"
#include "./include/Stack.h"
#include "./include/Queue.h"
#include "./include/List.h"
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
	list<int> l;
	for (int i = 0; i < 10; i++)
		l.push_back(i);
	for (auto iter = l.begin(); iter != l.end(); ++iter)
		std::cout << *iter << std::endl;
	
	return 0;
	
}