#pragma once

#include <type_traits>

namespace StupidLittle
{
    template <typename TData, typename TSize, TSize TCapacity>
    class Queue
    {
    public:
        Queue()
        {
            static_assert(std::is_unsigned<TSize>::value, "Queue<TData, TSize, TCapacity>: only unsigned integral types are allowed as TSize");
        }

        ~Queue() {}

        void enqueue(TData value)
        {
            data[head] = value;

            // increment head index and wrap around if necessary:
            head = ++head % capacity;

            if (count < capacity)
            {
                count++;
            }
            else // implies count >= capacity, but in practice should never be count > capacity
            {
                // queue is full, but we have added a new element and incremented the head index,
                // so we want to increment the tail index to point to the oldest element still left in the queue.
                // increment tail index and wrap around if necessary:
                tail = ++tail % capacity;

                // set the overflow flag as an element has been added to a full queue:
                overflow = true;
            }
        }

        TData dequeue()
        {
            TData dequeuedValue{ data[tail] };

            if (count > 0)
            {
                // increment tail index and wrap around if necessary:
                tail = ++tail % capacity;
                count--;

                // clear the overflow flag as an element has been dequeued:
                overflow = false;
            }

            return dequeuedValue;
        }

        inline void clear()
        {
            head = 0;
            tail = 0;
            count = 0;
        }

        inline TSize getCount() { return count; }
        inline bool isEmpty() { return count == 0; }
        inline bool isFull() { return count == capacity; }
        inline bool isOverflown() { return overflow; }

    private:
        TData data[TCapacity]{};
        TSize capacity{ TCapacity };
        TSize head{ 0 };
        TSize tail{ 0 };
        TSize count{ 0 };
        bool overflow{ false };
    };
} // namespace StupidLittle