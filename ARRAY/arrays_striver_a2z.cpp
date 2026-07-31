#include <algorithm>
#include <climits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace striver_arrays {

int largestElement(const vector<int>& numbers) {
    if (numbers.empty()) {
        return INT_MIN;
    }
    return *max_element(numbers.begin(), numbers.end());
}

int secondLargestDistinct(const vector<int>& numbers) {
    bool hasLargest = false;
    bool hasSecondLargest = false;
    int largest = 0;
    int secondLargest = 0;

    for (int value : numbers) {
        if (!hasLargest || value > largest) {
            if (hasLargest && value != largest) {
                secondLargest = largest;
                hasSecondLargest = true;
            }
            largest = value;
            hasLargest = true;
        } else if (value < largest && (!hasSecondLargest || value > secondLargest)) {
            secondLargest = value;
            hasSecondLargest = true;
        }
    }

    return hasSecondLargest ? secondLargest : -1;
}

bool isSortedNonDecreasing(const vector<int>& numbers) {
    for (int index = 1; index < static_cast<int>(numbers.size()); ++index) {
        if (numbers[index] < numbers[index - 1]) {
            return false;
        }
    }
    return true;
}

int removeDuplicatesFromSorted(vector<int>& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    int uniqueIndex = 0;
    for (int currentIndex = 1; currentIndex < static_cast<int>(numbers.size()); ++currentIndex) {
        if (numbers[currentIndex] != numbers[uniqueIndex]) {
            ++uniqueIndex;
            numbers[uniqueIndex] = numbers[currentIndex];
        }
    }

    return uniqueIndex + 1;
}

void leftRotateByOne(vector<int>& numbers) {
    if (numbers.empty()) {
        return;
    }

    int firstValue = numbers.front();
    for (int index = 1; index < static_cast<int>(numbers.size()); ++index) {
        numbers[index - 1] = numbers[index];
    }
    numbers.back() = firstValue;
}

void leftRotateByD(vector<int>& numbers, int rotations) {
    int arraySize = static_cast<int>(numbers.size());
    if (arraySize == 0) {
        return;
    }

    rotations %= arraySize;
    if (rotations < 0) {
        rotations += arraySize;
    }

    reverse(numbers.begin(), numbers.begin() + rotations);
    reverse(numbers.begin() + rotations, numbers.end());
    reverse(numbers.begin(), numbers.end());
}

void moveZeroesToEnd(vector<int>& numbers) {
    int insertIndex = 0;
    for (int value : numbers) {
        if (value != 0) {
            numbers[insertIndex] = value;
            ++insertIndex;
        }
    }

    while (insertIndex < static_cast<int>(numbers.size())) {
        numbers[insertIndex] = 0;
        ++insertIndex;
    }
}

int linearSearch(const vector<int>& numbers, int target) {
    for (int index = 0; index < static_cast<int>(numbers.size()); ++index) {
        if (numbers[index] == target) {
            return index;
        }
    }
    return -1;
}

vector<int> unionOfTwoSortedArrays(const vector<int>& first, const vector<int>& second) {
    vector<int> result;
    int firstIndex = 0;
    int secondIndex = 0;

    while (firstIndex < static_cast<int>(first.size()) && secondIndex < static_cast<int>(second.size())) {
        int nextValue = 0;
        if (first[firstIndex] <= second[secondIndex]) {
            nextValue = first[firstIndex];
            ++firstIndex;
        } else {
            nextValue = second[secondIndex];
            ++secondIndex;
        }

        if (result.empty() || result.back() != nextValue) {
            result.push_back(nextValue);
        }
    }

    while (firstIndex < static_cast<int>(first.size())) {
        if (result.empty() || result.back() != first[firstIndex]) {
            result.push_back(first[firstIndex]);
        }
        ++firstIndex;
    }

    while (secondIndex < static_cast<int>(second.size())) {
        if (result.empty() || result.back() != second[secondIndex]) {
            result.push_back(second[secondIndex]);
        }
        ++secondIndex;
    }

    return result;
}

int missingNumberFromOneToN(const vector<int>& numbers, int totalNumbers) {
    int missingValue = 0;
    for (int value = 1; value <= totalNumbers; ++value) {
        missingValue ^= value;
    }
    for (int value : numbers) {
        missingValue ^= value;
    }
    return missingValue;
}

