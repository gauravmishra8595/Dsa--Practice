#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {

        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);

        for (auto &it : prerequisites)
        {
            adj[it[1]].push_back(it[0]);
            indegree[it[0]]++;
        }

        queue<int> q;

        for (int i = 0; i < numCourses; i++)
        {
            if (indegree[i] == 0)
                q.push(i);
        }

        vector<int> ans;

        while (!q.empty())
        {

            int node = q.front();
            q.pop();

            ans.push_back(node);

            for (auto &nbr : adj[node])
            {

                indegree[nbr]--;

                if (indegree[nbr] == 0)
                    q.push(nbr);
            }
        }

        if (ans.size() == numCourses)
            return ans;

        return {};
    }
};

int main()
{

    Solution obj;

    int numCourses = 4;

    vector<vector<int>> prerequisites = {
        {1, 0},
        {2, 0},
        {3, 1},
        {3, 2}};

    vector<int> result = obj.findOrder(numCourses, prerequisites);

    for (int x : result)
        cout << x << " ";

    return 0;
}

/*

========================================
Problem Statement
========================================

LeetCode 210: Course Schedule II

There are numCourses courses labeled from 0 to numCourses-1.

You are given prerequisites where:

[a, b] means:
To take course a, you must complete course b first.

Return the ordering of courses you should take to finish all courses.

If multiple answers exist, return any valid ordering.

If impossible, return an empty array.

========================================
Example
========================================

Input:

numCourses = 4

prerequisites =
[
 [1,0],
 [2,0],
 [3,1],
 [3,2]
]

Graph:

0 ---> 1 ---> 3
 \
  ---> 2 ---> 3


Output:

[0,1,2,3]

====================================================
Brute Force Approach
====================================================

Idea
----

Generate all possible course orders using permutations.

For every possible ordering:

1. Check whether every prerequisite condition is satisfied.
2. If valid, return that ordering.

This approach tries every possible arrangement.

Pseudo Code
-----------

generate all permutations of courses

for each permutation:

    valid = true

    for each prerequisite:

        if prerequisite course appears after current course

            valid = false

    if valid:

        return permutation


return empty


Complete Brute Force Code
-------------------------

// class Solution {
//
// public:
//
// bool check(vector<int>& order,
//            vector<vector<int>>& prerequisites){
//
//     vector<int> pos(order.size());
//
//     for(int i=0;i<order.size();i++)
//         pos[order[i]]=i;
//
//     for(auto &p: prerequisites){
//
//         if(pos[p[1]] > pos[p[0]])
//             return false;
//     }
//
//     return true;
// }
//
//
// void solve(int index,
//            vector<int>& nums,
//            vector<int>& ans,
//            vector<vector<int>>& prerequisites){
//
//     if(index==nums.size()){
//
//         if(check(nums,prerequisites))
//             ans=nums;
//
//         return;
//     }
//
//     for(int i=index;i<nums.size();i++){
//
//         swap(nums[index],nums[i]);
//
//         solve(index+1,
//               nums,
//               ans,
//               prerequisites);
//
//         swap(nums[index],nums[i]);
//     }
// }
//
//
// vector<int> findOrder(int n,
//                       vector<vector<int>>& prerequisites){
//
//     vector<int> nums(n);
//
//     for(int i=0;i<n;i++)
//         nums[i]=i;
//
//     vector<int> ans;
//
//     solve(0,nums,ans,prerequisites);
//
//     return ans;
// }
//
// };


Time Complexity
---------------

O(V! * E)

Space Complexity
----------------

O(V)


====================================================
Optimal Approach (Topological Sort - Kahn's Algorithm)
====================================================

Observation
-----------

Course dependency forms a directed graph.

A valid course order is a topological ordering.

If every node can be processed in topological order,
then no cycle exists.

If some nodes remain,
a cycle exists and ordering is impossible.


Intuition
---------

Use BFS based topological sorting.

1. Calculate indegree of every course.
2. Courses with indegree 0 have no prerequisites.
3. Take them first.
4. Remove their dependency from other courses.
5. Continue until all courses are processed.


Pseudo Code
-----------

Create adjacency list

Calculate indegree


Push all nodes with indegree 0 into queue


while queue is not empty:

    remove node

    add node to answer

    decrease indegree of neighbours

    if neighbour indegree becomes 0:

        push neighbour


if answer size == number of courses:

    return answer

else:

    return empty


Complete Optimal Code
---------------------

// class Solution {
//
// public:
//
// vector<int> findOrder(int numCourses,
//                       vector<vector<int>>& prerequisites){
//
//     vector<vector<int>> adj(numCourses);
//
//     vector<int> indegree(numCourses,0);
//
//
//     for(auto &it:prerequisites){
//
//         adj[it[1]].push_back(it[0]);
//
//         indegree[it[0]]++;
//     }
//
//
//     queue<int> q;
//
//
//     for(int i=0;i<numCourses;i++){
//
//         if(indegree[i]==0)
//             q.push(i);
//     }
//
//
//     vector<int> ans;
//
//
//     while(!q.empty()){
//
//         int node=q.front();
//         q.pop();
//
//         ans.push_back(node);
//
//
//         for(auto nbr:adj[node]){
//
//             indegree[nbr]--;
//
//             if(indegree[nbr]==0)
//                 q.push(nbr);
//         }
//     }
//
//
//     if(ans.size()==numCourses)
//         return ans;
//
//
//     return {};
// }
//
//};


Time Complexity
---------------

O(V + E)


Space Complexity
----------------

O(V + E)


====================================================
Dry Run With Example
====================================================

Input:

numCourses = 4

prerequisites:

[1,0]
[2,0]
[3,1]
[3,2]


Indegree:

0 -> 0

1 -> 1

2 -> 1

3 -> 2


Queue:

[0]


Remove 0

Answer:

[0]


Decrease:

indegree[1]=0

indegree[2]=0


Queue:

[1,2]


Remove 1

Answer:

[0,1]


Decrease:

indegree[3]=1


Remove 2

Answer:

[0,1,2]


Decrease:

indegree[3]=0


Queue:

[3]


Remove 3


Answer:

[0,1,2,3]


All courses processed.

Return answer.


====================================================
Interview Notes
====================================================

Pattern
-------

Topological Sorting


Key Observation
---------------

Course dependency problems are directed graph problems.

A valid order exists only when the graph is a DAG
(Directed Acyclic Graph).


Common Mistakes
---------------

1. Using wrong edge direction.

   Correct:

   prerequisite -> course


2. Forgetting cycle detection.


3. Returning partial ordering.


4. Confusing LeetCode 207 and 210.

   207:
   Return true/false.

   210:
   Return ordering.


5. Not handling disconnected graphs.


When to use this approach
-------------------------

1. Course scheduling problems.

2. Dependency resolution.

3. Build systems.

4. Package installation order.

5. Task scheduling problems.

*/