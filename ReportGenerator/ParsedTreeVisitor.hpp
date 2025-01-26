
#include "StringReplacer.h"

namespace ReportParser
{
	namespace Converter
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
				repGen.appendText (strRep.processText(text));
			}

			const ReportGenerator::DepthContextType& ctxt;
			ReportGenerator& repGen;
			StringReplacer& strRep;
		};

		void ReportTree_runner::operator()(ReportTree const& xml) const
		{
			StringReplacer replacer;

			// set replacement data
			repGen.setCurrentStringReplacer(&replacer);

			if (repGen.processHeader(xml.context) == ReportGenerator::PROCESS_SECTION)
			{
				if ( xml.header.size() > 0 )
				{
					BOOST_FOREACH(ReportTree_node const& node, xml.header)
					{
						boost::apply_visitor(ReportTree_node_visitor( repGen, xml.context, replacer ) , node);
					}
				}
	
				if ( xml.body.size() > 0 )
				{
					replacer.reset();
					ReportGenerator::ExecuteReturnValues doLoop = ReportGenerator::LOOP_AGAIN;
					// set replacement data
					while (doLoop == ReportGenerator::LOOP_AGAIN )
					{
						// set replacement data
						replacer.reset();
						repGen.setCurrentStringReplacer(&replacer);
						doLoop = repGen.processBody(xml.context);
						if (doLoop != ReportGenerator::REMOVE_BODY)
						{
							BOOST_FOREACH(ReportTree_node const& node, xml.body)
							{
								boost::apply_visitor(ReportTree_node_visitor( repGen, xml.context, replacer ), node);
							}
						}
					}
				}
	
				// set replacement data
				replacer.reset();
				repGen.setCurrentStringReplacer(&replacer);
				repGen.processFooter(xml.context);
	
				if ( xml.footer.size() > 0 )
				{
					BOOST_FOREACH(ReportTree_node const& node, xml.footer)
					{
						boost::apply_visitor(ReportTree_node_visitor( repGen, xml.context, replacer ), node);
					}
				}
			}
		}
	};
};
