#include <bits/stdc++.h>
using namespace std;

/*
Striver Binary Search Playlist Notes - C++17

Important:
- This is not a verbatim copy of Striver/TUF code.
- It follows the same playlist order, standard Striver-style intuition, and fresh C++ implementations.
- Comments include revision-friendly "Hint" / "Approach" / answer-space state pointers.
*/

/*
Launching Binary Search Bootcamp
Problem: Study Binary Search by dividing it into common patterns.
Hint: Binary Search is not only for searching in sorted arrays; it is also used on the answer space.
Approach:
1. Apply index-space binary search on sorted arrays.
2. Use condition-based half elimination in rotated/special arrays.
3. In answer-space binary search, the "can we do it?" predicate must be monotonic.
TC: Not applicable
SC: Not applicable
*/

/*
BS-1. Binary Search Introduction | Iterative | Recursive | Overflow Cases
Problem: Find the index of target in a sorted array; return -1 if it is absent.
Hint: Use mid = low + (high - low) / 2 because low + high can overflow.
Approach: If nums[mid] is smaller, move right; if it is larger, move left.
TC: O(log N)
SC: O(1) iterative, O(log N) recursive stack
*/
int binarySearchIterative(const vector<int>& nums, int target) {
    int low = 0;
    int high = static_cast<int>(nums.size()) - 1;

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
    return binarySearchRecursiveHelper(nums, 0, static_cast<int>(nums.size()) - 1, target);
}

/*
BS-2. Lower Bound | Upper Bound | Search Insert Position | Floor and Ceil
Problem: Find bound/index/value type answers in a sorted array.
Hint:
- Lower Bound = first index where arr[index] >= x.
- Upper Bound = first index where arr[index] > x.
- Search Insert Position same as lower bound.
- Floor = greatest value <= x; Ceil = smallest value >= x.
Approach: Store the possible answer, then move left/right to search for a better candidate.
TC: O(log N)
SC: O(1)
*/
int lowerBoundIndex(const vector<int>& arr, int x) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;
    int answer = static_cast<int>(arr.size());

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
    int high = static_cast<int>(arr.size()) - 1;
    int answer = static_cast<int>(arr.size());

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
    int high = static_cast<int>(arr.size()) - 1;
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
    int high = static_cast<int>(arr.size()) - 1;
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

/*
BS-3. First and Last Occurrences | Count Occurrences
Problem: Find the first position, last position, and count of x in a sorted array.
Hint: Do not stop after finding x once:
- For first occurrence, continue searching on the left side.
- For last occurrence, continue searching on the right side.
Approach: Use two binary searches.
TC: O(log N)
SC: O(1)
*/
int firstOccurrenceIndex(const vector<int>& arr, int x) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;
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
    int high = static_cast<int>(arr.size()) - 1;
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

/*
BS-4. Search Element in Rotated Sorted Array - I
Problem: Search target in a rotated sorted array with distinct elements.
Hint: At every mid, at least one half is guaranteed to be sorted.
Approach:
1. If the left half is sorted, check whether target lies in that range.
2. Otherwise, the right half is sorted; check whether target lies in that range.
TC: O(log N)
SC: O(1)
*/
int searchInRotatedSortedArrayI(const vector<int>& arr, int target) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;

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

/*
BS-5. Search Element in Rotated Sorted Array - II
Problem: Check whether target exists in a rotated sorted array with duplicates.
Hint: arr[low] == arr[mid] == arr[high] creates ambiguity; shrink using low++ and high--.
Approach: Use the same sorted-half logic, but handle duplicate ambiguity by shrinking boundaries.
TC: O(log N) average, O(N) worst case due to duplicates
SC: O(1)
*/
bool searchInRotatedSortedArrayII(const vector<int>& arr, int target) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;

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

