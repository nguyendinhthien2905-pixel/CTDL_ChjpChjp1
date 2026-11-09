#ifndef GIAODICH_H_INCLUDED_
#define GIAODICH_H_INCLUDED_

#include <string>

class CGiaoDich {
private:
	std::string m_strLoai;          // LOAI_RUT, LOAI_CHUYEN hoac LOAI_NHAN
	long long m_llSoTien;
	std::string m_strThoiGian;
	std::string m_strNoiDung;

public:
	CGiaoDich();
	CGiaoDich(const std::string& strLoai, const long long llSoTien,
	          const std::string& strThoiGian, const std::string& strNoiDung);

	const std::string& layLoai() const;
	long long laySoTien() const;
	const std::string& layThoiGian() const;
	const std::string& layNoiDung() const;
};

#endif
