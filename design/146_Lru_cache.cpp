#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache
{
    int capacity;

    // Doubly Linked List stores {key, value}
    list<pair<int, int>> dll;

    // Maps key to its node in the list
    unordered_map<int, list<pair<int, int>>::iterator> umap;

public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        // Key not present
        if (umap.find(key) == umap.end())
        {
            return -1;
        }

        // Move accessed node to front
        dll.splice(dll.begin(), dll, umap[key]);

        return umap[key]->second;
    }

    void put(int key, int value)
    {
        // If key already exists
        if (get(key) != -1)
        {
            umap[key]->second = value;
            return;
        }

        // Cache is full
        if (dll.size() == capacity)
        {
            int lastKey = dll.back().first;

            dll.pop_back();

            umap.erase(lastKey);
        }

        // Insert new node at front
        dll.push_front({key, value});

        umap[key] = dll.begin();
    }
};

int main()
{
    LRUCache cache(2);

    cache.put(1, 1);

    cache.put(2, 2);

    cout << cache.get(1) << endl; // 1

    cache.put(3, 3); // Evicts key 2

    cout << cache.get(2) << endl; // -1

    cache.put(4, 4); // Evicts key 1

    cout << cache.get(1) << endl; // -1

    cout << cache.get(3) << endl; // 3

    cout << cache.get(4) << endl; // 4

    return 0;
}

/*
=========================================
LeetCode 146 : LRU Cache
=========================================

Problem:

Design a data structure that follows
the Least Recently Used (LRU) cache policy.

Support two operations:

1. get(key)
2. put(key, value)

Both operations must run in O(1).

-----------------------------------------
Example
-----------------------------------------

LRUCache cache(2);

cache.put(1,1);

cache.put(2,2);

cache.get(1);      // returns 1

cache.put(3,3);    // evicts key 2

cache.get(2);      // returns -1

cache.put(4,4);    // evicts key 1

cache.get(1);      // returns -1

cache.get(3);      // returns 3

cache.get(4);      // returns 4

=========================================
Brute Force Approach
=========================================

Idea:

Store elements in an array or vector.

Whenever get() is called,

search linearly.

Whenever put() is called,

search for the key.

If cache is full,

remove the least recently used element
by maintaining usage order manually.

Time Complexity:

get()  -> O(N)

put()  -> O(N)

Not acceptable.

=========================================
Optimal Approach
=========================================

Use two data structures:

1. Doubly Linked List

Stores cache entries in order of usage.

Front = Most Recently Used (MRU)

Back = Least Recently Used (LRU)

-----------------------------------------

2. Hash Map

Maps

key -> iterator of list node

Allows O(1) lookup.

=========================================
Operations
=========================================

get(key)

1. If key doesn't exist

   return -1

2. Move node to front

3. Return value

-----------------------------------------

put(key,value)

If key already exists

    Move it to front

    Update value

Else

    If cache is full

        Remove node from back

        Remove key from hash map

    Insert new node at front

    Store iterator in hash map

=========================================
Why splice() ?
=========================================

dll.splice(dll.begin(), dll, umap[key]);

Moves the existing node directly to the
front of the list.

No copying.

No new allocation.

Time Complexity = O(1)

=========================================
Dry Run
=========================================

Capacity = 2

put(1,1)

List:

(1)

-----------------------------------------

put(2,2)

List:

(2)
(1)

-----------------------------------------

get(1)

Move 1 to front

List:

(1)
(2)

-----------------------------------------

put(3,3)

Cache full

Remove back

Remove (2)

Insert (3)

List:

(3)
(1)

-----------------------------------------

put(4,4)

Remove back

Remove (1)

Insert (4)

List:

(4)
(3)

=========================================
Time Complexity
=========================================

get()

Hash Map lookup : O(1)

splice() : O(1)

Overall : O(1)

-----------------------------------------

put()

Hash Map lookup : O(1)

Insertion : O(1)

Deletion : O(1)

Overall : O(1)

=========================================
Space Complexity
=========================================

Doubly Linked List : O(capacity)

Hash Map : O(capacity)

Overall : O(capacity)

=========================================
Interview Tip
=========================================

Whenever an interview asks for:

- O(1) search
- O(1) insertion
- O(1) deletion
- Maintain usage/order

Think:

Hash Map + Doubly Linked List

This is the standard pattern for
implementing an LRU Cache.

=========================================
*/