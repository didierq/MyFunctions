
// REPORT GENERATOR EXAMPLE

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>

#include "ReportGenerator/ReportGenerator.h"


#include <CtrlLib/CtrlLib.h>
#include <RichText/RichText.h>
#include <RichEdit/RichEdit.h>


using namespace Upp;

#define TOPICFILE <ReportGeneratorTest/app.tpp/all.i>
#include <Core/topic_group.h>

#define LAYOUTFILE <ReportGeneratorTest/ReportGenerator.lay>
#include <CtrlCore/lay.h>

#define IMAGECLASS ReportGeneratorTestImg
#define IMAGEFILE <ReportGeneratorTest/ReportGeneratorTest.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS ReportGeneratorTestImg
#define IMAGEFILE <ReportGeneratorTest/ReportGeneratorTest.iml>
#include <Draw/iml_source.h>


class ReportPanel : public WithReportLayout<TopWindow>
{
	typedef ReportPanel CLASSNAME;
	
	public:
		ReportPanel()
		{
			Sizeable();
			CtrlLayoutOK(*this, "");
			//SetTimeCallback(30000, THISBACK(Close));
		}
};


class MyRepGenerator : public ReportGenerator
{
	private:
		int loopCount;
		int letterloopCount, currentNameLength, counterCount;
		enum {NB_NAMES = 5};
		const char* tabNames[NB_NAMES];
		
	public:
		MyRepGenerator()
		{
			tabNames[0] = "Luzr";
			tabNames[1] = "Rylek";
			tabNames[2] = "Koldo";
			tabNames[3] = "Mrjt";
			tabNames[4] = "Sergey";
		}
		~MyRepGenerator() {}

		// =====================================================================
		// =====================================================================
		virtual ProcessHeaderReturnValues processHeader(const DepthContextType& ctxt )
		{
			ProcessHeaderReturnValues res = PROCESS_SECTION;
			if (isSameContext(ctxt, 1, 0))
			{
				replaceVar("##DATE", AsString(GetSysDate()));
				replaceVar("##TIME", AsString(GetSysTime()));
			}
			else if (isSameContext(ctxt, 2, 0, 0))
			{
				loopCount = -1;
			}
			else if (isSameContext(ctxt, 3, 0, 0, 0))
			{
				letterloopCount = -1;
				currentNameLength = strlen(tabNames[loopCount]);
				replaceVar("##NBLETTERS", AsString( currentNameLength ) );
			}
			else if (isSameContext(ctxt, 2, 0, 1))
			{
				replaceVar("##TITLE", "Let's count to 10 !");
				counterCount = -1;
			}
			
			return res;
		}
		
		// =====================================================================
		// =====================================================================
		virtual ExecuteReturnValues processBody(const DepthContextType& ctxt )
		{
			ExecuteReturnValues res = DO_NOT_LOOP;
			if (isSameContext(ctxt, 1, 0))
			{
				replaceVar("##DATE", AsString(GetSysDate()));
			}
			else if (isSameContext(ctxt, 2, 0, 0))
			{
				++loopCount;
				replaceVar("##NAME", tabNames[loopCount]);
				replaceImage("##IMG", ReportGeneratorTestImg::IDE_ICON(), Size(400,400));
				replaceVar("##SEPARATOR", "===============================");
				if ( loopCount < (NB_NAMES-1)) res = LOOP_AGAIN;
			}
			else if (isSameContext(ctxt, 3, 0, 0, 0))
			{
				letterloopCount++;
				char letterString[3] = { tabNames[loopCount][letterloopCount], 0, 0};
				replaceVar("##LETTER", letterString );
				if ( letterloopCount < (currentNameLength-1)) res = LOOP_AGAIN;
			}
			else if (isSameContext(ctxt, 2, 0, 1))
			{
				counterCount++;
				replaceVar("##COUNT", AsString(counterCount));
				if ( counterCount < 10) res = LOOP_AGAIN;
			}

			return res;
		}

		// =====================================================================
		// =====================================================================
		virtual void processFooter(const DepthContextType& ctxt )
		{
			if (isSameContext(ctxt, 1, 0))
			{
			}
			else if (isSameContext(ctxt, 2, 0, 0))
			{
					replaceVar("##RESUME", "Upp is a great Framework");
			}
			else if (isSameContext(ctxt, 3, 0, 0, 0))
			{
			}
			else if (isSameContext(ctxt, 2, 0, 1))
			{
			}
		}
};

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
GUI_APP_MAIN
{
	ReportGenerator::StringType  templateText = "##H";
//	templateText << Upp::GetTopic("topic://ReportGeneratorTest/app/TEMPLATE_1$en-us").text;
	templateText << Upp::GetTopic("topic://ReportGeneratorTest/app/HelloWorld_1$en-us").text;
	templateText << "##E";
	ReportPanel reportPanel;
	reportPanel.Title("    ANNOTATED  TEMPLATE");
	reportPanel.templat.SetQTF(templateText);

    MyRepGenerator repGenerator;
    LOG(   "\n\n ================================\nINPUT TEMPLATE:\n");
    LOG( templateText);

    LOG( "\n\n ================================\nDOC STRUCTURE:\n");
    LOG( repGenerator.getDocStructure(templateText) );
	
    LOG( "\n\n ================================\nANNOTATED TEMPLATE:\n");
    {
    String annotatedText = repGenerator.getAnnotatedDoc(templateText);
    LOG( annotatedText );
	reportPanel.annotTemplat.SetQTF(annotatedText);
    }
    
    LOG( "\n\n\n ================================\nREPORT DOCUMENT (after template processing):\n");
    {
    String reportText = repGenerator.generateReport(templateText);
    LOG( reportText );
	reportPanel.report.SetQTF(reportText);
    }
	reportPanel.Run();

	
	reportPanel.templat.SetQTF(repGenerator.generateReport(String("##H") + Upp::GetTopic("topic://ReportGeneratorTest/app/TEMPLATE_1$en-us").text + "##E"));
	reportPanel.annotTemplat.SetQTF(repGenerator.generateReport(String("##H") + Upp::GetTopic("topic://ReportGeneratorTest/app/TEMPLATE_2$en-us").text + "##E"));
	reportPanel.report.SetQTF(repGenerator.generateReport(String("##H") + Upp::GetTopic("topic://ReportGeneratorTest/app/TEMPLATE_3$en-us").text + "##E"));
	reportPanel.Run();

}


