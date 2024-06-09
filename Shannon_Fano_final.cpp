#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct tin_x {
    char kyTu;
    short number;
    double xacsuat;
    vector<short> bin; // luu ky hieu 0 va 1 de thanh mot tu ma hoan chinh
};

void CapPhat_NguonTin(tin_x*& ptr, int n) {
    ptr = new tin_x[n];
}

void ThuHoi_NguonTin(tin_x* ptr) {
    delete[] ptr;
}

void TinhXacSuat(const string& chuoi, tin_x*& ptr, int& n) {
    // Mang tinh tan suat xuat hien cua cac ky tu 'a' den 'z' va '0' đến '9'
    int tanSo[36] = {0};
    int tongSoKyTu = 0;

    // Tinh xac suat xuat hien cua tung ky tu (khong phan biet chu hoa voi chu thuong)
    for (char kyTu : chuoi) {
        char kyTuThuong = tolower(kyTu);
        if (isalnum(kyTuThuong)) {
            int viTri;
            if (isalpha(kyTuThuong)) {
                viTri = kyTuThuong - 'a';
            } else {
                viTri = 26 + (kyTuThuong - '0');
            }
            tanSo[viTri]++;
            tongSoKyTu++;
        }
    }

    // Tinh so luong ky tu khac nhau de cap phat cho mang dong
    n = 0;
    for (int i = 0; i < 36; ++i) {
        if (tanSo[i] > 0) {
            n++;
        }
    }
    CapPhat_NguonTin(ptr, n);

    // Gan cac gia tri cho mang dong tin_x
    int index = 0;
    for (int i = 0; i < 36; ++i) {
        if (tanSo[i] > 0) {
            if (i < 26) {
                ptr[index].kyTu = 'a' + i;
            } else {
                ptr[index].kyTu = '0' + (i - 26);
            }
            ptr[index].number = index + 1;
            ptr[index].xacsuat = static_cast<double>(tanSo[i]) / tongSoKyTu;
            index++;
        }
    }
}

void SapXep_XacSuatNguonTin(tin_x*& ptr, int n) {
    tin_x max, temp;
    int id;
    for (int i = 0; i < n; ++i) {
        max = ptr[i];
        for (int j = i; j < n; ++j) {
            if (max.xacsuat < ptr[j].xacsuat) {
                max = ptr[j];
                id = j;
            }
        }
        if (ptr[i].xacsuat < max.xacsuat) {
            temp = ptr[i];
            ptr[i] = ptr[id];
            ptr[id] = temp;
        }
    }
}

void ChiaNhom_NguonTin(tin_x* ptr, int n) {
    if (n > 1) {
        // sum_p la tong xac suat cua nguon tin
        double sum_p = 0;
        for (int i = 0; i < n; ++i) {
            sum_p += ptr[i].xacsuat;
        }
        // half_sum_p la 1/2 tong xac suat (xap xi tong xac suat cua 2 nhom)
        double half_sum_p = sum_p / 2;

        // sum de tim tong xac suat cua nhom tren
        double sum = 0;
        // mid_id de tim vi tri chia nhom
        int mid_id;
        for (int i = 0; i < n; ++i) {
            sum += ptr[i].xacsuat;
            if (sum >= half_sum_p) {
                mid_id = i;
                break;
            }
        }
        if ((sum - half_sum_p) > (half_sum_p - sum + ptr[mid_id].xacsuat)) {
            sum -= ptr[mid_id].xacsuat;
            mid_id--;
        }

        // Gan 0 cho nhom tren
        for (int i = 0; i < mid_id + 1; ++i) {
            ptr[i].bin.push_back(0);
        }
        // Gan 1 cho nhom duoi
        for (int i = mid_id + 1; i < n; ++i) {
            ptr[i].bin.push_back(1);
        }

        // Dung de quy de tiep tuc chia nhom thanh cac nhom nho hon
        ChiaNhom_NguonTin(ptr, mid_id + 1);                         // De quy voi nhom tren
        ChiaNhom_NguonTin(ptr + mid_id + 1, n - mid_id - 1);        // De quy voi nhom duoi (Thay doi dia chi cua con tro)
    }
}

void HienThi_NguonTin(tin_x* ptr, int n) {
    cout << "\nBang ma hoa Shannon-Fano:\n";
    cout << " Ky tu | Ma nhi phan \n";
    cout << "--------------------\n";
    for (int i = 0; i < n; ++i) {
        cout << "   " << ptr[i].kyTu << "   |   ";
        for (int j = 0; j < ptr[i].bin.size(); ++j) {
            cout << ptr[i].bin[j];
        }
        cout << "\n";
    }
    cout << "--------------------\n";
}

string MaHoaTinNhan(const string& chuoi, tin_x* ptr, int n) {
    string tinNhanMaHoa;
    for (char kyTu : chuoi) {
        char kyTuThuong = tolower(kyTu);
        if (isalnum(kyTuThuong)) {
            for (int i = 0; i < n; ++i) {
                if (ptr[i].kyTu == kyTuThuong) {
                    for (int j = 0; j < ptr[i].bin.size(); ++j) {
                        tinNhanMaHoa += to_string(ptr[i].bin[j]);
                    }
                }
            }
        }
    }
    return tinNhanMaHoa;
}

double HeSoNenThongKe(tin_x* ptr, int n) {
    // Tinh entropy cua nguon tin
    double entropy = 0;
    for (int i = 0; i < n; ++i) {
        entropy -= ptr[i].xacsuat * log2(ptr[i].xacsuat);
    }

    // Tinh chieu dai tu ma cua nguon tin
    double ChieuDaiTuMaTrungBinh = 0;
    for (int i = 0; i < n; ++i) {
        ChieuDaiTuMaTrungBinh += ptr[i].bin.size() * ptr[i].xacsuat;
    }

    // He so nen thong ke khi thuc hien ma hoa Shannon-Fano
    double HeSoNenThongKe = entropy / ChieuDaiTuMaTrungBinh;
    return HeSoNenThongKe;
}

int main() {

    int n;
    tin_x* ptr;
    string chuoiKyTu;

    cout << "Nhap tin nhan can duoc ma hoa: ";
    getline(cin, chuoiKyTu);

    TinhXacSuat(chuoiKyTu, ptr, n);

    SapXep_XacSuatNguonTin(ptr, n);

    ChiaNhom_NguonTin(ptr, n);

    HienThi_NguonTin(ptr, n);

    string tinNhanMaHoa = MaHoaTinNhan(chuoiKyTu, ptr, n);
    cout << "Tin nhan sau khi duoc ma hoa: " << tinNhanMaHoa << endl;

    cout << "He so nen thong ke khi thuc hien ma hoa Shannon-Fano Kt = " << HeSoNenThongKe(ptr, n) << endl;

    ThuHoi_NguonTin(ptr);

    return 0;
}