int maximumConsecutiveOnes(const vector<int>& numbers) {
    int currentCount = 0;
    int bestCount = 0;

    for (int value : numbers) {
        if (value == 1) {
            ++currentCount;
            bestCount = max(bestCount, currentCount);
        } else {
            currentCount = 0;
        }
    }

    return bestCount;
}

int singleNumberWhenOthersAppearTwice(const vector<int>& numbers) {
    int answer = 0;
    for (int value : numbers) {
        answer ^= value;
    }
    return answer;
}

int longestSubarrayWithSumKPositive(const vector<int>& numbers, long long targetSum) {
    int leftIndex = 0;
    int bestLength = 0;
    long long currentSum = 0;

    for (int rightIndex = 0; rightIndex < static_cast<int>(numbers.size()); ++rightIndex) {
        currentSum += numbers[rightIndex];

        while (leftIndex <= rightIndex && currentSum > targetSum) {
            currentSum -= numbers[leftIndex];
            ++leftIndex;
        }

        if (currentSum == targetSum) {
            bestLength = max(bestLength, rightIndex - leftIndex + 1);
        }
    }

    return bestLength;
}

int longestSubarrayWithSumKAnyIntegers(const vector<int>& numbers, long long targetSum) {
    unordered_map<long long, int> firstIndexByPrefixSum;
    long long prefixSum = 0;
    int bestLength = 0;
    firstIndexByPrefixSum[0] = -1;

    for (int index = 0; index < static_cast<int>(numbers.size()); ++index) {
        prefixSum += numbers[index];

        auto neededPrefix = firstIndexByPrefixSum.find(prefixSum - targetSum);
        if (neededPrefix != firstIndexByPrefixSum.end()) {
            bestLength = max(bestLength, index - neededPrefix->second);
        }

        if (firstIndexByPrefixSum.find(prefixSum) == firstIndexByPrefixSum.end()) {
            firstIndexByPrefixSum[prefixSum] = index;
        }
    }

    return bestLength;
}

vector<int> twoSumIndices(const vector<int>& numbers, int targetSum) {
    unordered_map<int, int> indexByValue;

    for (int index = 0; index < static_cast<int>(numbers.size()); ++index) {
        int neededValue = targetSum - numbers[index];
        auto foundValue = indexByValue.find(neededValue);
        if (foundValue != indexByValue.end()) {
            return {foundValue->second, index};
        }
        indexByValue[numbers[index]] = index;
    }

    return {-1, -1};
}

void sortZeroOneTwo(vector<int>& numbers) {
    int lowIndex = 0;
    int midIndex = 0;
    int highIndex = static_cast<int>(numbers.size()) - 1;

    while (midIndex <= highIndex) {
        if (numbers[midIndex] == 0) {
            swap(numbers[lowIndex], numbers[midIndex]);
            ++lowIndex;
            ++midIndex;
        } else if (numbers[midIndex] == 1) {
            ++midIndex;
        } else {
            swap(numbers[midIndex], numbers[highIndex]);
            --highIndex;
        }
    }
}

int majorityElementNByTwo(const vector<int>& numbers) {
    int candidate = 0;
    int voteCount = 0;

    for (int value : numbers) {
        if (voteCount == 0) {
            candidate = value;
            voteCount = 1;
        } else if (value == candidate) {
            ++voteCount;
        } else {
            --voteCount;
        }
    }

    int occurrenceCount = 0;
    for (int value : numbers) {
        if (value == candidate) {
            ++occurrenceCount;
        }
    }

    return occurrenceCount > static_cast<int>(numbers.size()) / 2 ? candidate : -1;
}

long long maximumSubarraySum(const vector<int>& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    long long currentSum = numbers.front();
    long long bestSum = numbers.front();

    for (int index = 1; index < static_cast<int>(numbers.size()); ++index) {
        currentSum = max<long long>(numbers[index], currentSum + numbers[index]);
        bestSum = max(bestSum, currentSum);
    }

    return bestSum;
}

