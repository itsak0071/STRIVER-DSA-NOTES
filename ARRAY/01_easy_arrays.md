# Arrays Part 1: Easy Problems

Use this header for all C++ snippets:

```cpp
#include <bits/stdc++.h>
using namespace std;
```

## 1. Largest Element in an Array

### Problem

Given an array, find the largest element.

### Brute Force: Sort

Sort the array and return the last element.

```cpp
int largestBrute(vector<int> arr) {
    sort(arr.begin(), arr.end());
    return arr.back();
}
```

Time Complexity: O(n log n)  
Space Complexity: O(1), ignoring sorting recursion

### Optimal: Linear Scan

Keep one variable for the maximum element.

```cpp
int largestOptimal(vector<int>& arr) {
    int largest = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > largest) largest = arr[i];
    }
    return largest;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 2. Second Largest Element without Sorting

### Problem

Find the second largest distinct element. If it does not exist, return `-1`.

### Brute Force: Sort

Sort, then move left from the second-last index until a smaller value is found.

```cpp
int secondLargestBrute(vector<int> arr) {
    sort(arr.begin(), arr.end());
    int largest = arr.back();
    for (int i = arr.size() - 2; i >= 0; i--) {
        if (arr[i] != largest) return arr[i];
    }
    return -1;
}
```

Time Complexity: O(n log n)  
Space Complexity: O(1), ignoring sorting recursion

### Better: Two Passes

First find the largest, then find the best value smaller than largest.

```cpp
int secondLargestBetter(vector<int>& arr) {
    int largest = arr[0];
    for (int x : arr) largest = max(largest, x);

    int secondLargest = -1;
    for (int x : arr) {
        if (x < largest && x > secondLargest) secondLargest = x;
    }
    return secondLargest;
}
```

Time Complexity: O(2n)  
Space Complexity: O(1)

### Optimal: One Pass

Update largest and second largest together.

```cpp
int secondLargestOptimal(vector<int>& arr) {
    int largest = arr[0];
    int secondLargest = -1;

    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] > largest) {
            secondLargest = largest;
            largest = arr[i];
        } else if (arr[i] < largest && arr[i] > secondLargest) {
            secondLargest = arr[i];
        }
    }
    return secondLargest;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 3. Check if the Array is Sorted

### Problem

Check whether the array is sorted in non-decreasing order.

### Brute Force: Check All Pairs

For every `i < j`, `arr[i]` must be less than or equal to `arr[j]`.

