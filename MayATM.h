#ifndef MAYATM_H_INCLUDED_
#define MAYATM_H_INCLUDED_

#include "TheTu.h"
#include "DanhSachThe.h"

class CMayATM {
private:
	CDanhSachThe m_objDanhSachThe;

	static bool xacThucPin(const CTheTu* pThe);

	CTheTu* nhapThe() const;
	CTheTu* dangNhapUser(bool& bThoat);
	bool xuLyUser();
	void xuLyAdmin();

public:
	void chay();
};

#endif
