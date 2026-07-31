# Arrays Part 2: Medium Problems

Use this header for all C++ snippets:

```cpp
#include <bits/stdc++.h>
using namespace std;
```

## 15. Two Sum

### Problem

Given an array and a target, find two indices whose values add up to the target.

### Brute Force 1: Check All Pairs
```cpp
vector<int> twoSumBrute(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
              if(i==j)continue;//because we cannot take same index element twice
            if (arr[i] + arr[j] == target) return {i, j};
        }
    }
    return {-1, -1};
}
```
Time Complexity: O(n²)  
Space Complexity: O(1)


### Brute Force 2: Check All Pairs

```cpp
vector<int> twoSumBrute(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] + arr[j] == target) return {i, j};
        }
    }
    return {-1, -1};
}
```

Time Complexity:  slightly less thanO(n²)  
Space Complexity: O(1)

### Better: Hash Map

For each element, check if `target - arr[i]` was seen before.

```cpp
vector<int> twoSumBetter(vector<int>& arr, int target) {
    unordered_map<int, int> mp;

    for (int i = 0; i < arr.size(); i++) {
        int need = target - arr[i];
        if (mp.count(need)) return {mp[need], i};
        mp[arr[i]] = i;
    }
    return {-1, -1};
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

### Optimal for Yes/No Variant: Sort + Two Pointers

If only `YES/NO` is needed, sorting avoids hash space.

```cpp
bool twoSumOptimalYesNo(vector<int> arr, int target) {
    sort(arr.begin(), arr.end());
    int left = 0, right = arr.size() - 1;

    while (left < right) {
        int sum = arr[left] + arr[right];
        if (sum == target) return true;
        if (sum < target) left++;
        else right--;
    }
    return false;
}
```

Time Complexity: O(n log n)  
Space Complexity: O(1), ignoring sorting recursion
### Optimal for Yes/No  with index of two values Variant: Sort + Two Pointers

If only `YES/NO`   is needed, sorting avoids hash space.

```cpp
pair< int ,int> twoSumOptimalYesNo(vector<int> arr, int target) {
    vector<pair< int ,int>>arr1;
    for( int i=0; i<n ;i++){
         arr1.push_back({arr[i],i});
    }
    sort(arr1.begin(), arr1.end());
    int left = 0, right = arr1.size() - 1;

    while (left < right) {
        int sum = arr1[left].first + arr1[right].   first;
        if (sum == target) return  {arr1[left].second , arr1[right].second};
        if (sum < target) left++;
        else right--;
    }
    return {-1, -1};
}
```

Time Complexity: O(n log n)  
Space Complexity: O(1), ignoring sorting recursion

## Count all index pairs (i, j) where i < j (Most Common)

Use a hash map of frequencies.
```cpp
int countPairs(vector<int>& nums, int target) {
    unordered_map<int, int> freq;
    int ans = 0;

    for (int x : nums) {
        int need = target - x;

        if (freq.count(need))
            ans += freq[need];

        freq[x]++;
    }

    return ans;
}

