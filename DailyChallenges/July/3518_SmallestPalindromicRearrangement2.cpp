#include <bits/stdc++.h>
using namespace std;
class Solution {
    static constexpr long long LIM = 1000001LL;
    long long cappedComb(int n, int r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);
        __int128 ans = 1;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n - r + i) / i;
            if (ans >= LIM)
                return LIM;
        }
        return (long long)ans;
    }
    long long countWays(vector<int>& half) {
        int total = 0;
        for (int x : half)
            total += x;
        long long ans = 1;
        int remaining = total;
        for (int x : half) {
            if (x == 0)
                continue;
            ans = min(LIM, ans * cappedComb(remaining, x));
            remaining -= x;
            if (ans >= LIM)
                return LIM;
        }
        return ans;
    }
public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s)
            freq[c - 'a']++;
        vector<int> half(26, 0);
        string middle = "";
        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2)
                middle.push_back(char('a' + i));
        }
        if (countWays(half) < k)
            return "";
        string left = "";
        int n = s.size() / 2;
        for (int pos = 0; pos < n; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0)
                    continue;
                half[c]--;
                long long ways = countWays(half);
                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                } else {
                    k -= ways;
                    half[c]++;
                }
            }
        }
        string right = left;
        reverse(right.begin(), right.end());
        return left + middle + right;
    }
};
int main() {
    Solution obj;
    cout << obj.smallestPalindrome("abba", 2) << "\n";
    cout << obj.smallestPalindrome("aa", 2) << "\n";
    cout << obj.smallestPalindrome("bacab", 1) << "\n";
    return 0;
}
/*
====================================================
Problem Statement
====================================================
You are given a palindromic string s and an integer k.
A palindromic rearrangement is a palindrome formed by rearranging
the characters of s.
Return the k-th lexicographically smallest distinct palindromic
rearrangement.
If fewer than k palindromic rearrangements exist, return "".
====================================================
Example
====================================================
Input:
s = "abba"
k = 2
Possible palindromes:
1. abba
2. baab
Output:
baab
====================================================
Brute Force Approach
====================================================
Idea
----
Generate every permutation of the string.
For every permutation:
1. Check if it is a palindrome.
2. Store valid palindromes.
3. Remove duplicates.
4. Sort them.
5. Return kth.
This approach works only for very small strings because
number of permutations grows as n!.
----------------------------------------------------
Pseudo Code
----------------------------------------------------
generate all permutations of s
for every permutation:
    if permutation is palindrome:
        store it
remove duplicates
sort stored palindromes
if k > number of palindromes:
    return ""
return kth palindrome
----------------------------------------------------
Complete Brute Force Code
----------------------------------------------------
class Solution {
public:
string smallestPalindrome(string s,int k){
    set<string> st;
    sort(s.begin(),s.end());
    do{
        bool ok=true;
        int i=0;
        int j=s.size()-1;
        while(i<j){
            if(s[i]!=s[j]){
                ok=false;
                break;
            }
            i++;
            j--;
        }
        if(ok)
            st.insert(s);
    }while(next_permutation(s.begin(),s.end()));
    if(k>st.size())
        return "";
    auto it=st.begin();
    advance(it,k-1);
    return *it;
}
};
----------------------------------------------------
Time Complexity
----------------------------------------------------
Generating permutations:
O(n!)
Palindrome checking:
O(n)
Overall:
O(n * n!)
----------------------------------------------------
Space Complexity
----------------------------------------------------
O(n! * n)
====================================================
Optimal Approach
====================================================
Observation
-----------
A palindrome is completely determined by its left half.
Example:
abc | cba
If we know:
left half = abc
right half is automatically:
cba
So instead of generating full permutations,
we only generate permutations of half.
----------------------------------------------------
Intuition
----------------------------------------------------
1. Count frequency of characters.
2. Take half of every frequency.
3. Find kth lexicographical arrangement of this half.
4. Mirror it.
5. Add middle character if required.
To find kth arrangement:
Try every character from 'a' to 'z'.
Calculate how many arrangements are possible after choosing it.
If count >= k:
keep it.
Otherwise:
skip these arrangements and reduce k.
----------------------------------------------------
Pseudo Code
----------------------------------------------------
count frequency
half[i] = frequency[i] / 2
find middle character
if number of half arrangements < k:
    return ""
left = ""
repeat for every position:
    try characters from a-z
        place character temporarily
        calculate remaining arrangements
        if arrangements >= k:
            keep character
            break
        else:
            k -= arrangements
            restore character
right = reverse(left)
return left + middle + right
----------------------------------------------------
Complete Optimal Code (Revision)
----------------------------------------------------
class Solution {
    static constexpr long long LIM = 1000001;
    long long cappedComb(int n,int r){
        if(r<0 || r>n)
            return 0;
        r=min(r,n-r);
        __int128 ans=1;
        for(int i=1;i<=r;i++){
            ans=ans*(n-r+i)/i;
            if(ans>=LIM)
                return LIM;
        }
        return ans;
    }
    long long countWays(vector<int>&half){
        int total=0;
        for(int x:half)
            total+=x;
        long long ans=1;
        int rem=total;
        for(int x:half){
            if(x==0)
                continue;
            ans=min(LIM,ans*cappedComb(rem,x));
            rem-=x;
        }
        return ans;
    }
public:
string smallestPalindrome(string s,int k){
    vector<int> freq(26);
    for(char c:s)
        freq[c-'a']++;
    vector<int> half(26);
    string mid="";
    for(int i=0;i<26;i++){
        half[i]=freq[i]/2;
        if(freq[i]&1)
            mid+=char('a'+i);
    }
    if(countWays(half)<k)
        return "";
    string left="";
    for(int i=0;i<s.size()/2;i++){
        for(int c=0;c<26;c++){
            if(!half[c])
                continue;
            half[c]--;
            long long ways=countWays(half);
            if(ways>=k){
                left+=char('a'+c);
                break;
            }
            k-=ways;
            half[c]++;
        }
    }
    string right=left;
    reverse(right.begin(),right.end());
    return left+mid+right;
}
};
----------------------------------------------------
Time Complexity
----------------------------------------------------
For every position:
26 characters are tried.
Counting is done using 26 frequencies.
Complexity:
O(26 * n * 26)
Since alphabet size is constant:
O(n)
----------------------------------------------------
Space Complexity
----------------------------------------------------
O(26)
====================================================
Dry Run
====================================================
Example:
s = "abba"
k = 2
Frequency:
a = 2
b = 2
Half:
a = 1
b = 1
Possible left halves:
ab
ba
Position 1:
Try 'a'
Remaining:
b
Ways = 1
Since:
1 < k
Skip it.
Update:
k = 2 - 1 = 1
Try 'b'
Ways = 1
Keep b.
left = "b"
Remaining half:
a
left becomes:
"ba"
Reverse:
"ab"
Answer:
"baab"
====================================================
Interview Notes
====================================================
Pattern
-------
Greedy + Combinatorics
K-th Lexicographical Construction
----------------------------------------------------
Key Observation
---------------
Palindrome is decided by only half of its characters.
----------------------------------------------------
Common Mistakes
---------------
1. Generating complete permutations.
2. Ignoring duplicate characters.
3. Integer overflow while calculating combinations.
4. Not restoring frequencies after trying a character.
5. Forgetting that the second half is fixed.
----------------------------------------------------
When to use this approach
-------------------------
Use this pattern when:
- Need kth lexicographical arrangement.
- Total permutations are huge.
- Duplicate characters exist.
- Arrangement has a symmetric structure.
- Counting permutations is easier than generating them.
====================================================
*/