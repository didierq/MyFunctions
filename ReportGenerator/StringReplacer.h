/*
 * StringReplacer.h
 *
 *  Created on: 2 janv. 2010
 *      Author: didier
 */

#ifndef STRINREPLACER_H_
#define STRINREPLACER_H_

#include <map>

#include "ReportGenerator.h"


namespace ReportParser
{
	class StringReplacer
		{
			public:
				StringReplacer();
				virtual ~StringReplacer();

				void reset();

				void addReplacement(ReportGenerator::InternalStringType label, ReportGenerator::InternalStringType value);
				ReportGenerator::InternalStringType processText( const ReportGenerator::InternalStringType& templat );

			private:
				typedef std::map<ReportGenerator::InternalStringType, ReportGenerator::InternalStringType> MapType;
				MapType map;
		};

}

#endif /* STRINREPLACER_H_ */