pair<long long, pair<int, int>> maximumSubarrayWithIndices(const vector<int>& numbers) {
    if (numbers.empty()) {
        return {0, {-1, -1}};
    }

    long long currentSum = 0;
    long long bestSum = LLONG_MIN;
    int currentStart = 0;
    int bestStart = 0;
    int bestEnd = 0;

    for (int index = 0; index < static_cast<int>(numbers.size()); ++index) {
        if (currentSum < 0) {
            currentSum = 0;
            currentStart = index;
        }

        currentSum += numbers[index];

        if (currentSum > bestSum) {
            bestSum = currentSum;
            bestStart = currentStart;
            bestEnd = index;
        }
    }

    return {bestSum, {bestStart, bestEnd}};
}

int maximumStockProfitOneTransaction(const vector<int>& prices) {
    int minimumPrice = INT_MAX;
    int bestProfit = 0;

    for (int price : prices) {
        minimumPrice = min(minimumPrice, price);
        bestProfit = max(bestProfit, price - minimumPrice);
    }

    return bestProfit;
}

vector<int> rearrangeBySignEqualCounts(const vector<int>& numbers) {
    vector<int> result(numbers.size());
    int positiveIndex = 0;
    int negativeIndex = 1;

    for (int value : numbers) {
        if (value >= 0) {
            result[positiveIndex] = value;
            positiveIndex += 2;
        } else {
            result[negativeIndex] = value;
            negativeIndex += 2;
        }
    }

    return result;
}

vector<int> rearrangeBySignUnequalCounts(const vector<int>& numbers) {
    vector<int> positives;
    vector<int> negatives;

    for (int value : numbers) {
        if (value >= 0) {
            positives.push_back(value);
        } else {
            negatives.push_back(value);
        }
    }

    vector<int> result;
    int positiveIndex = 0;
    int negativeIndex = 0;

    while (positiveIndex < static_cast<int>(positives.size()) && negativeIndex < static_cast<int>(negatives.size())) {
        result.push_back(positives[positiveIndex]);
        result.push_back(negatives[negativeIndex]);
        ++positiveIndex;
        ++negativeIndex;
    }

    while (positiveIndex < static_cast<int>(positives.size())) {
        result.push_back(positives[positiveIndex]);
        ++positiveIndex;
    }

    while (negativeIndex < static_cast<int>(negatives.size())) {
        result.push_back(negatives[negativeIndex]);
        ++negativeIndex;
    }

    return result;
}

void nextPermutationArray(vector<int>& numbers) {
    if (numbers.size() <= 1) {
        return;
    }

    int pivotIndex = static_cast<int>(numbers.size()) - 2;
    while (pivotIndex >= 0 && numbers[pivotIndex] >= numbers[pivotIndex + 1]) {
        --pivotIndex;
    }

    if (pivotIndex >= 0) {
        int successorIndex = static_cast<int>(numbers.size()) - 1;
        while (numbers[successorIndex] <= numbers[pivotIndex]) {
            --successorIndex;
        }
        swap(numbers[pivotIndex], numbers[successorIndex]);
    }

    reverse(numbers.begin() + pivotIndex + 1, numbers.end());
}

vector<int> leadersInArray(const vector<int>& numbers) {
    vector<int> leaders;
    int maximumFromRight = INT_MIN;

    for (int index = static_cast<int>(numbers.size()) - 1; index >= 0; --index) {
        if (numbers[index] > maximumFromRight) {
            leaders.push_back(numbers[index]);
            maximumFromRight = numbers[index];
        }
    }

    reverse(leaders.begin(), leaders.end());
    return leaders;
}

int longestConsecutiveSequence(const vector<int>& numbers) {
    unordered_set<int> values(numbers.begin(), numbers.end());
    int bestLength = 0;

    for (int value : values) {
        if (values.find(value - 1) != values.end()) {
            continue;
        }

        int currentValue = value;
        int currentLength = 1;
        while (values.find(currentValue + 1) != values.end()) {
            ++currentValue;
            ++currentLength;
        }

        bestLength = max(bestLength, currentLength);
    }

    return bestLength;
}

