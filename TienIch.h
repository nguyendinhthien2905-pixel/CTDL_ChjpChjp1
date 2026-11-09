#ifndef TIENICH_H_INCLUDED_
#define TIENICH_H_INCLUDED_

#include <string>
#include <vector>

class CTienIch {
private:
	static void xuLyPhimNhapAn(const int iPhim, std::string& strNhap);
	static bool chiGomChuSo(const std::string& strChuoi);

public:
	static void batMau();
	static void xoaManHinh();
	static std::string catKhoangTrang(const std::string& strChuoi);

	static void baoLoi(const std::string& strThongBao);
	static void baoThanhCong(const std::string& strThongBao);
	static void baoThongTin(const std::string& strThongBao);

	static std::string nhapDong(const std::string& strLoiNhac);
	static std::string nhapAn(const std::string& strLoiNhac);
	static int nhapLuaChonMenu(const std::string& strLoiNhac);
	static void tamDung();

	static bool laChuoiSo(const std::string& strChuoi, const int iDoDai);
	static bool docSoTien(const std::string& strChuoi, long long& llKetQua);
	static std::string dinhDangTien(const long long llSoTien);
	static std::string layThoiGianHienTai();
	static bool xacNhan(const std::string& strCauHoi);

	static void inKhung(const std::string& strTieuDe);
	static void inMenu(const std::string& strTieuDe, const std::vector<std::string>& vecCacMuc);
};

#endif
