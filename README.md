# cp-nitty-gritty
> Collection of some unexpected things I came across on my journey of Competitive Programming so far.

* DP through recursion (top down) often takes more time than bottom up.
  * In DP through recusrsion, keep unvisited states in array initialsed to something which never occurs in answer set (and not simply to 0).
* Only a 1 D array can be initialized with 0 like this (int a[n] = {0}) in CPP, it doesn't works with 2 D.
  * This is because ```= {0}``` means a[0][0] = 0.
* Adding `ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);` in your `main` function sometimes helps in avoiding unnecessary TLE verdict by online judges.
  * This makes ```cin``` and ```cout``` as fast as ```printf``` and ```scanf``` which reduces time.
* (a - b + m) % m = ((a%m) - (b%m) + **m**) % m
* We can use memset() to set all values of integer array to 0 or -1 only. Doesnot work with other values like 1, 5, 132 etc..
  * Because memset works byte by byte.
* vector<int> v[N] -> an array of N different vector<int> objects, can be used as a 2D array.
  * For weighted graph implementation as Adjacency list, we use `vector<pair<int, int> > adj[V];`, where V is the Maximum possible vertex.
* When you are given expressions in CP problems, try to simplify it by rearranging before jumping into the problem.
* If you want the `priority_queue` in decreasing order, *that is first element largest then smaller and smaller*, in custom comparator function use `return a < b` which is in contrast to what we do in vectors.
* For P and N, P % N must be a multiple of their common factor.
* `stringstream ss(s)` is used in cpp for easy tokenization of string s, just like python.
* While giving custom_sort() function for sort(), the function has to be decisive otherwise it may end up in an infinite loop giving RE. That is for any element i, if custom_sort(a[i] , b[i]) is `true` custom_sort(b[i] , a[i]) must be `false` and vice versa.
  * Beacuse std::sort() is not stable sort.
