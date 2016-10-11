#ifndef _SYCRYPTION_H_
#define _SYCRYPTION_H_
#include <string>
#include <time.h>  //for time()
#include <stdlib.h>  //for rand()
#define rand_number(low,high) rand()%((high)-(low)+1)+(low);


//#define	 SYCRYPTION_MAP		L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./_"
//#define	 SYCRYPTION_KEY		L"FabricaCommunications.CO.LTD."

#define	 SYCRYPTION_MAP		L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789./_?-=&"
#define	 SYCRYPTION_KEY		L"ASUSTEK.COMPUTER.INC.CO.LTD.OPEN.PLATFORM.BUSSINESS.GROUP.MOTHERBOARD.BUSINESS.UNIT.COPYRIGHT.BY.SAWYER_2013"

class SYCryption
{
private:
	std::wstring CharAt(std::wstring src, size_t pos)
	{
		std::wstring result = L"";
		result+=src.at(pos);
 		return result;
	}

	long IndexOf(std::wstring src, std::wstring target)
	{
		size_t found = src.find_first_of(target);
		if (found==std::string::npos)
		{
			return -1;
		}
		return (long)found;
	}

	std::wstring GetRandomSpKey()
	{
		 srand((unsigned int)time(NULL));
		 size_t pos = rand_number(0, wcslen(SYCRYPTION_KEY)-1);
		 return CharAt(SYCRYPTION_KEY, pos);
	}
public:

	std::wstring EnCrypt(const wchar_t *source)
	{
	   // .nmsfs/fflv:2010:04:06:0uphvgi1ecj5q.flv/m2530952	
	   //A.s_GJNa5hMU:jaWP:gZ:al:28msBjf1j2.jLZ5nWkLjfYPWlX		  
	
		std::wstring spKey = GetRandomSpKey();

		std::wstring input = source;
		std::wstring result = spKey;
		std::wstring enc = input; 
		std::wstring key = spKey+SYCRYPTION_KEY;
		std::wstring map = SYCRYPTION_MAP;

		long lenc = (long)enc.length();
		long lenk = (long)key.length();
		long lenm = (long)wcslen(SYCRYPTION_MAP);

		for (int i=0; i<lenc; i++)
		{
			std::wstring ch = CharAt(enc, i);
			long pos = IndexOf(map, ch);
			if (pos > -1)
			{
				std::wstring cc = CharAt(key, (i%lenk));
				pos+= IndexOf(map, CharAt(key, (i%lenk)));
				if (pos < 0) pos+=lenm;
				if (pos >= lenm) pos-=lenm;
				ch = CharAt(map, pos);
			}//end if
			result+=ch;
		}//end for
		OutputDebugStringW(result.c_str());
		return result;
	}


	std::wstring DeCrypt(const wchar_t *source)
	{
		std::wstring input = source;
		std::wstring result = L"";
		std::wstring enc = input.substr(1);  // ex:"123456" => enc = "23456" 
		std::wstring key = CharAt(input, 0)+SYCRYPTION_KEY;
		std::wstring map = SYCRYPTION_MAP;
		
		long lenc = (long)enc.length();
		long lenk = (long)key.length();
		long lenm = (long)wcslen(SYCRYPTION_MAP);
	
		for (int i=0; i<lenc; i++)
		{
			std::wstring ch = CharAt(enc, i);
			long pos = IndexOf(map, ch);

			if (pos > -1)
			{
				pos-= IndexOf(map, CharAt(key, (i%lenk)));
				if (pos < 0) pos+=lenm;
				if (pos >= lenm) pos-=lenm;
				ch = CharAt(map, pos);
			}//end if
			result+=ch;
		}//end for
		OutputDebugStringW(result.c_str());
		return result;
	}
};

#endif

