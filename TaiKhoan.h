#ifndef TAIKHOAN_H_INCLUDED_
#define TAIKHOAN_H_INCLUDED_

#include <string>

class CTaiKhoan {
private:
	std::string m_strMaSo;
	std::string m_strTen;
	long long m_llSoDu;
	std::string m_strTienTe;

public:
	CTaiKhoan();
	CTaiKhoan(const std::string& strMaSo, const std::string& strTen,
	          const long long llSoDu, const std::string& strTienTe);

	const std::string& layMaSo() const;
	const std::string& layTen() const;
	long long laySoDu() const;
	const std::string& layTienTe() const;

	void datSoDu(const long long llSoDu);
};

#endif
