/*
 * @Author: zhzhou33
 * @Date: 2022-08-25 13:03:40
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-09-02 10:50:09
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
    A(int aa = 0) :
        a(aa)
    {
    }
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
    vector<int> nums(6);
    for (int i = 0; i < 6; i++)
        nums[i] = i + 1;
    for (auto iter = nums.begin(); iter != nums.end(); ++iter)
    {
        if (iter < nums.end() && (*iter) % 3 == 0)
        {
            nums.erase(iter);
        }
    }
    return 0;
}