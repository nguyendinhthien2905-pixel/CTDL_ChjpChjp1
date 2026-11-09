#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "TienIch.h"

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <conio.h>
#include <windows.h>

#include "HangSo.h"

const int DO_RONG_KHUNG = 43;
const int NHOM_HANG_NGAN = 3;
const int KICH_THUOC_BO_DEM_THOI_GIAN = 32;
const int SO_DAU_SAO_MENU = 8;
const int SO_CHU_SO_TOI_DA = 15;
const int PHIM_BACKSPACE = 8;
const int MA_ASCII_IN_DUOC_NHO_NHAT = 32;
const int MA_ASCII_XOA = 127;
const int LUA_CHON_KHONG_HOP_LE = -1;
const DWORD CO_BAT_MAU_CONSOLE = 0x0004;     // bat mau cho console Windows

/**********************************************************
 * @Description Xu ly mot phim khi nhap chuoi bi mat
 *
 * @return      Khong co
 * @attention   Backspace xoa mot ky tu, phim in duoc se hien dau *
 **********************************************************/
void CTienIch::xuLyPhimNhapAn(const int iPhim, std::string& strNhap) {
	const bool bPhimBackspace = (iPhim == PHIM_BACKSPACE);
	const bool bKyTuInDuoc = (iPhim >= MA_ASCII_IN_DUOC_NHO_NHAT && iPhim < MA_ASCII_XOA);
	if (bPhimBackspace && !strNhap.empty()) {
		strNhap.pop_back();
		std::cout << "\b \b";
	} else if (bKyTuInDuoc) {
		strNhap.push_back(static_cast<char>(iPhim));
		std::cout << '*';
	}
	std::cout.flush();
}

/**********************************************************
 * @Description Kiem tra chuoi khong rong va chi gom chu so
 *
 * @return      true neu moi ky tu deu la chu so
 **********************************************************/
bool CTienIch::chiGomChuSo(const std::string& strChuoi) {
	bool bKetQua = !strChuoi.empty();
	for (int i = 0; bKetQua && i < static_cast<int>(strChuoi.size()); i++) {
		bKetQua = std::isdigit(static_cast<unsigned char>(strChuoi[i])) != 0;
	}
	return bKetQua;
}

/**********************************************************
 * @Description Bat che do hien thi mau cua console Windows
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::batMau() {
	HANDLE hDauRa = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwCheDo = 0;
	if (GetConsoleMode(hDauRa, &dwCheDo)) {
		SetConsoleMode(hDauRa, dwCheDo | CO_BAT_MAU_CONSOLE);
	}
}

/**********************************************************
 * @Description Xoa man hinh console
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::xoaManHinh() {
	std::cout << "\033[2J\033[H";
}

/**********************************************************
 * @Description Xoa khoang trang o dau va cuoi chuoi
 *
 * @return      Chuoi da xoa khoang trang
 **********************************************************/
std::string CTienIch::catKhoangTrang(const std::string& strChuoi) {
	const std::string strKhoangTrang = " \t\r\n";
	const size_t uiDau = strChuoi.find_first_not_of(strKhoangTrang);
	if (uiDau == std::string::npos) {
		return "";
	}
	const size_t uiCuoi = strChuoi.find_last_not_of(strKhoangTrang);
	return strChuoi.substr(uiDau, uiCuoi - uiDau + 1);
}

/**********************************************************
 * @Description In thong bao loi mau do
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::baoLoi(const std::string& strThongBao) {
	std::cout << MAU_DO << "  [LOI] " << strThongBao << MAU_RESET << "\n";
}

/**********************************************************
 * @Description In thong bao thanh cong mau xanh la
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::baoThanhCong(const std::string& strThongBao) {
	std::cout << MAU_XANH_LA << "  [OK] " << strThongBao << MAU_RESET << "\n";
}

/**********************************************************
 * @Description In thong bao luu y mau vang
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::baoThongTin(const std::string& strThongBao) {
	std::cout << MAU_VANG << "  [!] " << strThongBao << MAU_RESET << "\n";
}

/**********************************************************
 * @Description Doc mot dong do nguoi dung nhap
 *
 * @return      Dong da xoa khoang trang
 * @attention   Thoat chuong trinh neu luong nhap bi dong
 **********************************************************/
