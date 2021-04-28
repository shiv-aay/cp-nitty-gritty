# cp-nitty-gritty
> Collection of some unexpected things I came across on my journey of Competitive Programming so far.

* DP through recursion (top down) often takes more time than bottom up.
* Only a 1 D array can be initialized with 0 like this (int a[n] = {0}) in CPP, it doesn't works with 2 D.
  * This is because ```={0}``` means setting the first coulmn and row to 0.
* Adding `ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);` in your `main` function sometimes helps in avoiding unnecessary TLE verdict by online judges.
  * This makes ```cin``` and ```cout``` as fast as ```printf``` and ```scanf``` which reduces time.
* (a - b + m) % m = ((a%m) - (b%m) + **m**) % m
