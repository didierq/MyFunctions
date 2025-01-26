
#include "StringReplacer.h"

namespace ReportParser
{
	namespace Annotator
	{
		struct ReportTree_runner
		{
			ReportTree_runner(ReportGenerator& _repGen)
			: repGen(_repGen)
			{
			}

			void operator()(ReportTree const& xml) const;

			ReportGenerator& repGen;
		};


		struct ReportTree_node_visitor : boost::static_visitor<>
		{
			ReportTree_node_visitor( ReportGenerator& _repGen, const ReportGenerator::DepthContextType& _ctxt, StringReplacer& _strRep )
			  : ctxt(_ctxt)
			  , repGen(_repGen)
			  , strRep(_strRep)
			{
			}

			// go to next node
			void operator()( const ReportTree& xml) const
			{
				ReportTree_runner repRun( repGen );
				repRun(xml);
			}

			// do text replacements
			void operator()(ReportGenerator::InternalStringType const& text) const
			{
				std::stringstream ctxtStr;
				// ================ INSERT CONTEXT INFO INTO TEMPLATE DOC =================
				ReportParser::AppendQtf(ctxtStr, ctxt);
				// ========================================================================
				repGen.appendText(ctxtStr.str());
				repGen.appendText(text);
			}

			const ReportGenerator::DepthContextType& ctxt;
			ReportGenerator& repGen;
			StringReplacer& strRep;
		};

		void ReportTree_runner::operator()(ReportTree const& xml) const
		{

			repGen.appendText("##H");
			if ( xml.header.size() > 0 )
			{
				StringReplacer replacer;
				// set replacement data
				repGen.setCurrentStringReplacer(&replacer);
				repGen.processHeader(xml.context);

				BOOST_FOREACH(ReportTree_node const& node, xml.header)
				{
					boost::apply_visitor(ReportTree_node_visitor( repGen, xml.context, replacer ) , node);
				}
			}

			if ( xml.body.size() > 0 )
			{
				repGen.appendText("##B");
				StringReplacer replacer;
				// set replacement data
				replacer.reset();
				repGen.setCurrentStringReplacer(&replacer);
				repGen.processBody(xml.context);

				BOOST_FOREACH(ReportTree_node const& node, xml.body)
				{
					boost::apply_visitor(ReportTree_node_visitor( repGen, xml.context, replacer ), node);
				}
			}

			if ( xml.footer.size() > 0 )
			{
				repGen.appendText("##F");
				StringReplacer replacer;
				// set replacement data
				repGen.setCurrentStringReplacer(&replacer);
				repGen.processFooter(xml.context);

				BOOST_FOREACH(ReportTree_node const& node, xml.footer)
				{
					boost::apply_visitor(ReportTree_node_visitor( repGen, xml.context, replacer ), node);
				}
			}
			repGen.appendText("##E");
		}
	};
};

