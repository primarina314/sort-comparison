#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;
using std::chrono::system_clock;

bool check_sorted(int* arr, int n);
void print_arr(int* arr, int n)
int* gen_data(int n, int seed = 0);
int* mysort(int* arr, int n);
int* insertion_sort(int* arr, int n);
void merge_sort_helper(int* arr, int l, int r, int* temp);
int* merge_sort(int* arr, int n);
void quick_sort_rand_piv_helper(int* arr, int l, int r);
int* quick_sort_rand_piv(int* arr, int n);
void quick_sort_last_piv_helper(int* arr, int l, int r);
int* quick_sort_last_piv(int* arr, int n);
int* heap_sort(int* arr, int n);
int* radix_sort(int* arr, int n);
void stooge_sort_helper(int* arr, int p, int r);
int* stooge_sort(int* arr, int n);

int main(void) {
    system_clock::time_point begin;
    double duration;
    bool is_sorted;
    int* arr;
    int n;

    // example of gen_data
    arr = gen_data(10);
    std::cout << "Example: ";
    print_arr(arr, 10);
    delete[] arr;

    n = 10000000;
    begin = system_clock::now();
    arr = gen_data(n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    std::cout << "Time for gen data: " << duration << "s" << endl;

    begin = system_clock::now();
    int* sorted = radix_sort(arr, n);
    duration = duration_cast<milliseconds>(system_clock::now() - begin).count() / 1000.0;
    std::cout << "Time for sort: " << duration << "s" << endl;

    is_sorted = check_sorted(sorted, n);
    std::cout << "Sorted(1: true, 0:false): " << check_sorted(sorted, n) << endl;
    if (!is_sorted) {
        std::cout << "Try the implementation again" << endl;
    }
    delete[] sorted;

    delete[] arr;
    return 0;
}

bool check_sorted(int* arr, int n) {
    for (size_t i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

void print_arr(int* arr, int n) {
    for (size_t i = 0; i < n; i++) {
        if (i) cout << ", ";
        cout << arr[i];
    }
    cout << endl;
}

int* gen_data(int n, int seed = 0) {
    int* arr = new int[n];
    mt19937 rs(seed);
    uniform_int_distribution<int> dist(0, INT32_MAX);

    for (size_t i = 0; i < n; i++) {
        arr[i] = dist(rs);
    }
    return arr;
}

int* mysort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    return sorted;
}
int* insertion_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    for(int j=1;j<n;j++)
    {
        int key = sorted[j];
        int i = j-1;
        while(i>=0 && sorted[i]>key)
        {
            sorted[i+1] = sorted[i];
            i--;
        }
        sorted[i+1] = key;
    }
    return sorted;
}
void merge_sort_helper(int* arr, int l, int r, int* temp)
{
    if(l<r)
    {
        int mid = (l+r)>>1;
        merge_sort_helper(arr, l, mid, temp);
        merge_sort_helper(arr, mid+1, r, temp);

        int* leftHalf = temp;
        int* rightHalf = temp + (mid-l+1);
        for(int i=l;i<=mid;i++) leftHalf[i-l] = arr[i];
        for(int i=mid+1;i<=r;i++) rightHalf[i-mid-1] = arr[i];

        int leftIdx=0, rightIdx=0;
        int idx = l;
        while(idx<=r)
        {
            if(leftIdx==mid-l+1) arr[idx++] = rightHalf[rightIdx++];
            else if(rightIdx==r-mid) arr[idx++] = leftHalf[leftIdx++];
            else if(leftHalf[leftIdx] < rightHalf[rightIdx]) arr[idx++] = leftHalf[leftIdx++];
            else arr[idx++] = rightHalf[rightIdx++];
        }
    }
}
int* merge_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    int* temp = new int[n];
    merge_sort_helper(sorted, 0, n-1, temp);
    delete[] temp;
    return sorted;
}
void quick_sort_rand_piv_helper(int* arr, int l, int r)
{
    int random = l+rand()%(r-l+1);
    int pivot = arr[random];
    std::swap(arr[random], arr[r]);
    int i = l-1;
    for(int j=l;j<r;j++)
    {
        if(arr[j] <= pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[r]);
    if(l<i) quick_sort_rand_piv_helper(arr, l, i);
    if(i+2<r) quick_sort_rand_piv_helper(arr, i+2, r);
}
int* quick_sort_rand_piv(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    quick_sort_rand_piv_helper(sorted, 0, n-1);
    return sorted;
}
void quick_sort_last_piv_helper(int* arr, int l, int r)
{
    int pivot = arr[r];
    int i = l-1;
    for(int j=l;j<r;j++)
    {
        if(arr[j] <= pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i+1], arr[r]);
    if(l<i) quick_sort_last_piv_helper(arr, l, i);
    if(i+2<r) quick_sort_last_piv_helper(arr, i+2, r);
}
int* quick_sort_last_piv(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    quick_sort_last_piv_helper(sorted, 0, n-1);
    return sorted;
}
int* heap_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    // Build max-heap
    for(int i=(n/2)-1;i >= 0;i--)
    {
        int parent=i;
        while(2*parent+1<n)
        {
            int child = 2*parent+1;
            if(child+1 < n && sorted[child] < sorted[child+1]) child++;
            if(sorted[parent] < sorted[child])
            {
                std::swap(sorted[parent], sorted[child]);
                parent = child;
            }
            else break;
        }
    }

    // Heap sort
    for(int i=n-1;i>=0;i--)
    {
        std::swap(sorted[0], sorted[i]);
        int parent = 0;
        while (2*parent+1 < i)
        {
            int child = 2*parent+1;
            if(child+1 < i && sorted[child] < sorted[child+1]) child++;
            if(sorted[parent] < sorted[child])
            {
                std::swap(sorted[parent], sorted[child]);
                parent = child;
            }
            else break;
        }
    }
    return sorted;
}
int* radix_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    int max_val = sorted[0];
    for(int i=1;i<n;i++) if(max_val < sorted[i]) max_val = sorted[i];
    
    // radix sort with 256-nary digit count sort
    int* count = new int[256]{0};
    int* output = new int[n]{0};
    for (int shift=0;shift<32;shift+=8)
    {
        for(int i=0;i<256;i++) count[i]=0;//reset count[]

        // each digit occurence - count
        for(int i=0;i<n;i++) count[(sorted[i] >> shift) & 0xFF]++;

        // prev sum
        for(int i=1;i<256;i++) count[i] += count[i-1];

        // output[] sorting
        for(int i=n-1;i>=0;i--) output[--count[(sorted[i] >> shift) & 0xFF]] = sorted[i];

        // sorted <- output for next iteration(shift)
        for(int i=0;i<n;i++) sorted[i] = output[i];
    }

    delete[] count;
    delete[] output;

    return sorted;
}
void stooge_sort_helper(int* arr, int p, int r)
{
    if(p==r) return;
    if(p+1==r)
    {
        if(arr[p]>arr[r]) std::swap(arr[p], arr[r]);
        return;
    }
    int q = (r-p+1)/3;
    stooge_sort_helper(arr, p, r-q);
    stooge_sort_helper(arr, p+q, r);
    stooge_sort_helper(arr, p, r-q);
}
int* stooge_sort(int* arr, int n) {
    int* sorted = new int[n];
    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }
    stooge_sort_helper(sorted, 0, n-1);
    return sorted;
}


