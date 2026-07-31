# Arrays Part 3: Hard and Final Problems

Use this header for all C++ snippets:

```cpp
#include <bits/stdc++.h>
using namespace std;
```

## 29. Pascal's Triangle

### Problem

Pascal's Triangle has each value equal to the sum of the two values above it.

### Type 1: Find Element at Row r and Column c

Use `nCr`, where answer is `C(r - 1, c - 1)` for 1-based indexing.

```cpp
long long nCr(int n, int r) {
    long long ans = 1;
    for (int i = 0; i < r; i++) {
        ans = ans * (n - i);
        ans = ans / (i + 1);
    }
    return ans;
}

long long pascalElement(int row, int col) {
    return nCr(row - 1, col - 1);
}
```

Time Complexity: O(c)  
Space Complexity: O(1)

### Type 2: Print nth Row

## brute force
```cpp
for( int col=1; col<=row ;i++){
    return nCr(row - 1, col -1);

}
```

## optimal

```cpp
vector<long long> pascalRow(int row) {// roe is one based index
    vector<long long> ans;
    long long value = 1;
    ans.push_back(value);

    for (int i = 1; i < row; i++) {
        value = value * (row - i);
        value = value / i;
        ans.push_back(value);
    }
    return ans;
}
```

Time Complexity: O(row)  
Space Complexity: O(row)

### Type 3: Print Whole Triangle
## brute force
```cpp
vector<vector<int>>ans;
for( int row=1;row<=n; row++){
    vector< int> temp;

 
for( int col=1; col<=row ;i++){
    temp.push_back( nCr(row - 1, col -1));

}
ans.push_back(temp);
}
```



```cpp
vector<vector<long long>> pascalTriangle(int n) {
    vector<vector<long long>> triangle;

    for (int row = 1; row <= n; row++) {
        triangle.push_back(pascalRow(row));
    }
    return triangle;
}
```

Time Complexity: O(n²)  
Space Complexity: O(n²)

## 30. Majority Element Greater than n/3

### Problem

Find all elements that appear more than `n/3` times. There can be at most two such elements.

### Brute Force: Count Every Element

```cpp
vector<int> majorityN3Brute(vector<int>& arr) {
    vector<int> ans;
    int n = arr.size();

for (int i = 0; i < n; i++) {
     if (ans.empty() || ans[0] != arr[i]){//arr[i]is previously not a part of my answer so i need to check it;
            int count = 0;
          for (int j = 0; j < n; j++) {
            if (arr[j] == arr[i]) count++;
           }

        if (count > n / 3) ans.push_back(arr[i]);
        if (ans.size() == 2) break;

        }

        
    }

    sort(ans.begin(), ans.end());
    return ans;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1), excluding answer
### Better: Hash Map

```cpp
vector<int> majorityN3Better(vector<int>& arr) {
    unordered_map<int, int> freq;
    vector<int> ans;
    int n = arr.size();

    for (int x : arr) {
        freq[x]++;
       
    }
    for( auto it:fre){
        if(it.second>n/3){
            ans.push_abck( it.first);
        }
    }

    sort(ans.begin(), ans.end());
    return ans;
}