std::string CTienIch::nhapDong(const std::string& strLoiNhac) {
	std::cout << strLoiNhac;
	std::cout.flush();
	std::string strDong;
	if (!std::getline(std::cin, strDong)) {
		std::cout << "\nKet thuc nhap lieu. Thoat chuong trinh.\n";
		std::exit(0);
	}
	return CTienIch::catKhoangTrang(strDong);
}

/**********************************************************
 * @Description Doc chuoi bi mat (PIN, mat khau), moi phim hien dau *
 *
 * @return      Chuoi nguoi dung da nhap
 **********************************************************/
std::string CTienIch::nhapAn(const std::string& strLoiNhac) {
	std::cout << strLoiNhac;
	std::cout.flush();
	std::string strNhap;
	int iPhim = _getch();
	while (iPhim != '\r' && iPhim != '\n') {
		CTienIch::xuLyPhimNhapAn(iPhim, strNhap);
		iPhim = _getch();
	}
	std::cout << "\n";
	return CTienIch::catKhoangTrang(strNhap);
}

/**********************************************************
 * @Description Doc lua chon menu, chi nhan mot chu so
 *
 * @return      Chu so da nhap, hoac LUA_CHON_KHONG_HOP_LE neu nhap sai
 **********************************************************/
int CTienIch::nhapLuaChonMenu(const std::string& strLoiNhac) {
	const std::string strNhap = CTienIch::nhapDong(strLoiNhac);
	int iLuaChon = LUA_CHON_KHONG_HOP_LE;
	if (CTienIch::laChuoiSo(strNhap, 1)) {
		iLuaChon = strNhap[0] - '0';
	}
	return iLuaChon;
}

/**********************************************************
 * @Description Cho nguoi dung nhan Enter
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::tamDung() {
	CTienIch::nhapDong(std::string(MAU_VANG) + "\n  Nhan Enter de tiep tuc..." + MAU_RESET);
}

/**********************************************************
 * @Description Kiem tra chuoi gom dung iDoDai chu so
 *
 * @return      true neu chuoi hop le
 **********************************************************/
bool CTienIch::laChuoiSo(const std::string& strChuoi, const int iDoDai) {
	return static_cast<int>(strChuoi.size()) == iDoDai && CTienIch::chiGomChuSo(strChuoi);
}

/**********************************************************
 * @Description Doi chuoi chu so thanh so
 *
 * @return      true neu chuoi la so khong am hop le
 * @attention   llKetQua chi bi thay doi khi chuoi hop le
 **********************************************************/
bool CTienIch::docSoTien(const std::string& strChuoi, long long& llKetQua) {
	const bool bHopLe = CTienIch::chiGomChuSo(strChuoi)
	                    && static_cast<int>(strChuoi.size()) <= SO_CHU_SO_TOI_DA;
	if (bHopLe) {
		llKetQua = std::stoll(strChuoi);
	}
	return bHopLe;
}

/**********************************************************
 * @Description Dinh dang tien co dau cham, 1500000 thanh 1.500.000
 *
 * @return      Chuoi da dinh dang
 **********************************************************/
std::string CTienIch::dinhDangTien(const long long llSoTien) {
	const std::string strCacChuSo = std::to_string(llSoTien);
	const int iDoDai = static_cast<int>(strCacChuSo.size());
	std::string strKetQua;
	for (int i = 0; i < iDoDai; i++) {
		strKetQua += strCacChuSo[i];
		const int iConLai = iDoDai - 1 - i;
		if (iConLai > 0 && iConLai % NHOM_HANG_NGAN == 0) {
			strKetQua += '.';
		}
	}
	return strKetQua;
}

