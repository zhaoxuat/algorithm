#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

void PrintArray(const vector<int> & array);
bool equal(const vector<int>& l, const vector<int>& r);
void insertion_sort(vector<int>& array);
void bubbleSort(vector<int>& array);
void mergeSort(vector<int>& array);
void merget(vector<int>& array, int l, int m, int r);
void _mergeSort(vector<int>& array, int l, int r);
void heapSort(vector<int>& array);
void quick_sort(vector<int>& array);

int main() {
    vector<int> arr = {6, 5, 23, 11, 3, 4, 111, 233, 8, 5, 4, 0, 1, 34, 56};
    auto arrtTemp = arr;
    insertion_sort(arrtTemp);
    quick_sort(arr);
    PrintArray(arr);
 
}

void PrintArray(const vector<int> & array) {
    cout << "{";
    for(const auto & x: array) {
        cout << x << ", ";
    }
    cout << "}" << endl;
}

bool equal(const vector<int>& l, const vector<int>& r){
    if (l.size() != r.size()) {
        return false;
    }
    for(int index = 0; index < l.size(); index++) {
        if (l[index] != r[index]) {
            return false;
        }
    }
    return true;
}

void insertion_sort(vector<int>& array) {
    auto len = array.size();
    int i,j;
    for(i = 1; i < len; i++) {
        auto temp = array[i];
        for (j = i; j > 0 && array[j - 1] > temp; j--) {
            array[j] = array[j-1];
        }
        array[j] = temp;
    }
}

void bubbleSort(vector<int>& array) {
    auto swap = array.size();
    while (swap)
    {
        swap = false;
        for(int i = 0; i < array.size() - 1; i++) {
            if(array[i] > array[i+1]) {
                std::swap(array[i], array[i+1]);
                swap = true;
            }
        }
    }
}

void merget(vector<int>& array, int l, int m, int r) {
    auto n1 = m - l + 1;
    auto n2 = r - m;
    vector<int> Larr(n1);
    vector<int> Rarr(n2);
    for(int index = 0; index < n1; index++) {
         Larr[index] = array[l + index];
    }
    for(int index = 0; index < n2; index++) {
        Rarr[index] = array[index + m + 1];
    }
    int i = 0, j = 0; 
    int k = l;
    while (i < n1 && j < n2)
    {
        if(Larr[i] <= Rarr[j]) {
            array[k] = Larr[i];
            i++;
        } else {
            array[k] = Rarr[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        array[k] = Larr[i];
        i++;
        k++;
    }
    while (j < n2) {
        array[k] = Rarr[j];
        j++;
        k++;
    }
    return ;
}

void _mergeSort(vector<int>& array, int l, int r) {
    if (l < r) {
        auto m = (l + r) / 2;
        _mergeSort(array, l, m);
        _mergeSort(array, m+1, r);
        merget(array, l, m, r);
       
    }
    return;
}

void mergeSort(vector<int>& array) {
    _mergeSort(array, 0, array.size() -1);
}

void heapModify(vector<int>& array, int index, int length) {
    while (true)
    {
        int laster = index;
        int left = index * 2 + 1;
        int right = index * 2 + 2;
        if (left < length && array[left] > array[laster]) {
            laster = left;
        }
        if (right < length && array[right] > array[laster]) {
            laster = right;
        }
        if (laster == index) {
            break;
        }
        std::swap(array[laster], array[index]);
        index = laster;
    }
}

void heapSort(vector<int>& array) {
    for(int index = array.size() / 2 -1; index >=0; index--) {
        heapModify(array, index, array.size());
    }
    for(int index = array.size() -1 ; index >= 1; index --) {
        std::swap(array[0], array[index]);
        heapModify(array, 0, index);
    }
}


int partition(vector<int>& array, int low, int hight) {
    int laster = array[hight];
    int index = low - 1;
    for (int i = low; i < hight; i++) {
        if(array[i] <= laster){
            index++;
            std::swap(array[index], array[i]);
        }
    }
    index++;
    std::swap(array[index], array[hight]);
    return index;
}

void _quick_sort(vector<int>& array,int low, int hight) {
    if (low < hight) {
        int par = partition(array, low, hight);
        _quick_sort(array, low, par - 1);
         _quick_sort(array, par + 1, hight);
    }
}

void quick_sort(vector<int>& array) {
    _quick_sort(array, 0, array.size() - 1);
}



