#include"lib.h"
int main() {
    doc_file("DANHSACHNHOM9.txt");
    hien_thi_danh_sach(head);
    int luaChon;
    char mssv[20];
    SinhVien svMoi;
    do {
        luaChon = menu();  // Gọi hàm menu để in và lấy lựa chọn
        switch (luaChon) {
        case 1:
            hien_thi_danh_sach(head);
            break;
        case 2:
            nhap_mot_sinh_vien(&svMoi);
            them_sinh_vien(svMoi);
            hien_thi_danh_sach(head);
            break;
        case 3:
            printf("Nhap MSSV can sua: ");
            scanf("%s", mssv);
            getchar();
            sua_thong_tin(mssv);
            hien_thi_danh_sach(head);
            break;
        case 4:
            printf("Nhap MSSV can xoa: ");
            scanf("%s", mssv);
            getchar();
            xoa_sinh_vien(mssv);
            hien_thi_danh_sach(head);
            break;
        case 5:
            menu_tim_kiem();
            break;
        case 6:
            menu_sap_xep();
            break;
        case 7:
            thong_ke(head);
            break;
        case 8:
            ghi_file("DANHSACHNHOM9.txt");
            break;
        case 0:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le.\n");
        }
    } while (luaChon != 0);

    return 0;
}
