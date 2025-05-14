#include <bits/stdc++.h>
#define MAXN 300
typedef int* pointer_int;
using namespace std;

void NhapChuoi(char hoten[]) {
    cin.getline(hoten, MAXN);
}
int DemChuInHoa(char hoten[]) {
    int dem = 0;
    for (int i = 0; i < strlen(hoten); i++) {
        if (hoten[i] >= 'A' && hoten[i] <= 'Z') {
            dem++;
        }
    }
    return dem;
}
int main(){
    char hoten[MAXN];
    NhapChuoi(hoten);
    std::cout << DemChuInHoa(hoten) << endl;
    return 0;
}