```



## 16. Sort an Array of 0s, 1s and 2s

### Problem

Sort an array containing only `0`, `1`, and `2`.

### Brute Force: Sorting

```cpp
void sortColorsBrute(vector<int>& arr) {
    sort(arr.begin(), arr.end());
}
```

Time Complexity: O(n log n)  
Space Complexity: O(1)

### Better: Count 0s, 1s and 2s

```cpp
void sortColorsBetter(vector<int>& arr) {
    int count0 = 0, count1 = 0, count2 = 0;
    for (int x : arr) {
        if (x == 0) count0++;
        else if (x == 1) count1++;
        else count2++;
    }

    int index = 0;
    while (count0--) arr[index++] = 0;
    while (count1--) arr[index++] = 1;
    while (count2--) arr[index++] = 2;
}
```

Time Complexity: O(2n)  
Space Complexity: O(1)

### Optimal: Dutch National Flag

Maintain three regions: `0`s, `1`s, and unknown values.
everything from 0 to low-1   will store 0's
everything from low to mid -1   will store 1
everything from high+1 to end  will store 2's
from 0 to mid-1 is sorted 
from high+1 to n-1 is sorted
unsoted portion is mid to high isi pr  hume focus krna hai

```cpp
void sortColorsOptimal(vector<int>& arr) {
    int low = 0, mid = 0, high = arr.size() - 1;

    while (mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        } else if (arr[mid] == 1) {
            mid++;
        } else {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 17. Majority Element Greater than n/2

### Problem

Find the element that appears more than `n/2` times. If no such element exists, return `-1`.

### Brute Force: Count Each Element

```cpp
int majorityN2Brute(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i]) count++;
        }
        if (count > n / 2) return arr[i];
    }
    return -1;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Better: Hash Map

```cpp
int majorityN2Better(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) {
        freq[x]++;
        if (freq[x] > arr.size() / 2) return x;
    }
    return -1;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

### Optimal: Moore's Voting Algorithm

Cancel different elements. Verify the candidate at the end.

```cpp
int majorityN2Optimal(vector<int>& arr) {
    int candidate = 0;
    int count = 0;

    for (int x : arr) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            count++;
        } else {
            count--;
        }
    }
    //if there exists a majority elememnt it would be condidae so check for condidate frequency

    int freq = 0;
    for (int x : arr) {
        if (x == candidate) freq++;
    }
    return freq > arr.size() / 2 ? candidate : -1;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 18. Maximum Subarray Sum

### Problem

Find the maximum possible sum of a contiguous subarray.

### Brute Force: All Subarrays

```cpp
long long maxSubarrayBrute(vector<int>& arr) {
    long long maxi = LLONG_MIN;

    for (int i = 0; i < arr.size(); i++) {
        long long sum = 0;
        for (int j = i; j < arr.size(); j++) {
            sum += arr[j];
            maxi = max(maxi, sum);
        }
    }
    return maxi;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Kadane's Algorithm

If current sum becomes negative, drop it and start fresh.

```cpp
long long maxSubarrayOptimal(vector<int>& arr) {
    long long sum = 0;
    long long maxi = LLONG_MIN;

    for (int x : arr) {
        sum += x;
        maxi = max(maxi, sum);

        if (sum < 0) sum = 0;
    }
    return maxi;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 19. Print Subarray with Maximum Subarray Sum

### Problem

Print or return the subarray that gives the maximum subarray sum.

### Brute Force: Track Best Range

```cpp
vector<int> printMaxSubarrayBrute(vector<int>& arr) {
    long long best = LLONG_MIN;
    int start = 0, end = 0;

    for (int i = 0; i < arr.size(); i++) {
        long long sum = 0;
        for (int j = i; j < arr.size(); j++) {
            sum += arr[j];
            if (sum > best) {
                best = sum;
                start = i;
                end = j;
            }
        }
    }

    vector<int> ans;
    for (int i = start; i <= end; i++) ans.push_back(arr[i]);
    return ans;
}
```

Time Complexity: O(n²)  
Space Complexity: O(length of answer)

### Optimal: Kadane with Start and End

```cpp
vector<int> printMaxSubarrayOptimal(vector<int>& arr) {
    long long sum = 0;
    long long best = LLONG_MIN;
    int tempStart = 0, start = 0, end = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (sum == 0) tempStart = i;

        sum += arr[i];

        if (sum > best) {
            best = sum;
            start = tempStart;
            end = i;
        }

        if (sum < 0) sum = 0;
    }

    vector<int> ans;
    for (int i = start; i <= end; i++) ans.push_back(arr[i]);
    return ans;
}
```

Time Complexity: O(n)  
Space Complexity: O(length of answer)

## 20. Stock Buy and Sell

### Problem

Given stock prices, choose one day to buy and one later day to sell for maximum profit.

### Brute Force: Check Every Buy-Sell Pair

```cpp
int stockProfitBrute(vector<int>& prices) {
    int profit = 0;
    for (int buy = 0; buy < prices.size(); buy++) {
        for (int sell = buy + 1; sell < prices.size(); sell++) {
            profit = max(profit, prices[sell] - prices[buy]);
        }
    }
    return profit;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Track Minimum Price

```cpp
int stockProfitOptimal(vector<int>& prices) {
    int mini = prices[0];
    int profit = 0;

    for (int i = 1; i < prices.size(); i++) {
        int cost = prices[i] - mini;
        profit = max(profit, cost);
        mini = min(mini, prices[i]);
    }
    return profit;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 21. Rearrange Array in Alternating Positive and Negative Items

### Problem

Rearrange the array so positive and negative numbers appear alternately.

### Brute Force: Separate Positives and Negatives

Works when positives and negatives are equal in count.

```cpp
vector<int> rearrangeEqualBrute(vector<int>& arr) {
    vector<int> pos, neg;
    for (int x : arr) {
        if (x > 0) pos.push_back(x);
        else neg.push_back(x);
    }

    for (int i = 0; i < arr.size() / 2; i++) {
        arr[2 * i] = pos[i];
        arr[2 * i + 1] = neg[i];
    }
    return arr;
}
```

Time Complexity: O(n)  
Space Complexity: O(n)

### Optimal for Equal Counts: Direct Placement

```cpp
vector<int> rearrangeEqualOptimal(vector<int>& arr) {
    vector<int> ans(arr.size());
    int posIndex = 0;
    int negIndex = 1;

    for (int x : arr) {
        if (x > 0) {
            ans[posIndex] = x;
            posIndex += 2;
        } else {
            ans[negIndex] = x;
            negIndex += 2;
        }
    }
    return ans;
}
```

Time Complexity: O(n)  
Space Complexity: O(n)

### Variant: Unequal Counts

```cpp
vector<int> rearrangeUnequal(vector<int>& arr) {
    vector<int> pos, neg;
    for (int x : arr) {
        if (x > 0) pos.push_back(x);
        else neg.push_back(x);
    }

    vector<int> ans;
    int i = 0, j = 0;
    while (i < pos.size() && j < neg.size()) {
        ans.push_back(pos[i++]);
        ans.push_back(neg[j++]);
    }

    while (i < pos.size()) ans.push_back(pos[i++]);
    while (j < neg.size()) ans.push_back(neg[j++]);
    return ans;
}
```

Time Complexity: O(n)  
Space Complexity: O(n)

## 22. Next Permutation

### Problem

Find the next lexicographically greater permutation. If it does not exist, return the smallest permutation.

### Brute Force: Generate All Permutations

Generate all permutations, sort them, and pick the next one. This is only theoretical.

```cpp
void generatePermutations(vector<int>& arr, int index, vector<vector<int>>& all) {
    if (index == arr.size()) {
        all.push_back(arr);
        return;
    }

    for (int i = index; i < arr.size(); i++) {
        swap(arr[index], arr[i]);
        generatePermutations(arr, index + 1, all);
        swap(arr[index], arr[i]);
    }
}
```

Time Complexity: O(n! × n)  
Space Complexity: O(n!)

### Better: STL

```cpp
void nextPermutationBetter(vector<int>& arr) {
    next_permutation(arr.begin(), arr.end());
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

### Optimal: Manual Pivot Method

```cpp
void nextPermutationOptimal(vector<int>& arr) {
    int n = arr.size();
    int index = -1;

    //finding the first breakpoint   from  back index i st a[i]<a[i+1];

    for (int i = n - 2; i >= 0; i--) {
        if (arr[i] < arr[i + 1]) {
            index = i;//breakpoint
            break;
        }
    }

    if (index == -1) {//agr breakpoint nhi h to first perpermulation return kr do
        reverse(arr.begin(), arr.end());
        return;
    }

    for (int i = n - 1; i > index; i--) {
        if (arr[i] > arr[index]) {
            swap(arr[i], arr[index]);//first element from back greater than a[index];
            break;
        }
    }

    reverse(arr.begin() + index + 1, arr.end());
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 23. Leaders in an Array

### Problem

An element is a leader if every element to its right is smaller.

### Brute Force: Check Right Side

```cpp
vector<int> leadersBrute(vector<int>& arr) {
    vector<int> ans;

    for (int i = 0; i < arr.size(); i++) {
        bool leader = true;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] > arr[i]) {
                leader = false;
                break;
            }
        }
        if (leader) ans.push_back(arr[i]);
    }
    return ans;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1), excluding answer

### Optimal: Scan from Right

```cpp
vector<int> leadersOptimal(vector<int>& arr) {
    vector<int> ans;
    int maxi = INT_MIN;

    for (int i = arr.size() - 1; i >= 0; i--) {
        if (arr[i] > maxi) {  
            ans.push_back(arr[i]);
            maxi = arr[i];
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}
```

Time Complexity: O(n)  
Space Complexity: O(1), excluding answer

## 24. Longest Consecutive Sequence

### Problem

Find the length of the longest consecutive sequence in an unsorted array.

### Brute Force: Linear Search Next Element

```cpp
bool linearSearchValue(vector<int>& arr, int target) {
    for (int x : arr) {
        if (x == target) return true;
    }
    return false;
}

int longestConsecutiveBrute(vector<int>& arr) {
    int longest = 1;

    for (int x : arr) {
        int current = x;
        int count = 1;

        while (linearSearchValue(arr, current + 1)) {
            current++;
            count++;
        }
        longest = max(longest, count);
    }
    return longest;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Better: Sorting

```cpp
int longestConsecutiveBetter(vector<int> arr) {
    sort(arr.begin(), arr.end());

    int longest = 1;
    int count = 0;
    int lastSmaller = INT_MIN;

    for (int x : arr) {
        if (x - 1 == lastSmaller) {
            count++;
            lastSmaller = x;
        } else if (x != lastSmaller) {
            count = 1;
            lastSmaller = x;
        }
        longest = max(longest, count);
    }
    return longest;
}
```

Time Complexity: O(n log n)  
Space Complexity: O(1)

### Optimal: Hash Set

Start counting only from numbers that do not have a previous value.

```cpp
int longestConsecutiveOptimal(vector<int>& arr) {
    unordered_set<int> st(arr.begin(), arr.end());
    int longest = 0;

    for (int x : st) {
        if (!st.count(x - 1)) {
            int current = x;
            int count = 1;

            while (st.count(current + 1)) {
                current++;
                count++;
            }
            longest = max(longest, count);
        }
    }
    return longest;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

## 25. Set Matrix Zeroes

### Problem

If any cell is `0`, make its whole row and column `0`.

### Brute Force: Mark Rows and Columns

Mark cells with `-1` first, then convert them to zero. This works only if matrix values are non-negative.

```cpp
void markRow(vector<vector<int>>& matrix, int row) {
    for (int col = 0; col < matrix[0].size(); col++) {
        if (matrix[row][col] != 0) matrix[row][col] = -1;
    }
}

void markCol(vector<vector<int>>& matrix, int col) {
    for (int row = 0; row < matrix.size(); row++) {
        if (matrix[row][col] != 0) matrix[row][col] = -1;
    }
}

void setZeroesBrute(vector<vector<int>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (matrix[row][col] == 0) {
                markRow(matrix, row);
                markCol(matrix, col);
            }
        }
    }

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            if (matrix[row][col] == -1) matrix[row][col] = 0;
        }
    }
}
```

Time Complexity: O((n × m) × (n + m))  
Space Complexity: O(1)

### Better: Row and Column Arrays

```cpp
void setZeroesBetter(vector<vector<int>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    vector<int> row(n, 0), col(m, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                row[i] = 1;
                col[j] = 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (row[i] || col[j]) matrix[i][j] = 0;
        }
    }
}
```

Time Complexity: O(n × m)  
Space Complexity: O(n + m)

### Optimal: First Row and First Column as Markers

```cpp
void setZeroesOptimal(vector<vector<int>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    int col0 = 1;

    for (int i = 0; i < n; i++) {
       

        for (int j = 0; j < m; j++) {
            if (matrix[i][j] == 0) {
                matrix[i][0] = 0;
                if(j!==0){
                matrix[0][j] = 0;
                }
                else{
                    col0=0;
                }
            }
        }
    }

    for (int i = i; i <n; i++) {
        for (int j = 1; j <m; j++) {
            if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                matrix[i][j] = 0;
            }
        }
        
    }
    if(mat[0][0]==0){
        for( int j=0; j<m ;j++){
             matrix[0][j]=0;
        }
       
    }
    if(col0==0){
         for( i=0; i<n ;i++){
             matrix[i][0]=0;
        }

    }
}
```

Time Complexity: O(n × m)  
Space Complexity: O(1)

## 26. Rotate Matrix by 90 Degrees

### Problem

Rotate a square matrix by 90 degrees clockwise.

### Brute Force: Extra Matrix

```cpp
vector<vector<int>> rotateMatrixBrute(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> rotated(n, vector<int>(n));
    // i j goes to j , n-1-i;;/ observation  but we put reverre order in rotaterd array

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            rotated[j][n - 1 - i] = matrix[i][j];
        }
    }
    return rotated;
}
```

Time Complexity: O(n²)  
Space Complexity: O(n²)

### Optimal: Transpose + Reverse Rows
transpose the matrix and the reverse it rows
for row i start swaping from column j=i+1;
half past hi run krns loop ka

```cpp
void rotateMatrixOptimal(vector<vector<int>>& matrix) {
    int n = matrix.size();
    f

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    for (int i = 0; i < n; i++) {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

## 27. Spiral Traversal of Matrix

### Problem

Print the matrix in spiral order.

### Optimal: Boundary Traversal

```cpp
vector<int> spiralOrder(vector<vector<int>>& matrix) {
    vector<int> ans;
    int n = matrix.size(), m = matrix[0].size();
    int top = 0, left = 0;
    int bottom = n - 1, right = m - 1;

    while (top <= bottom && left <= right) {
        for (int i = left; i <= right; i++) ans.push_back(matrix[top][i]);
        top++;

        for (int i = top; i <= bottom; i++) ans.push_back(matrix[i][right]);
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) ans.push_back(matrix[bottom][i]);
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) ans.push_back(matrix[i][left]);
            left++;
        }
    }
    return ans;
}
```

Time Complexity: O(n × m)  
Space Complexity: O(1), excluding answer

## 28. Count Subarrays with Given Sum K

### Problem

Count the number of subarrays whose sum is exactly `k`.


### Brute Force: Generate Subarrays

```cpp
int countSubarraysSumBrute(vector<int>& arr, int k) {
    int count = 0;

    for (int i = 0; i < arr.size(); i++) {
        int sum = 0;
        for (int j = i; j < arr.size(); j++) {
            for( int  k1=i;k1<=j; k1++){
                sum += arr[k1];
            if (sum == k) count++;

            }
            
        }
    }
    return count;
}
```

Time Complexity: O(n^3)  
Space Complexity: O(1)

### Optimal: Prefix Sum Frequency

If current prefix sum is `sum`, we need an old prefix sum `sum - k`.

```cpp
int countSubarraysSumOptimal(vector<int>& arr, int k) {
    unordered_map<int, int> mp;
    mp[0] = 1;/subaray of sum o is always exist

    int prefixSum = 0;
    int count = 0;

    for (int x : arr) {
        prefixSum += x;
        int remove = prefixSum - k;
        count += mp[remove];
        mp[prefixSum]++;
    }
    return count;
}
```

Time Complexity: O(nlogn)  due to map
Space Complexity: O(n)
