#include "DichVuUser.h"

#include <iomanip>
#include <iostream>
#include <vector>

#include "HangSo.h"
#include "KhoFile.h"
#include "NganXep.h"
#include "TienIch.h"

const std::string NHAP_HUY = "0";

enum LuaChonMenuUser {
	USER_XEM_THONG_TIN = 1,
	USER_RUT_TIEN,
	USER_CHUYEN_TIEN,
	USER_XEM_LICH_SU,
	USER_DOI_PIN,
	USER_THOAT
};

/**********************************************************
 * @Description Kiem tra so tien rut / chuyen
 *
 * @return      true neu so tien hop le
 * @attention   strThongBao nhan ly do khi khong hop le
 *              Quy tac: >= 50.000, la boi so cua 50.000, so du con lai >= 50.000
 **********************************************************/
bool CDichVuUser::laSoTienHopLe(const long long llSoTien, const long long llSoDu, std::string& strThongBao) {
	const std::string strBuoc = CTienIch::dinhDangTien(BUOC_TIEN);
	if (llSoTien < BUOC_TIEN) {
		strThongBao = "So tien toi thieu la " + strBuoc + ".";
		return false;
	}
	if (llSoTien % BUOC_TIEN != 0) {
		strThongBao = "So tien phai la boi so cua " + strBuoc + ".";
		return false;
	}
	if (llSoTien > llSoDu - BUOC_TIEN) {
		strThongBao = "So tien vuot muc cho phep (phai giu lai " + strBuoc + " trong tai khoan).";
		return false;
	}
	return true;
}

/**********************************************************
 * @Description Yeu cau nhap so tien cho den khi hop le
 *
 * @return      So tien, hoac 0 neu nguoi dung huy
 **********************************************************/
long long CDichVuUser::nhapSoTien(const long long llSoDu, const std::string& strLoiNhac) {
	while (true) {
		const std::string strNhap = CTienIch::nhapDong(strLoiNhac);
		if (strNhap == NHAP_HUY) {
			return 0;
		}
		long long llSoTien = 0;
		std::string strThongBao;
		if (!CTienIch::docSoTien(strNhap, llSoTien)) {
			CTienIch::baoLoi("So tien khong hop le.");
		} else if (!CDichVuUser::laSoTienHopLe(llSoTien, llSoDu, strThongBao)) {
			CTienIch::baoLoi(strThongBao);
		} else {
			return llSoTien;
		}
	}
}

/**********************************************************
 * @Description In so du hien tai cua tai khoan
 *
 * @return      Khong co
 **********************************************************/
void CDichVuUser::inSoDu(const CTaiKhoan& objTaiKhoan) {
	std::cout << "  So du hien tai: " << MAU_XANH_LA
	          << CTienIch::dinhDangTien(objTaiKhoan.laySoDu()) << " "
	          << objTaiKhoan.layTienTe() << MAU_RESET << "\n";
}

/**********************************************************
 * @Description In mot dong giao dich trong bang lich su
 *
 * @return      Khong co
 **********************************************************/
void CDichVuUser::inDongGiaoDich(const CGiaoDich& objGiaoDich) {
	const bool bLaNhan = (objGiaoDich.layLoai() == LOAI_NHAN);
	const std::string strDau = bLaNhan ? "+" : "-";
	const std::string strSoTien = strDau + CTienIch::dinhDangTien(objGiaoDich.laySoTien());
	std::cout << std::left << std::setw(DO_RONG_COT_THOI_GIAN) << objGiaoDich.layThoiGian()
	          << (bLaNhan ? MAU_XANH_LA : MAU_DO)
	          << std::setw(DO_RONG_COT_LOAI) << objGiaoDich.layLoai()
	          << std::setw(DO_RONG_COT_SO_TIEN) << strSoTien
	          << MAU_RESET << objGiaoDich.layNoiDung() << "\n";
}

/**********************************************************
 * @Description Chuyen tien giua hai tai khoan va ghi lich su
 *
 * @return      Khong co
 * @attention   Hoan lai thay doi neu khong ghi duoc file
 **********************************************************/
