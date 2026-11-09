#ifndef NUT_H_INCLUDED_
#define NUT_H_INCLUDED_

template <typename T>
class CNut {
private:
	T m_duLieu;
	CNut<T>* m_pTiep;

public:
	/**********************************************************
	 * @Description Tao nut chua ban sao cua du lieu
	 *
	 * @return      Khong co
	 **********************************************************/
	explicit CNut(const T& duLieu)
		: m_duLieu(duLieu), m_pTiep(nullptr) {
	}

	/**********************************************************
	 * @Description Lay du lieu cua nut nay
	 *
	 * @return      Tham chieu toi du lieu da luu
	 **********************************************************/
	T& layDuLieu() {
		return this->m_duLieu;
	}

	/**********************************************************
	 * @Description Lay du lieu cua nut nay (chi doc)
	 *
	 * @return      Tham chieu hang toi du lieu da luu
	 **********************************************************/
	const T& layDuLieu() const {
		return this->m_duLieu;
	}

	/**********************************************************
	 * @Description Lay nut ke tiep
	 *
	 * @return      Con tro toi nut ke tiep
	 * @attention   Tra ve nullptr neu day la nut cuoi
	 **********************************************************/
	CNut<T>* layTiep() const {
		return this->m_pTiep;
	}

	/**********************************************************
	 * @Description Noi nut nay voi nut ke tiep
	 *
	 * @return      Khong co
	 **********************************************************/
	void datTiep(CNut<T>* pTiep) {
		this->m_pTiep = pTiep;
	}
};

#endif
