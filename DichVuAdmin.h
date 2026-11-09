#ifndef DICHVUADMIN_H_INCLUDED_
#define DICHVUADMIN_H_INCLUDED_

#include <string>

#include "TaiKhoan.h"
#include "TheTu.h"
#include "DanhSachThe.h"

class CDichVuAdmin {
private:
	CDanhSachThe& m_objDanhSachThe;

	static void inDongThe(const int iThuTu, const CTheTu& objThe);
	void hienDanhSachTaiKhoan();
	bool laMaSoMoiHopLe(const std::string& strMaSo) const;
	void luuTaiKhoanMoi(const CTaiKhoan& objTaiKhoan);
	void themTaiKhoan();
	void xoaTaiKhoan();
	int inTheBiKhoa() const;
	void moKhoaTaiKhoan();

public:
	explicit CDichVuAdmin(CDanhSachThe& objDanhSachThe);

	bool dangNhap() const;
	void chay();
};

#endif
