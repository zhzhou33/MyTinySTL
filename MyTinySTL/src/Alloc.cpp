/*
 * @Author: zhzhou33
 * @Date: 2022-05-30 15:13:50
 * @LastEditors: zhzhou33
 * @LastEditTime: 2022-06-09 17:14:53
 */
#include "../include/Alloc.h"

namespace MyTinySTL
{
    char *alloc::start_free = 0;
    char *alloc::end_free = 0;
    size_t alloc::heap_size = 0;
    alloc::obj *alloc::free_list[alloc::ENFreeLists::NFREELISTS] =
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    void *alloc::allocate(size_t bytes)
    {
        if (bytes > EMaxBytes::MAXBYTES)
            return malloc(bytes);
        size_t index = FREELIST_INDEX(bytes);
        obj *list = free_list[index];
        if (list)
        {
            free_list[index] = list->next;
            return list;
        }
        return refill(ROUND_UP(bytes));
    }

    void alloc::deallocate(void *ptr, size_t bytes)
    {
        if (bytes > EMaxBytes::MAXBYTES)
            free(ptr);
        else
        {
            //头插法回收空间
            size_t index = FREELIST_INDEX(bytes);
            obj *node = static_cast<obj *>(ptr);
            node->next = free_list[index];
            free_list[index] = node;
        }
    }
    // 不常用
    void *alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz)
    {
        deallocate(ptr, old_sz);
        ptr = allocate(new_sz);
        return ptr;
    }

    void *alloc::refill(size_t bytes)
    {
        size_t nobjs = ENObjs::NOBJS;
        char *chunk = chunk_alloc(bytes, nobjs);
        if (nobjs == 1)
            return chunk;
        //需要改变的是数组链表头指针所指向,因此采用二级指针
        obj **my_free_list = 0;
        obj *result = 0;
        obj *current = 0, *next = 0;
        my_free_list = free_list + FREELIST_INDEX(bytes);
        result = (obj *)(chunk);
        *my_free_list = next = (obj *)(chunk + bytes);
        for (int i = 1;; i++)
        {
            current = next;
            next = (obj *)((char *)next + bytes);
            if (nobjs - 1 == i)
            {
                current->next = 0;
                break;
            }
            else
                current->next = next;
        }
        return result;
    }

    char *alloc::chunk_alloc(size_t bytes, size_t &nobjs)
    {
        char *result = 0;
        size_t total_bytes = bytes * nobjs;
        size_t bytes_remain = end_free - start_free;

        if (bytes_remain >= total_bytes)
        {
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else if (bytes_remain >= bytes)
        {
            nobjs = bytes_remain / bytes;
            total_bytes = nobjs * bytes;
            result = start_free;
            start_free += total_bytes;
            return result;
        }
        else
        {
            size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);
            if (bytes_remain > 0)
            {
                obj **my_free_list = free_list + FREELIST_INDEX(bytes_remain);
                ((obj *)start_free)->next = *my_free_list;
                *my_free_list = (obj *)start_free;
            }
            start_free = (char *)malloc(bytes_to_get);
            if (!start_free)
            {
                obj **my_free_list = 0, *p = 0;
                for (int i = bytes; i <= EMaxBytes::MAXBYTES; i += EAlign::ALIGN)
                {
                    my_free_list = free_list + FREELIST_INDEX(i);
                    p = *my_free_list;
                    if (p)
                    {
                        *my_free_list = p->next;
                        start_free = (char *)p;
                        end_free = start_free + i;
                        return chunk_alloc(bytes, nobjs);
                    }
                }
                end_free = 0;
                start_free = (char *)alloc::allocate(bytes_to_get);
            }
            heap_size += bytes_to_get;
            end_free = start_free + bytes_to_get;
            return chunk_alloc(bytes, nobjs);
        }
    }
}