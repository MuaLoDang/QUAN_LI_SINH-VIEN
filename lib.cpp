#include"lib.h"
SinhVien* head = NULL;
void xoa_xuong_dong(char x[]) {
    size_t len = strlen(x);      //tính độ dài chuỗi không tính /0
    if (len > 0 && x[len - 1] == '\n') {
        x[len - 1] = '\0';
    }
}
const char* layTen(const char* hoTen) {
    const char* ten = strrchr(hoTen, ' ');
    return (ten != NULL) ? ten + 1 : hoTen;
}
void doc_file(const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Khong mo duoc file.\n");
        return;
    }

    char dong[200];
    SinhVien sv;
    while (fgets(dong, sizeof(dong), f)) {
        xoa_xuong_dong(dong);
        sscanf(dong, "%[^;];%[^;];%[^;];%f", sv.mssv, sv.hoTen, sv.lopHoc, &sv.GPA);
        them_sinh_vien(sv);
    }

    fclose(f);
}
void ghi_file(const char* tenFile) {
    FILE* f = fopen(tenFile, "w");
    if (f == NULL) {
        printf("Khong mo duoc file de ghi.\n");
        return;
    }
    SinhVien* p = head;
    while (p != NULL) {
        fprintf(f, "%s;%s;%s;%.2f\n", p->mssv, p->hoTen, p->lopHoc, p->GPA);
        p = p->next;
    }

    fclose(f);
    printf("Da ghi file thanh cong!\n");
}
void nhap_mot_sinh_vien(SinhVien* sv) {

    printf("Nhap MSSV: ");
    fgets(sv->mssv,50, stdin);
    xoa_xuong_dong(sv->mssv);

    printf("Nhap ho ten: ");
    fgets(sv->hoTen,20, stdin);
    xoa_xuong_dong(sv->hoTen);

    printf("Nhap lop hoc: ");
    fgets(sv->lopHoc, 20, stdin);
    xoa_xuong_dong(sv->lopHoc);

    printf("Nhap diem GPA: ");
    scanf("%f", &sv->GPA); 
    getchar();

    sv->next = NULL; // Khởi tạo con trỏ next là NULL xem node cuối danh sách
}
void them_sinh_vien(SinhVien svMoi) {
    SinhVien* nodeMoi = (SinhVien*)malloc(sizeof(SinhVien));
    *nodeMoi = svMoi;
    nodeMoi->next = NULL;

    if (head == NULL || strcmp(svMoi.mssv, head->mssv) < 0) {
        nodeMoi->next = head;
        head = nodeMoi;
    }
    else {
        SinhVien* p = head;
        while (p->next != NULL && strcmp(p->next->mssv, svMoi.mssv) < 0) {
            p = p->next;
        }
        nodeMoi->next = p->next;
        p->next = nodeMoi;
    }
}
void hien_thi_danh_sach(SinhVien* head) {
    SinhVien* p = head;// Duyệt từ đầu danh sách

    if (p == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    printf("+------------+-------------------------------+---------------+--------+\n");
    printf("|   MSSV     |           Ho ten              |   Lop hoc     |  Diem  |\n");
    printf("+------------+-------------------------------+---------------+--------+\n");

    while (p != NULL) {
        printf("| %-10s | %-29s | %-13s | %6.2f |\n",p->mssv, p->hoTen, p->lopHoc, p->GPA);
        printf("+------------+-------------------------------+---------------+--------+\n");
        p = p->next;
    }
}
void xoa_sinh_vien(char mssv[]) {
    SinhVien* p = head;
    SinhVien* truoc = NULL; //con trỏ để lưu phần tử trước phần tử hiện tại

    while (p != NULL && strcmp(p->mssv, mssv) != 0) {
        truoc = p;
        p = p->next;
    }

    if (p == NULL) {
        printf("Khong tim thay MSSV %s\n", mssv);
        return;
    }

    if (truoc == NULL) head = p->next;
    else truoc->next = p->next;

    free(p);
}
void sua_thong_tin(char mssv[]) {
    SinhVien* sv = tim_theo_mssv(mssv);
    if (sv == NULL) {
        printf("Khong tim thay MSSV %s\n", mssv);
        return;
    }

    printf("Nhap ho ten: ");
    fgets(sv->hoTen, 20, stdin);
    xoa_xuong_dong(sv->hoTen);

    printf("Nhap lop hoc: ");
    fgets(sv->lopHoc, 20, stdin);
    xoa_xuong_dong(sv->lopHoc);

    printf("Nhap diem GPA: ");
    scanf("%f", &sv->GPA);
    getchar();
}
void thong_ke(SinhVien* danh_sach) {
    if (danh_sach == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    int tong_sv = 0, gioi = 0, kha = 0, tb = 0, kem = 0;
    float tong_gpa = 0.0;
    float gpa_max = -1.0;
    SinhVien* sv_max = NULL;

    SinhVien* p = danh_sach;
    while (p != NULL) {
        tong_sv++;
        tong_gpa += p->GPA;

        // Phân loại
        if (p->GPA >= 8.0)
            gioi++;
        else if (p->GPA >= 6.5)
            kha++;
        else if (p->GPA >= 5.0)
            tb++;
        else
            kem++;

        // Điểm cao nhất
        if (p->GPA > gpa_max) {
            gpa_max = p->GPA;
            sv_max = p;
        }

        p = p->next;
    }

    float gpa_tb = tong_gpa / tong_sv;

    printf("\n=== THONG KE LOP HOC ===\n");
    printf("So sinh vien: %d\n", tong_sv);
    printf("GPA trung binh ca lop: %.2f\n", gpa_tb);
    printf("Sinh vien gioi: %d (%.2f%%)\n", gioi, (float)gioi / tong_sv * 100);
    printf("Sinh vien kha : %d (%.2f%%)\n", kha, (float)kha / tong_sv * 100);
    printf("Sinh vien TB  : %d (%.2f%%)\n", tb, (float)tb / tong_sv * 100);
    printf("Sinh vien kem : %d (%.2f%%)\n", kem, (float)kem / tong_sv * 100);

    if (sv_max != NULL) {
        printf("\n Sinh vien diem cao nhat:\n");
        printf("MSSV: %s\t", sv_max->mssv);
        printf("Ho ten: %s\t", sv_max->hoTen);
        printf("GPA: %.2f\n", sv_max->GPA);
    }
}
SinhVien* tim_theo_mssv(char mssv[]) {
    SinhVien* p = head;
    while (p != NULL) {
        if (strcmp(p->mssv, mssv) == 0) {
            return p;  // Trả về địa chỉ node tìm được
        }
        p = p->next;
    }
    return NULL; // Không tìm thấy thì trả NULL
}
void hien_thi_diem_cao_nhat(SinhVien* head) {
    if (head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }

    float maxGPA = head->GPA;
    SinhVien* p = head->next;

    // Tìm GPA cao nhất
    while (p != NULL) {
        if (p->GPA > maxGPA) {
            maxGPA = p->GPA;
        }
        p = p->next;
    }

    // Kiểm tra có sinh viên nào có GPA cao nhất không
    if (maxGPA == 0) {
        printf("Khong co sinh vien co GPA cao.\n");
        return;
    }

    // In các SV có GPA cao nhất
    printf("\nCac sinh vien co GPA cao nhat (%.2f):\n", maxGPA);
    printf("+------------+-------------------------------+---------------+--------+\n");
    printf("|   MSSV     |           Ho ten              |   Lop hoc     |  Diem  |\n");
    printf("+------------+-------------------------------+---------------+--------+\n");

    p = head;
    int found = 0;  // Biến kiểm tra nếu có sinh viên nào có GPA cao nhất
    while (p != NULL) {
        if (p->GPA == maxGPA) {
            printf("| %-10s | %-29s | %-13s | %6.2f |\n",
                p->mssv, p->hoTen, p->lopHoc, p->GPA);
            found = 1;
        }
        p = p->next;
    }

    if (!found) {
        printf("Khong tim thay sinh vien co GPA cao nhat.\n");
    }
    else {
        printf("+------------+-------------------------------+---------------+--------+\n");
    }
}
void tim_theo_khoang_diem(float min, float max) {
    int found = 0;
    SinhVien* p = head;

    printf("\nCac sinh vien co GPA trong khoang %.2f - %.2f:\n", min, max);
    printf("+------------+-------------------------------+---------------+--------+\n");
    printf("|   MSSV     |           Ho ten              |   Lop hoc     |  Diem  |\n");
    printf("+------------+-------------------------------+---------------+--------+\n");

    while (p != NULL) {
        if (p->GPA >= min && p->GPA <= max) {
            found = 1;
            printf("| %-10s | %-29s | %-13s | %6.2f |\n",
                p->mssv, p->hoTen, p->lopHoc, p->GPA);
            printf("+------------+-------------------------------+---------------+--------+\n");
        }
        p = p->next;
    }

    if (!found) {
        printf("Khong co sinh vien nao trong khoang diem nay.\n");
    }
}
void sap_xep_theo_ten(SinhVien* head) {
    if (head == NULL || head->next == NULL) return;

    SinhVien* i, * j;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (strcmp(layTen(i->hoTen), layTen(j->hoTen)) > 0) {
                // Hoán đổi toàn bộ dữ liệu sinh viên
                SinhVien temp = *i;
                *i = *j;
                *j = temp;

                // Khôi phục liên kết next (vì *i và *j bị tráo)
                SinhVien* tmpNext = i->next;
                i->next = j->next;
                j->next = tmpNext;
            }
        }
    }
}
void sap_xep_theo_gpa(SinhVien* head) {
    if (head == NULL || head->next == NULL) return;

    SinhVien* i, * j;
    for (i = head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->GPA < j->GPA) {
                // Hoán đổi 
                SinhVien temp = *i;
                *i = *j;
                *j = temp;

                // Giữ liên kết đúng
                SinhVien* tmpNext = i->next;
                i->next = j->next;
                j->next = tmpNext;
            }
        }
    }
}
void menu_tim_kiem() {
    int chon;
    char mssv[20];
    float min, max;

    do {
        printf("\n===== MENU TIM KIEM =====\n");
        printf("1. Tim theo MSSV\n");
        printf("2. Tim diem cao nhat\n");
        printf("3. Tim theo khoang diem\n");
        printf("4. Quay lai menu chinh\n");
        printf("Chon: ");
        scanf("%d", &chon);

        switch (chon) {
        case 1: {
              printf("Nhap MSSV: ");
              scanf("%s", mssv); getchar();
              SinhVien* sv = tim_theo_mssv(mssv);
              if (sv) {
                  hien_thi_danh_sach(sv);
              }
              else {
                  printf("Khong tim thay sinh vien.\n");
              }
              break;
        }
        case 2:
            hien_thi_diem_cao_nhat(head);
            break;
        case 3:
            printf("Nhap diem min: ");
            scanf("%f", &min);
            printf("Nhap diem max: ");
            scanf("%f", &max);
            tim_theo_khoang_diem(min, max);
            break;
        case 4:
            return;
        default:
            printf("Lua chon khong hop le.\n");
        }
    } while (chon != 4);
}
void menu_sap_xep() {
    int chon;

    do {
        printf("\n===== MENU SAP XEP =====\n");
        printf("1. Sap xep theo ten\n");
        printf("2. Sap xep theo GPA (Max -> Min)\n");
        printf("3. Quay lai menu chinh\n");
        printf("Chon: ");
        scanf("%d", &chon);

        switch (chon) {
        case 1:
            sap_xep_theo_ten(head);
            hien_thi_danh_sach(head);
            break;
        case 2:
            sap_xep_theo_gpa(head);
            hien_thi_danh_sach(head);
            break;
        case 3:
            return;
        default:
            printf("Lua chon khong hop le.\n");
        }
    } while (chon != 3);
}
int menu() {
    int luaChon;
    printf("\n===== MENU QUAN LY SINH VIEN =====\n");
    printf("1. In danh sach sinh vien \n");
    printf("2. Them sinh vien\n");
    printf("3. Sua sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Tim kiem\n");
    printf("6. Sap xep\n");
    printf("7. Thong ke\n");
    printf("8. Sao luu (file)\n");
    printf("0. Thoat\n");
    printf("Chon: ");
    scanf("%d", &luaChon);
    getchar();
    return luaChon;
}