void CDichVuUser::thucHienChuyenTien(CTaiKhoan& objNguoiGui, CTaiKhoan& objNguoiNhan, const long long llSoTien) {
	objNguoiGui.datSoDu(objNguoiGui.laySoDu() - llSoTien);
	objNguoiNhan.datSoDu(objNguoiNhan.laySoDu() + llSoTien);
	if (!CKhoFile::ghiTaiKhoan(objNguoiGui)) {
		CTienIch::baoLoi("Loi ghi file. Giao dich bi huy.");
		return;
	}
	if (!CKhoFile::ghiTaiKhoan(objNguoiNhan)) {
		objNguoiGui.datSoDu(objNguoiGui.laySoDu() + llSoTien);
		CKhoFile::ghiTaiKhoan(objNguoiGui);
		CTienIch::baoLoi("Loi ghi file tai khoan nhan. Giao dich bi huy.");
		return;
	}
	const std::string strThoiGian = CTienIch::layThoiGianHienTai();
	CKhoFile::themLichSu(objNguoiGui.layMaSo(), CGiaoDich(LOAI_CHUYEN, llSoTien, strThoiGian,
	                     "Chuyen den " + objNguoiNhan.layMaSo() + " - " + objNguoiNhan.layTen()));
	CKhoFile::themLichSu(objNguoiNhan.layMaSo(), CGiaoDich(LOAI_NHAN, llSoTien, strThoiGian,
	                     "Nhan tu " + objNguoiGui.layMaSo() + " - " + objNguoiGui.layTen()));
	CTienIch::baoThanhCong("Chuyen tien thanh cong. So du con lai: "
	                       + CTienIch::dinhDangTien(objNguoiGui.laySoDu()) + " " + objNguoiGui.layTienTe());
}

/**********************************************************
 * @Description Yeu cau nhap tai khoan nhan cho den khi hop le
 *
 * @return      true neu da chon nguoi nhan, false neu nguoi dung huy
 **********************************************************/
bool CDichVuUser::nhapNguoiNhan(CTaiKhoan& objNguoiNhan) const {
	while (true) {
		const std::string strMaSo = CTienIch::nhapDong("  Nhap so tai khoan nhan (0 de huy): ");
		if (strMaSo == NHAP_HUY) {
			CTienIch::baoThongTin("Da huy giao dich.");
			return false;
		}
		if (!CTienIch::laChuoiSo(strMaSo, DO_DAI_MA_SO)) {
			CTienIch::baoLoi("So tai khoan phai gom 14 chu so.");
		} else if (strMaSo == this->m_pThe->layMaSo()) {
			CTienIch::baoLoi("Khong the chuyen tien cho chinh minh.");
		} else if (this->m_objDanhSachThe.tim(strMaSo) == nullptr || !CKhoFile::docTaiKhoan(strMaSo, objNguoiNhan)) {
			CTienIch::baoLoi("So tai khoan nhan khong ton tai.");
		} else {
			return true;
		}
	}
}

/**********************************************************
 * @Description Kiem tra ma PIN hien tai nguoi dung nhap
 *
 * @return      true neu ma PIN dung
 **********************************************************/
bool CDichVuUser::xacThucPinHienTai() const {
	const std::string strPinCu = CTienIch::nhapAn("  Nhap ma PIN hien tai: ");
	if (strPinCu != this->m_pThe->layPin()) {
		CTienIch::baoLoi("Ma PIN hien tai khong dung.");
		return false;
	}
	return true;
}

/**********************************************************
 * @Description Kiem tra ma PIN moi
 *
 * @return      true neu ma PIN hop le
 * @attention   strThongBao nhan ly do khi khong hop le
 **********************************************************/
bool CDichVuUser::laPinMoiHopLe(const std::string& strPin, std::string& strThongBao) const {
	if (!CTienIch::laChuoiSo(strPin, DO_DAI_PIN)) {
		strThongBao = "Ma PIN phai gom dung 6 chu so.";
		return false;
	}
	if (strPin == this->m_pThe->layPin()) {
		strThongBao = "Ma PIN moi khong duoc giong ma PIN cu.";
		return false;
	}
	if (strPin == PIN_MAC_DINH) {
		strThongBao = "Ma PIN moi khong duoc giong ma PIN mac dinh.";
		return false;
	}
	return true;
}

/**********************************************************
 * @Description Yeu cau nguoi dung nhap ma PIN moi hai lan
 *
 * @return      true neu ma PIN moi duoc xac nhan, false neu nguoi dung huy
 * @attention   bBatBuoc = true nghia la nguoi dung khong the huy
 **********************************************************/
bool CDichVuUser::nhapPinMoi(const bool bBatBuoc, std::string& strPinMoi) const {
	const std::string strLoiNhac = bBatBuoc ? "  Nhap ma PIN moi (6 chu so): "
	                                        : "  Nhap ma PIN moi (6 chu so, 0 de huy): ";
	while (true) {
		const std::string strLanMot = CTienIch::nhapAn(strLoiNhac);
		if (!bBatBuoc && strLanMot == NHAP_HUY) {
			CTienIch::baoThongTin("Da huy doi ma PIN.");
			return false;
		}
		std::string strThongBao;
		if (!this->laPinMoiHopLe(strLanMot, strThongBao)) {
			CTienIch::baoLoi(strThongBao);
			continue;
		}
		const std::string strLanHai = CTienIch::nhapAn("  Nhap lai ma PIN moi: ");
		if (strLanMot != strLanHai) {
			CTienIch::baoLoi("Hai lan nhap khong khop. Vui long nhap lai.");
			continue;
		}
		strPinMoi = strLanMot;
		return true;
	}
}