/*
BS-6. Minimum in Rotated Sorted Array
Problem: Find the minimum element in a rotated sorted array.
Hint: If arr[low] <= arr[high], the current search space is already sorted; arr[low] is the minimum.
Approach: Store the minimum of the sorted half, then search the unsorted half for the actual pivot/minimum.
TC: O(log N)
SC: O(1)
*/
int minimumInRotatedSortedArray(const vector<int>& arr) {
    if (arr.empty()) {
        return -1;
    }

    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;
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

/*
BS-7. Find Out How Many Times Array Has Been Rotated
Problem: Find the rotation count of a rotated sorted array.
Hint: Rotation count = index of the minimum element.
Approach: Same as BS-6, but store the index along with the minimum value.
TC: O(log N)
SC: O(1)
*/
int rotationCountInRotatedArray(const vector<int>& arr) {
    if (arr.empty()) {
        return 0;
    }

    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;
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

/*
BS-8. Single Element in Sorted Array
Problem: In a sorted array, every element appears exactly twice except one; find that single element.
Hint:
- Pairing pattern before the single element: even index has the first copy, odd index has the second copy.
- After the single element, the pairing pattern flips.
Approach: Use mid parity and neighbor comparison to decide whether the single element is on the left or right.
TC: O(log N)
SC: O(1)
*/
int singleNonDuplicateSortedArray(const vector<int>& arr) {
    int n = static_cast<int>(arr.size());

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

        bool leftPartIsCorrect =
            (mid % 2 == 1 && arr[mid] == arr[mid - 1]) ||
            (mid % 2 == 0 && arr[mid] == arr[mid + 1]);

        // Hint: If the pairing pattern is still correct, the single element lies on the right.
        if (leftPartIsCorrect) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;
}

/*
BS-9. Find Peak Element
Problem: Find a peak index in a 1D array where arr[i] is greater than its neighbors.
Hint: Observe the slope; on an increasing slope, a peak is guaranteed on the right.
Approach: Handle edge cases, then compare mid with its neighbors.
TC: O(log N)
SC: O(1)
*/
int findPeakElement1D(const vector<int>& arr) {
    int n = static_cast<int>(arr.size());

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

/*
BS-10. Finding Sqrt of a Number Using Binary Search
Problem: Given n, return floor(sqrt(n)).
Hint: mid * mid can overflow, so use long long.
Approach: If mid^2 <= n, mid is a possible answer; move right for a bigger valid answer.
TC: O(log N)
SC: O(1)
*/
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

/*
BS-11. Find the Nth Root of an Integer
Problem: Given n and m, find integer x such that x^n == m; return -1 if it does not exist.
Hint: While calculating power, stop as soon as the value becomes greater than m.
Approach: Search space for x is [1, m]; compare x^n with m.
TC: O(log M * N)
SC: O(1)
*/
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

/*
BS-12. Koko Eating Bananas
Problem: Find the minimum eating speed so Koko can finish all banana piles within h hours.
Hint: As speed increases, required hours decrease monotonically.
Approach: Answer-space BS on speed [1, maxPile].
TC: O(N * log(max pile))
SC: O(1)
*/
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

/*
BS-13. Minimum Days to Make M Bouquets
Problem: Make m bouquets, each with k adjacent flowers; find the minimum day.
Hint: As days increase, the number of bloomed flowers increases, so possible/not possible is monotonic.
Approach: Answer-space BS on day [min bloom, max bloom].
TC: O(N * log(max bloom - min bloom + 1))
SC: O(1)
*/
bool canMakeBouquets(const vector<int>& bloomDay, int day, int bouquetsNeeded, int flowersPerBouquet) {
    int bouquetsMade = 0;
    int consecutiveFlowers = 0;

    for (int bloom : bloomDay) {
        if (bloom <= day) {
            consecutiveFlowers++;
        } else {
            bouquetsMade += consecutiveFlowers / flowersPerBouquet;
            consecutiveFlowers = 0;
        }
    }

    bouquetsMade += consecutiveFlowers / flowersPerBouquet;
    return bouquetsMade >= bouquetsNeeded;
}

int minimumDaysToMakeBouquets(const vector<int>& bloomDay, int bouquetsNeeded, int flowersPerBouquet) {
    long long totalFlowersRequired = 1LL * bouquetsNeeded * flowersPerBouquet;

    if (totalFlowersRequired > static_cast<long long>(bloomDay.size())) {
        return -1;
    }

    int low = *min_element(bloomDay.begin(), bloomDay.end());
    int high = *max_element(bloomDay.begin(), bloomDay.end());
    int answer = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (canMakeBouquets(bloomDay, mid, bouquetsNeeded, flowersPerBouquet)) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}

/*
BS-14. Find the Smallest Divisor Given a Threshold
Problem: Find the smallest divisor d such that the sum of ceil(nums[i] / d) is <= threshold.
Hint: As divisor increases, the sum decreases; this creates a monotonic predicate.
Approach: Answer-space BS on divisor [1, max(nums)].
TC: O(N * log(max element))
SC: O(1)
*/
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

/*
BS-15. Capacity to Ship Packages Within D Days
Problem: Given weights and days, find the minimum ship capacity.
Hint:
- Minimum capacity must be at least the maximum weight.
- Maximum capacity can be the total sum of weights.
- As capacity increases, days needed decrease.
Approach: Answer-space BS on capacity.
TC: O(N * log(sum(weights) - max(weights) + 1))
SC: O(1)
*/
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

/*
BS-16. Kth Missing Positive Number
Problem: Find the kth missing positive number in a sorted positive array.
Hint: Missing numbers till index mid = arr[mid] - (mid + 1).
Approach: If missing count < k, the answer lies on the right side; otherwise it lies on the left side.
TC: O(log N)
SC: O(1)
*/
int kthMissingPositiveNumber(const vector<int>& arr, int k) {
    int low = 0;
    int high = static_cast<int>(arr.size()) - 1;

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
    return k + low;
}

/*
BS-17. Aggressive Cows
Problem: Place C cows in stalls such that the minimum pair distance is maximized.
Hint: If distance d is possible, all smaller distances are also possible.
Approach: Sort stalls, then answer-space BS on minimum distance.
TC: O(N log N + N * log(max distance))
SC: O(1) extra
*/
bool canPlaceCows(const vector<int>& stalls, int minimumDistance, int cows) {
    int cowsPlaced = 1;
    int lastStall = stalls[0];

    for (int index = 1; index < static_cast<int>(stalls.size()); index++) {
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

/*
BS-18. Allocate Books
Problem: Allocate books contiguously so each student gets at least one book; minimize the maximum pages.
Hint:
- Minimum possible max pages = max single book.
- Maximum possible max pages = total pages.
- As max pages increases, required students decrease.
Approach: Answer-space BS on maximum pages allowed.
TC: O(N * log(sum pages - max pages + 1))
SC: O(1)
*/
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
    int n = static_cast<int>(pages.size());

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

/*
BS-19. Painter's Partition and Split Array - Largest Sum
Problem: Split the array into k contiguous parts and minimize the largest part sum.
Hint: This is the same pattern as Allocate Books; only the names change.
Approach: Answer-space BS on maximum allowed partition sum.
TC: O(N * log(sum - max element + 1))
SC: O(1)
*/
int partitionsRequiredForMaxSum(const vector<int>& nums, int maxSumAllowed) {
    int partitions = 1;
    int currentSum = 0;

    for (int num : nums) {
        if (currentSum + num > maxSumAllowed) {
            partitions++;
            currentSum = num;
        } else {
            currentSum += num;
        }
    }

    return partitions;
}

int splitArrayLargestSum(const vector<int>& nums, int partitionsAllowed) {
    int low = *max_element(nums.begin(), nums.end());
    int high = accumulate(nums.begin(), nums.end(), 0);
    int answer = high;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (partitionsRequiredForMaxSum(nums, mid) <= partitionsAllowed) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return answer;
}

int paintersPartition(const vector<int>& boards, int painters) {
    return splitArrayLargestSum(boards, painters);
}

/*
BS-20. Minimise Maximum Distance Between Gas Stations
Problem: Add K new gas stations and minimize the maximum distance between adjacent gas stations.
Hint: This is decimal answer-space binary search.
Approach:
1. Brute: Split the largest section K times by scanning.
2. Better: Use a max heap to find the largest section quickly.
3. Optimal: Binary search on the distance answer; if required stations <= K, the distance is possible.
TC:
- Brute: O(K * N)
- Better: O(N log N + K log N)
- Optimal: O(N * log(range / precision))
SC:
- Brute: O(N)
- Better: O(N)
- Optimal: O(1)
*/
double minimiseMaximumDistanceGasStationsBrute(const vector<int>& stations, int k) {
    int n = static_cast<int>(stations.size());
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
    int n = static_cast<int>(stations.size());
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

int numberOfGasStationsRequired(const vector<int>& stations, double maximumAllowedDistance) {
    int requiredStations = 0;

    for (int index = 1; index < static_cast<int>(stations.size()); index++) {
        double gap = stations[index] - stations[index - 1];
        int stationsInGap = static_cast<int>(gap / maximumAllowedDistance);

        // Hint: If the gap is exactly divisible, the last station overlaps an existing station, so subtract one.
        if (fabs(stationsInGap * maximumAllowedDistance - gap) < 1e-9) {
            stationsInGap--;
        }

        requiredStations += stationsInGap;
    }

    return requiredStations;
}

double minimiseMaximumDistanceGasStationsOptimal(const vector<int>& stations, int k) {
    double low = 0.0;
    double high = 0.0;

    for (int index = 0; index + 1 < static_cast<int>(stations.size()); index++) {
        high = max(high, static_cast<double>(stations[index + 1] - stations[index]));
    }

    while (high - low > 1e-6) {
        double mid = (low + high) / 2.0;

        if (numberOfGasStationsRequired(stations, mid) > k) {
            low = mid;
        } else {
            high = mid;
        }
    }

    return high;
}

/*
BS-21. Median of Two Sorted Arrays of Different Sizes
Problem: Find the median of two sorted arrays.
Hint:
- Brute: Merge both arrays and find the median.
- Better: Simulate merge and track only the median positions.
- Optimal: Binary search on the smaller array and keep the left half size fixed.
Approach: Partition such that max(left part) <= min(right part).
TC:
- Brute: O(N1 + N2)
- Better: O(N1 + N2)
- Optimal: O(log(min(N1, N2)))
SC:
- Brute: O(N1 + N2)
- Better: O(1)
- Optimal: O(1)
*/
double medianOfTwoSortedArraysBrute(const vector<int>& first, const vector<int>& second) {
    vector<int> merged;
    int firstIndex = 0;
    int secondIndex = 0;

    while (firstIndex < static_cast<int>(first.size()) && secondIndex < static_cast<int>(second.size())) {
        if (first[firstIndex] <= second[secondIndex]) {
            merged.push_back(first[firstIndex++]);
        } else {
            merged.push_back(second[secondIndex++]);
        }
    }

    while (firstIndex < static_cast<int>(first.size())) {
        merged.push_back(first[firstIndex++]);
    }

    while (secondIndex < static_cast<int>(second.size())) {
        merged.push_back(second[secondIndex++]);
    }

    int total = static_cast<int>(merged.size());

    if (total % 2 == 1) {
        return merged[total / 2];
    }

    return (merged[total / 2 - 1] + merged[total / 2]) / 2.0;
}

double medianOfTwoSortedArraysBetter(const vector<int>& first, const vector<int>& second) {
    int n1 = static_cast<int>(first.size());
    int n2 = static_cast<int>(second.size());
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

    int n1 = static_cast<int>(first.size());
    int n2 = static_cast<int>(second.size());
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

/*
BS-22. K-th Element of Two Sorted Arrays
Problem: Find the kth element in the merged sorted order of two sorted arrays.
Hint: This is the generalized version of the optimal median approach.
Approach: Binary search on the smaller array and keep exactly k elements on the left side.
TC: O(log(min(N1, N2)))
SC: O(1)
*/
int kthElementOfTwoSortedArrays(const vector<int>& first, const vector<int>& second, int k) {
    if (first.size() > second.size()) {
        return kthElementOfTwoSortedArrays(second, first, k);
    }

    int n1 = static_cast<int>(first.size());
    int n2 = static_cast<int>(second.size());
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

/*
BS-23. Row with Maximum Number of 1s
Problem: Return the index of the row with the maximum number of 1s in a binary matrix.
Hint: Each row is sorted, so the first 1 can be found using lower bound.
Approach: Apply lower_bound(1) on each row, count = columns - firstOneIndex.
TC: O(N * log M)
SC: O(1)
*/
int rowWithMaximumOnes(const vector<vector<int>>& matrix) {
    int rows = static_cast<int>(matrix.size());
    int columns = matrix.empty() ? 0 : static_cast<int>(matrix[0].size());
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

/*
BS-24. Search in a 2D Matrix - I
Problem: Matrix is sorted like a flattened 1D array; check whether target is present.
Hint: virtualIndex -> row = index / columns, col = index % columns.
Approach: Treat the entire matrix as a sorted 1D array and apply binary search.
TC: O(log(N * M))
SC: O(1)
*/
bool searchMatrixI(const vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }

    int rows = static_cast<int>(matrix.size());
    int columns = static_cast<int>(matrix[0].size());
    int low = 0;
    int high = rows * columns - 1;

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

/*
BS-25. Search in a 2D Matrix - II
Problem: Search target in a matrix where rows and columns are sorted.
Hint: Start from the top-right; move left for smaller values and down for larger values.
Approach: At every step, eliminate one row or one column.
TC: O(N + M)
SC: O(1)
*/
bool searchMatrixII(const vector<vector<int>>& matrix, int target) {
    if (matrix.empty() || matrix[0].empty()) {
        return false;
    }

    int row = 0;
    int column = static_cast<int>(matrix[0].size()) - 1;

    while (row < static_cast<int>(matrix.size()) && column >= 0) {
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

/*
BS-26. Find Peak Element-II
Problem: Find a peak cell in a 2D grid where the value is greater than left/right/up/down neighbors.
Hint: Take the maximum element in the current column; if it is greater than left and right, it is a peak.
Approach: Binary search on columns, scan the maximum row, then move left/right based on the larger neighbor.
TC: O(N * log M)
SC: O(1)
*/
int rowOfMaximumElementInColumn(const vector<vector<int>>& matrix, int column) {
    int maximumRow = 0;

    for (int row = 1; row < static_cast<int>(matrix.size()); row++) {
        if (matrix[row][column] > matrix[maximumRow][column]) {
            maximumRow = row;
        }
    }

    return maximumRow;
}

vector<int> findPeakGrid(const vector<vector<int>>& matrix) {
    int columns = static_cast<int>(matrix[0].size());
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

/*
BS-27. Median in a Row Wise Sorted Matrix
Problem: Find the median of a row-wise sorted matrix.
Hint: Use the count of elements <= mid; binary search on values.
Approach: Search space minimum matrix value to maximum matrix value, count <= mid using upper bound in each row.
TC: O(log(maxValue - minValue + 1) * N * log M)
SC: O(1)
*/
int upperBoundInRow(const vector<int>& row, int x) {
    int low = 0;
    int high = static_cast<int>(row.size()) - 1;
    int answer = static_cast<int>(row.size());

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
    int rows = static_cast<int>(matrix.size());
    int columns = static_cast<int>(matrix[0].size());
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

    return low;
}

#ifndef BINARY_SEARCH_PLAYLIST_LIBRARY_ONLY
int main() {
    return 0;
}
#endif
