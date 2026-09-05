# DAG DP + Modified Topological Sort Notes

These notes are prepared from your pasted chat content. The original ChatGPT private link could not be opened because `chatgpt.com` is blocked by saved Browser permission, so I used the pasted attachment text safely.

## Table of Contents

- [Lecture 1. CSES Game Routes — Forward DP and Reverse DAG DP](#lecture-1-cses-game-routes--forward-dp-and-reverse-dag-dp)
- [Lecture 2. Codeforces 909E — Coprocessor](#lecture-2-codeforces-909e--coprocessor)
- [Lecture 3. Codeforces 1572A — Book](#lecture-3-codeforces-1572a--book)
- [Master Takeaways](#master-takeaways)

## Lecture 1. CSES Game Routes — Forward DP and Reverse DAG DP

Problem Link: [Open on CSES](https://cses.fi/problemset/task/1681/)

Related Problem: [CSES Longest Flight Route](https://cses.fi/problemset/task/1680/)

### Problem

Given a directed acyclic graph with levels `1` to `n`, count the number of different routes from level `1` to level `n`.

Return the answer modulo `1e9 + 7`.

### Doubt You Asked

Can we define DP in reverse direction like:

```cpp
dp[u] = number of ways from u to n
```

Yes, this is correct. Only the base case changes.

### Key Observation

- Forward DP asks: "How many ways can I reach this node from `1`?"
- Reverse DP asks: "How many ways can I reach `n` from this node?"
- Both are valid on a DAG because topological order gives dependency order.

### Approach 1: Forward DP

```cpp
// DP State:
// dp[u] = number of ways to reach node u from node 1
//
// Revision hint:
// Start from source because source has exactly 1 way to reach itself.
// Push source contribution forward through outgoing edges.

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        indegree[b]++;
    }

    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> topo;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        topo.push_back(node);

        for (int child : adj[node])
        {
            indegree[child]--;

            if (indegree[child] == 0)
            {
                q.push(child);
            }
        }
    }

    vector<int> dp(n + 1, 0);
    dp[1] = 1;

    for (int node : topo)
    {
        for (int child : adj[node])
        {
            // Transition:
            // ways to reach child += ways to reach current node
            dp[child] = (dp[child] + dp[node]) % MOD;
        }
    }

    cout << dp[n] << '\n';

    return 0;
}
```

### Complexity

- Time Complexity: `O(n + m)`
- Space Complexity: `O(n + m)`

### Approach 2: Reverse DP

```cpp
// DP State:
// dp[u] = number of ways to go from node u to node n
//
// Base Case:
// dp[n] = 1
//
// Revision hint:
// Destination to destination has exactly 1 empty path.
// If dp[n] is kept 0, every previous node will also become 0.

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        indegree[b]++;
    }

    queue<int> q;

    for (int i = 1; i <= n; i++)
    {
        if (indegree[i] == 0)
        {
            q.push(i);
        }
    }

    vector<int> topo;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        topo.push_back(node);

        for (int child : adj[node])
        {
            indegree[child]--;

            if (indegree[child] == 0)
            {
                q.push(child);
            }
        }
    }

    vector<int> dp(n + 1, 0);
    dp[n] = 1;

    reverse(topo.begin(), topo.end());

    for (int node : topo)
    {
        for (int child : adj[node])
        {
            // Transition:
            // ways from node to n += ways from child to n
            dp[node] = (dp[node] + dp[child]) % MOD;
        }
    }

    cout << dp[1] << '\n';

    return 0;
}
```

### Complexity

- Time Complexity: `O(n + m)`
- Space Complexity: `O(n + m)`

### Example

```text
1 -> 2 -> 4
1 -> 3 -> 4
```

Reverse DP:

```text
dp[4] = 1
dp[3] = dp[4] = 1
dp[2] = dp[4] = 1
dp[1] = dp[2] + dp[3] = 2
```

### Relation With Longest Flight Route

```cpp
// Longest Flight Route:
// dp[u] = longest path length from u to n
// dp[n] = 1
// dp[u] = max(dp[u], dp[v] + 1)

// Game Routes:
// dp[u] = number of paths from u to n
// dp[n] = 1
// dp[u] += dp[v]
```

### Possible Doubts

- Why is `dp[n] = 1` in reverse DP? Because destination to destination has one empty path.
- Why do we reverse topological order? Because `dp[u]` depends on `dp[child]`.
- Can forward and reverse both work? Yes, if the DP state and base case are correct.

### What You Learned

- Same DAG can be solved with forward DP or reverse DP.
- DP meaning decides the base case.
- In DAG DP, operation changes by problem: `sum`, `max`, `min`, etc.

## Lecture 2. Codeforces 909E — Coprocessor

Problem Link: [Open on Codeforces](https://codeforces.com/problemset/problem/909/E)

### Problem

You are given a dependency DAG of tasks.

- Type `0` task runs on the main processor.
- Type `1` task runs on the coprocessor.
- In one coprocessor call, you can execute any number of available coprocessor tasks.

Find the minimum number of coprocessor calls needed to finish all tasks.

### Doubt You Asked

You asked for a hint.

### Key Observation

This is not normal DP. It is a modified Kahn's Algorithm with greedy ordering.

Always process all available type `0` tasks first because they are free and may unlock more type `1` tasks before starting a coprocessor call.

### Approach

- Maintain two queues:
  - `cpu` for available type `0` tasks.
  - `cop` for available type `1` tasks.
- Process all `cpu` tasks first.
- If `cop` has tasks, increase answer by `1`.
- Process all currently and newly available coprocessor tasks in the same coprocessor call.

### C++ Code

```cpp
// Pattern:
// Modified Kahn's Algorithm with two queues.
//
// Revision hint:
// Type 0 tasks are free, so always process them before using coprocessor.
// Every time we start processing type 1 tasks, answer increases by 1.

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> type(n);

    for (int i = 0; i < n; i++)
    {
        cin >> type[i];
    }

    vector<vector<int>> adj(n);
    vector<int> indegree(n, 0);

    for (int i = 0; i < m; i++)
    {
        int t1, t2;
        cin >> t1 >> t2;

        // t1 depends on t2.
        // So t2 must be completed before t1.
        // Edge direction: t2 -> t1
        adj[t2].push_back(t1);
        indegree[t1]++;
    }

    queue<int> cpu;
    queue<int> cop;

    for (int i = 0; i < n; i++)
    {
        if (indegree[i] == 0)
        {
            if (type[i] == 0)
            {
                cpu.push(i);
            }
            else
            {
                cop.push(i);
            }
        }
    }

    auto unlock = [&](int node)
    {
        for (int child : adj[node])
        {
            indegree[child]--;

            if (indegree[child] == 0)
            {
                if (type[child] == 0)
                {
                    cpu.push(child);
                }
                else
                {
                    cop.push(child);
                }
            }
        }
    };

    int answer = 0;

    while (!cpu.empty() || !cop.empty())
    {
        while (!cpu.empty())
        {
            int node = cpu.front();
            cpu.pop();

            // Free tasks should be finished before a coprocessor call.
            unlock(node);
        }

        if (cop.empty())
        {
            continue;
        }

        answer++;

        while (!cop.empty())
        {
            int node = cop.front();
            cop.pop();

            // All coprocessor tasks available through coprocessor-only chains
            // can be included in the same coprocessor call.
            unlock(node);
        }
    }

    cout << answer << '\n';

    return 0;
}
```

### Complexity

- Time Complexity: `O(n + m)`
- Space Complexity: `O(n + m)`

### Possible Doubts

- Why process type `0` first? Because it costs no coprocessor call and may unlock more type `1` tasks.
- Why can many type `1` tasks be processed together? One coprocessor call can include a set of available coprocessor tasks.
- Why not simple topological sort? We need minimum coprocessor calls, so available nodes must be separated by processor type.

### What You Learned

- Kahn's Algorithm can be customized using multiple queues.
- Greedy ordering matters when some operations are free.
- Edge direction is very important: `T1 depends on T2` means `T2 -> T1`.

## Lecture 3. Codeforces 1572A — Book

Problem Link: [Open on Codeforces](https://codeforces.com/problemset/problem/1572/A)

### Problem

You have a book with `n` chapters. Each chapter may require some other chapters before it can be understood.

You read the book from chapter `1` to chapter `n` repeatedly.

Find the minimum number of readings needed to understand every chapter. If it is impossible because of a cycle, print `-1`.

### Doubt You Asked

You asked to explain and implement it.

### Key Observation

Normal topological sort only tells whether an order exists.

Here, we also need:

```cpp
day[u] = minimum reading/pass in which chapter u can be understood
```

### DP State

```cpp
day[u] = minimum pass number when chapter u can be understood
```

Initial value:

```cpp
day[i] = 1;
```

If a chapter has no prerequisites, it can be understood in the first reading.

### Transition

For every edge:

```cpp
u -> v
```

It means chapter `u` must be understood before chapter `v`.

Two cases:

```cpp
if (u < v)
{
    // u comes before v in the book.
    // v can be understood in the same reading pass.
    day[v] = max(day[v], day[u]);
}
else
{
    // u comes after v in the book.
    // v has already been crossed in this pass, so next pass is needed.
    day[v] = max(day[v], day[u] + 1);
}
```

### C++ Code

```cpp
// Pattern:
// Kahn's Algorithm + DP on DAG.
//
// DP State:
// day[u] = minimum reading/pass in which chapter u can be understood
//
// Revision hint:
// If prerequisite index is smaller, same pass is possible.
// If prerequisite index is bigger, next pass is needed.

#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
    {
        int n;
        cin >> n;

        vector<vector<int>> adj(n + 1);
        vector<int> indegree(n + 1, 0);

        for (int chapter = 1; chapter <= n; chapter++)
        {
            int k;
            cin >> k;

            while (k--)
            {
                int prerequisite;
                cin >> prerequisite;

                // prerequisite must be understood before chapter.
                // Edge direction: prerequisite -> chapter
                adj[prerequisite].push_back(chapter);
                indegree[chapter]++;
            }
        }

        queue<int> q;
        vector<int> day(n + 1, 1);

        for (int i = 1; i <= n; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }

        int processed = 0;
        int answer = 1;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            processed++;
            answer = max(answer, day[node]);

            for (int child : adj[node])
            {
                if (node < child)
                {
                    // Prerequisite appears before child in the book.
                    // Same reading pass is possible.
                    day[child] = max(day[child], day[node]);
                }
                else
                {
                    // Prerequisite appears after child in the book.
                    // Child needs the next reading pass.
                    day[child] = max(day[child], day[node] + 1);
                }

                indegree[child]--;

                if (indegree[child] == 0)
                {
                    q.push(child);
                }
            }
        }

        if (processed < n)
        {
            cout << -1 << '\n';
        }
        else
        {
            cout << answer << '\n';
        }
    }

    return 0;
}
```

### Complexity

- Time Complexity: `O(n + total prerequisites)` per test set traversal.
- Space Complexity: `O(n + total prerequisites)`.

### Example

```text
2 -> 1
```

Chapter `1` depends on chapter `2`.

Since `2 > 1`, chapter `1` cannot be understood in the same reading pass.

```text
Day 1: chapter 2
Day 2: chapter 1
Answer = 2
```

### Possible Doubts

- Why `max` in transition? A chapter may have many prerequisites, so it is ready only after the worst/latest prerequisite.
- Why cycle gives `-1`? If prerequisites form a cycle, no chapter in that cycle can ever become fully understood.
- Why compare indices? Reading happens in increasing chapter order during each pass.

### What You Learned

- This is DAG DP with topological sort.
- `day[]` is the DP state.
- Transition depends on edge direction and node indices.

## Master Takeaways

### Reverse DAG DP Template

```cpp
// dp[target] = base case

for (int node : reverse_topo)
{
    for (int child : adj[node])
    {
        // dp[node] = combine(dp[node], dp[child])
    }
}
```

### Forward DAG DP Template

```cpp
// dp[source] = base case

for (int node : topo)
{
    for (int child : adj[node])
    {
        // dp[child] = combine(dp[child], dp[node])
    }
}
```

### Common Transitions

```cpp
// Longest path
dp[child] = max(dp[child], dp[node] + 1);

// Number of paths
dp[child] += dp[node];

// Minimum cost
dp[child] = min(dp[child], dp[node] + cost);

// Book problem
if (node < child)
{
    day[child] = max(day[child], day[node]);
}
else
{
    day[child] = max(day[child], day[node] + 1);
}
```

### Recognition Pattern

Think of `Topo Sort + DP` when the problem has:

- Directed graph with dependencies.
- No cycle, or cycle detection needed.
- Minimum rounds, maximum path, number of ways, or scheduling.
- A transition that depends on edge direction, node type, or node index.
