#include "MayATM.h"

#include <iostream>
#include <string>
#include <vector>

#include "DichVuAdmin.h"
#include "HangSo.h"
#include "KhoFile.h"
#include "DichVuUser.h"
#include "TienIch.h"

// ---------------------------- Cac lua chon menu ---------------------------
enum LuaChonMenuChinh {
	CHINH_DANG_NHAP_ADMIN = 1,
	CHINH_DANG_NHAP_USER,
	CHINH_THOAT
};

/**********************************************************
 * @Description Yeu cau nhap PIN, nguoi dung co 3 lan thu
 *
 * @return      true neu ma PIN dung
 **********************************************************/
bool CMayATM::xacThucPin(const CTheTu* pThe) {
	for (int iLanThu = 1; iLanThu <= SO_LAN_THU_TOI_DA; iLanThu++) {
		if (CTienIch::nhapAn("  Pin: ") == pThe->layPin()) {
			return true;
		}
		if (iLanThu < SO_LAN_THU_TOI_DA) {
			CTienIch::baoLoi("Sai ma PIN. Con " + std::to_string(SO_LAN_THU_TOI_DA - iLanThu) + " lan thu.");
		}
	}
	return false;
}

/**********************************************************
 * @Description Yeu cau nhap ID the, nguoi dung co 3 lan thu
 *
 * @return      Con tro toi the
 * @attention   Tra ve nullptr neu nhap sai ca 3 lan
 **********************************************************/
CTheTu* CMayATM::nhapThe() const {
	for (int iLanThu = 1; iLanThu <= SO_LAN_THU_TOI_DA; iLanThu++) {
		CTheTu* pThe = this->m_objDanhSachThe.tim(CTienIch::nhapDong("  ID: "));
		if (pThe != nullptr) {
			return pThe;
		}
		CTienIch::baoLoi("ID khong ton tai. Con " + std::to_string(SO_LAN_THU_TOI_DA - iLanThu) + " lan thu.");
	}
	return nullptr;
}

/**********************************************************
 * @Description Dang nhap user: nhap ID roi nhap PIN
 *
 * @return      Con tro toi the da dang nhap
 * @attention   Tra ve nullptr neu dang nhap that bai
 *              bThoat = true nghia la chuong trinh phai thoat
 *              (sai ID 3 lan, hoac sai PIN 3 lan va the bi khoa)
 **********************************************************/
CTheTu* CMayATM::dangNhapUser(bool& bThoat) {
	bThoat = false;
	CTienIch::inKhung("DANG NHAP USER");
	CTheTu* pThe = this->nhapThe();
	if (pThe == nullptr) {
		bThoat = true;
		CTienIch::baoLoi("Nhap sai qua 3 lan. Thoat he thong.");
		return nullptr;
	}
	if (pThe->biKhoa()) {
		CTienIch::baoLoi("Tai khoan da bi khoa. Vui long lien he Admin de mo khoa.");
		return nullptr;
	}
	CTaiKhoan objTaiKhoan;
	if (!CKhoFile::docTaiKhoan(pThe->layMaSo(), objTaiKhoan)) {
		CTienIch::baoLoi("Thong tin tai khoan khong ton tai trong he thong.");
		return nullptr;
	}
	if (!CMayATM::xacThucPin(pThe)) {
		pThe->datKhoa(true);
		this->m_objDanhSachThe.ghiRaFile();
		bThoat = true;
		CTienIch::baoLoi("Nhap sai PIN 3 lan. Tai khoan da bi khoa va he thong se thoat.");
		return nullptr;
	}
	return pThe;
}

/**********************************************************
 * @Description Dang nhap user, bat buoc doi PIN o lan dang nhap dau,
 *              sau do hien menu user
 *
 * @return      true neu chuong trinh phai thoat
 **********************************************************/
bool CMayATM::xuLyUser() {
	bool bThoat = false;
	CTheTu* pThe = this->dangNhapUser(bThoat);
	if (bThoat) {
		return true;
	}
	if (pThe == nullptr) {
		CTienIch::tamDung();
		return false;
	}
	CDichVuUser objUser(this->m_objDanhSachThe, pThe);
	if (pThe->layPin() == PIN_MAC_DINH) {
		CTienIch::xoaManHinh();
		const bool bDaDoi = objUser.doiPin(true);
		CTienIch::tamDung();
		if (!bDaDoi) {
			return false;
		}
	}
	objUser.chay();
	return false;
}

/**********************************************************
 * @Description Dang nhap admin, sau do hien menu admin
 *
 * @return      Khong co
 **********************************************************/
void CMayATM::xuLyAdmin() {
	CDichVuAdmin objAdmin(this->m_objDanhSachThe);
	if (!objAdmin.dangNhap()) {
		CTienIch::baoLoi("Dang nhap Admin that bai.");
		CTienIch::tamDung();
		return;
	}
	objAdmin.chay();
}

/**********************************************************
 * @Description Chay chuong trinh ATM cho den khi nguoi dung chon Thoat
 *
 * @return      Khong co
 **********************************************************/
void CMayATM::chay() {
	CTienIch::batMau();
	this->m_objDanhSachThe.docTuFile();
	std::vector<std::string> vecCacMuc;
	vecCacMuc.push_back("Dang nhap Admin");
	vecCacMuc.push_back("Dang nhap User");
	vecCacMuc.push_back("Thoat chuong trinh");
	while (true) {
		CTienIch::xoaManHinh();
		CTienIch::inMenu("MAY ATM", vecCacMuc);
		const int iLuaChon = CTienIch::nhapLuaChonMenu("  Chon: ");
		CTienIch::xoaManHinh();
		switch (iLuaChon) {
		case CHINH_DANG_NHAP_ADMIN:
			this->xuLyAdmin();
			break;
		case CHINH_DANG_NHAP_USER:
			if (this->xuLyUser()) {
				return;
			}
			break;
		case CHINH_THOAT:
			std::cout << MAU_XANH_NGOC << "\n  Cam on ban da su dung dich vu ATM. Tam biet!\n" << MAU_RESET;
			return;
		default:
			CTienIch::baoLoi("Lua chon khong hop le.");
			CTienIch::tamDung();
			break;
		}
	}
}
