#include "DichVuAdmin.h"

#include <iomanip>
#include <iostream>
#include <vector>

#include "HangSo.h"
#include "KhoFile.h"
#include "TienIch.h"

const std::string TIEN_TE_MAC_DINH = "VND";

enum LuaChonMenuAdmin {
	ADMIN_XEM_DANH_SACH = 1,
	ADMIN_THEM_TAI_KHOAN,
	ADMIN_XOA_TAI_KHOAN,
	ADMIN_MO_KHOA,
	ADMIN_THOAT
};

/**********************************************************
 * @Description In mot dong cua bang danh sach tai khoan
 *
 * @return      Khong co
 **********************************************************/
void CDichVuAdmin::inDongThe(const int iThuTu, const CTheTu& objThe) {
	const char* pMauTrangThai = objThe.biKhoa() ? MAU_DO : MAU_XANH_LA;
	const char* pChuTrangThai = objThe.biKhoa() ? "Bi khoa" : "Hoat dong";
	std::cout << std::left << std::setw(DO_RONG_COT_SO_THU_TU) << iThuTu
	          << std::setw(DO_RONG_COT_MA_SO) << objThe.layMaSo()
	          << std::setw(DO_RONG_COT_PIN) << "******"
	          << pMauTrangThai << pChuTrangThai << MAU_RESET << "\n";
}

/**********************************************************
 * @Description In tat ca the, sap xep theo ID
 *
 * @return      Khong co
 **********************************************************/
void CDichVuAdmin::hienDanhSachTaiKhoan() {
	CTienIch::inKhung("DANH SACH TAI KHOAN");
	if (this->m_objDanhSachThe.laySoLuong() == 0) {
		CTienIch::baoThongTin("Danh sach trong.");
		return;
	}
	this->m_objDanhSachThe.sapXepTheoMaSo();
	std::cout << MAU_XANH_NGOC << std::left << std::setw(DO_RONG_COT_SO_THU_TU) << "STT"
	          << std::setw(DO_RONG_COT_MA_SO) << "Ma so tai khoan"
	          << std::setw(DO_RONG_COT_PIN) << "Ma PIN" << "Trang thai" << MAU_RESET << "\n";
	int iThuTu = 0;
	for (CNut<CTheTu>* pNut = this->m_objDanhSachThe.layDau(); pNut != nullptr; pNut = pNut->layTiep()) {
		iThuTu++;
		CDichVuAdmin::inDongThe(iThuTu, pNut->layDuLieu());
	}
	std::cout << "\n  Tong so: " << this->m_objDanhSachThe.laySoLuong() << " the.\n";
}

/**********************************************************
 * @Description Kiem tra ID cua tai khoan moi
 *
 * @return      true neu ID gom 14 chu so va chua ton tai
 * @attention   In ly do khi ID khong hop le
 **********************************************************/
bool CDichVuAdmin::laMaSoMoiHopLe(const std::string& strMaSo) const {
	if (!CTienIch::laChuoiSo(strMaSo, DO_DAI_MA_SO)) {
		CTienIch::baoLoi("ID phai gom dung 14 chu so.");
		return false;
	}
	if (this->m_objDanhSachThe.tim(strMaSo) != nullptr) {
		CTienIch::baoLoi("ID da ton tai.");
		return false;
	}
	return true;
}

/**********************************************************
 * @Description Luu tai khoan moi vao bo nho va vao file
 *
 * @return      Khong co
 * @attention   Hoan lai tat ca neu mot file khong ghi duoc
 **********************************************************/
void CDichVuAdmin::luuTaiKhoanMoi(const CTaiKhoan& objTaiKhoan) {
	const std::string strMaSo = objTaiKhoan.layMaSo();
	this->m_objDanhSachThe.them(CTheTu(strMaSo, PIN_MAC_DINH, false));
	const bool bDaLuu = CKhoFile::ghiTaiKhoan(objTaiKhoan)
	                    && CKhoFile::taoLichSuRong(strMaSo)
	                    && this->m_objDanhSachThe.ghiRaFile();
	if (bDaLuu) {
		CTienIch::baoThanhCong("Them thanh cong. Ma PIN mac dinh: " + PIN_MAC_DINH);
		return;
	}
	this->m_objDanhSachThe.xoa(strMaSo);
	this->m_objDanhSachThe.ghiRaFile();
	CKhoFile::xoaFileTaiKhoan(strMaSo);
	CTienIch::baoLoi("Khong ghi duoc du lieu. Da huy them tai khoan.");
}

/**********************************************************
 * @Description Yeu cau admin nhap thong tin tai khoan moi
 *
 * @return      Khong co
 **********************************************************/
void CDichVuAdmin::themTaiKhoan() {
	CTienIch::inKhung("THEM TAI KHOAN");
	const std::string strMaSo = CTienIch::nhapDong("  Nhap ID moi (14 chu so): ");
	if (!this->laMaSoMoiHopLe(strMaSo)) {
		return;
	}
	const std::string strTen = CTienIch::nhapDong("  Ten tai khoan: ");
	if (strTen.empty()) {
		CTienIch::baoLoi("Ten khong duoc de trong.");
		return;
	}
	long long llSoDu = 0;
	if (!CTienIch::docSoTien(CTienIch::nhapDong("  So du ban dau: "), llSoDu)) {
		CTienIch::baoLoi("So du khong hop le.");
		return;
	}
	std::string strTienTe = CTienIch::nhapDong("  Loai tien te (Enter = VND): ");
	if (strTienTe.empty()) {
		strTienTe = TIEN_TE_MAC_DINH;
	}
	this->luuTaiKhoanMoi(CTaiKhoan(strMaSo, strTen, llSoDu, strTienTe));
}

