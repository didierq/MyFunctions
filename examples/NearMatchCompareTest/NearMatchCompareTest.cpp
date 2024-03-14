#include <Core/Core.h>
#include <NearMatchCompare/NearMatchCompare.hpp>

using namespace Upp;


#define TEST(A, B)  RLOG( String( "Compare ") << A << "  -  " << B << "\t==> " <<  (NearMatchCompare::isNearMatch(String(A), String(B))==true?"MATCH":"-----")\
                   << "    correlation=" << NearMatchCompare::correlation(String(A), String(B))\
                   <<  "        MAXa=" << NearMatchCompare::correlation(String(A), String(A))\
                   << "     MAXb=" << NearMatchCompare::correlation(String(B), String(B))\
                   );





void doCompare(Vector<String>& list)
{
	Vector<String>::Iterator iter = list.Begin();
	Vector<String>::Iterator iter2 = list.Begin();
	Vector<String>::Iterator endIter = list.End();
	while( iter != endIter )
	{
		iter2 = iter;
		//++iter2;
		while(iter2 != endIter)
		{
			if (*iter!=*iter2)
			if (NearMatchCompare::isNearMatch(*iter, *iter2))
			{
				RLOG(String("NEAR MATCH :   ") << *iter << " <=> " << *iter2 << "\t\tcorr = " << NearMatchCompare::correlation(*iter, *iter2)
							<<   "        MAXa=" << NearMatchCompare::correlation(*iter, *iter) << "     MAXb=" << NearMatchCompare::correlation(*iter2, *iter2) );
			}
			++iter2;
		}
		++iter;
	}
}

CONSOLE_APP_MAIN
{
	RLOG("\n---------------------------------------------------------------------");
	RLOG("\n--- 1 CARACTERE ---");
	TEST("1", "1");
	TEST("1", "2");

	RLOG("\n---------------------------------------------------------------------");
	RLOG("\n--- 2 CARACTERES ---");
	TEST("12", "12");
	TEST("12", "123");
	TEST("12", "11");
	TEST("12", "22");
	TEST("12", "33");
	TEST("12", "21");
	
	
	RLOG("\n---------------------------------------------------------------------");
	RLOG("\n--- 3 CARACTERES ---");
	TEST("123", "123");
	TEST("123", "122");
	TEST("123", "124");
	TEST("123", "143");
	TEST("123", "423");
	TEST("123", "223");
	TEST("123", "113");
	TEST("123", "133");
	TEST("123", "0123");
	TEST("123", "1023");
	TEST("123", "1203");
	TEST("123", "1230");
	TEST("123", "12345");
	TEST("123", "01234");
	TEST("123", "00123");
	TEST("123", "30012");
	TEST("123", "23001");
	TEST("123", "12300");

	RLOG("\n---------------------------------------------------------------------");
	RLOG("\n--- 4 CARACTERES ---");
	TEST("1234", "1234");
	TEST("1234", "0123");
	TEST("1234", "3012");
	TEST("1234", "2301");
	TEST("1234", "1032");
	TEST("1234", "1204");
	TEST("1234", "1224");
	TEST("1234", "1223");
	TEST("1234", "1244");
	TEST("1234", "1123");
	TEST("1234", "1134");
	TEST("1234", "4321");
	TEST("1234", "4432");
	TEST("1234", "4431");
	TEST("1234", "4324");


	RLOG("\n---------------------------------------------------------------------");
	RLOG("\n--- 5 CARACTERES ---");
	TEST("12345", "12345");
	TEST("12345", "12344");
	TEST("12345", "41234");
	TEST("12345", "12034");
	TEST("12345", "12045");
	TEST("12345", "12054");
	TEST("12345", "21045");
	TEST("12345", "21054");
	TEST("12345", "54021");
	
	Vector<String> listNums;

	listNums << "123";
	listNums << "122";
	listNums << "124";
	listNums << "143";
	listNums << "423";
	listNums << "223";
	listNums << "113";
	listNums << "133";
	
	listNums << "0123";
	listNums << "1023";
	listNums << "1203";
	listNums << "1230";
	
	listNums << "12345";
	listNums << "01234";
	listNums << "00123";
	listNums << "30012";
	listNums << "23001";

	listNums << "0123";
	listNums << "3012";
	listNums << "2301";
	listNums << "1032";
	listNums << "1204";
	listNums << "1224";
	listNums << "1223";
	listNums << "1244";
	listNums << "1123";
	listNums << "1134";
	listNums << "4321";
	listNums << "4432";
	listNums << "4431";
	listNums << "4324";
	
	listNums << "12345";
	listNums << "12344";
	listNums << "41234";
	listNums << "12034";
	listNums << "12045";
	listNums << "12054";
	listNums << "21045";
	listNums << "21054";
	listNums << "54021";
	
	
	RLOG("\n---------------------------------------------------------------------");
	RLOG("---------------------------------------------------------------------");
	RLOG("---                        NUMBERS                                   ---");
	RLOG("---------------------------------------------------------------------");
	doCompare(listNums);


}