void setMatrixZeroes(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix.front().empty()) {
        return;
    }

    int rowCount = static_cast<int>(matrix.size());
    int columnCount = static_cast<int>(matrix.front().size());
    bool firstRowHasZero = false;
    bool firstColumnHasZero = false;

    for (int column = 0; column < columnCount; ++column) {
        if (matrix[0][column] == 0) {
            firstRowHasZero = true;
        }
    }

    for (int row = 0; row < rowCount; ++row) {
        if (matrix[row][0] == 0) {
            firstColumnHasZero = true;
        }
    }

    for (int row = 1; row < rowCount; ++row) {
        for (int column = 1; column < columnCount; ++column) {
            if (matrix[row][column] == 0) {
                matrix[row][0] = 0;
                matrix[0][column] = 0;
            }
        }
    }

    for (int row = 1; row < rowCount; ++row) {
        for (int column = 1; column < columnCount; ++column) {
            if (matrix[row][0] == 0 || matrix[0][column] == 0) {
                matrix[row][column] = 0;
            }
        }
    }

    if (firstRowHasZero) {
        for (int column = 0; column < columnCount; ++column) {
            matrix[0][column] = 0;
        }
    }

    if (firstColumnHasZero) {
        for (int row = 0; row < rowCount; ++row) {
            matrix[row][0] = 0;
        }
    }
}

void rotateMatrix90Clockwise(vector<vector<int>>& matrix) {
    int size = static_cast<int>(matrix.size());

    for (int row = 0; row < size; ++row) {
        for (int column = row + 1; column < size; ++column) {
            swap(matrix[row][column], matrix[column][row]);
        }
    }

    for (int row = 0; row < size; ++row) {
        reverse(matrix[row].begin(), matrix[row].end());
    }
}

vector<int> spiralOrder(const vector<vector<int>>& matrix) {
    vector<int> result;
    if (matrix.empty() || matrix.front().empty()) {
        return result;
    }

    int topRow = 0;
    int bottomRow = static_cast<int>(matrix.size()) - 1;
    int leftColumn = 0;
    int rightColumn = static_cast<int>(matrix.front().size()) - 1;

    while (topRow <= bottomRow && leftColumn <= rightColumn) {
        for (int column = leftColumn; column <= rightColumn; ++column) {
            result.push_back(matrix[topRow][column]);
        }
        ++topRow;

        for (int row = topRow; row <= bottomRow; ++row) {
            result.push_back(matrix[row][rightColumn]);
        }
        --rightColumn;

        if (topRow <= bottomRow) {
            for (int column = rightColumn; column >= leftColumn; --column) {
                result.push_back(matrix[bottomRow][column]);
            }
            --bottomRow;
        }

        if (leftColumn <= rightColumn) {
            for (int row = bottomRow; row >= topRow; --row) {
                result.push_back(matrix[row][leftColumn]);
            }
            ++leftColumn;
        }
    }

    return result;
}

int countSubarraysWithSumK(const vector<int>& numbers, long long targetSum) {
    unordered_map<long long, int> frequencyByPrefixSum;
    long long prefixSum = 0;
    int subarrayCount = 0;
    frequencyByPrefixSum[0] = 1;

    for (int value : numbers) {
        prefixSum += value;
        auto neededPrefix = frequencyByPrefixSum.find(prefixSum - targetSum);
        if (neededPrefix != frequencyByPrefixSum.end()) {
            subarrayCount += neededPrefix->second;
        }
        ++frequencyByPrefixSum[prefixSum];
    }

    return subarrayCount;
}

vector<vector<long long>> pascalTriangle(int rowCount) {
    vector<vector<long long>> triangle;

    for (int row = 0; row < rowCount; ++row) {
        vector<long long> currentRow(row + 1, 1);
        for (int column = 1; column < row; ++column) {
            currentRow[column] = triangle[row - 1][column - 1] + triangle[row - 1][column];
        }
        triangle.push_back(currentRow);
    }

    return triangle;
}

long long combinationValue(int totalItems, int chooseItems) {
    if (chooseItems < 0 || chooseItems > totalItems) {
        return 0;
    }

    chooseItems = min(chooseItems, totalItems - chooseItems);
    long long answer = 1;

    for (int step = 1; step <= chooseItems; ++step) {
        answer = answer * (totalItems - chooseItems + step) / step;
    }

    return answer;
}

vector<long long> pascalTriangleRowOneIndexed(int rowNumber) {
    vector<long long> row;
    long long value = 1;

    for (int column = 1; column <= rowNumber; ++column) {
        row.push_back(value);
        value = value * (rowNumber - column) / column;
    }

    return row;
}

