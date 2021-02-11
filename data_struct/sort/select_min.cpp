#include <iostream>
#include <vector>
using std::cout;
using std::vector;
using std::endl;

void PrintArray(const vector<int> & array);
int randomized_Select(std::vector<int>& array, int low, int higth, int index);
int main() {
    std::vector<int> array = {6,5,23,11,3, 4,111, 233, 8,5,4,0,1,34,56};
    auto temp = array;
    std::sort(temp.begin(), temp.end());
    PrintArray(temp);
    int k = randomized_Select(array, 0, array.size()-1 , 12);
    std::cout << "index 12, value "<< k << std::endl;
    k = randomized_Select(array, 0, array.size()-1 , array.size()-1);
    std::cout << "index 12, value "<< k << std::endl;
    k = randomized_Select(array, 0, array.size()-1 , 0);
    std::cout << "index 12, value "<< k << std::endl;
}

void PrintArray(const vector<int> & array) {
    cout << "{";
    for(const auto & x: array) {
        cout << x << ", ";
    }
    cout << "}" << endl;
}


int randomized_Partition(std::vector<int>& array, int low, int higth){
    int laster = array[higth];
    int index = low - 1;
    for(int i = low; i < higth; i++) {
        if (array[i] <= laster) {
            index++;
             std::swap(array[index], array[i]);
        }
    }
    index++;
    std::swap(array[index], array[higth]);
    return index;
}

int randomized_Select(std::vector<int>& array, int low, int higth, int index) {
    if (low == higth) {
        return array[low];
    }
    int par = randomized_Partition(array, low, higth);
    int key = par - low;
    if (key == index) {
        return array[key];
    }
    if (index < key) {
        return randomized_Select(array, low, par - 1, index);
    } else {
        return randomized_Select(array, par + 1, higth, index - key);
    }

}