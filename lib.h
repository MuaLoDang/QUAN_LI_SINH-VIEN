#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct SinhVien
{
    char hoTen[50];
    char mssv[20];
    char lopHoc[20];
    float GPA;
    struct SinhVien* next;
} SinhVien;

extern SinhVien* head;  // Danh sách sinh viên gốc

void xoa_xuong_dong(char x[]);//Hàm xóa ký tự /n
const char* layTen(const char* hoTen);//Hàm loại bỏ họ và tên đệm,

void ghi_file(const char* tenFile);
void doc_file(const char* tenFile);

void nhap_mot_sinh_vien(SinhVien* sv);
void them_sinh_vien(SinhVien svMoi);
void hien_thi_danh_sach(SinhVien* head);
void xoa_sinh_vien(char mssv[]);
void sua_thong_tin(char mssv[]);
void thong_ke(SinhVien* danh_sach);

SinhVien* tim_theo_mssv(char mssv[]);
void hien_thi_diem_cao_nhat(SinhVien* head);
void tim_theo_khoang_diem(float min, float max);

void sap_xep_theo_ten(SinhVien* head);
void sap_xep_theo_gpa(SinhVien* head);

void menu_sap_xep();// Hàm menu con: Tìm kiếm
void menu_tim_kiem();// Hàm menu con: Sắp xếp
int menu();// Hàm để in các chức năng và lấy lựa chọn