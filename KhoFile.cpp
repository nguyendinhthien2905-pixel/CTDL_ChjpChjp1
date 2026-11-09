#include "KhoFile.h"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <vector>

#include "TienIch.h"

const std::string FILE_ADMIN = "Admin.txt";
const std::string THU_MUC_TAI_KHOAN = "ThanhVien";
const std::string THU_MUC_LICH_SU = "LichSu";
const char KY_TU_NGAN_CACH = '|';

// Vi tri cua tung truong trong mot dong cua file lich su
enum TruongLichSu {
	TRUONG_LICH_SU_MA_SO = 0,
	TRUONG_LICH_SU_LOAI,
	TRUONG_LICH_SU_SO_TIEN,
	TRUONG_LICH_SU_THOI_GIAN,
	TRUONG_LICH_SU_NOI_DUNG,
	TRUONG_LICH_SU_SO_LUONG
};

/**********************************************************
 * @Description Tach mot dong lich su va tao giao dich
 *
 * @return      true neu dong co du cac truong
 **********************************************************/
bool CKhoFile::phanTichDongLichSu(const std::string& strDong, CGiaoDich& objGiaoDich) {
	std::vector<std::string> vecCacTruong;
	std::string strTruong;
	std::istringstream objLuongChuoi(strDong);
	while (std::getline(objLuongChuoi, strTruong, KY_TU_NGAN_CACH)) {
		vecCacTruong.push_back(strTruong);
	}
	if (static_cast<int>(vecCacTruong.size()) < TRUONG_LICH_SU_SO_LUONG) {
		return false;
	}
	long long llSoTien = 0;
	CTienIch::docSoTien(vecCacTruong[TRUONG_LICH_SU_SO_TIEN], llSoTien);
	objGiaoDich = CGiaoDich(vecCacTruong[TRUONG_LICH_SU_LOAI], llSoTien,
	                        vecCacTruong[TRUONG_LICH_SU_THOI_GIAN], vecCacTruong[TRUONG_LICH_SU_NOI_DUNG]);
	return true;
}

/**********************************************************
 * @Description Lay duong dan file TheTu.txt
 *
 * @return      Duong dan file
 **********************************************************/
std::string CKhoFile::layDuongDanTheTu() {
	return THU_MUC_TAI_KHOAN + "/TheTu.txt";
}

/**********************************************************
 * @Description Lay duong dan file tai khoan [ID].txt
 *
 * @return      Duong dan file
 **********************************************************/
std::string CKhoFile::layDuongDanTaiKhoan(const std::string& strMaSo) {
	return THU_MUC_TAI_KHOAN + "/" + strMaSo + ".txt";
}

/**********************************************************
 * @Description Lay duong dan file lich su LichSu[ID].txt
 *
 * @return      Duong dan file
 **********************************************************/
std::string CKhoFile::layDuongDanLichSu(const std::string& strMaSo) {
	return THU_MUC_LICH_SU + "/LichSu" + strMaSo + ".txt";
}

/**********************************************************
 * @Description Kiem tra user va mat khau trong Admin.txt
 *
 * @return      true neu cap user/mat khau co trong file
 **********************************************************/
bool CKhoFile::laAdminHopLe(const std::string& strUser, const std::string& strMatKhau) {
	std::ifstream objFile(FILE_ADMIN.c_str());
	bool bTimThay = false;
	std::string strDong;
	while (!bTimThay && std::getline(objFile, strDong)) {
		std::istringstream objLuongChuoi(strDong);
		std::string strUserTrongFile;
		std::string strMatKhauTrongFile;
		const bool bDocDuoc = static_cast<bool>(objLuongChuoi >> strUserTrongFile >> strMatKhauTrongFile);
		bTimThay = bDocDuoc && strUserTrongFile == strUser && strMatKhauTrongFile == strMatKhau;
	}
	objFile.close();
	return bTimThay;
}

/**********************************************************
 * @Description Doc file tai khoan [ID].txt (4 dong:
 *              ID, ten, so du, loai tien)
 *
 * @return      true neu doc file thanh cong
 * @attention   objTaiKhoan chi bi thay doi khi file hop le
 **********************************************************/
