/*
 * ReportGenerator.h
 *
 *  Created on: 1 janv. 2010
 *      Author: didier
 */

#ifndef REPORTGENERATOR_H_
#define REPORTGENERATOR_H_


#include <string>
#include <vector>

#include <Core/Core.h>
#include <CtrlLib/CtrlLib.h>
#include <RichText/RichText.h>


namespace ReportParser
{
	class StringReplacer;
}




class ReportGenerator
{
	public:
		typedef ::std::vector<unsigned int> DepthContextType;
		typedef Upp::String                 StringType;
		typedef ::std::string               InternalStringType;

	public:
		ReportGenerator();
		virtual ~ReportGenerator();

		typedef enum {
			PROCESS_SECTION = 0, // the section ( HEADER/BODY/FOOTER wil be processed )
			REMOVE_SECTION  = 1  // the whole section ( HEADER/BODY/FOOTER )will be removed from the processed report
		} ProcessHeaderReturnValues;
		

		typedef enum
		{
			DO_NOT_LOOP = 0,
			LOOP_AGAIN = 1,
			REMOVE_BODY = 2
		} ExecuteReturnValues;

		virtual ProcessHeaderReturnValues processHeader(const DepthContextType& ctxt ) = 0;
		virtual ExecuteReturnValues processBody(const DepthContextType& ctxt ) = 0;
		virtual void processFooter(const DepthContextType& ctxt ) = 0;

		void replaceVar(const StringType& label, const StringType& value);

		void replaceVar(const StringType& label, const char* value)
		{
			replaceVar(label, Upp::String(value));
		}

		void replaceVar(const StringType& label, char* value)
		{
			replaceVar(label, Upp::String(value));
		}

		template <class T>
		void replaceVar(const StringType& label, const T& value)
		{
			replaceVar(label, AsString(value));
		}

		
		void replaceImage(const StringType& label, const Upp::Image& inputImg, Upp::Size destSize );
		void replaceDrawing(const StringType& label, const Upp::Drawing& inputDrw, Upp::Size destSize );

		StringType getAnnotatedDoc(const StringType& templat );
		StringType generateReport(const StringType& templat);
		StringType getDocStructure(const StringType& templat );

		bool isSameContext(const DepthContextType& ctxt, unsigned int depth, unsigned int sec0=0, unsigned int sec1=0, unsigned int sec2=0, unsigned int sec3=0, unsigned int sec4=0, unsigned int sec5=0, unsigned int sec6=0, unsigned int sec7=0, unsigned int sec8=0);

		void setCurrentStringReplacer(ReportParser::StringReplacer* currReplacer) { currentReplacer = currReplacer; }
		void appendText(const InternalStringType& str) { reportResult += str; }


	private:
		ReportParser::StringReplacer* currentReplacer;
		InternalStringType reportResult;
};

#endif /* REPORTGENERATOR_H_ */
