#include "Tools.h"
#include <iconv.h>
//#pragma comment(lib,"libiconv.lib")

Tools::Tools()
{
}

Tools::~Tools()
{
}

std::string Tools::Unicode2Utf8(const std::wstring& widestring)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
	if(utf8size == 0)
	{
		throw std::exception("Error in conversion.");
	}
	std::vector<char> resultstring(utf8size);
	int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
	if (convresult != utf8size)
	{
		throw std::exception("La falla!");
	}
	return std::string(&resultstring[0]);
#else
	return "";
#endif
}

int Tools::GBKToUTF8(std::string &gbkStr)
{
	iconv_t iconvH;
	iconvH = iconv_open("utf-8","gb2312");
	if (iconvH == 0)
	{
		return -1;
	}
	const char* strChar = gbkStr.c_str();
	const char** pin = &strChar;
	size_t strLength = gbkStr.length();
	char* outbuf = (char*)malloc(strLength*4);
	char* pBuff = outbuf;
	memset(outbuf, 0, strLength*4);
	size_t outLength = strLength*4;
	if (-1 == iconv(iconvH, (char**)pin, &strLength, &outbuf, &outLength))
	{
		iconv_close(iconvH);
		return -1;
	}
	gbkStr = pBuff;
	iconv_close(iconvH);
	return 0;
}