bool CKhoFile::docTaiKhoan(const std::string& strMaSo, CTaiKhoan& objTaiKhoan) {
	std::ifstream objFile(CKhoFile::layDuongDanTaiKhoan(strMaSo).c_str());
	bool bThanhCong = objFile.is_open();
	if (bThanhCong) {
		std::string strMaSoTrongFile;
		std::string strTen;
		std::string strSoDu;
		std::string strTienTe;
		std::getline(objFile, strMaSoTrongFile);
		std::getline(objFile, strTen);
		std::getline(objFile, strSoDu);
		std::getline(objFile, strTienTe);
		strMaSoTrongFile = CTienIch::catKhoangTrang(strMaSoTrongFile);
		long long llSoDu = 0;
		bThanhCong = !strMaSoTrongFile.empty() && CTienIch::docSoTien(CTienIch::catKhoangTrang(strSoDu), llSoDu);
		if (bThanhCong) {
			objTaiKhoan = CTaiKhoan(strMaSoTrongFile, CTienIch::catKhoangTrang(strTen), llSoDu, CTienIch::catKhoangTrang(strTienTe));
		}
	}
	objFile.close();
	return bThanhCong;
}

/**********************************************************
 * @Description Ghi file tai khoan [ID].txt
 *
 * @return      true neu ghi file thanh cong
 **********************************************************/
bool CKhoFile::ghiTaiKhoan(const CTaiKhoan& objTaiKhoan) {
	std::ofstream objFile(CKhoFile::layDuongDanTaiKhoan(objTaiKhoan.layMaSo()).c_str());
	bool bThanhCong = objFile.is_open();
	if (bThanhCong) {
		objFile << objTaiKhoan.layMaSo() << "\n" << objTaiKhoan.layTen() << "\n"
		        << objTaiKhoan.laySoDu() << "\n" << objTaiKhoan.layTienTe() << "\n";
		bThanhCong = static_cast<bool>(objFile);
	}
	objFile.close();
	return bThanhCong;
}

/**********************************************************
 * @Description Tao file lich su rong cho tai khoan moi
 *
 * @return      true neu tao file thanh cong
 **********************************************************/
bool CKhoFile::taoLichSuRong(const std::string& strMaSo) {
	std::ofstream objFile(CKhoFile::layDuongDanLichSu(strMaSo).c_str());
	const bool bThanhCong = objFile.is_open();
	objFile.close();
	return bThanhCong;
}

/**********************************************************
 * @Description Them mot dong vao cuoi file lich su
 *              Dinh dang: ID|loai|so tien|thoi gian|noi dung
 *
 * @return      true neu ghi dong thanh cong
 **********************************************************/
bool CKhoFile::themLichSu(const std::string& strMaSo, const CGiaoDich& objGiaoDich) {
	std::ofstream objFile(CKhoFile::layDuongDanLichSu(strMaSo).c_str(), std::ios::app);
	bool bThanhCong = objFile.is_open();
	if (bThanhCong) {
		objFile << strMaSo << KY_TU_NGAN_CACH << objGiaoDich.layLoai()
		        << KY_TU_NGAN_CACH << objGiaoDich.laySoTien()
		        << KY_TU_NGAN_CACH << objGiaoDich.layThoiGian()
		        << KY_TU_NGAN_CACH << objGiaoDich.layNoiDung() << "\n";
		bThanhCong = static_cast<bool>(objFile);
	}
	objFile.close();
	return bThanhCong;
}

/**********************************************************
 * @Description Doc file lich su va day tung giao dich
 *              vao ngan xep (giao dich moi nhat nam tren cung)
 *
 * @return      true neu mo duoc file
 * @attention   iSoLuong nhan so giao dich da doc
 **********************************************************/
bool CKhoFile::docLichSu(const std::string& strMaSo, CNganXep<CGiaoDich>& objNganXep, int& iSoLuong) {
	std::ifstream objFile(CKhoFile::layDuongDanLichSu(strMaSo).c_str());
	const bool bThanhCong = objFile.is_open();
	iSoLuong = 0;
	std::string strDong;
	while (bThanhCong && std::getline(objFile, strDong)) {
		CGiaoDich objGiaoDich;
		if (CKhoFile::phanTichDongLichSu(strDong, objGiaoDich)) {
			objNganXep.dayVao(objGiaoDich);
			iSoLuong++;
		}
	}
	objFile.close();
	return bThanhCong;
}

/**********************************************************
 * @Description Xoa file tai khoan va file lich su
 *
 * @return      Khong co
 **********************************************************/
void CKhoFile::xoaFileTaiKhoan(const std::string& strMaSo) {
	std::remove(CKhoFile::layDuongDanTaiKhoan(strMaSo).c_str());
	std::remove(CKhoFile::layDuongDanLichSu(strMaSo).c_str());
}
