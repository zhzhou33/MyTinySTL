/*
 * @Author: zhzhou33
 * @Date: 2022-06-10 17:39:56
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-06-10 17:52:51
 */
#pragma once
#include "Vector.h"
namespace MyTinySTL
{
    template <class T, class Container = MyTinySTL::vector<T>>
    class stack
    {
    public:
        using value_type = typename Container::value_type;
        using reference = typename Container::reference;
        using size_type = typename Container::size_type;
        using container_type = Container;

    private:
        container_type container_;

    public:
        explicit stack(const container_type &ctnr = container_type()) : container_(ctnr) {}

        bool empty() const { return container_.empty(); };
        size_type size() const { return container_.size(); };
        value_type &top() { return container_.back(); }
        const value_type &top() const { return container_.back(); }
        void push(const value_type &val) { container_.push_back(val); }
        void pop() { container_.pop_back(); }
        void swap(stack &x)
        {
        }
    };

    template <class T, class Container>
    bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ == rhs.container_;
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
    {
        return lhs.container_ != rhs.container_;
    }

} // namespace MyTinySTL
