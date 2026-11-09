#ifndef HANGSO_H_INCLUDED_
#define HANGSO_H_INCLUDED_

#include <string>

// ---------------------------- Mau sac -------------------------------------
const char* const MAU_RESET = "\033[0m";
const char* const MAU_DO = "\033[1;31m";
const char* const MAU_XANH_LA = "\033[1;32m";
const char* const MAU_VANG = "\033[1;33m";
const char* const MAU_XANH_NGOC = "\033[1;36m";
const char* const MAU_TRANG = "\033[1;37m";

// ---------------------------- Hang so nghiep vu ---------------------------
const long long BUOC_TIEN = 50000;             // 50 ngan
const std::string PIN_MAC_DINH = "123456";
const int SO_LAN_THU_TOI_DA = 3;
const int DO_DAI_MA_SO = 14;
const int DO_DAI_PIN = 6;

// ---------------------------- Loai giao dich ------------------------------
const std::string LOAI_RUT = "RUT";
const std::string LOAI_CHUYEN = "CHUYEN";
const std::string LOAI_NHAN = "NHAN";

// ---------------------------- Do rong cot cua bang ------------------------
const int DO_RONG_COT_SO_THU_TU = 6;
const int DO_RONG_COT_MA_SO = 18;
const int DO_RONG_COT_PIN = 10;
const int DO_RONG_COT_THOI_GIAN = 22;
const int DO_RONG_COT_LOAI = 9;
const int DO_RONG_COT_SO_TIEN = 16;

#endif