/**********************************************************
 * @Description Hien thong tin tai khoan
 *
 * @return      Khong co
 **********************************************************/
void CDichVuUser::hienThongTinTaiKhoan() const {
	CTienIch::inKhung("THONG TIN TAI KHOAN");
	CTaiKhoan objTaiKhoan;
	if (!CKhoFile::docTaiKhoan(this->m_pThe->layMaSo(), objTaiKhoan)) {
		CTienIch::baoLoi("Khong doc duoc thong tin tai khoan.");
		return;
	}
	std::cout << "  So tai khoan : " << MAU_TRANG << objTaiKhoan.layMaSo() << MAU_RESET << "\n"
	          << "  Chu tai khoan: " << MAU_TRANG << objTaiKhoan.layTen() << MAU_RESET << "\n"
	          << "  So du        : " << MAU_XANH_LA << CTienIch::dinhDangTien(objTaiKhoan.laySoDu())
	          << " " << objTaiKhoan.layTienTe() << MAU_RESET << "\n";
}

/**********************************************************
 * @Description Rut tien tu tai khoan
 *
 * @return      Khong co
 * @attention   Hoi xac nhan, sau do ghi lich su
 **********************************************************/
void CDichVuUser::rutTien() const {
	CTienIch::inKhung("RUT TIEN");
	CTaiKhoan objTaiKhoan;
	if (!CKhoFile::docTaiKhoan(this->m_pThe->layMaSo(), objTaiKhoan)) {
		CTienIch::baoLoi("Khong doc duoc thong tin tai khoan.");
		return;
	}
	CDichVuUser::inSoDu(objTaiKhoan);
	const long long llSoTien = CDichVuUser::nhapSoTien(objTaiKhoan.laySoDu(),
	                                                   "  Nhap so tien can rut (0 de huy): ");
	if (llSoTien == 0) {
		CTienIch::baoThongTin("Da huy giao dich.");
		return;
	}
	const std::string strCauHoi = "  Xac nhan rut " + CTienIch::dinhDangTien(llSoTien)
	                              + " " + objTaiKhoan.layTienTe();
	if (!CTienIch::xacNhan(strCauHoi)) {
		CTienIch::baoThongTin("Da huy giao dich.");
		return;
	}
	objTaiKhoan.datSoDu(objTaiKhoan.laySoDu() - llSoTien);
	if (!CKhoFile::ghiTaiKhoan(objTaiKhoan)) {
		CTienIch::baoLoi("Loi ghi file. Giao dich bi huy.");
		return;
	}
	CKhoFile::themLichSu(objTaiKhoan.layMaSo(),
	                     CGiaoDich(LOAI_RUT, llSoTien, CTienIch::layThoiGianHienTai(), "Rut tien mat"));
	CTienIch::baoThanhCong("Rut tien thanh cong. So du con lai: "
	                       + CTienIch::dinhDangTien(objTaiKhoan.laySoDu()) + " " + objTaiKhoan.layTienTe());
}

/**********************************************************
 * @Description Chuyen tien sang tai khoan khac
 *
 * @return      Khong co
 * @attention   Hoi xac nhan, sau do ghi lich su cua ca hai tai khoan
 **********************************************************/
void CDichVuUser::chuyenTien() const {
	CTienIch::inKhung("CHUYEN TIEN");
	CTaiKhoan objNguoiGui;
	if (!CKhoFile::docTaiKhoan(this->m_pThe->layMaSo(), objNguoiGui)) {
		CTienIch::baoLoi("Khong doc duoc thong tin tai khoan.");
		return;
	}
	CDichVuUser::inSoDu(objNguoiGui);
	CTaiKhoan objNguoiNhan;
	if (!this->nhapNguoiNhan(objNguoiNhan)) {
		return;
	}
	std::cout << "  Nguoi nhan: " << MAU_TRANG << objNguoiNhan.layTen() << MAU_RESET << "\n";
	const long long llSoTien = CDichVuUser::nhapSoTien(objNguoiGui.laySoDu(),
	                                                   "  Nhap so tien can chuyen (0 de huy): ");
	if (llSoTien == 0) {
		CTienIch::baoThongTin("Da huy giao dich.");
		return;
	}
	const std::string strCauHoi = "  Xac nhan chuyen " + CTienIch::dinhDangTien(llSoTien) + " "
	                              + objNguoiGui.layTienTe() + " den " + objNguoiNhan.layTen()
	                              + " (" + objNguoiNhan.layMaSo() + ")";
	if (!CTienIch::xacNhan(strCauHoi)) {
		CTienIch::baoThongTin("Da huy giao dich.");
		return;
	}
	CDichVuUser::thucHienChuyenTien(objNguoiGui, objNguoiNhan, llSoTien);
}