vector<int> majorityElementNByThree(const vector<int>& numbers) {
    int firstCandidate = 0;
    int secondCandidate = 0;
    int firstCount = 0;
    int secondCount = 0;

    for (int value : numbers) {
        if (firstCount > 0 && value == firstCandidate) {
            ++firstCount;
        } else if (secondCount > 0 && value == secondCandidate) {
            ++secondCount;
        } else if (firstCount == 0) {
            firstCandidate = value;
            firstCount = 1;
        } else if (secondCount == 0) {
            secondCandidate = value;
            secondCount = 1;
        } else {
            --firstCount;
            --secondCount;
        }
    }

    firstCount = 0;
    secondCount = 0;
    for (int value : numbers) {
        if (value == firstCandidate) {
            ++firstCount;
        } else if (value == secondCandidate) {
            ++secondCount;
        }
    }

    vector<int> result;
    if (firstCount > static_cast<int>(numbers.size()) / 3) {
        result.push_back(firstCandidate);
    }
    if (secondCandidate != firstCandidate && secondCount > static_cast<int>(numbers.size()) / 3) {
        result.push_back(secondCandidate);
    }

    sort(result.begin(), result.end());
    return result;
}

vector<vector<int>> threeSum(vector<int> numbers) {
    vector<vector<int>> result;
    sort(numbers.begin(), numbers.end());
    int arraySize = static_cast<int>(numbers.size());

    for (int firstIndex = 0; firstIndex < arraySize; ++firstIndex) {
        if (firstIndex > 0 && numbers[firstIndex] == numbers[firstIndex - 1]) {
            continue;
        }

        int secondIndex = firstIndex + 1;
        int thirdIndex = arraySize - 1;

        while (secondIndex < thirdIndex) {
            long long sum = static_cast<long long>(numbers[firstIndex]) + numbers[secondIndex] + numbers[thirdIndex];
            if (sum == 0) {
                result.push_back({numbers[firstIndex], numbers[secondIndex], numbers[thirdIndex]});
                ++secondIndex;
                --thirdIndex;
                while (secondIndex < thirdIndex && numbers[secondIndex] == numbers[secondIndex - 1]) {
                    ++secondIndex;
                }
                while (secondIndex < thirdIndex && numbers[thirdIndex] == numbers[thirdIndex + 1]) {
                    --thirdIndex;
                }
            } else if (sum < 0) {
                ++secondIndex;
            } else {
                --thirdIndex;
            }
        }
    }

    return result;
}

vector<vector<int>> fourSum(vector<int> numbers, long long targetSum) {
    vector<vector<int>> result;
    sort(numbers.begin(), numbers.end());
    int arraySize = static_cast<int>(numbers.size());

    for (int firstIndex = 0; firstIndex < arraySize; ++firstIndex) {
        if (firstIndex > 0 && numbers[firstIndex] == numbers[firstIndex - 1]) {
            continue;
        }

        for (int secondIndex = firstIndex + 1; secondIndex < arraySize; ++secondIndex) {
            if (secondIndex > firstIndex + 1 && numbers[secondIndex] == numbers[secondIndex - 1]) {
                continue;
            }

            int thirdIndex = secondIndex + 1;
            int fourthIndex = arraySize - 1;

            while (thirdIndex < fourthIndex) {
                long long sum = static_cast<long long>(numbers[firstIndex]) + numbers[secondIndex] + numbers[thirdIndex] + numbers[fourthIndex];
                if (sum == targetSum) {
                    result.push_back({numbers[firstIndex], numbers[secondIndex], numbers[thirdIndex], numbers[fourthIndex]});
                    ++thirdIndex;
                    --fourthIndex;
                    while (thirdIndex < fourthIndex && numbers[thirdIndex] == numbers[thirdIndex - 1]) {
                        ++thirdIndex;
                    }
                    while (thirdIndex < fourthIndex && numbers[fourthIndex] == numbers[fourthIndex + 1]) {
                        --fourthIndex;
                    }
                } else if (sum < targetSum) {
                    ++thirdIndex;
                } else {
                    --fourthIndex;
                }
            }
        }
    }

    return result;
}

int longestZeroSumSubarray(const vector<int>& numbers) {
    unordered_map<long long, int> firstIndexByPrefixSum;
    long long prefixSum = 0;
    int bestLength = 0;
    firstIndexByPrefixSum[0] = -1;

    for (int index = 0; index < static_cast<int>(numbers.size()); ++index) {
        prefixSum += numbers[index];

        auto foundPrefix = firstIndexByPrefixSum.find(prefixSum);
        if (foundPrefix != firstIndexByPrefixSum.end()) {
            bestLength = max(bestLength, index - foundPrefix->second);
        } else {
            firstIndexByPrefixSum[prefixSum] = index;
        }
    }

    return bestLength;
}