```cpp
bool isSortedBrute(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] > arr[j]) return false;
        }
    }
    return true;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Adjacent Check

Only compare neighbouring elements.

```cpp
bool isSortedOptimal(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 4. Remove Duplicates from Sorted Array

### Problem

Given a sorted array, remove duplicates in-place and return the number of unique elements.

### Brute Force: Set

Insert elements into a set, then copy unique values back.

```cpp
int removeDuplicatesBrute(vector<int>& arr) {
    set<int> st;
    for (int x : arr) st.insert(x);

    int index = 0;
    for (int x : st) arr[index++] = x;
    return index;
}
```

Time Complexity: O(n log n)  
Space Complexity: O(n)

### Optimal: Two Pointers

Keep `i` at the last unique element and scan with `j`.

```cpp
int removeDuplicatesOptimal(vector<int>& arr) {
    int i = 0;
    for (int j = 1; j < arr.size(); j++) {
        if (arr[j] != arr[i]) {
            i++;
            arr[i] = arr[j];
        }
    }
    return i + 1;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 5. Left Rotate an Array by One Place

### Problem

Move the first element to the end and shift all other elements left by one.

### Optimal

Store the first element, shift, then place it at the end.

```cpp
void leftRotateByOne(vector<int>& arr) {
    int temp = arr[0];
    for (int i = 1; i < arr.size(); i++) {
        arr[i - 1] = arr[i];
    }
    arr[arr.size() - 1] = temp;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 6. Left Rotate an Array by D Places

### Problem

Rotate the array left by `d` positions.

### Brute Force: Rotate One by One

Perform one-left-rotation `d` times.

```cpp
void leftRotateDBrute(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;
    while (d--) {
        int temp = arr[0];
        for (int i = 1; i < n; i++) arr[i - 1] = arr[i];
        arr[n - 1] = temp;
    }
}
```

Time Complexity: O(n × d)  
Space Complexity: O(1)

### Better: Temporary Array

Store the first `d` elements, shift the rest, then copy temp back.

```cpp
void leftRotateDBetter(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;

    vector<int> temp;
    for (int i = 0; i < d; i++) temp.push_back(arr[i]);

    for (int i = d; i < n; i++) arr[i - d] = arr[i];
    for (int i = n - d; i < n; i++) arr[i] = temp[i - (n - d)];
}
```

Time Complexity: O(n)  
Space Complexity: O(d)

### Optimal: Reverse Technique

Reverse first `d`, reverse remaining `n-d`, then reverse the whole array.

```cpp
void leftRotateDOptimal(vector<int>& arr, int d) {
    int n = arr.size();
    d = d % n;
    reverse(arr.begin(), arr.begin() + d);
    reverse(arr.begin() + d, arr.end());
    reverse(arr.begin(), arr.end());
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 7. Move Zeroes to End

### Problem

Move all zeroes to the end while keeping non-zero elements in the same order.

### Brute Force: Temporary Array

Store all non-zero elements, copy them back, then fill remaining places with zero.

```cpp
void moveZeroesBrute(vector<int>& arr) {
    vector<int> temp;
    for (int x : arr) {
        if (x != 0) temp.push_back(x);
    }

    for (int i = 0; i < temp.size(); i++) arr[i] = temp[i];
    for (int i = temp.size(); i < arr.size(); i++) arr[i] = 0;
}
```

Time Complexity: O(n)  
Space Complexity: O(n)

### Optimal: Two Pointers

Find the first zero, then swap it with later non-zero elements.

```cpp
void moveZeroesOptimal(vector<int>& arr) {
    int j = -1;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            j = i;
            break;
        }
    }

    if (j == -1) return;

    for (int i = j + 1; i < arr.size(); i++) {
        if (arr[i] != 0) {
            swap(arr[i], arr[j]);
            j++;
        }
    }
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 8. Linear Search

### Problem

Find the index of a target element. If not present, return `-1`.

### Optimal

Scan from left to right.

```cpp
int linearSearch(vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 9. Union of Two Sorted Arrays

### Problem

Given two sorted arrays, return their sorted union without duplicates.

### Brute Force: Set

Insert all elements into a set.

```cpp
vector<int> unionBrute(vector<int>& a, vector<int>& b) {
    set<int> st;
    for (int x : a) st.insert(x);
    for (int x : b) st.insert(x);

    vector<int> ans;
    for (int x : st) ans.push_back(x);
    return ans;
}
```

Time Complexity: O((n + m) log(n + m))  
Space Complexity: O(n + m)

### Optimal: Two Pointers

Move through both sorted arrays and push only new values.

```cpp
vector<int> unionOptimal(vector<int>& a, vector<int>& b) {
    int i = 0, j = 0;
    vector<int> ans;

    while (i < a.size() && j < b.size()) {
        int value;
        if (a[i] <= b[j]) value = a[i++];
        else value = b[j++];

        if (ans.empty() || ans.back() != value) ans.push_back(value);
    }

    while (i < a.size()) {
        if (ans.empty() || ans.back() != a[i]) ans.push_back(a[i]);
        i++;
    }

    while (j < b.size()) {
        if (ans.empty() || ans.back() != b[j]) ans.push_back(b[j]);
        j++;
    }

    return ans;
}


```

Time Complexity: O(n + m)  
Space Complexity: O(n + m) for answer
## 9. Intersection of two sorted array 



int n1=arr1.size();
int n2= arr2.size();
 vector< int> ans;
vector< int> vis( n2, 0);
for( int i=0; i<n1; i++){
      for( int j=0; j<n2; j++){
          if(arr1[i]==arr2[j]&& vis[j]==0){
              vis[j]=1;
              ans.push_back( arr[i]);
              break;

          }
          if(arr2[j]>arr1[i])break;
      }
}


// OPtimal;
int i =0, j=0;
vector<int> ans;
while( i<arr1.szie() && j<arr2.size()){
       if( arr1[i]<arr2[j]){
         i++;
       }
       else if(arr2[j]<arr1[i]){
         j++;
       }
       else{
         ans.push_back(arr1[i]);
         i++;j++;
       }
}
return ans;



## 10. Missing Number in an Array

### Problem

Given `n-1` numbers from `1` to `n`, find the missing number.

### Brute Force: Linear Search for Every Number

For each number from `1` to `n`, check if it exists.

```cpp
int missingBrute(vector<int>& arr, int n) {
    for (int num = 1; num <= n; num++) {
        bool found = false;
        for (int x : arr) {
            if (x == num) {
                found = true;
                break;
            }
        }
        if (!found) return num;
    }
    return -1;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Better: Hashing

Mark every present number.

```cpp
int missingBetter(vector<int>& arr, int n) {
    vector<int> hash(n + 1, 0);
    for (int x : arr) hash[x] = 1;

    for (int num = 1; num <= n; num++) {
        if (hash[num] == 0) return num;
    }
    return -1;
}
```

Time Complexity: O(n)  
Space Complexity: O(n)

### Optimal: XOR

XOR all numbers from `1` to `n` and XOR all array elements. Pairs cancel out.

```cpp
int missingOptimal(vector<int>& arr, int n) {
    int xr = 0;
    for (int num = 1; num <= n; num++) xr ^= num;
    for (int x : arr) xr ^= x;
    return xr;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 11. Maximum Consecutive Ones

### Problem

Find the maximum number of consecutive `1`s in a binary array.

### Optimal

Maintain current streak and best streak.

```cpp
int maximumConsecutiveOnes(vector<int>& arr) {
    int count = 0;
    int maxi = 0;

    for (int x : arr) {
        if (x == 1) {
            count++;
            maxi = max(maxi, count);
        } else {
            count = 0;
        }
    }
    return maxi;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 12. Find the Number that Appears Once, Others Twice

### Problem

Every element appears twice except one element. Find that single element.

### Brute Force: Count Every Element

For each element, count its frequency.

```cpp
int singleNumberBrute(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        int count = 0;
        for (int j = 0; j < arr.size(); j++) {
            if (arr[j] == arr[i]) count++;
        }
        if (count == 1) return arr[i];
    }
    return -1;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Better: Hash Map

Count frequency of every number.

```cpp
int singleNumberBetter(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;

    for (auto it : freq) {
        if (it.second == 1) return it.first;
    }
    return -1;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

### Optimal: XOR

Same numbers cancel because `x ^ x = 0`.

```cpp
int singleNumberOptimal(vector<int>& arr) {
    int xr = 0;
    for (int x : arr) xr ^= x;
    return xr;
}
```

Time Complexity: O(n)  
Space Complexity: O(1)

## 13. Longest Subarray with Sum K: Positives

### Problem

Find the longest subarray with sum `k` when all elements are positive.

### Brute Force: Generate Subarrays

Check every subarray sum.

```cpp
int longestSubarrayPositiveBrute(vector<int>& arr, long long k) {
    int maxLen = 0;
    for (int i = 0; i < arr.size(); i++) {
        long long sum = 0;
        for (int j = i; j < arr.size(); j++) {
            sum += arr[j];
            if (sum == k) maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Better: Prefix Sum Hash Map

Works for positives and negatives also.

```cpp
int longestSubarrayPositiveBetter(vector<int>& arr, long long k) {
    unordered_map<long long, int> firstIndex;
    long long sum = 0;
    int maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];

        if (sum == k) maxLen = max(maxLen, i + 1);

        long long rem = sum - k;
        if (firstIndex.count(rem)) {
            maxLen = max(maxLen, i - firstIndex[rem]);
        }

        if (!firstIndex.count(sum)) firstIndex[sum] = i;
    }
    return maxLen;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)

### Optimal: Two Pointers

Since all numbers are positive, shrinking the left pointer always reduces the sum.

```cpp
int longestSubarrayPositiveOptimal(vector<int>& arr, long long k) {
    int left = 0;
    long long sum = 0;
    int maxLen = 0;

    for (int right = 0; right < arr.size(); right++) {
        sum += arr[right];

        while (left <= right && sum > k) {
            sum -= arr[left];
            left++;
        }

        if (sum == k) maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}
```

Time Complexity: O(2n), effectively O(n)  
Space Complexity: O(1)

## 14. Longest Subarray with Sum K: Positives and Negatives

### Problem

Find the longest subarray with sum `k` when the array can contain positive, negative, and zero values.

### Brute Force: Generate Subarrays

```cpp
int longestSubarrayAnyBrute(vector<int>& arr, long long k) {
    int maxLen = 0;
    for (int i = 0; i < arr.size(); i++) {
        long long sum = 0;
        for (int j = i; j < arr.size(); j++) {
            sum += arr[j];
            if (sum == k) maxLen = max(maxLen, j - i + 1);
        }
    }
    return maxLen;
}
```

Time Complexity: O(n²)  
Space Complexity: O(1)

### Optimal: Prefix Sum Hash Map

Two pointers fails with negative numbers. Store the first index where each prefix sum appears.

```cpp
int longestSubarrayAnyOptimal(vector<int>& arr, long long k) {
    unordered_map<long long, int> firstIndex;
    long long sum = 0;
    int maxLen = 0;

    for (int i = 0; i < arr.size(); i++) {
        sum += arr[i];

        if (sum == k) maxLen = max(maxLen, i + 1);

        long long rem = sum - k;
        if (firstIndex.count(rem)) {
            maxLen = max(maxLen, i - firstIndex[rem]);
        }

        if (!firstIndex.count(sum)) firstIndex[sum] = i;
    }
    return maxLen;
}
```

Time Complexity: O(n) average  
Space Complexity: O(n)
###  number of subarrya iwth sum ==k
#include <bits/stdc++.h>
using namespace std;
```cpp
int countSubarrays(vector<int>& arr, int k) {
    unordered_map<long long, int> mp;

    long long sum = 0;
    int ans = 0;

    mp[0] = 1;//this is for when we take array from 0 to i 

    for (int x : arr) {
        sum += x;

        if (mp.count(sum - k))
            ans += mp[sum - k];

        mp[sum]++;
    }

    return ans;
}
```
this   code will work for positve negative and zeroes all