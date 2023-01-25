/**
 * @file include/base_library/_codepages.h
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-13
 * @language C
 * @brief C++ Plus codepages and codenames convert
 * @version 1.0.0.0
 */

#ifndef _CPPP_CODEPAGES_HPP_
#define _CPPP_CODEPAGES_HPP_

#include "_cpppinclude.h"
#if _CPPPRT_PLATFORM_COMPILER == CPPPRT_PLATFORM_COMPILER_MSVC
#pragma warning(disable:6011)
#pragma warning(disable:6386)
#endif

#ifdef __cplusplus
namespace _cpppbase
{
	namespace _encoding
	{
		namespace _codepages
		{
#endif
			/**
			 * @date 2023-1-8
			 * @brief 通过[value,key,v,k,...]实现简单的静态字典
			 * @brief value通过const wchar_t*地址表示代码页
			 */
			static const wchar_t* __cppp_encoding_cps[] = {
				(const wchar_t*)0,L"ansi",//CP_ACP
				(const wchar_t*)37,L"ibm037",//ibm EBCDIC（美国 - 加拿大）
				(const wchar_t*)437,L"ibm437",//OEM 美国
				(const wchar_t*)500,L"ibm500",//ibm EBCDIC（国际）
				(const wchar_t*)708,L"asmo-708",//阿拉伯字符 (ASMO 708)
				(const wchar_t*)720,L"dos-720",//阿拉伯字符 (DOS)
				(const wchar_t*)737,L"ibm737",//希腊字符 (DOS)
				(const wchar_t*)775,L"ibm775",//波罗的海字符 (DOS)
				(const wchar_t*)850,L"ibm850",//西欧字符 (DOS)
				(const wchar_t*)852,L"ibm852",//中欧字符 (DOS)
				(const wchar_t*)855,L"ibm855",//OEM 西里尔语
				(const wchar_t*)857,L"ibm857",//土耳其字符 (DOS)
				(const wchar_t*)858,L"ibm00858",//OEM 多语言拉丁语 I
				(const wchar_t*)860,L"ibm860",//葡萄牙语 (DOS)
				(const wchar_t*)861,L"ibm861",//冰岛语 (DOS)
				(const wchar_t*)862,L"dos-862",//希伯来字符 (DOS)
				(const wchar_t*)863,L"ibm863",//加拿大法语 (DOS)
				(const wchar_t*)864,L"ibm864",//阿拉伯字符 (864)
				(const wchar_t*)865,L"ibm865",//北欧字符 (DOS)
				(const wchar_t*)866,L"cyrillic-dos",//西里尔字符 (DOS)
				(const wchar_t*)869,L"ibm869",//现代希腊字符 (DOS)
				(const wchar_t*)870,L"ibm870",//ibm EBCDIC（多语言拉丁语 2）
				(const wchar_t*)874,L"windows-874",//泰语 (Windows)
				(const wchar_t*)875,L"greek",//ibm EBCDIC（现代希腊语）
				(const wchar_t*)932,L"shift_jis",//日语 (Shift-JIS)
				(const wchar_t*)936,L"gb2312",//简体中文 (GB2312)
				(const wchar_t*)949,L"ks_c_5601-1987",//朝鲜语
				(const wchar_t*)950,L"big5",//繁体中文 (Big5)
				(const wchar_t*)1026,L"ibm1026",//ibm EBCDIC（土耳其拉丁语 5）
				(const wchar_t*)1047,L"ibm01047",//ibm 拉丁语 1
				(const wchar_t*)1140,L"ibm01140",//ibm EBCDIC（美国 - 加拿大 - 欧洲）
				(const wchar_t*)1141,L"ibm01141",//ibm EBCDIC（德国 - 欧洲）
				(const wchar_t*)1142,L"ibm01142",//ibm EBCDIC（丹麦 - 挪威 - 欧洲）
				(const wchar_t*)1143,L"ibm01143",//ibm EBCDIC（芬兰 - 瑞典 - 欧洲）
				(const wchar_t*)1144,L"ibm01144",//ibm EBCDIC（意大利 - 欧洲）
				(const wchar_t*)1145,L"ibm01145",//ibm EBCDIC（西班牙 - 欧洲）
				(const wchar_t*)1146,L"ibm01146",//ibm EBCDIC（英国 - 欧洲）
				(const wchar_t*)1147,L"ibm01147",//ibm EBCDIC（法国 - 欧洲）
				(const wchar_t*)1148,L"ibm01148",//ibm EBCDIC（国际 - 欧洲）
				(const wchar_t*)1149,L"ibm01149",//ibm EBCDIC（冰岛语 - 欧洲）
				(const wchar_t*)1200,L"utf-16",//Unicode
				(const wchar_t*)1201,L"unicodefffe",//Unicode (Big-Endian)
				(const wchar_t*)1250,L"windows-1250",//中欧字符 (Windows)
				(const wchar_t*)1251,L"windows-1251",//西里尔字符 (Windows)
				(const wchar_t*)1252,L"Windows-1252",//西欧字符 (Windows)
				(const wchar_t*)1253,L"windows-1253",//希腊字符 (Windows)
				(const wchar_t*)1254,L"windows-1254",//土耳其字符 (Windows)
				(const wchar_t*)1255,L"windows-1255",//希伯来字符 (Windows)
				(const wchar_t*)1256,L"windows-1256",//阿拉伯字符 (Windows)
				(const wchar_t*)1257,L"windows-1257",//波罗的海字符 (Windows)
				(const wchar_t*)1258,L"windows-1258",//越南字符 (Windows)
				(const wchar_t*)1361,L"johab",//朝鲜语 (Johab)
				(const wchar_t*)10000,L"macintosh",//西欧字符 (Mac)
				(const wchar_t*)10001,L"x-mac-japanese",//日语 (Mac)
				(const wchar_t*)10002,L"x-mac-chinesetrad",//繁体中文 (Mac)
				(const wchar_t*)10003,L"x-mac-korean",//朝鲜语 (Mac)
				(const wchar_t*)10004,L"x-mac-arabic",//阿拉伯字符 (Mac)
				(const wchar_t*)10005,L"x-mac-hebrew",//希伯来字符 (Mac)
				(const wchar_t*)10006,L"x-mac-greek",//希腊字符 (Mac)
				(const wchar_t*)10007,L"x-mac-cyrillic",//西里尔字符 (Mac)
				(const wchar_t*)10008,L"x-mac-chinesesimp",//简体中文 (Mac)
				(const wchar_t*)10010,L"x-mac-romanian",//罗马尼亚语 (Mac)
				(const wchar_t*)10017,L"x-mac-ukrainian",//乌克兰语 (Mac)
				(const wchar_t*)10021,L"x-mac-thai",//泰语 (Mac)
				(const wchar_t*)10029,L"x-mac-ce",//中欧字符 (Mac)
				(const wchar_t*)10079,L"x-mac-icelandic",//冰岛语 (Mac)
				(const wchar_t*)10081,L"x-mac-turkish",//土耳其字符 (Mac)
				(const wchar_t*)10082,L"x-mac-croatian",//克罗地亚语 (Mac)
				(const wchar_t*)20000,L"x-chinese-cns",//繁体中文 (CNS)
				(const wchar_t*)20001,L"x-cp20001",//TCA 台湾
				(const wchar_t*)20002,L"x-chinese-eten",//繁体中文 (Eten)
				(const wchar_t*)20003,L"x-cp20003",//ibm5550 台湾
				(const wchar_t*)20004,L"x-cp20004",//TeleText 台湾
				(const wchar_t*)20005,L"x-cp20005",//Wang 台湾
				(const wchar_t*)20105,L"x-ia5",//西欧字符 (IA5)
				(const wchar_t*)20106,L"x-ia5-german",//德语 (IA5)
				(const wchar_t*)20107,L"x-ia5-swedish",//瑞典语 (IA5)
				(const wchar_t*)20108,L"x-ia5-norwegian",//挪威语 (IA5)
				(const wchar_t*)20127,L"us-ascii",//US-ASCII
				(const wchar_t*)20261,L"x-cp20261",//T.61
				(const wchar_t*)20269,L"x-cp20269",//ISO-6937
				(const wchar_t*)20273,L"ibm273",//ibm EBCDIC（德国）
				(const wchar_t*)20277,L"ibm277",//ibm EBCDIC（丹麦 - 挪威）
				(const wchar_t*)20278,L"ibm278",//ibm EBCDIC（芬兰 - 瑞典）
				(const wchar_t*)20280,L"ibm280",//ibm EBCDIC（意大利）
				(const wchar_t*)20284,L"ibm284",//ibm EBCDIC（西班牙）
				(const wchar_t*)20285,L"ibm285",//ibm EBCDIC（英国）
				(const wchar_t*)20290,L"ibm290",//ibm EBCDIC（日语片假名）
				(const wchar_t*)20297,L"ibm297",//ibm EBCDIC（法国）
				(const wchar_t*)20420,L"ibm420",//ibm EBCDIC（阿拉伯语）
				(const wchar_t*)20423,L"ibm423",//ibm EBCDIC（希腊语）
				(const wchar_t*)20424,L"ibm424",//ibm EBCDIC（希伯来语）
				(const wchar_t*)20833,L"x-ebcdic-koreanextended",//ibm EBCDIC（朝鲜语扩展）
				(const wchar_t*)20838,L"ibm-thai",//ibm EBCDIC（泰语）
				(const wchar_t*)20866,L"koi8-r",//西里尔字符 (KOI8-R)
				(const wchar_t*)20871,L"ibm871",//ibm EBCDIC（冰岛语）
				(const wchar_t*)20880,L"ibm880",//ibm EBCDIC（西里尔俄语）
				(const wchar_t*)20905,L"ibm905",//ibm EBCDIC（土耳其语）
				(const wchar_t*)20924,L"ibm00924",//ibm 拉丁语 1
				(const wchar_t*)20932,L"euc-jp",//日语（JIS 0208-1990 和 0212-1990）
				(const wchar_t*)20936,L"x-cp20936",//简体中文 (GB2312-80)
				(const wchar_t*)20949,L"x-cp20949",//朝鲜语 Wansung
				(const wchar_t*)21025,L"cyrillic-serbian-bulgarian",//ibm EBCDIC（西里尔塞尔维亚 - 保加利亚语）
				(const wchar_t*)21866,L"koi8-u",//西里尔字符 (KOI8-U)
				(const wchar_t*)28591,L"iso-8859-1",//西欧字符 (ISO)
				(const wchar_t*)28592,L"iso-8859-2",//中欧字符 (ISO)
				(const wchar_t*)28593,L"iso-8859-3",//拉丁语 3 (ISO)
				(const wchar_t*)28594,L"iso-8859-4",//波罗的海字符 (ISO)
				(const wchar_t*)28595,L"iso-8859-5",//西里尔字符 (ISO)
				(const wchar_t*)28596,L"iso-8859-6",//阿拉伯字符 (ISO)
				(const wchar_t*)28597,L"iso-8859-7",//希腊字符 (ISO)
				(const wchar_t*)28598,L"iso-8859-8",//希伯来字符 (ISO-Visual)
				(const wchar_t*)28599,L"iso-8859-9",//土耳其字符 (ISO)
				(const wchar_t*)28603,L"iso-8859-13",//爱沙尼亚语 (ISO)
				(const wchar_t*)28605,L"iso-8859-15",//拉丁语 9 (ISO)
				(const wchar_t*)29001,L"x-europa",//欧罗巴
				(const wchar_t*)38598,L"iso-8859-8-i",//希伯来字符 (ISO-Logical)
				(const wchar_t*)50220,L"iso-2022-jp",//日语 (JIS)
				(const wchar_t*)50221,L"csiso2022jp",//日语（JIS- 允许 1 字节假名）
				(const wchar_t*)50222,L"iso-2022-jp",//日语（JIS- 允许 1 字节假名 - SO/SI）
				(const wchar_t*)50225,L"iso-2022-kr",//朝鲜语 (ISO)
				(const wchar_t*)50227,L"x-cp50227",//简体中文 (ISO-2022)
				(const wchar_t*)51932,L"euc-jp",//日语 (EUC)
				(const wchar_t*)51936,L"euc-cn",//简体中文 (EUC)
				(const wchar_t*)51949,L"euc-kr",//朝鲜语 (EUC)
				(const wchar_t*)52936,L"hz-gb-2312",//简体中文 (HZ)
				(const wchar_t*)54936,L"gb18030",//简体中文 (GB18030)
				(const wchar_t*)57002,L"x-iscii-de",//ISCII 梵文
				(const wchar_t*)57003,L"x-iscii-be",//ISCII 孟加拉语
				(const wchar_t*)57004,L"x-iscii-ta",//ISCII 泰米尔语
				(const wchar_t*)57005,L"x-iscii-te",//ISCII 泰卢固语
				(const wchar_t*)57006,L"x-iscii-as",//ISCII 阿萨姆语
				(const wchar_t*)57007,L"x-iscii-or",//ISCII 奥里雅语
				(const wchar_t*)57008,L"x-iscii-ka",//ISCII 卡纳达语
				(const wchar_t*)57009,L"x-iscii-ma",//ISCII 马拉雅拉姆语
				(const wchar_t*)57010,L"x-iscii-gu",//ISCII 古吉拉特语
				(const wchar_t*)57011,L"x-iscii-pa",//ISCII 旁遮普语
				(const wchar_t*)65000,L"utf-7",//Unicode (UTF-7)
				(const wchar_t*)65001,L"utf-8",//Unicode (UTF-8)
				(const wchar_t*)65005,L"utf-32",//Unicode (UTF-32)
				(const wchar_t*)65006,L"utf-32be",//Unicode (UTF-32 Big-Endian)

				(const wchar_t*)437,L"ascii",//ASCII Code Page
				(const wchar_t*)1200,L"utf",//UTF Code Page
				(const wchar_t*)936,L"gbk",//cp936 code page
				(const wchar_t*)936,L"chinese",//Chinese alias
				(const wchar_t*)437,L"english",//English alias

			};
			/**
			 * @date 2023-1-8
			 * @brief array cps's length
			 */
			constexpr static const size_t __cppp_encoding_cpslen = sizeof(__cppp_encoding_cps) / sizeof(const wchar_t*);

#if _CPPPRT_PLATFORM!=CPPPRT_PLATFORM_WIN32
			/**
			 * @date 2023-1-8
			 * @brief unsigned int
			 */
			typedef unsigned int UINT;
#endif
			/**
			 * @date 2023-1-13
			 * @brief convert string to codename in cps
			 * @param name a string
			 * @param len string length
			 * @return wchar_t* cps's codename format string
			 */
			_CONSTEXPR20 wchar_t* __cppp_encoding_tocodename(const wchar_t* name,const size_t len)
			{
				wchar_t* res=(wchar_t*)malloc((sizeof(wchar_t)+1)*len);
				for (size_t i=0; i<len; i++)
				{
					res[i]=towlower(name[i]);
				}
				res[(sizeof(wchar_t) * len) - 1] = 0;
				return res;
			}