/**********************************************************
 * @Description Lay ngay gio hien tai
 *
 * @return      Chuoi co dinh dang dd/mm/yyyy hh:mm:ss
 **********************************************************/
std::string CTienIch::layThoiGianHienTai() {
	const time_t lBayGio = time(nullptr);
	const tm* pGioDiaPhuong = localtime(&lBayGio);
	char szBoDem[KICH_THUOC_BO_DEM_THOI_GIAN] = { 0 };
	strftime(szBoDem, sizeof(szBoDem), "%d/%m/%Y %H:%M:%S", pGioDiaPhuong);
	return std::string(szBoDem);
}

/**********************************************************
 * @Description Hoi nguoi dung cau hoi Yes/No
 *
 * @return      true neu nguoi dung tra loi Y
 * @attention   Hoi lai cho den khi nguoi dung nhap Y hoac N
 **********************************************************/
bool CTienIch::xacNhan(const std::string& strCauHoi) {
	while (true) {
		const std::string strTraLoi = CTienIch::nhapDong(strCauHoi + " (Y/N): ");
		if (strTraLoi == "y" || strTraLoi == "Y") {
			return true;
		}
		if (strTraLoi == "n" || strTraLoi == "N") {
			return false;
		}
		CTienIch::baoLoi("Vui long nhap Y hoac N.");
	}
}

/**********************************************************
 * @Description In khung hinh chu nhat, tieu de nam giua
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::inKhung(const std::string& strTieuDe) {
	std::string strDongSao;
	for (int i = 0; i < DO_RONG_KHUNG; i++) {
		strDongSao += (i % 2 == 0) ? '*' : ' ';
	}
	const int iDoRongBenTrong = DO_RONG_KHUNG - 2;
	int iKhoangTrong = iDoRongBenTrong - static_cast<int>(strTieuDe.size());
	if (iKhoangTrong < 0) {
		iKhoangTrong = 0;
	}
	const int iLeTrai = iKhoangTrong / 2;
	const int iLePhai = iKhoangTrong - iLeTrai;
	std::cout << MAU_VANG << strDongSao << "\n"
	          << "*" << std::string(iLeTrai, ' ')
	          << MAU_XANH_LA << strTieuDe << MAU_VANG
	          << std::string(iLePhai, ' ') << "*\n"
	          << strDongSao << MAU_RESET << "\n";
}

/**********************************************************
 * @Description In menu danh so (1, 2, 3 ...)
 *
 * @return      Khong co
 **********************************************************/
void CTienIch::inMenu(const std::string& strTieuDe, const std::vector<std::string>& vecCacMuc) {
	std::string strGiua = strTieuDe;
	if (strGiua.size() % 2 == 0) {
		strGiua += ' ';           // giu do rong le de cac dau * thang hang
	}
	std::string strSaoTrai;
	std::string strSaoPhai;
	for (int i = 0; i < SO_DAU_SAO_MENU; i++) {
		strSaoTrai += "* ";
		strSaoPhai += " *";
	}
	const int iDoRong = static_cast<int>(strSaoTrai.size() + strGiua.size() + strSaoPhai.size());
	std::string strDongDuoi;
	for (int i = 0; i < iDoRong; i++) {
		strDongDuoi += (i % 2 == 0) ? '*' : ' ';
	}
	std::cout << MAU_XANH_NGOC << strSaoTrai << MAU_VANG << strGiua
	          << MAU_XANH_NGOC << strSaoPhai << MAU_RESET << "\n";
	for (int i = 0; i < static_cast<int>(vecCacMuc.size()); i++) {
		std::cout << MAU_TRANG << "  " << (i + 1) << ". " << MAU_RESET << vecCacMuc[i] << "\n";
	}
	std::cout << MAU_XANH_NGOC << strDongDuoi << MAU_RESET << "\n";
}
