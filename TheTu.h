#ifndef THETU_H_INCLUDED_
#define THETU_H_INCLUDED_

#include <string>

class CTheTu {
private:
	std::string m_strMaSo;
	std::string m_strPin;
	bool m_bBiKhoa;

public:
	CTheTu();
	CTheTu(const std::string& strMaSo, const std::string& strPin, const bool bBiKhoa);

	const std::string& layMaSo() const;
	const std::string& layPin() const;
	bool biKhoa() const;

	void datPin(const std::string& strPin);
	void datKhoa(const bool bBiKhoa);
};

#endif
