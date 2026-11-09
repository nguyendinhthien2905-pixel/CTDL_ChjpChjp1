#ifndef KHOFILE_H_INCLUDED_
#define KHOFILE_H_INCLUDED_

#include <string>

#include "TaiKhoan.h"
#include "NganXep.h"
#include "GiaoDich.h"

class CKhoFile {
private:
	static bool phanTichDongLichSu(const std::string& strDong, CGiaoDich& objGiaoDich);

public:
	static std::string layDuongDanTheTu();
	static std::string layDuongDanTaiKhoan(const std::string& strMaSo);
	static std::string layDuongDanLichSu(const std::string& strMaSo);

	static bool laAdminHopLe(const std::string& strUser, const std::string& strMatKhau);

	static bool docTaiKhoan(const std::string& strMaSo, CTaiKhoan& objTaiKhoan);
	static bool ghiTaiKhoan(const CTaiKhoan& objTaiKhoan);

	static bool taoLichSuRong(const std::string& strMaSo);
	static bool themLichSu(const std::string& strMaSo, const CGiaoDich& objGiaoDich);
	static bool docLichSu(const std::string& strMaSo, CNganXep<CGiaoDich>& objNganXep, int& iSoLuong);

	static void xoaFileTaiKhoan(const std::string& strMaSo);
};

#endif
