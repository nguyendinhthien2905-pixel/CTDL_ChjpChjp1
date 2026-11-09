#ifndef DANHSACHLIENKET_H_INCLUDED_
#define DANHSACHLIENKET_H_INCLUDED_

#include <utility>

#include "Nut.h"

template <typename T>
class CDanhSachLienKet {
private:
	CNut<T>* m_pDau;
	int m_iSoLuong;

	// Cam sao chep de tranh giai phong cung mot nut hai lan
	CDanhSachLienKet(const CDanhSachLienKet&) = delete;
	CDanhSachLienKet& operator=(const CDanhSachLienKet&) = delete;

public:
	/**********************************************************
	 * @Description Tao danh sach rong
	 *
	 * @return      Khong co
	 **********************************************************/
	CDanhSachLienKet()
		: m_pDau(nullptr), m_iSoLuong(0) {
	}

	/**********************************************************
	 * @Description Giai phong moi nut cua danh sach
	 *
	 * @return      Khong co
	 **********************************************************/
	~CDanhSachLienKet() {
		this->xoaHet();
	}

	/**********************************************************
	 * @Description Lay nut dau tien
	 *
	 * @return      Con tro toi nut dau tien
	 * @attention   Tra ve nullptr neu danh sach rong
	 **********************************************************/
	CNut<T>* layDau() const {
		return this->m_pDau;
	}

	/**********************************************************
	 * @Description Lay so phan tu
	 *
	 * @return      So phan tu trong danh sach
	 **********************************************************/
	int laySoLuong() const {
		return this->m_iSoLuong;
	}

	/**********************************************************
	 * @Description Them phan tu moi vao cuoi danh sach
	 *
	 * @return      Khong co
	 **********************************************************/
	void themCuoi(const T& duLieu) {
		CNut<T>* pNutMoi = new CNut<T>(duLieu);
		if (this->m_pDau == nullptr) {
			this->m_pDau = pNutMoi;
		} else {
			CNut<T>* pCuoi = this->m_pDau;
			while (pCuoi->layTiep() != nullptr) {
				pCuoi = pCuoi->layTiep();
			}
			pCuoi->datTiep(pNutMoi);
		}
		this->m_iSoLuong++;
	}

	/**********************************************************
	 * @Description Xoa mot nut khoi danh sach
	 *
	 * @return      true neu da xoa nut
	 * @attention   Tra ve false neu nut khong co trong danh sach
	 **********************************************************/
	bool xoaNut(const CNut<T>* pCanXoa) {
		CNut<T>* pTruoc = nullptr;
		CNut<T>* pHienTai = this->m_pDau;
		while (pHienTai != nullptr && pHienTai != pCanXoa) {
			pTruoc = pHienTai;
			pHienTai = pHienTai->layTiep();
		}
		if (pHienTai == nullptr) {
			return false;
		}
		if (pTruoc == nullptr) {
			this->m_pDau = pHienTai->layTiep();
		} else {
			pTruoc->datTiep(pHienTai->layTiep());
		}
		delete pHienTai;
		this->m_iSoLuong--;
		return true;
	}

	/**********************************************************
	 * @Description Xoa toan bo phan tu
	 *
	 * @return      Khong co
	 **********************************************************/
	void xoaHet() {
		while (this->m_pDau != nullptr) {
			CNut<T>* pBiXoa = this->m_pDau;
			this->m_pDau = pBiXoa->layTiep();
			delete pBiXoa;
		}
		this->m_iSoLuong = 0;
	}

	/**********************************************************
	 * @Description Sap xep danh sach bang thuat toan chon (selection sapXep)
	 *
	 * @return      Khong co
	 * @attention   pDungTruoc(a, b) tra ve true neu a phai dung truoc b
	 **********************************************************/
	void sapXep(bool (*pDungTruoc)(const T&, const T&)) {
		for (CNut<T>* pHienTai = this->m_pDau; pHienTai != nullptr; pHienTai = pHienTai->layTiep()) {
			CNut<T>* pNhoNhat = pHienTai;
			for (CNut<T>* pDuyet = pHienTai->layTiep(); pDuyet != nullptr; pDuyet = pDuyet->layTiep()) {
				if (pDungTruoc(pDuyet->layDuLieu(), pNhoNhat->layDuLieu())) {
					pNhoNhat = pDuyet;
				}
			}
			std::swap(pHienTai->layDuLieu(), pNhoNhat->layDuLieu());
		}
	}
};

#endif
