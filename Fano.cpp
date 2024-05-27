#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct tin_x {
    char name = 'x';
    short number;
    double xacsuat;
    vector<short> bin; // de luu ky hieu 0 va 1 thanh mot tu ma hoan chinh
};

void CapPhat_NguonTin (tin_x*& ptr, int n){
    ptr = new tin_x[n];
}
void ThuHoi_NguonTin (tin_x* ptr){
    delete [] ptr;
}

void Nhap_NguonTin (tin_x*& ptr, int n){
    for (int i=0; i<n; ++i){
        ptr[i].number = i+1;
        cout << "Tin x" << ptr[i].number << " co xac suat tuong ung p" << ptr[i].number << " = ";
        cin >> ptr[i].xacsuat;
    }
}

void SapXep_XacSuatNguonTin (tin_x*& ptr, int n){
    tin_x max, temp;
    int id;
    for (int i=0; i<n; ++i){
        max = ptr[i];
        for (int j=i; j<n; ++j){
            if (max.xacsuat < ptr[j].xacsuat){
                max = ptr[j];
                id = j;
            }
        }
        if (ptr[i].xacsuat < max.xacsuat){
            temp = ptr[i];
            ptr[i] = ptr[id];
            ptr[id] = temp;
        }
    }
}

void ChiaNhom_NguonTin (tin_x* ptr, int n){
    int j=0;
    if (n > 1){
        // sum_arr de tinh tong xac suat ca nguon tin
        double sum_p = 0;
        for (int i=0; i<n; ++i){
            sum_p += ptr[i].xacsuat;
        }
        // half_sum_arr de xac dinh xac suat 2 nhom xap xi nhau
        double half_sum_p = sum_p / 2;

        // sum de tim tong xac suat nhom tren
        double sum = 0;
        // mid_id de tim vi tri chia nhom
        int mid_id;
        for (int i=0; i<n; ++i){
            sum += ptr[i].xacsuat;
            if (sum >= half_sum_p){
                mid_id = i;
                break;
            }
        }
        if ((sum - half_sum_p) > (half_sum_p - sum + ptr[mid_id].xacsuat)){
            sum -= ptr[mid_id].xacsuat;
            mid_id--;
        }

        // Gan 0 cho nhom tren
        for (int i=0; i<mid_id+1; ++i){
            ptr[i].bin.push_back(0);
        }
        // Gan 1 cho nhom duoi
        for (int i=mid_id+1; i<n; ++i){
            ptr[i].bin.push_back(1);
        }

        // Dung de quy de tiep tuc chia nguon tin thanh cac nhom
        ChiaNhom_NguonTin(ptr, mid_id + 1);                         // De quy voi nhom tren
        ChiaNhom_NguonTin(ptr + mid_id + 1, n - mid_id - 1);        // De quy voi nhom duoi (Dung con tro)
    }
}

void HienThi_NguonTin (tin_x* ptr, int n){
    cout << endl;
    for (int i=0; i<n; ++i){
        cout << "Tin x" << ptr[i].number << " duoc ma hoa thanh ";
        for (int j=0; j<ptr[i].bin.size(); ++j){
            cout << ptr[i].bin[j];
        }
        cout << endl;
    }
}

double HeSoNenThongKe (tin_x* ptr, int n){
    // Tinh entropy cua nguon tin
    double entropy = 0;
    for (int i=0; i<n; ++i){
        entropy -= ptr[i].xacsuat * log2(ptr[i].xacsuat);
    }
    cout << "Entropy cua nguon tin H(X) = " << entropy << endl;

    // Tinh chieu dai tu ma trung binh cua nguon tin
    double ChieuDaiTuMaTrungBinh = 0;
    for (int i=0; i<n; ++i){
        ChieuDaiTuMaTrungBinh += ptr[i].bin.size() * ptr[i].xacsuat;
    }
    cout << "Chieu dai tu ma trung binh cua nguon tin la: " << ChieuDaiTuMaTrungBinh << endl;

    // He so nen thong ke khi thuc hien ma hoa theo Shannon-Fano
    double HeSoNenThongKe = entropy / ChieuDaiTuMaTrungBinh;
    return HeSoNenThongKe;
}

int main (){

    int n;
    tin_x* ptr;
    cout << "So tin trong nguon tin la ";
    cin >> n;

    CapPhat_NguonTin(ptr, n);

    Nhap_NguonTin(ptr, n);

    SapXep_XacSuatNguonTin(ptr, n);

    ChiaNhom_NguonTin(ptr, n);

    HienThi_NguonTin(ptr, n);

    cout << "He so nen thong ke khi thuc hien ma hoa Shannon-Fano Kt = " << HeSoNenThongKe(ptr, n);

    ThuHoi_NguonTin(ptr);
    
    return 0;
}
