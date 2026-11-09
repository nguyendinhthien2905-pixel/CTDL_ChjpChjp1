#include "TheTu.h"

/**********************************************************
 * @Description Tao the rong
 *
 * @return      Khong co
 **********************************************************/
CTheTu::CTheTu()
	: m_bBiKhoa(false) {
}

/**********************************************************
 * @Description Tao the voi day du thong tin
 *
 * @return      Khong co
 **********************************************************/
CTheTu::CTheTu(const std::string& strMaSo, const std::string& strPin, const bool bBiKhoa)
	: m_strMaSo(strMaSo), m_strPin(strPin), m_bBiKhoa(bBiKhoa) {
}

/**********************************************************
 * @Description Lay ma so tai khoan cua the
 *
 * @return      Ma so tai khoan (14 chu so)
 **********************************************************/
const std::string& CTheTu::layMaSo() const {
	return this->m_strMaSo;
}

/**********************************************************
 * @Description Lay ma PIN cua the
 *
 * @return      Ma PIN (6 chu so)
 **********************************************************/
const std::string& CTheTu::layPin() const {
	return this->m_strPin;
}

/**********************************************************
 * @Description Kiem tra the co bi khoa khong
 *
 * @return      true neu the bi khoa
 **********************************************************/
bool CTheTu::biKhoa() const {
	return this->m_bBiKhoa;
}

/**********************************************************
 * @Description Doi ma PIN cua the
 *
 * @return      Khong co
 **********************************************************/
void CTheTu::datPin(const std::string& strPin) {
	this->m_strPin = strPin;
}

/**********************************************************
 * @Description Khoa hoac mo khoa the
 *
 * @return      Khong co
 **********************************************************/
void CTheTu::datKhoa(const bool bBiKhoa) {
	this->m_bBiKhoa = bBiKhoa;
}
