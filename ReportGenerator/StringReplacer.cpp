/*
 * StringReplacer.cpp
 *
 *  Created on: 2 janv. 2010
 *      Author: didier
 */


#include "StringReplacer.h"

#include <Core/Core.h>

using namespace Upp;

namespace ReportParser
{
	String Replace(String str, String find, String replace) {
		String ret;
		
		int lenStr = str.GetCount();
		int lenFind = find.GetCount();
		int i = 0, j;
		while ((j = str.Find(find, i)) >= i) {
			ret += str.Mid(i, j-i) + replace;
			i = j + lenFind;
			if (i >= lenStr)
				break;
		}
		ret += str.Mid(i);
		return ret;
	}
	


	StringReplacer::StringReplacer()
	{
	}

	StringReplacer::~StringReplacer()
	{
	}

	void StringReplacer::addReplacement(ReportGenerator::InternalStringType label, ReportGenerator::InternalStringType value)
	{
		map.insert(std::make_pair(label, value));
	}

	ReportGenerator::InternalStringType StringReplacer::processText( const ReportGenerator::InternalStringType& templat )
	{
		String result = templat.c_str();
		MapType::iterator iter = map.begin();
		const MapType::iterator end = map.end();

		String label;
		String value;
		while(iter != end)
		{
			// process each label to substitute
			label = (*iter).first.c_str();
			value = (*iter).second.c_str();
			while ( result.Find(label) >= 0)
				{
					result = ReportParser::Replace(result, label, value);
				}
			++iter;
		}
		return result.ToStd();
	}

    void StringReplacer::reset()
    {
    	map.clear();
    }
}