/**********************************************************
 * @Description Hien tat ca giao dich, giao dich moi nhat o dau
 *
 * @return      Khong co
 * @attention   Ngan xep cho giao dich moi nhat ra truoc
 **********************************************************/
void CDichVuUser::hienLichSu() const {
	CTienIch::inKhung("LICH SU GIAO DICH");
	CNganXep<CGiaoDich> objNganXep;
	int iSoLuong = 0;
	if (!CKhoFile::docLichSu(this->m_pThe->layMaSo(), objNganXep, iSoLuong)) {
		CTienIch::baoLoi("Khong doc duoc file lich su giao dich.");
		return;
	}
	if (iSoLuong == 0) {
		CTienIch::baoThongTin("Chua co giao dich nao.");
		return;
	}
	std::cout << MAU_XANH_NGOC << std::left << std::setw(DO_RONG_COT_THOI_GIAN) << "Thoi gian"
	          << std::setw(DO_RONG_COT_LOAI) << "Loai" << std::setw(DO_RONG_COT_SO_TIEN) << "So tien"
	          << "Noi dung" << MAU_RESET << "\n";
	CGiaoDich objGiaoDich;
	while (objNganXep.layRa(objGiaoDich)) {
		CDichVuUser::inDongGiaoDich(objGiaoDich);
	}
	std::cout << "\n  Tong so giao dich: " << iSoLuong << "\n";
}

/**********************************************************
 * @Description Tao doi tuong chuc nang user cho the dang dang nhap
 *
 * @return      Khong co
 **********************************************************/
CDichVuUser::CDichVuUser(CDanhSachThe& objDanhSachThe, CTheTu* pThe)
	: m_objDanhSachThe(objDanhSachThe), m_pThe(pThe) {
}

/**********************************************************
 * @Description Doi ma PIN cua the
 *
 * @return      true neu da doi PIN
 * @attention   bBatBuoc = true dung o lan dang nhap dau (khong the huy)
 **********************************************************/
bool CDichVuUser::doiPin(const bool bBatBuoc) {
	CTienIch::inKhung("DOI MA PIN");
	if (bBatBuoc) {
		CTienIch::baoThongTin("Day la lan dang nhap dau tien. Ban phai doi ma PIN mac dinh.");
	} else if (!this->xacThucPinHienTai()) {
		return false;
	}
	std::string strPinMoi;
	if (!this->nhapPinMoi(bBatBuoc, strPinMoi)) {
		return false;
	}
	const std::string strPinCu = this->m_pThe->layPin();
	this->m_pThe->datPin(strPinMoi);
	if (!this->m_objDanhSachThe.ghiRaFile()) {
		this->m_pThe->datPin(strPinCu);
		CTienIch::baoLoi("Khong ghi duoc TheTu.txt. Doi ma PIN that bai.");
		return false;
	}
	CTienIch::baoThanhCong("Doi ma PIN thanh cong.");
	return true;
}

/**********************************************************
 * @Description Hien menu user va chay chuc nang duoc chon
 *
 * @return      Khong co
 * @attention   Ket thuc khi nguoi dung chon Thoat
 **********************************************************/
void CDichVuUser::chay() {
	std::vector<std::string> vecCacMuc;
	vecCacMuc.push_back("Xem thong tin tai khoan");
	vecCacMuc.push_back("Rut tien");
	vecCacMuc.push_back("Chuyen tien");
	vecCacMuc.push_back("Xem noi dung giao dich");
	vecCacMuc.push_back("Doi ma Pin");
	vecCacMuc.push_back("Thoat");
	while (true) {
		CTienIch::xoaManHinh();
		CTienIch::inMenu("MENU", vecCacMuc);
		const int iLuaChon = CTienIch::nhapLuaChonMenu("  Chon chuc nang: ");
		CTienIch::xoaManHinh();
		switch (iLuaChon) {
		case USER_XEM_THONG_TIN:
			this->hienThongTinTaiKhoan();
			break;
		case USER_RUT_TIEN:
			this->rutTien();
			break;
		case USER_CHUYEN_TIEN:
			this->chuyenTien();
			break;
		case USER_XEM_LICH_SU:
			this->hienLichSu();
			break;
		case USER_DOI_PIN:
			this->doiPin(false);
			break;
		case USER_THOAT:
			return;
		default:
			CTienIch::baoLoi("Lua chon khong hop le.");
			break;
		}
		CTienIch::tamDung();
	}
}
