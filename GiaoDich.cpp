#include "GiaoDich.h"

/**********************************************************
 * @Description Tao giao dich rong
 *
 * @return      Khong co
 **********************************************************/
CGiaoDich::CGiaoDich()
	: m_llSoTien(0) {
}

/**********************************************************
 * @Description Tao giao dich voi day du thong tin
 *
 * @return      Khong co
 **********************************************************/
CGiaoDich::CGiaoDich(const std::string& strLoai, const long long llSoTien,
                     const std::string& strThoiGian, const std::string& strNoiDung)
	: m_strLoai(strLoai), m_llSoTien(llSoTien), m_strThoiGian(strThoiGian), m_strNoiDung(strNoiDung) {
}

/**********************************************************
 * @Description Lay loai giao dich
 *
 * @return      LOAI_RUT, LOAI_CHUYEN hoac LOAI_NHAN
 **********************************************************/
const std::string& CGiaoDich::layLoai() const {
	return this->m_strLoai;
}

/**********************************************************
 * @Description Lay so tien giao dich
 *
 * @return      So tien
 **********************************************************/
long long CGiaoDich::laySoTien() const {
	return this->m_llSoTien;
}

/**********************************************************
 * @Description Lay thoi gian giao dich
 *
 * @return      Chuoi thoi gian, dinh dang dd/mm/yyyy hh:mm:ss
 **********************************************************/
const std::string& CGiaoDich::layThoiGian() const {
	return this->m_strThoiGian;
}

/**********************************************************
 * @Description Lay noi dung giao dich
 *
 * @return      Noi dung giao dich
 **********************************************************/
const std::string& CGiaoDich::layNoiDung() const {
	return this->m_strNoiDung;
}
