# Striver Binary Search Playlist: Lecture-wise C++ Notes

Playlist: https://www.youtube.com/playlist?list=PLgUwDviBIf0pMFMWuuvDNMAkoQFi-h0ZF

Important: I cannot provide an exact verbatim copy of Striver/TUF code. These notes follow the same playlist flow and standard Striver-style approaches with fresh C++17 implementations.

## Common Setup

```cpp
#include <bits/stdc++.h>
using namespace std;
```

## 1. Launching Binary Search Bootcamp

### Problem

Study Binary Search by dividing it into common patterns.

### Revision Hints

- Binary Search is not only for searching in sorted arrays; it is also used on the answer space.

### Approach

1. Apply index-space binary search on sorted arrays.
2. Use condition-based half elimination in rotated/special arrays.
3. In answer-space binary search, the "can we do it?" predicate must be monotonic.

### Complexity

**Time Complexity:**
- `Not applicable`

**Space Complexity:**
- `Not applicable`

### C++ Code

_No direct code for this theory/concept lecture._

## 2. BS-1. Binary Search Introduction | Iterative | Recursive | Overflow Cases

### Problem

Find the index of target in a sorted array; return -1 if it is absent.

### Revision Hints

- Use mid = low + (high - low) / 2 because low + high can overflow.

### Approach

