#ifndef DICHVUUSER_H_INCLUDED_
#define DICHVUUSER_H_INCLUDED_

#include <string>

#include "TaiKhoan.h"
#include "TheTu.h"
#include "DanhSachThe.h"
#include "GiaoDich.h"

class CDichVuUser {
private:
	CDanhSachThe& m_objDanhSachThe;
	CTheTu* m_pThe;                 // the cua user dang dang nhap

	static bool laSoTienHopLe(const long long llSoTien, const long long llSoDu, std::string& strThongBao);
	static long long nhapSoTien(const long long llSoDu, const std::string& strLoiNhac);
	static void inSoDu(const CTaiKhoan& objTaiKhoan);
	static void inDongGiaoDich(const CGiaoDich& objGiaoDich);
	static void thucHienChuyenTien(CTaiKhoan& objNguoiGui, CTaiKhoan& objNguoiNhan, const long long llSoTien);

	bool nhapNguoiNhan(CTaiKhoan& objNguoiNhan) const;
	bool xacThucPinHienTai() const;
	bool laPinMoiHopLe(const std::string& strPin, std::string& strThongBao) const;
	bool nhapPinMoi(const bool bBatBuoc, std::string& strPinMoi) const;

	void hienThongTinTaiKhoan() const;
	void rutTien() const;
	void chuyenTien() const;
	void hienLichSu() const;

public:
	CDichVuUser(CDanhSachThe& objDanhSachThe, CTheTu* pThe);

	bool doiPin(const bool bBatBuoc);
	void chay();
};

#endif
