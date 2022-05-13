#include <stack>
#include <vector>

// Quicksort source: https://www.techiedelight.com/iterative-implementation-of-quicksort/

int _partition(std::vector<int> a, int start, int end)
{
    // Pick the rightmost element as a pivot from the array
    int pivot = a[end];

    // elements less than the pivot goes to the left of `pIndex`
    // elements more than the pivot goes to the right of `pIndex`
    // equal elements can go either way
    int pIndex = start;

    // each time we find an element less than or equal to the pivot, `pIndex`
    // is incremented, and that element would be placed before the pivot.
    for (int i = start; i < end; i++)
    {
        if (a[i] <= pivot)
        {
            std::swap(a[i], a[pIndex]);
            pIndex++;
        }
    }

    // swap `pIndex` with pivot
    std::swap(a[pIndex], a[end]);

    // return `pIndex` (index of the pivot element)
    return pIndex;
}

// Iterative Quicksort routine
void iterativeQuicksort(std::vector<int> a, int n)
{
    // create a stack of `std::pairs` for storing subarray start and end index
    std::stack<std::pair<int, int>> s;

    // get the starting and ending index of the given array
    int start = 0;
    int end = n - 1;

    // push the start and end index of the array into the stack
    s.push(std::make_pair(start, end));

    // loop till stack is empty
    while (!s.empty())
    {
        // remove top pair from the list and get subarray starting
        // and ending indices
        start = s.top().first, end = s.top().second;
        s.pop();

        // rearrange elements across pivot
        int pivot = _partition(a, start, end);

        // push subarray indices containing elements that are
        // less than the current pivot to stack
        if (pivot - 1 > start) {
            s.push(std::make_pair(start, pivot - 1));
        }

        // push subarray indices containing elements that are
        // more than the current pivot to stack
        if (pivot + 1 < end) {
            s.push(std::make_pair(pivot + 1, end));
        }
    }
}