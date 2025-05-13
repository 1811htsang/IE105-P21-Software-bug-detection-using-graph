#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

// Hàm xử lý mảng
void processArray(vector<int> &arr);
void printArray(const vector<int> &arr);
int findMax(const vector<int> &arr);
int findMin(const vector<int> &arr);

int main() {
    try {
        // Tạo mảng và thêm phần tử
        vector<int> arr = {10, 20, 30, 40, 50};

        // In mảng ban đầu
        cout << "Mảng ban đầu: ";
        printArray(arr);

        // Xử lý mảng
        processArray(arr);

        // In mảng sau khi xử lý
        cout << "Mảng sau khi xử lý: ";
        printArray(arr);

        // Tìm giá trị lớn nhất và nhỏ nhất
        cout << "Giá trị lớn nhất: " << findMax(arr) << endl;
        cout << "Giá trị nhỏ nhất: " << findMin(arr) << endl;

    } catch (const out_of_range &e) {
        cerr << "Lỗi: Truy cập ngoài phạm vi mảng - " << e.what() << endl;
    } catch (const exception &e) {
        cerr << "Lỗi: " << e.what() << endl;
    }

    return 0;
}

// Hàm xử lý mảng: nhân đôi giá trị của mỗi phần tử
void processArray(vector<int> &arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] *= 2;
    }
}

// Hàm in mảng
void printArray(const vector<int> &arr) {
    for (int val : arr) {
        cout << val << " ";
    }
    cout << endl;
}

// Hàm tìm giá trị lớn nhất trong mảng
int findMax(const vector<int> &arr) {
    if (arr.empty()) {
        throw runtime_error("Mảng rỗng, không thể tìm giá trị lớn nhất.");
    }
    int maxVal = arr[0];
    for (int val : arr) {
        if (val > maxVal) {
            maxVal = val;
        }
    }
    return maxVal;
}

// Hàm tìm giá trị nhỏ nhất trong mảng
int findMin(const vector<int> &arr) {
    if (arr.empty()) {
        throw runtime_error("Mảng rỗng, không thể tìm giá trị nhỏ nhất.");
    }
    int minVal = arr[0];
    for (int val : arr) {
        if (val < minVal) {
            minVal = val;
        }
    }
    return minVal;
}