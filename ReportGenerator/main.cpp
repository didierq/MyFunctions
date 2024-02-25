
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




class ReportPanel : public WithReportLayout<TopWindow>
{
	typedef ReportPanel CLASSNAME;
	
	public:
		ReportPanel(String& reportText)
		{
			CtrlLayoutOK(*this, "");
			report.SetQTF(reportText);

			SetTimeCallback(30000, THISBACK(Close));
		}
};


class MyRepGenerator : public ReportGenerator
{
	private:
		int loopCount;
		
	public:
		MyRepGenerator() {}
		~MyRepGenerator() {}

		virtual void processHeader(const DepthContextType& ctxt )
		{
			loopCount = 0;
			replaceVar("##DATE", AsString(GetSysDate()));
		}
		virtual ExecuteReturnValues processBody(const DepthContextType& ctxt )
		{
			const char* tabNames[] = {"Luzr", "Rylek", "Koldo", "Mrjt"};
			replaceVar("##NAME", tabNames[loopCount]);
			if (++loopCount < 4) return LOOP_AGAIN;
			return DO_NOT_LOOP;
		}
		virtual void processFooter(const DepthContextType& ctxt )
		{
			replaceVar("##RESUME", "Upp is a great Framework");
		}
};

///////////////////////////////////////////////////////////////////////////////
//  Main program
///////////////////////////////////////////////////////////////////////////////
GUI_APP_MAIN
{
	ReportGenerator::StringType  templateText = "##H";
	templateText << Upp::AsQTF(Upp::ParseQTF( Upp::GetTopic("topic://ReportGeneratorTest/app/TEMPLATE_1$en-us").text ));
	templateText << "##E";

    MyRepGenerator repGenerator;
    LOG(   "\n\n ================================\nINPUT TEMPLATE:\n");
    LOG( templateText);

    LOG( "\n\n ================================\nDOC STRUCTURE:\n");
    LOG( repGenerator.getDocStructure(templateText) );

    LOG( "\n\n ================================\nANNOTATED TEMPLATE:\n");
    {
    String annotatedText = repGenerator.getAnnotatedDoc(templateText);
    LOG( annotatedText );
	ReportPanel reportPanel(annotatedText);
	reportPanel.Title("    ANNOTATED  TEMPLATE");
	reportPanel.Run();
    }
    
    LOG( "\n\n\n ================================\nREPORT DOCUMENT (after template processing):\n");
    {
    String reportText = repGenerator.generateReport(templateText);
    LOG( reportText );
	ReportPanel reportPanel(reportText);
	reportPanel.Title("REPORT GENERATED FROM TEMPLATE");
	reportPanel.Run();
    }
}