int countSubarraysWithXorK(const vector<int>& numbers, int targetXor) {
    unordered_map<int, int> frequencyByPrefixXor;
    int prefixXor = 0;
    int subarrayCount = 0;
    frequencyByPrefixXor[0] = 1;

    for (int value : numbers) {
        prefixXor ^= value;
        int neededPrefixXor = prefixXor ^ targetXor;
        auto foundPrefixXor = frequencyByPrefixXor.find(neededPrefixXor);
        if (foundPrefixXor != frequencyByPrefixXor.end()) {
            subarrayCount += foundPrefixXor->second;
        }
        ++frequencyByPrefixXor[prefixXor];
    }

    return subarrayCount;
}

vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>> intervals) {
    vector<vector<int>> result;
    if (intervals.empty()) {
        return result;
    }

    sort(intervals.begin(), intervals.end());
    result.push_back(intervals.front());

    for (int index = 1; index < static_cast<int>(intervals.size()); ++index) {
        if (intervals[index][0] <= result.back()[1]) {
            result.back()[1] = max(result.back()[1], intervals[index][1]);
        } else {
            result.push_back(intervals[index]);
        }
    }

    return result;
}

void mergeTwoSortedArraysWithoutExtraSpace(vector<long long>& first, vector<long long>& second) {
    int totalSize = static_cast<int>(first.size() + second.size());
    auto nextGap = [](int currentGap) {
        if (currentGap <= 1) {
            return 0;
        }
        return currentGap / 2 + currentGap % 2;
    };

    for (int gap = nextGap(totalSize); gap > 0; gap = nextGap(gap)) {
        int leftIndex = 0;
        int rightIndex = gap;

        while (rightIndex < totalSize) {
            if (leftIndex < static_cast<int>(first.size()) && rightIndex < static_cast<int>(first.size())) {
                if (first[leftIndex] > first[rightIndex]) {
                    swap(first[leftIndex], first[rightIndex]);
                }
            } else if (leftIndex < static_cast<int>(first.size())) {
                int secondRightIndex = rightIndex - static_cast<int>(first.size());
                if (first[leftIndex] > second[secondRightIndex]) {
                    swap(first[leftIndex], second[secondRightIndex]);
                }
            } else {
                int secondLeftIndex = leftIndex - static_cast<int>(first.size());
                int secondRightIndex = rightIndex - static_cast<int>(first.size());
                if (second[secondLeftIndex] > second[secondRightIndex]) {
                    swap(second[secondLeftIndex], second[secondRightIndex]);
                }
            }

            ++leftIndex;
            ++rightIndex;
        }
    }
}

pair<int, int> repeatingAndMissingNumber(const vector<int>& numbers) {
    long long arraySize = static_cast<long long>(numbers.size());
    long long expectedSum = arraySize * (arraySize + 1) / 2;
    long long expectedSquareSum = arraySize * (arraySize + 1) * (2 * arraySize + 1) / 6;
    long long actualSum = 0;
    long long actualSquareSum = 0;

    for (int value : numbers) {
        actualSum += value;
        actualSquareSum += 1LL * value * value;
    }

    long long difference = actualSum - expectedSum;
    long long sumOfRepeatingAndMissing = (actualSquareSum - expectedSquareSum) / difference;
    int repeating = static_cast<int>((difference + sumOfRepeatingAndMissing) / 2);
    int missing = static_cast<int>(sumOfRepeatingAndMissing - repeating);

    return {repeating, missing};
}

