#ifndef NGANXEP_H_INCLUDED_
#define NGANXEP_H_INCLUDED_

#include "Nut.h"

template <typename T>
class CNganXep {
private:
	CNut<T>* m_pDinh;

	// Cam sao chep de tranh giai phong cung mot nut hai lan
	CNganXep(const CNganXep&) = delete;
	CNganXep& operator=(const CNganXep&) = delete;

public:
	/**********************************************************
	 * @Description Tao ngan xep rong
	 *
	 * @return      Khong co
	 **********************************************************/
	CNganXep()
		: m_pDinh(nullptr) {
	}

	/**********************************************************
	 * @Description Giai phong moi nut cua ngan xep
	 *
	 * @return      Khong co
	 **********************************************************/
	~CNganXep() {
		while (this->m_pDinh != nullptr) {
			CNut<T>* pBiXoa = this->m_pDinh;
			this->m_pDinh = pBiXoa->layTiep();
			delete pBiXoa;
		}
	}

	/**********************************************************
	 * @Description Kiem tra ngan xep co rong khong
	 *
	 * @return      true neu ngan xep rong
	 **********************************************************/
	bool laRong() const {
		return this->m_pDinh == nullptr;
	}

	/**********************************************************
	 * @Description Dat mot phan tu len dinh ngan xep
	 *
	 * @return      Khong co
	 **********************************************************/
	void dayVao(const T& duLieu) {
		CNut<T>* pNutMoi = new CNut<T>(duLieu);
		pNutMoi->datTiep(this->m_pDinh);
		this->m_pDinh = pNutMoi;
	}

	/**********************************************************
	 * @Description Lay phan tu tren cung ra khoi ngan xep
	 *
	 * @return      true neu lay duoc phan tu
	 * @attention   Tra ve false neu ngan xep rong
	 **********************************************************/
	bool layRa(T& ketQua) {
		if (this->m_pDinh == nullptr) {
			return false;
		}
		CNut<T>* pBiXoa = this->m_pDinh;
		ketQua = pBiXoa->layDuLieu();
		this->m_pDinh = pBiXoa->layTiep();
		delete pBiXoa;
		return true;
	}
};

#endif