- If nums[mid] is smaller, move right; if it is larger, move left.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1) iterative, O(log N) recursive stack`

### C++ Code

```cpp
int binarySearchIterative(const vector<int>& nums, int target) {
    int low = 0;
    int high = (nums.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Hint: If mid is the target, the answer is found.
        if (nums[mid] == target) {
            return mid;
        }

        // Hint: The array is sorted, so if target is greater, discard the left half.
        if (nums[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

int binarySearchRecursiveHelper(const vector<int>& nums, int low, int high, int target) {
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (nums[mid] == target) {
        return mid;
    }

    if (nums[mid] < target) {
        return binarySearchRecursiveHelper(nums, mid + 1, high, target);
    }

    return binarySearchRecursiveHelper(nums, low, mid - 1, target);
}

int binarySearchRecursive(const vector<int>& nums, int target) {
    return binarySearchRecursiveHelper(nums, 0, (nums.size()) - 1, target);
}
```

## 3. BS-2. Lower Bound | Upper Bound | Search Insert Position | Floor and Ceil

### Problem

Find bound/index/value type answers in a sorted array.

### Revision Hints

- Lower Bound = first index where arr[index] >= x.
- Upper Bound = first index where arr[index] > x.
- Search Insert Position same as lower bound.
- Floor = greatest value <= x; Ceil = smallest value >= x.

### Approach

- Store the possible answer, then move left/right to search for a better candidate.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int lowerBoundIndex(const vector<int>& arr, int x) {
    int low = 0;
    int high = (arr.size()) - 1;
    int answer = (arr.size());

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Hint: arr[mid] can be a valid lower bound, but we need the first such index.
        if (arr[mid] >= x) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}

int upperBoundIndex(const vector<int>& arr, int x) {
    int low = 0;
    int high = (arr.size()) - 1;
    int answer = (arr.size());

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Hint: Upper bound is the first index of an element strictly greater than x.
        if (arr[mid] > x) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}

int searchInsertPosition(const vector<int>& nums, int target) {
    return lowerBoundIndex(nums, target);
}

int floorInSortedArray(const vector<int>& arr, int x) {
    int low = 0;
    int high = (arr.size()) - 1;
    int answer = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Hint: If arr[mid] <= x, it is a floor candidate; a larger floor may exist on the right.
        if (arr[mid] <= x) {
            answer = arr[mid];
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return answer;
}

int ceilInSortedArray(const vector<int>& arr, int x) {
    int low = 0;
    int high = (arr.size()) - 1;
    int answer = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Hint: If arr[mid] >= x, it is a ceil candidate; a smaller ceil may exist on the left.
        if (arr[mid] >= x) {
            answer = arr[mid];
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}

pair<int, int> getFloorAndCeil(const vector<int>& arr, int x) {
    return {floorInSortedArray(arr, x), ceilInSortedArray(arr, x)};
}
```

## 4. BS-3. First and Last Occurrences | Count Occurrences

### Problem

Find the first position, last position, and count of x in a sorted array.

### Revision Hints

- Do not stop after finding x once:
- For first occurrence, continue searching on the left side.
- For last occurrence, continue searching on the right side.

### Approach

- Use two binary searches.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int firstOccurrenceIndex(const vector<int>& arr, int x) {
    int low = 0;
    int high = (arr.size()) - 1;
    int first = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x) {
            first = mid;
            high = mid - 1;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return first;
}

int lastOccurrenceIndex(const vector<int>& arr, int x) {
    int low = 0;
    int high = (arr.size()) - 1;
    int last = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x) {
            last = mid;
            low = mid + 1;
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return last;
}

pair<int, int> firstAndLastPosition(const vector<int>& arr, int x) {
    int first = firstOccurrenceIndex(arr, x);

    if (first == -1) {
        return {-1, -1};
    }

    int last = lastOccurrenceIndex(arr, x);
    return {first, last};
}

int countOccurrencesInSortedArray(const vector<int>& arr, int x) {
    pair<int, int> positions = firstAndLastPosition(arr, x);

    if (positions.first == -1) {
        return 0;
    }

    return positions.second - positions.first + 1;
}
```

## 5. BS-4. Search Element in Rotated Sorted Array - I

### Problem

Search target in a rotated sorted array with distinct elements.

### Revision Hints

- At every mid, at least one half is guaranteed to be sorted.

### Approach

1. If the left half is sorted, check whether target lies in that range.
2. Otherwise, the right half is sorted; check whether target lies in that range.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int searchInRotatedSortedArrayI(const vector<int>& arr, int target) {
    int low = 0;
    int high = (arr.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        // Hint: The left half is sorted.
        if (arr[low] <= arr[mid]) {
            if (arr[low] <= target && target <= arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else {
            // Hint: The right half is sorted.
            if (arr[mid] <= target && target <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return -1;
}
```

## 6. BS-5. Search Element in Rotated Sorted Array - II

### Problem

Check whether target exists in a rotated sorted array with duplicates.

### Revision Hints

- arr[low] == arr[mid] == arr[high] creates ambiguity; shrink using low++ and high--.

### Approach

- Use the same sorted-half logic, but handle duplicate ambiguity by shrinking boundaries.

### Complexity

**Time Complexity:**
- `O(log N) average, O(N) worst case due to duplicates`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
bool searchInRotatedSortedArrayII(const vector<int>& arr, int target) {
    int low = 0;
    int high = (arr.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return true;
        }

        // Hint: Equal boundaries make it impossible to identify the sorted half, so shrink.
        if (arr[low] == arr[mid] && arr[mid] == arr[high]) {
            low++;
            high--;
            continue;
        }

        if (arr[low] <= arr[mid]) {
            if (arr[low] <= target && target <= arr[mid]) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        } else {
            if (arr[mid] <= target && target <= arr[high]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
    }

    return false;
}
```

## 7. BS-6. Minimum in Rotated Sorted Array

### Problem

Find the minimum element in a rotated sorted array  (unique).

### Revision Hints

- If arr[low] <= arr[high], the current search space is already sorted; arr[low] is the minimum.

### Approach

- Store the minimum of the sorted half, then search the unsorted half for the actual pivot/minimum.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int minimumInRotatedSortedArray(const vector<int>& arr) {
    if (arr.empty()) {
        return -1;
    }

    int low = 0;
    int high = (arr.size()) - 1;
    int answer = INT_MAX;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[low] <= arr[high]) {
            answer = min(answer, arr[low]);
            break;
        }

        if (arr[low] <= arr[mid]) {
            answer = min(answer, arr[low]);
            low = mid + 1;
        } else {
            answer = min(answer, arr[mid]);
            high = mid - 1;
        }
    }

    return answer;
}
```
## 7. BS-6. Minimum in Rotated Sorted Array duplicates

### Problem

Find the minimum element in a rotated sorted array  (duplicates).

### Revision Hints
- If arr[low] =arr[mid]= arr[high], this will create ambigiutyin finding sorted half;
so shrink  low++, high--;just like serach in duplicates;

- If arr[low] <= arr[high], the current search space is already sorted; arr[low] is the minimum.

### Approach

- Store the minimum of the sorted half, then search the unsorted half for the actual pivot/minimum.

### Complexity

**Time Complexity:**
- `O(log N)`
Rotated sorted array + duplicates → worst-case O(N) because when low == mid == high, we may only shrink the search space.

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int minimumInRotatedSortedArray(const vector<int>& arr) {
    if (arr.empty()) {
        return -1;
    }

    int low = 0;
    int high = (arr.size()) - 1;
    int answer = INT_MAX;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if((arr[low] == arr[high])&&  (arr[mid] == arr[high] ) ){
             low ++; high--;
             continue;
        }

        if (arr[low] <= arr[high]) {
            answer = min(answer, arr[low]);
            break;
        }

        if (arr[low] <= arr[mid]) {
            answer = min(answer, arr[low]);
            low = mid + 1;
        } else {
            answer = min(answer, arr[mid]);
            high = mid - 1;
        }
    }

    return answer;
}
```

## 8. BS-7. Find Out How Many Times Array Has Been Rotated

### Problem

Find the rotation count of a rotated sorted array ( unique).

### Revision Hints

- Rotation count = index of the minimum element.

### Approach

- Same as BS-6, but store the index along with the minimum value.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int rotationCountInRotatedArray(const vector<int>& arr) {
    if (arr.empty()) {
        return 0;
    }

    int low = 0;
    int high = (arr.size()) - 1;
    int answer = INT_MAX;
    int answerIndex = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[low] <= arr[high]) {
            if (arr[low] < answer) {
                answer = arr[low];
                answerIndex = low;
            }
            break;
        }

        if (arr[low] <= arr[mid]) {
            if (arr[low] < answer) {
                answer = arr[low];
                answerIndex = low;
            }
            low = mid + 1;
        } else {
            if (arr[mid] < answer) {
                answer = arr[mid];
                answerIndex = mid;
            }
            high = mid - 1;
        }
    }

    return answerIndex;
}
```

## 8. BS-7. Find Out How Many Times Array Has Been Rotated

### Problem

Find the rotation count of a rotated sorted array ( dulicate).

### Revision Hints

- Rotation count = index of the minimum element.

### Approach

- Same as BS-6, but store the index along with the minimum value.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int rotationCountInRotatedArray(const vector<int>& arr) {
    if (arr.empty()) {
        return 0;
    }

    int low = 0;
    int high = (arr.size()) - 1;
    int answer = INT_MAX;
    int answerIndex = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if(arr[low]==arr[mid ] && arr[mid]== arr[high]){
            low++;
             high--;
              continue;
        }

        if (arr[low] <= arr[high]) {
            if (arr[low] < answer) {
                answer = arr[low];
                answerIndex = low;
            }
            break;
        }

        if (arr[low] <= arr[mid]) {
            if (arr[low] < answer) {
                answer = arr[low];
                answerIndex = low;
            }
            low = mid + 1;
        } else {
            if (arr[mid] < answer) {
                answer = arr[mid];
                answerIndex = mid;
            }
            high = mid - 1;
        }
    }

    // Find first occurrence of minimum
    while (answerIndex > 0 && arr[answerIndex - 1] == answer) {
        answerIndex--;
    }

    return answerIndex;
}
```

## 9. BS-8. Single Element in Sorted Array

### Problem

In a sorted array, every element appears exactly twice except one; find that single element.

### Revision Hints

- Pairing pattern before the single element: even index has the first copy, odd index has the second copy.(e, o)
- After the single element, the pairing pattern flips. (o ,e)


### Approach

- Use mid parity and neighbor comparison to decide whether the single element is on the left or right.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int singleNonDuplicateSortedArray(const vector<int>& arr) {
    int n = (arr.size());

    if (n == 1) {
        return arr[0];
    }

    if (arr[0] != arr[1]) {
        return arr[0];
    }

    if (arr[n - 1] != arr[n - 2]) {
        return arr[n - 1];
    }

    int low = 1;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] != arr[mid - 1] && arr[mid] != arr[mid + 1]) {
            return arr[mid];
        }

        //

        // Hint: If the pairing pattern is still correct, the single element lies on the right.
        if ((mid % 2 == 1 && arr[mid] == arr[mid - 1]) || (mid % 2 == 0 && arr[mid] == arr[mid + 1])) {
            low = mid + 1;// i am standing on the left side of single element;
        } else {
            high = mid - 1;// i am standing on the riggt side of single element;
        }
    }

    return -1;
}
```

## 10. BS-9. Find Peak Element

### Problem

Find a peak index in a 1D array where arr[i] is greater than its neighbors.

### Revision Hints

- Observe the slope; on an increasing slope, a peak is guaranteed on the right.

### Approach

- Handle edge cases, then compare mid with its neighbors.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int findPeakElement1D(const vector<int>& arr) {
    int n = (arr.size());

    if (n == 0) {
        return -1;
    }

    if (n == 1) {
        return 0;
    }

    if (arr[0] > arr[1]) {
        return 0;
    }

    if (arr[n - 1] > arr[n - 2]) {
        return n - 1;
    }

    int low = 1;
    int high = n - 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1]) {
            return mid;
        }

        // Hint: The right side is uphill, so a peak is guaranteed on the right.
        if (arr[mid] > arr[mid - 1]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}
```

## 11. BS-10. Finding Sqrt of a Number Using Binary Search

### Problem

Given n, return floor(sqrt(n)).

### Revision Hints

- mid * mid can overflow, so use long long.

### Approach

- If mid^2 <= n, mid is a possible answer; move right for a bigger valid answer.

### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int floorSqrt(int n) {
    int low = 1;
    int high = n;
    int answer = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long square = 1LL * mid * mid;

        if (square <= n) {
            answer = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return answer;
}
```

## 12. BS-11. Find the Nth Root of an Integer

### Problem

Given n and m, find integer x such that x^n == m; return -1 if it does not exist.

### Revision Hints

- While calculating power, stop as soon as the value becomes greater than m.

### Approach

- Search space for x is [1, m]; compare x^n with m.

### Complexity

**Time Complexity:**
- `O(log M * N)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int comparePowerWithTarget(int base, int exponent, int target) {
    long long product = 1;

    for (int count = 1; count <= exponent; count++) {
        product *= base;

        // Hint: Exact value is not needed; return "greater" as soon as target is crossed.
        if (product > target) {
            return 2;
        }
    }

    if (product == target) {
        return 1;
    }

    return 0;
}

int nthRoot(int n, int m) {
    int low = 1;
    int high = m;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int comparison = comparePowerWithTarget(mid, n, m);

        if (comparison == 1) {
            return mid;
        }

        if (comparison == 0) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}
```

## 13. BS-12. Koko Eating Bananas

### Problem

Find the minimum eating speed so Koko can finish all banana piles within h hours.

### Revision Hints

- As speed increases, required hours decrease monotonically.

### Approach

- Answer-space BS on speed [1, maxPile].

### Complexity

**Time Complexity:**
- `O(N * log(max pile))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
long long hoursRequiredToEatBananas(const vector<int>& piles, int hourlySpeed) {
    long long hours = 0;

    for (int pile : piles) {
        // Hint: ceil(pile / speed) without floating point.
        hours += (pile + hourlySpeed - 1LL) / hourlySpeed;
    }

    return hours;
}

int minEatingSpeedKoko(const vector<int>& piles, int h) {
    int low = 1;
    int high = *max_element(piles.begin(), piles.end());
    int answer = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        long long requiredHours = hoursRequiredToEatBananas(piles, mid);

        if (requiredHours <= h) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}
```

## 14. BS-13. Minimum Days to Make M Bouquets

### Problem

Make m bouquets, each with k adjacent flowers; find the minimum day.

### Revision Hints

- As days increase, the number of bloomed flowers increases, so possible/not possible is monotonic.

### Approach

- Answer-space BS on day [min bloom, max bloom].

### Complexity

**Time Complexity:**
- `O(N * log(max bloom - min bloom + 1))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
class Solution {
            int check(vector< int>& bloomdays, int mid ,int m,int k ){
                
                 int n= bloomdays.size();
                vector<int>temp(n,0);
                for( int i=0; i<n ;i++){
                    if(bloomdays[i]<=mid){
                         temp[i]=1;
                    }

                }
                 int made=0;
                 int count =0;
                 for( int i =0; i< n ;i++){
                       if( temp[i]==1){
                          count++;
                          if(count==k){
                            made++;
                            count=0;
                          }
                       }
                       else{
                         count=0;
                       }
                 }
                 return made>=m;


            }

public:
    int minDays(vector<int>& bloomDay, int m, int k) {
     int s=1,e=*max_element(bloomDay.begin(), bloomDay.end()), ans=-1;
     while( s<=e){
         int mid=(s+e)/2;
         if( check(  bloomDay,mid,m ,k)){
            ans= mid;
            e=mid-1;
         }
         else{
             s= mid+1;
         }
     }
     return ans;



        
    }
};
```

## 15. BS-14. Find the Smallest Divisor Given a Threshold

### Problem

Find the smallest divisor d such that the sum of ceil(nums[i] / d) is <= threshold.

### Revision Hints

- As divisor increases, the sum decreases; this creates a monotonic predicate.

### Approach

- Answer-space BS on divisor [1, max(nums)].

### Complexity

**Time Complexity:**
- `O(N * log(max element))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int sumByDivisor(const vector<int>& nums, int divisor) {
    int sum = 0;

    for (int num : nums) {
        sum += (num + divisor - 1) / divisor;
    }

    return sum;
}

int smallestDivisorGivenThreshold(const vector<int>& nums, int threshold) {
    int low = 1;
    int high = *max_element(nums.begin(), nums.end());
    int answer = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (sumByDivisor(nums, mid) <= threshold) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}
```

## 16. BS-15. Capacity to Ship Packages Within D Days

### Problem

Given weights and days, find the minimum ship capacity.

### Revision Hints

- Minimum capacity must be at least the maximum weight.
- Maximum capacity can be the total sum of weights.
- As capacity increases, days needed decrease.

### Approach

- Answer-space BS on capacity.

### Complexity

**Time Complexity:**
- `O(N * log(sum(weights) - max(weights) + 1))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int daysNeededToShip(const vector<int>& weights, int capacity) {
    int days = 1;
    int currentLoad = 0;

    for (int weight : weights) {
        if (currentLoad + weight > capacity) {
            days++;
            currentLoad = weight;
        } else {
            currentLoad += weight;
        }
    }

    return days;
}

int shipWithinDays(const vector<int>& weights, int days) {
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);
    int answer = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (daysNeededToShip(weights, mid) <= days) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}
```

## 17. BS-16. Kth Missing Positive Number

### Problem

Find the kth missing positive number in a sorted positive array.

### Revision Hints

- Missing numbers till index mid = arr[mid] - (mid + 1).

### Approach

- If missing count < k, the answer lies on the right side; otherwise it lies on the left side.

## brute force
```cpp
int kthMissingPositiveNumber(const vector<int>& arr, int k) {
    // let say  kth missig number k; if koi isse <= ayega to k ko increment kr denge
       for( int i =0; i< n; i++){
           if(arr[i]<=k)k++;
           else{
             break;
           }
       }
       return k;
    }
    tc O(n);
```



### Complexity

**Time Complexity:**
- `O(log N)`

**Space Complexity:**

- `O(1)`

### C++ Code

```cpp
int kthMissingPositiveNumber(const vector<int>& arr, int k) {
    int low = 0;
    int high = (arr.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int missingTillMid = arr[mid] - (mid + 1);

        if (missingTillMid < k) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Hint: After the loop, low elements are present before the answer, so answer = k + low.
    return k + low;// we can also return high+1+k  ///because low= high +1;
}
# Kth Missing Positive Number — `k + low` Logic

## 1. Problem

Given a sorted array of positive integers, find the **kth missing positive number**.

Example:

```text
arr = [2, 3, 4, 7, 11]
k = 5
```

Missing numbers:

```text
1, 5, 6, 8, 9, 10, ...
```

Therefore:

```text
5th missing = 9
```

---

## 2. Important Formula

At index `mid`:

```cpp
int missingTillMid = arr[mid] - (mid + 1);
```

### Why?

From `1` to `arr[mid]`, there are:

```text
arr[mid]
```

positive numbers.

But the array contains:

```text
mid + 1
```

numbers up to index `mid`.

Therefore:

```text
Missing numbers
= Total numbers - Present numbers

= arr[mid] - (mid + 1)
```

Example:

```text
arr[mid] = 7
mid = 3

Missing = 7 - 4
        = 3
```

The missing numbers are:

```text
1, 5, 6
```

---

# 3. What Does `low` Mean?

After binary search finishes:

```cpp
low
```

represents the **number of array elements that are before the kth missing number**.

For:

```text
arr = [2, 3, 4, 7, 11]
k = 5
```

Binary search finishes with:

```text
low = 4
high = 3
```

So there are `4` present elements before the answer:

```text
2, 3, 4, 7
↑           ↑
4 elements
```

---

# 4. Why Is the Answer `k + low`?

The answer contains two types of numbers before/reaching it:

```text
Missing numbers + Present numbers
```

We need:

```text
k = 5 missing numbers
```

And binary search tells us:

```text
low = 4 present numbers
```

Therefore:

```text
Answer = k + low
       = 5 + 4
       = 9
```

So:

```cpp
return k + low;
```

---

# 5. Visual Understanding

For:

```text
arr = [2, 3, 4, 7, 11]
k = 5
```

Numbers:

```text
1  2  3  4  5  6  7  8  9
   P  P  P     M  M  P  M
   └──────┘
   4 present numbers

Missing:
1, 5, 6, 8, 9
└────────────────┘
     5 missing
```

Therefore:

```text
4 present + 5 missing = 9
```

Hence:

```cpp
answer = low + k;
```

---

# 6. Why Does Binary Search Produce This `low`?

The condition is:

```cpp
missingTillMid < k
```

If fewer than `k` numbers are missing:

```cpp
low = mid + 1;
```

We need to move right.

If at least `k` numbers are missing:

```cpp
high = mid - 1;
```

We move left.

Eventually:

```text
low = first position where missingTillMid >= k
```

This means all elements before `low` are present before the answer.

Therefore, the number of such present elements is exactly:

```text
low
```

---

# 7. Why `high + 1 + k` Also Works

When binary search ends:

```text
low > high
```

Since they are adjacent:

```text
low = high + 1
```

Therefore:

```text
k + low
= k + (high + 1)
= k + high + 1
```

So both are correct:

```cpp
return k + low;
```

and:

```cpp
return k + high + 1;
```

`k + low` is usually clearer.

---

# 8. General Binary Search Pattern

This problem teaches an important pattern:

```text
Binary search finds a boundary
            ↓
low ends at the first valid position
            ↓
use low to calculate the answer
```

The binary search does **not necessarily return the answer directly**.

Instead, it finds:

```text
how many array elements are before the answer
```

Then:

```text
answer = required_missing_count + elements_before_answer

       = k + low
```

---

# 9. Code

```cpp
int kthMissingPositiveNumber(const vector<int>& arr, int k) {

    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {

        int mid = low + (high - low) / 2;

        int missingTillMid = arr[mid] - (mid + 1);

        if (missingTillMid < k) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }

    return k + low;
}
```

## Key line to remember

```cpp
return k + low;
```

**Meaning:**

```text
k   = number of missing numbers we need
low = number of present array elements before the answer

answer = k + low
```

### Interview takeaway

Whenever you see:

```cpp
low = mid + 1;
high = mid - 1;
```

and the loop finishes with:

```text
low = first position satisfying the condition
```

ask:

> **What does `low` represent after the binary search?**

In this problem:

```text
low = number of present elements before the answer
```

That directly leads to:

```text
answer = k + low
```

``

## 18. BS-17. Aggressive Cows

### Problem

Place C cows in stalls such that the minimum pair distance is maximized.

### Revision Hints

- If distance d is possible, all smaller distances are also possible.

### Approach

- Sort stalls, then answer-space BS on minimum distance.

### Complexity

**Time Complexity:**
- `O(N log N + N * log(max distance))`

**Space Complexity:**
- `O(1) extra`

### C++ Code

```cpp
bool canPlaceCows(const vector<int>& stalls, int minimumDistance, int cows) {
    int cowsPlaced = 1;
    int lastStall = stalls[0];

    for (int index = 1; index < stalls.size(); index++) {
        if (stalls[index] - lastStall >= minimumDistance) {
            cowsPlaced++;
            lastStall = stalls[index];
        }

        if (cowsPlaced >= cows) {
            return true;
        }
    }

    return false;
}

int aggressiveCows(vector<int> stalls, int cows) {
    sort(stalls.begin(), stalls.end());

    int low = 1;
    int high = stalls.back() - stalls.front();
    int answer = 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canPlaceCows(stalls, mid, cows)) {
            answer = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return answer;
}
```

## 19. BS-18. Allocate Books

### Problem

Allocate books contiguously so each student gets at least one book; minimize the maximum pages.

### Revision Hints

- Minimum possible max pages = max single book.
- Maximum possible max pages = total pages.
- As max pages increases, required students decrease.

### Approach

- Answer-space BS on maximum pages allowed.

### Complexity

**Time Complexity:**
- `O(N * log(sum pages - max pages + 1))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int studentsRequiredForPages(const vector<int>& pages, int maxPagesAllowed) {
    int students = 1;
    int currentPages = 0;

    for (int pageCount : pages) {
        if (currentPages + pageCount > maxPagesAllowed) {
            students++;
            currentPages = pageCount;
        } else {
            currentPages += pageCount;
        }
    }

    return students;
}

int allocateBooks(const vector<int>& pages, int students) {
    int n = (pages.size());

    if (students > n) {
        return -1;
    }

    int low = *max_element(pages.begin(), pages.end());
    int high = accumulate(pages.begin(), pages.end(), 0);
    int answer = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (studentsRequiredForPages(pages, mid) <= students) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}
```

## 20. BS-19. Painter's Partition and Split Array - Largest Sum

### Problem

Split the array into k contiguous parts and minimize the largest part sum.

### Revision Hints

- This is the same pattern as Allocate Books; only the names change.

### Approach

- Answer-space BS on maximum allowed partition sum.

### Complexity

**Time Complexity:**
- `O(N * log(sum - max element + 1))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
class Solution {
public:
    int splitArray(vector<int>& nums, int k) {
         int n =nums.size();
         if( k>n)return -1;
         long long s = *max_element(nums.begin(), nums.end());
         long long e = accumulate(nums.begin(), nums.end(), 0LL);
           long long ans=-1;
          while( s<=e){
              long long mid= (s+e)/2;
             auto check=[&](  long long mid)-> bool{
                  long long count=1;
                  long long total=0;
                  for( int i=0; i< n ;i++){
                     if( total+nums[i]>mid){
                         count++;
                          total= nums[i];
                     }else{
                         total+=nums[i];
                     }
                  }
                  return count<=k;
             };
             if( check( mid)){
                 ans= mid; e=mid-1;
             }
             else{
                 s= mid+1;
             }


          }
          return (int)ans;
        
        
    }
};

int paintersPartition(const vector<int>& boards, int painters) {
    return splitArrayLargestSum(boards, painters);
}
```

## 21. BS-20. Minimise Maximum Distance Between Gas Stations

### Problem

Add K new gas stations and minimize the maximum distance between adjacent gas stations.

### Revision Hints

- This is decimal answer-space binary search.

### Approach

1. Brute: Split the largest section K times by scanning.
2. Better: Use a max heap to find the largest section quickly.
3. Optimal: Binary search on the distance answer; if required stations <= K, the distance is possible.

### Complexity

**Time Complexity:**
- ``
- `- Brute: O(K * N)`
- `- Better: O(N log N + K log N)`
- `- Optimal: O(N * log(range / precision))`

**Space Complexity:**
- ``
- `- Brute: O(N)`
- `- Better: O(N)`
- `- Optimal: O(1)`

### C++ Code

```cpp
double minimiseMaximumDistanceGasStationsBrute(const vector<int>& stations, int k) {
    int n = (stations.size());
    vector<int> insertedStations(n - 1, 0);

    for (int gasStation = 1; gasStation <= k; gasStation++) {
        double maximumSection = -1.0;
        int maximumSectionIndex = -1;

        for (int index = 0; index < n - 1; index++) {
            double sectionLength = static_cast<double>(stations[index + 1] - stations[index]) / (insertedStations[index] + 1);

            if (sectionLength > maximumSection) {
                maximumSection = sectionLength;
                maximumSectionIndex = index;
            }
        }

        insertedStations[maximumSectionIndex]++;
    }

    double answer = 0.0;

    for (int index = 0; index < n - 1; index++) {
        double sectionLength = static_cast<double>(stations[index + 1] - stations[index]) / (insertedStations[index] + 1);
        answer = max(answer, sectionLength);
    }

    return answer;
}

double minimiseMaximumDistanceGasStationsBetter(const vector<int>& stations, int k) {
    int n = (stations.size());
    vector<int> insertedStations(n - 1, 0);
    priority_queue<pair<double, int>> maxHeap;

    for (int index = 0; index < n - 1; index++) {
        maxHeap.push({static_cast<double>(stations[index + 1] - stations[index]), index});
    }

    for (int gasStation = 1; gasStation <= k; gasStation++) {
        int sectionIndex = maxHeap.top().second;
        maxHeap.pop();

        insertedStations[sectionIndex]++;
        double originalDifference = stations[sectionIndex + 1] - stations[sectionIndex];
        double newSectionLength = originalDifference / (insertedStations[sectionIndex] + 1);

        maxHeap.push({newSectionLength, sectionIndex});
    }

    return maxHeap.top().first;
}

class Solution {
public:
    long double minimiseMaxDistance(vector<int> &arr, int k) {
         int n = arr.size();
         auto check= [&]( double mid)-> bool{
              int needtoplace=0;
              for( int i=0;i< n-1; i++){
                   needtoplace+=((ceil((arr[i+1]-arr[i])/mid))-1);
              }
              return needtoplace<=k;


         };
         double s=1e-8,e=1e9, ans=-1;
          for( int i =0; i<60; i++){

            double mid=(s+e)/2;

            if( check( mid)){
                ans= mid;
                e=mid;
            }
            else{
                 s=mid;
            }
          }
          return ans;
    }
};
```

## 22. BS-21. Median of Two Sorted Arrays of Different Sizes

### Problem

Find the median of two sorted arrays.

### Revision Hints

- Brute: Merge both arrays and find the median.
- Better: Simulate merge and track only the median positions.
- Optimal: Binary search on the smaller array and keep the left half size fixed.

### Approach

- Partition such that max(left part) <= min(right part).

### Complexity

**Time Complexity:**
- ``
- `- Brute: O(N1 + N2)`
- `- Better: O(N1 + N2)`
- `- Optimal: O(log(min(N1, N2)))`

**Space Complexity:**
- ``
- `- Brute: O(N1 + N2)`
- `- Better: O(1)`
- `- Optimal: O(1)`

### C++ Code

```cpp
double medianOfTwoSortedArraysBrute(const vector<int>& first, const vector<int>& second) {
    vector<int> merged;
    int firstIndex = 0;
    int secondIndex = 0;

    while (firstIndex < (first.size()) && secondIndex < (second.size())) {
        if (first[firstIndex] <= second[secondIndex]) {
            merged.push_back(first[firstIndex++]);
        } else {
            merged.push_back(second[secondIndex++]);
        }
    }

    while (firstIndex < (first.size())) {
        merged.push_back(first[firstIndex++]);
    }

    while (secondIndex < (second.size())) {
        merged.push_back(second[secondIndex++]);
    }

    int total = (merged.size());

    if (total % 2 == 1) {
        return merged[total / 2];
    }

    return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
}

double medianOfTwoSortedArraysBetter(const vector<int>& first, const vector<int>& second) {
    int n1 = (first.size());
    int n2 = (second.size());
    int total = n1 + n2;
    int medianIndex2 = total / 2;
    int medianIndex1 = medianIndex2 - 1;
    int index1 = 0;
    int index2 = 0;
    int count = 0;
    int element1 = -1;
    int element2 = -1;

    while (index1 < n1 && index2 < n2) {
        int value;

        if (first[index1] <= second[index2]) {
            value = first[index1++];
        } else {
            value = second[index2++];
        }

        if (count == medianIndex1) {
            element1 = value;
        }

        if (count == medianIndex2) {
            element2 = value;
            break;
        }

        count++;
    }

    while (count <= medianIndex2 && index1 < n1) {
        if (count == medianIndex1) {
            element1 = first[index1];
        }

        if (count == medianIndex2) {
            element2 = first[index1];
            break;
        }

        index1++;
        count++;
    }

    while (count <= medianIndex2 && index2 < n2) {
        if (count == medianIndex1) {
            element1 = second[index2];
        }

        if (count == medianIndex2) {
            element2 = second[index2];
            break;
        }

        index2++;
        count++;
    }

    if (total % 2 == 1) {
        return element2;
    }

    return (element1 + element2) / 2.0;
}

double medianOfTwoSortedArraysOptimal(const vector<int>& first, const vector<int>& second) {
    if (first.size() > second.size()) {
        return medianOfTwoSortedArraysOptimal(second, first);
    }

    int n1 = (first.size());
    int n2 = (second.size());
    int total = n1 + n2;
    int leftSize = (total + 1) / 2;
    int low = 0;
    int high = n1;

    while (low <= high) {
        int cut1 = low + (high - low) / 2;
        int cut2 = leftSize - cut1;

        int left1 = (cut1 == 0) ? INT_MIN : first[cut1 - 1];
        int left2 = (cut2 == 0) ? INT_MIN : second[cut2 - 1];
        int right1 = (cut1 == n1) ? INT_MAX : first[cut1];
        int right2 = (cut2 == n2) ? INT_MAX : second[cut2];

        if (left1 <= right2 && left2 <= right1) {
            if (total % 2 == 1) {
                return max(left1, left2);
            }

            return (max(left1, left2) + min(right1, right2)) / 2.0;
        }

        if (left1 > right2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }

    return 0.0;
}
```

## 23. BS-22. K-th Element of Two Sorted Arrays

### Problem

Find the kth element in the merged sorted order of two sorted arrays.

### Revision Hints

- This is the generalized version of the optimal median approach.

### Approach

- Binary search on the smaller array and keep exactly k elements on the left side.

### Complexity

**Time Complexity:**
- `O(log(min(N1, N2)))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int kthElementOfTwoSortedArrays(const vector<int>& first, const vector<int>& second, int k) {
    if (first.size() > second.size()) {
        return kthElementOfTwoSortedArrays(second, first, k);
    }

    int n1 = (first.size());
    int n2 = (second.size());
    int low = max(0, k - n2);
    int high = min(k, n1);

    while (low <= high) {
        int cut1 = low + (high - low) / 2;
        int cut2 = k - cut1;

        int left1 = (cut1 == 0) ? INT_MIN : first[cut1 - 1];
        int left2 = (cut2 == 0) ? INT_MIN : second[cut2 - 1];
        int right1 = (cut1 == n1) ? INT_MAX : first[cut1];
        int right2 = (cut2 == n2) ? INT_MAX : second[cut2];

        if (left1 <= right2 && left2 <= right1) {
            return max(left1, left2);
        }

        if (left1 > right2) {
            high = cut1 - 1;
        } else {
            low = cut1 + 1;
        }
    }

    return -1;
}
```

## 24. BS-23. Row with Maximum Number of 1s

### Problem

Return the index of the row with the maximum number of 1s in a binary matrix.\

### Revision Hints

- Each row is sorted, so the first 1 can be found using lower bound.
## bruteforce 
 count for every row no. of ones   tc(n*m)

###  optimal Approach

- Apply lower_bound(1) on each row, count = columns - firstOneIndex.

### Complexity

**Time Complexity:**
- `O(N * log M)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int rowWithMaximumOnes(const vector<vector<int>>& matrix) {
    int rows = (matrix.size());
    int columns = matrix.empty() ? 0 : (matrix[0].size());
    int maximumOnes = 0;
    int rowIndex = -1;

    for (int row = 0; row < rows; row++) {
        int firstOne = lowerBoundIndex(matrix[row], 1);
        int onesCount = columns - firstOne;

        if (onesCount > maximumOnes) {
            maximumOnes = onesCount;
            rowIndex = row;
        }
    }

    return rowIndex;
}
```

## 25. BS-24. Search in a 2D Matrix - I

### Problem

Matrix is sorted like a flattened 1D array; check whether target is present.

### Revision Hints


- virtualIndex -> row = index / columns, col = index % columns.
###   brute force Approach
iterate complete matrix 
tc O(n*m)
###  better Approach
```cpp
for( int i=0; i< n;i++){
      if(mat[i][0]<=target && target <=matrix[i][m-1]){
         return binarysearchelement(matrix[i], target);
      }
}
return false;
//tc O(n)+log( m);
```



### Approach

- Treat the entire matrix as a sorted 1D array and apply binary search.

### Complexity

**Time Complexity:**
- `O(log(N * M))`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
bool searchMatrixI(const vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }

    int rows = (matrix.size());
    int columns = (matrix[0].size());
    int low = 0;
    int high = rows * columns - 1;//matrix is sorted like   one d   // all thel elements of i+1  are>=  [i][m-1];;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int row = mid / columns;
        int column = mid % columns;

        if (matrix[row][column] == target) {
            return true;
        }

        if (matrix[row][column] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return false;
}
```

## 26. BS-25. Search in a 2D Matrix - II

### Problem

Search target in a matrix where rows and columns are sorted.

## brute force
iterate complete aaaray 
 tc ( n*m);
 ## better 
 ```cpp
for( int i =0; i< n;i++){
       int index=bs( matrix[i], target);// binary search is normal binary search
       if( inddex!= -1)return {i, index};
}
return {-1,-1};
//tc =O(n log m);
```


### Revision Hints

- Start from the top-right; move left for smaller values and down for larger values.

### Approach

- At every step, eliminate one row or one column.

### Complexity

**Time Complexity:**
- `O(N + M)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
bool searchMatrixII(const vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }

    int row = 0;
    int column = matrix[0].size() - 1;

    while (row < matrix.size() && column >= 0) {
        if (matrix[row][column] == target) {
            return true;
        }

        if (matrix[row][column] < target) {
            row++;
        } else {
            column--;
        }
    }

    return false;
}
```

## 27. BS-26. Find Peak Element-II

### Problem

Find a peak cell in a 2D grid where the value is greater than left/right/up/down neighbors.

### Revision Hints

- Take the maximum element in the current column; if it is greater than left and right, it is a peak.
## brute force
check for every element 
 tc O(n*m*4)// 4 is for checkking its neighbours

## better approach;
maximum element of the matrix is peak;
tc O(n*m)

### optimal Approach

- Binary search on columns, scan the maximum row, then move left/right based on the larger neighbor.

### Complexity

**Time Complexity:**
- `O(N * log M)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int rowOfMaximumElementInColumn(const vector<vector<int>>& matrix, int column) {
     int maxvalue=-1;
     index=-1;

    for (int row = 0; row < (matrix.size()); row++) {
        if (matrix[row][column] > maxvalue) {
            maxvalue=matrix[row][col];
            index= row;
        }
    }

    return index;
}

vector<int> findPeakGrid(const vector<vector<int>>& matrix) {
    int columns = (matrix[0].size());
    int low = 0;
    int high = columns - 1;

    while (low <= high) {
        int midColumn = low + (high - low) / 2;
        int maxRow = rowOfMaximumElementInColumn(matrix, midColumn);

        int leftValue = (midColumn - 1 >= 0) ? matrix[maxRow][midColumn - 1] : -1;
        int rightValue = (midColumn + 1 < columns) ? matrix[maxRow][midColumn + 1] : -1;
        int currentValue = matrix[maxRow][midColumn];

        if (currentValue > leftValue && currentValue > rightValue) {
            return {maxRow, midColumn};
        }

        if (leftValue > currentValue) {
            high = midColumn - 1;
        } else {
            low = midColumn + 1;
        }
    }

    return {-1, -1};
}
```

## 28. BS-27. Median in a Row Wise Sorted Matrix

### Problem

Find the median of a row-wise sorted matrix where m  and n is odd.


### Revision Hints

- Use the count of elements <= mid; binary search on values.
### Approach
brute force convert 2D to one D then sort then find middle  tc: (n*m)+ ( m*n)log( m*n);

### Approach

- Search space minimum matrix value to maximum matrix value, count <= mid using upper bound in each row.

### Complexity

**Time Complexity:**
- `O(log(maxValue - minValue + 1) * N * log M)`

**Space Complexity:**
- `O(1)`

### C++ Code

```cpp
int upperBoundInRow(const vector<int>& row, int x) {
    int low = 0;
    int high = (row.size()) - 1;
    int answer = (row.size());

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (row[mid] > x) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}

int countLessThanOrEqualToMid(const vector<vector<int>>& matrix, int value) {
    int count = 0;

    for (const vector<int>& row : matrix) {
        count += upperBoundInRow(row, value);
    }

    return count;
}

int medianInRowWiseSortedMatrix(const vector<vector<int>>& matrix) {
    int rows = (matrix.size());
    int columns = (matrix[0].size());
    int low = INT_MAX;
    int high = INT_MIN;

    for (int row = 0; row < rows; row++) {
        low = min(low, matrix[row][0]);
        high = max(high, matrix[row][columns - 1]);
    }

    int requiredSmallerOrEqual = (rows * columns) / 2;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        int count = countLessThanOrEqualToMid(matrix, mid);

        if (count <= requiredSmallerOrEqual) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;// low wil points to median
}

#ifndef BINARY_SEARCH_PLAYLIST_LIBRARY_ONLY
int main() {
    return 0;
}
#endif
```