/**********************************************************
 * @Description Xoa tai khoan va cac file cua no
 *
 * @return      Khong co
 * @attention   Hoi xac nhan truoc khi xoa
 **********************************************************/
void CDichVuAdmin::xoaTaiKhoan() {
	CTienIch::inKhung("XOA TAI KHOAN");
	const std::string strMaSo = CTienIch::nhapDong("  Nhap ID can xoa: ");
	if (this->m_objDanhSachThe.tim(strMaSo) == nullptr) {
		CTienIch::baoLoi("Khong tim thay ID.");
		return;
	}
	if (!CTienIch::xacNhan("  Ban chac chan muon xoa tai khoan " + strMaSo)) {
		CTienIch::baoThongTin("Da huy.");
		return;
	}
	this->m_objDanhSachThe.xoa(strMaSo);
	if (!this->m_objDanhSachThe.ghiRaFile()) {
		this->m_objDanhSachThe.docTuFile();        // khoi phuc du lieu cu tu file
		CTienIch::baoLoi("Khong ghi duoc TheTu.txt. Da huy xoa.");
		return;
	}
	CKhoFile::xoaFileTaiKhoan(strMaSo);
	CTienIch::baoThanhCong("Da xoa tai khoan " + strMaSo + " va cac file lien quan.");
}

/**********************************************************
 * @Description In ID cua tat ca the dang bi khoa
 *
 * @return      So the dang bi khoa
 **********************************************************/
int CDichVuAdmin::inTheBiKhoa() const {
	int iSoTheBiKhoa = 0;
	for (CNut<CTheTu>* pNut = this->m_objDanhSachThe.layDau(); pNut != nullptr; pNut = pNut->layTiep()) {
		if (pNut->layDuLieu().biKhoa()) {
			std::cout << "   - " << pNut->layDuLieu().layMaSo() << "\n";
			iSoTheBiKhoa++;
		}
	}
	return iSoTheBiKhoa;
}

/**********************************************************
 * @Description Mo khoa the da bi khoa do nhap sai PIN
 *
 * @return      Khong co
 **********************************************************/
void CDichVuAdmin::moKhoaTaiKhoan() {
	CTienIch::inKhung("MO KHOA TAI KHOAN");
	if (this->inTheBiKhoa() == 0) {
		CTienIch::baoThongTin("Khong co tai khoan nao bi khoa.");
		return;
	}
	const std::string strMaSo = CTienIch::nhapDong("\n  Nhap ID can mo khoa: ");
	CTheTu* pThe = this->m_objDanhSachThe.tim(strMaSo);
	if (pThe == nullptr) {
		CTienIch::baoLoi("Khong tim thay ID.");
		return;
	}
	if (!pThe->biKhoa()) {
		CTienIch::baoThongTin("Tai khoan nay khong bi khoa.");
		return;
	}
	pThe->datKhoa(false);
	if (!this->m_objDanhSachThe.ghiRaFile()) {
		pThe->datKhoa(true);
		CTienIch::baoLoi("Khong ghi duoc TheTu.txt. Mo khoa that bai.");
		return;
	}
	CTienIch::baoThanhCong("Da mo khoa tai khoan " + strMaSo);
}

/**********************************************************
 * @Description Tao doi tuong chuc nang admin lam viec tren danh sach the
 *
 * @return      Khong co
 **********************************************************/
CDichVuAdmin::CDichVuAdmin(CDanhSachThe& objDanhSachThe)
	: m_objDanhSachThe(objDanhSachThe) {
}

/**********************************************************
 * @Description Dang nhap admin, co 3 lan thu
 *
 * @return      true neu user va mat khau dung
 **********************************************************/
bool CDichVuAdmin::dangNhap() const {
	CTienIch::inKhung("DANG NHAP ADMIN");
	for (int iLanThu = 1; iLanThu <= SO_LAN_THU_TOI_DA; iLanThu++) {
		const std::string strUser = CTienIch::nhapDong("  User: ");
		const std::string strMatKhau = CTienIch::nhapAn("  Pin: ");
		if (CKhoFile::laAdminHopLe(strUser, strMatKhau)) {
			return true;
		}
		CTienIch::baoLoi("Sai user hoac mat khau. Con "
		                 + std::to_string(SO_LAN_THU_TOI_DA - iLanThu) + " lan thu.");
	}
	return false;
}

/**********************************************************
 * @Description Hien menu admin va chay chuc nang duoc chon
 *
 * @return      Khong co
 * @attention   Ket thuc khi admin chon Thoat
 **********************************************************/
void CDichVuAdmin::chay() {
	std::vector<std::string> vecCacMuc;
	vecCacMuc.push_back("Xem danh sach tai khoan");
	vecCacMuc.push_back("Them tai khoan");
	vecCacMuc.push_back("Xoa tai khoan");
	vecCacMuc.push_back("Mo khoa tai khoan");
	vecCacMuc.push_back("Thoat");
	while (true) {
		CTienIch::xoaManHinh();
		CTienIch::inMenu("MENU ADMIN", vecCacMuc);
		const int iLuaChon = CTienIch::nhapLuaChonMenu("  Chon chuc nang: ");
		CTienIch::xoaManHinh();
		switch (iLuaChon) {
		case ADMIN_XEM_DANH_SACH:
			this->hienDanhSachTaiKhoan();
			break;
		case ADMIN_THEM_TAI_KHOAN:
			this->themTaiKhoan();
			break;
		case ADMIN_XOA_TAI_KHOAN:
			this->xoaTaiKhoan();
			break;
		case ADMIN_MO_KHOA:
			this->moKhoaTaiKhoan();
			break;
		case ADMIN_THOAT:
			return;
		default:
			CTienIch::baoLoi("Lua chon khong hop le.");
			break;
		}
		CTienIch::tamDung();
	}
}