```
is O(n)+ hash map ko iterate krna pda..

### Better: Hash Map

```cpp
vector<int> majorityN3Better(vector<int>& arr) {
    unordered_map<int, int> freq;
    vector<int> ans;
    int n = arr.size();

    for (int x : arr) {
        freq[x]++;
        if (freq[x] == n / 3 + 1) ans.push_back(x);
    }

    sort(ans.begin(), ans.end());
    return ans;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

### Optimal: Extended Moore's Voting Algorithm

Keep two candidates because only two elements can appear more than `n/3` times.

```cpp
vector<int> majorityN3Optimal(vector<int>& arr) {
    int count1 = 0, count2 = 0;
    int element1 = INT_MIN, element2 = INT_MIN;

    for (int x : arr) {
        if (count1 == 0 && x != element2) {//both of them must hold diffrent number thats why i need toi check before assigning that it should not be equal to othet element
            element1 = x;
            count1 = 1;
        } else if (count2 == 0 && x != element1) {
            //both of them must hold diffrent number thats why i need toi check before assigning that it should not be equal to othet element
            element2 = x;
            count2 = 1;
        } else if (x == element1) {
            count1++;
        } else if (x == element2) {
            count2++;
        } else {
            count1--;
            count2--;
        }
    }

    count1 = 0;
    count2 = 0;
    for (int x : arr) {
        if (x == element1) count1++;
        else if (x == element2) count2++;
    }

    vector<int> ans;
    int mini = arr.size() / 3 + 1;
    if (count1 >= mini) ans.push_back(element1);
    if (count2 >= mini) ans.push_back(element2);

    sort(ans.begin(), ans.end());
    return ans;
}
```

Time Complexity: O(n)  
Space Complexity: O(1), excluding answer

## 31. 3 Sum

### Problem

Find all unique triplets whose sum is `0`.

### Brute Force: Three Loops

```cpp
vector<vector<int>> threeSumBrute(vector<int>& arr) {
    set<vector<int>> st;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (arr[i] + arr[j] + arr[k] == 0) {
                    vector<int> temp = {arr[i], arr[j], arr[k]};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
            }
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}
```

Time Complexity: O(n³ × log uniqueTriplets)  
Space Complexity: O(uniqueTriplets)

### Better: Hash Set for Third Element

Fix two elements using loops and search the third in a set.

```cpp
vector<vector<int>> threeSumBetter(vector<int>& arr) {
    set<vector<int>> st;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        unordered_set<int> hashSet;//hash eill only store elemens b/w index i and j  ie( i+1, to j-1)

        for (int j = i + 1; j < n; j++) {
            int third = -(arr[i] + arr[j]);

            if (hashSet.count(third)) {
                vector<int> temp = {arr[i], arr[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hashSet.insert(arr[j]);
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}
```

Time Complexity: O(n² × log uniqueTriplets)  
Space Complexity: O(n) + O(uniqueTriplets)

### Optimal: Sort + Two Pointers

```cpp
vector<vector<int>> threeSumOptimal(vector<int>& arr) {
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    int n = arr.size();
    //i ko fir rakhenge  j ko i+1 se inialtize krenge  aur k ko  n-1 se

    for (int i = 0; i < n; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;
        //ye sirf check krrne le kiye h ki same tpit na aa jaye isliye

        int j = i + 1;
        int k = n - 1;

        while (j < k) {
            int sum = arr[i] + arr[j] + arr[k];

            if (sum < 0) {
                j++;
            } else if (sum > 0) {
                k--;
            } else {
                ans.push_back({arr[i], arr[j], arr[k]});
                j++;
                k--;

                while (j < k && arr[j] == arr[j - 1]) j++;//same wale in j nhi honi chaihe second triplet chek krnw ke liye
                while (j < k && arr[k] == arr[k + 1]) k--;//same wale in j nhi honi chaihe second triplet chek krnw ke liye
            }
        }
    }
    return ans;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1), excluding answer

## 32. 4 Sum

### Problem

Find all unique quadruplets whose sum equals the target.

### Brute Force: Four Loops

```cpp
vector<vector<int>> fourSumBrute(vector<int>& arr, int target) {
    set<vector<int>> st;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                for (int l = k + 1; l < n; l++) {
                    long long sum = 1LL * arr[i] + arr[j] + arr[k] + arr[l];
                    if (sum == target) {
                        vector<int> temp = {arr[i], arr[j], arr[k], arr[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
            }
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}
```

Time Complexity: O(n⁴ × log uniqueQuadruplets)  
Space Complexity: O(uniqueQuadruplets)

### Better: Hash Set for Fourth Element

```cpp
vector<vector<int>> fourSumBetter(vector<int>& arr, int target) {
    set<vector<int>> st;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            unordered_set<long long> hashSet;// hasdh map store krega j aur ke beacche ke eleemnts

            for (int k = j + 1; k < n; k++) {
                long long sum = 1LL * arr[i] + arr[j] + arr[k];
                long long fourth = target - sum;

                if (hashSet.count(fourth)) {
                    vector<int> temp = {arr[i], arr[j], arr[k], (int)fourth};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                hashSet.insert(arr[k]);
            }
        }
    }

    return vector<vector<int>>(st.begin(), st.end());
}
```

Time Complexity: O(n³ × log uniqueQuadruplets)  
Space Complexity: O(n) + O(uniqueQuadruplets)

### Optimal: Sort + Two Pointers

```cpp
vector<vector<int>> fourSumOptimal(vector<int>& arr, int target) {
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (i > 0 && arr[i] == arr[i - 1]) continue;

        for (int j = i + 1; j < n; j++) {
            if (j > i + 1 && arr[j] == arr[j - 1]) continue;

            int k = j + 1;
            int l = n - 1;

            while (k < l) {
                long long sum = 1LL * arr[i] + arr[j] + arr[k] + arr[l];

                if (sum == target) {
                    ans.push_back({arr[i], arr[j], arr[k], arr[l]});
                    k++;
                    l--;

                    while (k < l && arr[k] == arr[k - 1]) k++;
                    while (k < l && arr[l] == arr[l + 1]) l--;
                } else if (sum < target) {
                    k++;
                } else {
                    l--;
                }
            }
        }
    }
    return ans;
}
```

Time Complexity: O(n³)  
Space Complexity: O(1), excluding answer

## 33. Largest Subarray with 0 Sum

### Problem

Find the length of the longest subarray whose sum is `0`.

### Brute Force: All Subarrays

```cpp
int longestZeroSumBrute(vector<int>& arr) {
    int maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {
        int sum = 0;
        for (int j = i; j < arr.size(); j++) {
            sum += arr[j];
            if (sum == 0) maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Prefix Sum First Index

If the same prefix sum appears again, the subarray between them has sum `0`.

```cpp
int longestZeroSumOptimal(vector<int>& arr) {
    unordered_map<int, int> firstIndex;
    int sum = 0;
    int maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];

        if (sum == 0) maxLen = i + 1;
        else if (firstIndex.count(sum)) maxLen = max(maxLen, i - firstIndex[sum]);
        else firstIndex[sum] = i;
    }
    return maxLen;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

## 34. Count Subarrays with Given XOR K

### Problem

Count subarrays whose XOR is equal to `k`.

### Brute Force: All Subarrays

```cpp
int countXorBrute(vector<int>& arr, int k) {
    int count = 0;

    for (int i = 0; i < arr.size(); i++) {
        int xr = 0;
        for (int j = i; j < arr.size(); j++) {
            xr ^= arr[j];
            if (xr == k) count++;
        }
    }
    return count;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Prefix XOR Frequency

If `prefixXor ^ oldPrefix = k`, then `oldPrefix = prefixXor ^ k`.

```cpp
int countXorOptimal(vector<int>& arr, int k) {
    unordered_map<int, int> mp;
    mp[0] = 1;

    int xr = 0;
    int count = 0;

    for (int x : arr) {
        xr ^= x;
        int need = xr ^ k;
        count += mp[need];
        mp[xr]++;
    }
    return count;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

## 35. Merge Overlapping Intervals

### Problem

Given intervals, merge all overlapping intervals.

### Brute Force: Sort and Expand Each Interval

```cpp
vector<vector<int>> mergeIntervalsBrute(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;

    for (int i = 0; i < intervals.size(); i++) {
        int start = intervals[i][0];
        int end = intervals[i][1];

        if (!ans.empty() && end <= ans.back()[1]) continue;

        for (int j = i + 1; j < intervals.size(); j++) {
            if (intervals[j][0] <= end) {
                end = max(end, intervals[j][1]);
            } else {
                break;
            }
        }

        ans.push_back({start, end});
    }
    return ans;
}
```

Time Complexity: O(n log n) + O(2n)// beacusec every element is vivsired twice  
Space Complexity: O(n), excluding answer depending on sort

### Optimal: Sort and Merge Once

```cpp
vector<vector<int>> mergeIntervalsOptimal(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;

    for (auto interval : intervals) {
        if (ans.empty() || interval[0] > ans.back()[1]) {
            ans.push_back(interval);
        } else {
            ans.back()[1] = max(ans.back()[1], interval[1]);
        }
    }
    return ans;
}
```

Time Complexity: O(n log n)  
Space Complexity: O(n) for answer

## 36. Merge Two Sorted Arrays without Extra Space

### Problem

Merge two sorted arrays without using an extra merged array.

### Brute Force: Extra Array

```cpp
void mergeSortedBrute(vector<long long>& a, vector<long long>& b) {
    vector<long long> temp;
    int i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) temp.push_back(a[i++]);
        else temp.push_back(b[j++]);
    }

    while (i < a.size()) temp.push_back(a[i++]);
    while (j < b.size()) temp.push_back(b[j++]);

    for (int index = 0; index < temp.size(); index++) {
        if (index < a.size()) a[index] = temp[index];
        else b[index - a.size()] = temp[index];
    }
}
```

Time Complexity: O(n + m)  
Space Complexity: O(n + m)

### Better: Swap and Sort

Place smaller values in first array and larger values in second array, then sort both.

```cpp
void mergeSortedBetter(vector<long long>& a, vector<long long>& b) {
    //element from 0 to left are sorted in first aray any time 
    //element from right to last are sorted in second array  aray any time 
    int left = a.size() - 1; 
    int right = 0;

    while (left >= 0 && right < b.size()) {
        if (a[left] > b[right]) {
            swap(a[left], b[right]);
            left--;
            right++;
        } else {
            break;
        }
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
}
```

Time Complexity: O(min(n, m)) + O(n log n) + O(m log m)  
Space Complexity: O(1)

### Optimal: Gap Method

Use Shell-sort style comparison gaps over the combined virtual array.

```cpp
void swapIfGreater(vector<long long>& a, vector<long long>& b, int ind1, int ind2) {
    if (a[ind1] > b[ind2]) swap(a[ind1], b[ind2]);
}

void mergeSortedOptimal(vector<long long>& arr1, vector<long long>& arr2) {
    int n = arr1.size(), m = arr2.size();
    int len = n + m;
    int gap = (len / 2) + (len % 2);//ceil ((n+m)/2)

    while (gap > 0) {
        int left = 0;
        int right = left + gap;

        while (right < len) {
                //arr1   aar2
            if (left < n && right >= n) {
                swapIfGreater(arr1, arr2, left, right - n);
            } 
            //arr2 arr2
            else if (left >= n) {
                swapIfGreater(arr2, arr2, left - n, right - n);
            }
            //arr1 arr1
            else {
                swapIfGreater(arr1, arr1, left, right);
            }

            left++;
            right++;
        }

        if (gap == 1) break;
        gap = (gap / 2) + (gap % 2);
    }
}
```

Time Complexity: O((n + m) log(n + m))  
Space Complexity: O(1)

## 37. Find Repeating and Missing Number

### Problem

Array contains numbers from `1` to `n`. One number is missing and one number is repeated.

### Brute Force: Count Every Number

```cpp
pair<int, int> repeatMissingBrute(vector<int>& arr) {
    int n = arr.size();
    int repeating = -1, missing = -1;

    for (int num = 1; num <= n; num++) {
        int count = 0;
        for (int x : arr) {
            if (x == num) count++;
        }

        if (count == 2) repeating = num;
        else if (count == 0) missing = num;
        if(repeating!=-1 &&  missing!=-1){// means i got both of the elements
             break;
        }
    }
    return {repeating, missing};
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Better: Hashing

```cpp
pair<int, int> repeatMissingBetter(vector<int>& arr) {
    int n = arr.size();
    vector<int> hash(n + 1, 0);

    for (int x : arr) hash[x]++;

    int repeating = -1, missing = -1;
    for (int num = 1; num <= n; num++) {
        if (hash[num] == 2) repeating = num;
        else if (hash[num] == 0) missing = num;
          if(repeating!=-1 &&  missing!=-1){// means i got both of the elements
             break;
        }
    }
    return {repeating, missing};
}
```

Time Complexity: O(n )  
Space Complexity: O(n)

### Optimal: Maths

Use sum and square-sum equations.

```cpp
pair<int, int> repeatMissingOptimal(vector<int>& arr) {
    long long n = arr.size();
    long long sn = n * (n + 1) / 2;
    long long s2n = n * (n + 1) * (2 * n + 1) / 6;

    long long s = 0, s2 = 0;
    for (int x : arr) {
        s += x;
        s2 += 1LL * x * x;
    }

    long long val1 = s - sn;
    long long val2 = s2 - s2n;
    val2 = val2 / val1;

    long long repeating = (val1 + val2) / 2;
    long long missing = repeating - val1;

    return {(int)repeating, (int)missing};
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 38. Count Inversions

### Problem

Count pairs `(i, j)` such that `i < j` and `arr[i] > arr[j]`.

### Brute Force: Check All Pairs

```cpp
long long countInversionsBrute(vector<int>& arr) {
    long long count = 0;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] > arr[j]) count++;
        }
    }
    return count;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Merge Sort

While merging, if `left[i] > right[j]`, then all remaining elements in the left half also form inversions.

```cpp
long long mergeForInversions(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;
    long long count = 0;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left++]);
        } else {
            temp.push_back(arr[right++]);
            count += mid - left + 1;
        }
    }

    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++) arr[i] = temp[i - low];
    return count;
}

long long mergeSortInversions(vector<int>& arr, int low, int high) {
    if (low >= high) return 0;

    int mid = (low + high) / 2;
    long long count = 0;
    count += mergeSortInversions(arr, low, mid);
    count += mergeSortInversions(arr, mid + 1, high);
    count += mergeForInversions(arr, low, mid, high);
    return count;
}

long long countInversionsOptimal(vector<int> arr) {
    return mergeSortInversions(arr, 0, arr.size() - 1);
}
```

Time Complexity: O(n log n)  
Space Complexity: O(n)

## 39. Reverse Pairs

### Problem

Count pairs `(i, j)` such that `i < j` and `arr[i] > 2 * arr[j]`.

### Brute Force: Check All Pairs

```cpp
int reversePairsBrute(vector<int>& arr) {
    int count = 0;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (1LL * arr[i] > 2LL * arr[j]) count++;
        }
    }
    return count;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Merge Sort

Count valid cross pairs before merging the two sorted halves.

```cpp
void mergeReversePairs(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) temp.push_back(arr[left++]);
        else temp.push_back(arr[right++]);
    }

    while (left <= mid) temp.push_back(arr[left++]);
    while (right <= high) temp.push_back(arr[right++]);

    for (int i = low; i <= high; i++) arr[i] = temp[i - low];
}

int countPairs(vector<int>& arr, int low, int mid, int high) {
    int right = mid + 1;
    int count = 0;

    for (int i = low; i <= mid; i++) {
        while (right <= high && 1LL * arr[i] > 2LL * arr[right]) right++;
        count += right - (mid + 1);
    }
    return count;
}

int mergeSortReversePairs(vector<int>& arr, int low, int high) {
    if (low >= high) return 0;

    int mid = (low + high) / 2;
    int count = 0;
    count += mergeSortReversePairs(arr, low, mid);
    count += mergeSortReversePairs(arr, mid + 1, high);
    count += countPairs(arr, low, mid, high);
    mergeReversePairs(arr, low, mid, high);
    return count;
}

int reversePairsOptimal(vector<int> arr) {
    return mergeSortReversePairs(arr, 0, arr.size() - 1);
}
```

Time Complexity: O(n log n)  
Space Complexity: O(n)

## 40. Maximum Product Subarray

### Problem

Find the maximum product of any contiguous subarray.
### Brute Force: All Subarrays

```cpp
long long maxProductBrute(vector<int>& arr) {
    long long maxi = LLONG_MIN;

    for (int i = 0; i < arr.size(); i++) {
       
        for (int j = i; j < arr.size(); j++) {
             long long product = 1;
            for( int k =i;k<=j; k++){
                product *= arr[k];
                 maxi = max(maxi, product);

            }
            
        }
    }
    return maxi;
}
```

Time Complexity: O(n^3)  
Space Complexity: O(1)


### Brute Force: All Subarrays

```cpp
long long maxProductBrute(vector<int>& arr) {
    long long maxi = LLONG_MIN;

    for (int i = 0; i < arr.size(); i++) {
        long long product = 1;
        for (int j = i; j < arr.size(); j++) {
            product *= arr[j];
            maxi = max(maxi, product);
        }
    }
    return maxi;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Better: Prefix and Suffix Product

Zeros break product chains, so reset product to `1` when it becomes `0`.

```cpp
long long maxProductBetter(vector<int>& arr) {
    long long prefix = 1;
    long long suffix = 1;
    long long ans = LLONG_MIN;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        if (prefix == 0) prefix = 1;
        if (suffix == 0) suffix = 1;

        prefix *= arr[i];
        suffix *= arr[n - i - 1];

        ans = max(ans, max(prefix, suffix));
    }
    return ans;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

### Optimal: Track Maximum and Minimum Ending Here

A negative number can turn the minimum product into the maximum product.

```cpp
long long maxProductOptimal(vector<int>& arr) {
    long long maxi = arr[0];
    long long mini = arr[0];
    long long ans = arr[0];

    for (int i = 1; i < arr.size(); i++) {
        long long x = arr[i];

        if (x < 0) swap(maxi, mini);

        maxi = max(x, maxi * x);
        mini = min(x, mini * x);

        ans = max(ans, maxi);
    }
    return ans;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)
