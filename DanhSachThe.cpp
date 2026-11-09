#include "DanhSachThe.h"

#include <fstream>
#include <sstream>

#include "KhoFile.h"

const int CO_KHOA = 1;

/**********************************************************
 * @Description So sanh ID cua hai the, dung de sap xep
 *
 * @return      true neu the thu nhat co ID nho hon
 **********************************************************/
bool CDanhSachThe::maSoNhoHon(const CTheTu& objThuNhat, const CTheTu& objThuHai) {
	return objThuNhat.layMaSo() < objThuHai.layMaSo();
}

/**********************************************************
 * @Description Tim nut chua the co ID nay
 *
 * @return      Con tro toi nut
 * @attention   Tra ve nullptr neu khong tim thay
 **********************************************************/
CNut<CTheTu>* CDanhSachThe::timNut(const std::string& strMaSo) const {
	CNut<CTheTu>* pNut = this->m_objDanhSach.layDau();
	while (pNut != nullptr && pNut->layDuLieu().layMaSo() != strMaSo) {
		pNut = pNut->layTiep();
	}
	return pNut;
}

/**********************************************************
 * @Description Lay so luong the
 *
 * @return      So the trong danh sach
 **********************************************************/
int CDanhSachThe::laySoLuong() const {
	return this->m_objDanhSach.laySoLuong();
}

/**********************************************************
 * @Description Lay nut dau tien de duyet danh sach
 *
 * @return      Con tro toi nut dau tien
 * @attention   Tra ve nullptr neu danh sach rong
 **********************************************************/
CNut<CTheTu>* CDanhSachThe::layDau() const {
	return this->m_objDanhSach.layDau();
}

/**********************************************************
 * @Description Doc file TheTu.txt, moi dong co dang "ID PIN [khoa]"
 *
 * @return      Khong co
 * @attention   Du lieu cu trong danh sach bi xoa truoc
 **********************************************************/
void CDanhSachThe::docTuFile() {
	this->m_objDanhSach.xoaHet();
	std::ifstream objFile(CKhoFile::layDuongDanTheTu().c_str());
	std::string strDong;
	while (std::getline(objFile, strDong)) {
		std::istringstream objLuongChuoi(strDong);
		std::string strMaSo;
		std::string strPin;
		int iCoKhoa = 0;
		if (objLuongChuoi >> strMaSo >> strPin) {
			objLuongChuoi >> iCoKhoa;
			this->m_objDanhSach.themCuoi(CTheTu(strMaSo, strPin, iCoKhoa == CO_KHOA));
		}
	}
	objFile.close();
}

/**********************************************************
 * @Description Ghi toan bo danh sach vao file TheTu.txt
 *
 * @return      true neu ghi file thanh cong
 **********************************************************/
bool CDanhSachThe::ghiRaFile() const {
	std::ofstream objFile(CKhoFile::layDuongDanTheTu().c_str());
	bool bThanhCong = objFile.is_open();
	for (CNut<CTheTu>* pNut = this->m_objDanhSach.layDau(); bThanhCong && pNut != nullptr; pNut = pNut->layTiep()) {
		const CTheTu& objThe = pNut->layDuLieu();
		objFile << objThe.layMaSo() << " " << objThe.layPin() << " "
		        << (objThe.biKhoa() ? CO_KHOA : 0) << "\n";
	}
	bThanhCong = bThanhCong && static_cast<bool>(objFile);
	objFile.close();
	return bThanhCong;
}

/**********************************************************
 * @Description Tim the theo ID
 *
 * @return      Con tro toi the
 * @attention   Tra ve nullptr neu khong tim thay
 **********************************************************/
CTheTu* CDanhSachThe::tim(const std::string& strMaSo) const {
	CNut<CTheTu>* pNut = this->timNut(strMaSo);
	return (pNut == nullptr) ? nullptr : &pNut->layDuLieu();
}

/**********************************************************
 * @Description Them the vao cuoi danh sach
 *
 * @return      Khong co
 **********************************************************/
void CDanhSachThe::them(const CTheTu& objThe) {
	this->m_objDanhSach.themCuoi(objThe);
}

/**********************************************************
 * @Description Xoa the co ID nay
 *
 * @return      true neu da xoa the
 **********************************************************/
bool CDanhSachThe::xoa(const std::string& strMaSo) {
	CNut<CTheTu>* pNut = this->timNut(strMaSo);
	return pNut != nullptr && this->m_objDanhSach.xoaNut(pNut);
}

/**********************************************************
 * @Description Sap xep danh sach theo ID tang dan
 *
 * @return      Khong co
 **********************************************************/
void CDanhSachThe::sapXepTheoMaSo() {
	this->m_objDanhSach.sapXep(CDanhSachThe::maSoNhoHon);
}
