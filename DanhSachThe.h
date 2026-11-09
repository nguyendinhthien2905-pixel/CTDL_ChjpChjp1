#ifndef DANHSACHTHE_H_INCLUDED_
#define DANHSACHTHE_H_INCLUDED_

#include <string>

#include "TheTu.h"
#include "DanhSachLienKet.h"

class CDanhSachThe {
private:
	CDanhSachLienKet<CTheTu> m_objDanhSach;

	static bool maSoNhoHon(const CTheTu& objThuNhat, const CTheTu& objThuHai);
	CNut<CTheTu>* timNut(const std::string& strMaSo) const;

public:
	int laySoLuong() const;
	CNut<CTheTu>* layDau() const;

	void docTuFile();
	bool ghiRaFile() const;

	CTheTu* tim(const std::string& strMaSo) const;
	void them(const CTheTu& objThe);
	bool xoa(const std::string& strMaSo);
	void sapXepTheoMaSo();
};

#endif