			/**
			 * @date 2023-1-13
			 * @brief find codename in cps
			 * @param name codename
			 * @param len name length
			 * @return UINT codepage
			 * @retval if not found,return (UINT)(-1)
			 * @pre param name MUST can be found in cps,or return (UINT)(-1)
			 * @warning you'd better use "getcp" function
			 */
			_CONSTEXPR20 static const UINT __cppp_encoding_cpsfind(const wchar_t* name,const size_t len)
			{
				for (size_t i = 1; i < __cppp_encoding_cpslen; i += 2)
				{
					wchar_t* cname = __cppp_encoding_tocodename(name, len);
					if (wcscmp(__cppp_encoding_cps[i], cname)==0)
					{
						free(cname);
						return (UINT)
#if __POINTER_WIDTH__ == 64
							(unsigned long long)//64bit long pointer
#endif
							(void*)__cppp_encoding_cps[i - 1];
					}
					free(cname);
				}
				return (UINT)(-1);
			}

			/**
			 * @date 2023-1-13
			 * @brief return the code page corresponding to "cpname"
			 * @param cpname codepage name
			 * @return UINT codepage
			 * @retval if not found,return (UINT)(-1)
			 */
			_CONSTEXPR20 static const UINT __cppp_encoding_getcp(const wchar_t* cpname)
			{
				size_t nlen = wcslen(cpname)+1;
				UINT cp = __cppp_encoding_cpsfind(cpname,nlen);
				if (cp == (UINT)(-1) && nlen >= 3)//'c','p','x'
				{
					if (cpname[0] == 'c' && cpname[1] == 'p')
					{
						return (UINT)
							wcstoul(cpname+2, NULL, 10);
					}
				}
				return cp;
			}

			/**
			 * @date 2023-1-8
			 * @brief find Return the code page name corresponding to "codepage"
			 * @param UINT codepage : codepage
			 * @return const wchar_t* : codepage name
			 */
			_CONSTEXPR20 static const wchar_t* __cppp_encoding_which(UINT codepage)
			{
				for (size_t i = 0; i < sizeof(__cppp_encoding_cps); i += 2)
				{
					if ((UINT)
#if __POINTER_WIDTH__ == 64
						(unsigned long long)//64位长指针
#endif
						(void*)__cppp_encoding_cps[i] == codepage)
					{
						return (const wchar_t*)__cppp_encoding_cps[i + 1];
					}
				}
				return (const wchar_t*)NULL;
			}
#ifdef __cplusplus
		}
	}
}
#endif
#endif