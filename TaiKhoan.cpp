#include "TaiKhoan.h"

/**********************************************************
 * @Description Tao tai khoan rong
 *
 * @return      Khong co
 **********************************************************/
CTaiKhoan::CTaiKhoan()
	: m_llSoDu(0) {
}

/**********************************************************
 * @Description Tao tai khoan voi day du thong tin
 *
 * @return      Khong co
 **********************************************************/
CTaiKhoan::CTaiKhoan(const std::string& strMaSo, const std::string& strTen,
                     const long long llSoDu, const std::string& strTienTe)
	: m_strMaSo(strMaSo), m_strTen(strTen), m_llSoDu(llSoDu), m_strTienTe(strTienTe) {
}

/**********************************************************
 * @Description Lay ma so tai khoan
 *
 * @return      Ma so tai khoan
 **********************************************************/
const std::string& CTaiKhoan::layMaSo() const {
	return this->m_strMaSo;
}

/**********************************************************
 * @Description Lay ten chu tai khoan
 *
 * @return      Ten chu tai khoan
 **********************************************************/
const std::string& CTaiKhoan::layTen() const {
	return this->m_strTen;
}

/**********************************************************
 * @Description Lay so du hien tai
 *
 * @return      So du cua tai khoan
 **********************************************************/
long long CTaiKhoan::laySoDu() const {
	return this->m_llSoDu;
}

/**********************************************************
 * @Description Lay loai tien te
 *
 * @return      Loai tien te, vi du VND
 **********************************************************/
const std::string& CTaiKhoan::layTienTe() const {
	return this->m_strTienTe;
}

/**********************************************************
 * @Description Thay doi so du
 *
 * @return      Khong co
 **********************************************************/
void CTaiKhoan::datSoDu(const long long llSoDu) {
	this->m_llSoDu = llSoDu;
}