namespace detail {

long long mergeAndCountInversions(vector<int>& numbers, vector<int>& buffer, int leftStart, int middle, int rightEnd) {
    int leftIndex = leftStart;
    int rightIndex = middle + 1;
    int writeIndex = leftStart;
    long long inversionCount = 0;

    while (leftIndex <= middle && rightIndex <= rightEnd) {
        if (numbers[leftIndex] <= numbers[rightIndex]) {
            buffer[writeIndex] = numbers[leftIndex];
            ++leftIndex;
        } else {
            buffer[writeIndex] = numbers[rightIndex];
            inversionCount += middle - leftIndex + 1;
            ++rightIndex;
        }
        ++writeIndex;
    }

    while (leftIndex <= middle) {
        buffer[writeIndex] = numbers[leftIndex];
        ++leftIndex;
        ++writeIndex;
    }

    while (rightIndex <= rightEnd) {
        buffer[writeIndex] = numbers[rightIndex];
        ++rightIndex;
        ++writeIndex;
    }

    for (int index = leftStart; index <= rightEnd; ++index) {
        numbers[index] = buffer[index];
    }

    return inversionCount;
}

long long countInversionsMergeSort(vector<int>& numbers, vector<int>& buffer, int leftStart, int rightEnd) {
    if (leftStart >= rightEnd) {
        return 0;
    }

    int middle = leftStart + (rightEnd - leftStart) / 2;
    long long inversionCount = 0;
    inversionCount += countInversionsMergeSort(numbers, buffer, leftStart, middle);
    inversionCount += countInversionsMergeSort(numbers, buffer, middle + 1, rightEnd);
    inversionCount += mergeAndCountInversions(numbers, buffer, leftStart, middle, rightEnd);
    return inversionCount;
}

void mergeSortedRange(vector<int>& numbers, int leftStart, int middle, int rightEnd) {
    vector<int> merged;
    int leftIndex = leftStart;
    int rightIndex = middle + 1;

    while (leftIndex <= middle && rightIndex <= rightEnd) {
        if (numbers[leftIndex] <= numbers[rightIndex]) {
            merged.push_back(numbers[leftIndex]);
            ++leftIndex;
        } else {
            merged.push_back(numbers[rightIndex]);
            ++rightIndex;
        }
    }

    while (leftIndex <= middle) {
        merged.push_back(numbers[leftIndex]);
        ++leftIndex;
    }

    while (rightIndex <= rightEnd) {
        merged.push_back(numbers[rightIndex]);
        ++rightIndex;
    }

    for (int offset = 0; offset < static_cast<int>(merged.size()); ++offset) {
        numbers[leftStart + offset] = merged[offset];
    }
}

long long countReversePairsMergeSort(vector<int>& numbers, int leftStart, int rightEnd) {
    if (leftStart >= rightEnd) {
        return 0;
    }

    int middle = leftStart + (rightEnd - leftStart) / 2;
    long long pairCount = 0;
    pairCount += countReversePairsMergeSort(numbers, leftStart, middle);
    pairCount += countReversePairsMergeSort(numbers, middle + 1, rightEnd);

    int rightIndex = middle + 1;
    for (int leftIndex = leftStart; leftIndex <= middle; ++leftIndex) {
        while (rightIndex <= rightEnd && static_cast<long long>(numbers[leftIndex]) > 2LL * numbers[rightIndex]) {
            ++rightIndex;
        }
        pairCount += rightIndex - (middle + 1);
    }

    mergeSortedRange(numbers, leftStart, middle, rightEnd);
    return pairCount;
}

} 

long long countInversions(vector<int> numbers) {
    if (numbers.empty()) {
        return 0;
    }

    vector<int> buffer(numbers.size());
    return detail::countInversionsMergeSort(numbers, buffer, 0, static_cast<int>(numbers.size()) - 1);
}

long long countReversePairs(vector<int> numbers) {
    if (numbers.empty()) {
        return 0;
    }

    return detail::countReversePairsMergeSort(numbers, 0, static_cast<int>(numbers.size()) - 1);
}

long long maximumProductSubarray(const vector<int>& numbers) {
    if (numbers.empty()) {
        return 0;
    }

    long long maximumEndingHere = numbers.front();
    long long minimumEndingHere = numbers.front();
    long long bestProduct = numbers.front();

    for (int index = 1; index < static_cast<int>(numbers.size()); ++index) {
        long long value = numbers[index];
        if (value < 0) {
            swap(maximumEndingHere, minimumEndingHere);
        }

        maximumEndingHere = max(value, maximumEndingHere * value);
        minimumEndingHere = min(value, minimumEndingHere * value);
        bestProduct = max(bestProduct, maximumEndingHere);
    }

    return bestProduct;
}

}

#ifndef STRIVER_ARRAYS_LIBRARY_ONLY
int main() {
    return 0;
}
#endif
