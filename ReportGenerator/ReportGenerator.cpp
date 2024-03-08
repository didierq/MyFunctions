/*
 * ReportGenerator.cpp
 *
 *  Created on: 1 janv. 2010
 *      Author: didier
 */

#pragma BLITZ_PROHIBIT
//$-
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/foreach.hpp>
//$+

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "ReportGenerator.h"


using namespace Upp;

#define IMAGECLASS ReportGeneratorImg
#define IMAGEFILE <ReportGenerator/ReportGenerator.iml>
#include <Draw/iml_header.h>

#define IMAGECLASS ReportGeneratorImg
#define IMAGEFILE <ReportGenerator/ReportGenerator.iml>
#include <Draw/iml_source.h>

// =============================================================================

namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;
namespace qi = boost::spirit::qi;
//    namespace ascii = boost::spirit::ascii;
//    namespace ascii = boost::spirit::standard;
namespace asciiType = boost::spirit::iso8859_1;
namespace ReportParser
{

	template <class STREAM>
	STREAM& operator<<(STREAM& str, const ReportGenerator::DepthContextType& ctxt)
	{
		str << "(";
		str << ctxt.size() << ",(";
		for(unsigned int c=0; c<ctxt.size(); c++)
		{
			if (c>0)
			{
				str << ", ";
			}
			str << ctxt[c];
		}
		str << "))";
		return str;
	}

	template <class STREAM>
	void AppendQtf(STREAM& str, const ReportGenerator::DepthContextType& ctxt)
	{
		// Generate a QTF string 
		//[@(0.255.0)$(141.42.0) (1(0,1,2))]
		str << "[@(0.255.0)$(141.42.0) ";
		str << ctxt;
		str << "]";
	}

	class ContextManager
	{
		template <class STREAM>
		friend STREAM& operator<<(STREAM& str, const ContextManager& ctxt)
		{
			str << ctxt.ctxt;
			return str;
		}

		private:
		ReportGenerator::DepthContextType ctxt;
			int nextContextVal;

		public:
			ContextManager(): nextContextVal(0)
			{
				//ctxt << 0; // default context
			}

			inline void incDepth()
			{
				ctxt.push_back(nextContextVal);
				nextContextVal = 0;
			}

			inline void incDepth(ReportGenerator::DepthContextType& out)
			{
				ctxt.push_back(nextContextVal);
				nextContextVal = 0;
				out = ctxt;
			}

			inline void decDepth()
			{
				nextContextVal = ctxt[ctxt.size()-1] + 1;
				ctxt.pop_back();
			}

			inline const ReportGenerator::DepthContextType& incGetCtxt() { incDepth(); return ctxt; }
			inline const ReportGenerator::DepthContextType& getCtxt() { return ctxt; }
	};

    ///////////////////////////////////////////////////////////////////////////
    //  Our tree representation
    ///////////////////////////////////////////////////////////////////////////
    struct ReportTree;

    typedef
        boost::variant<
            boost::recursive_wrapper<ReportTree>
          , ReportGenerator::InternalStringType // header
        >
    ReportTree_node;
    enum
	{
		NODE_POS_CHILDREN = 0, NODE_POS_HEADER = 1, NODE_POS_BODY = 2, NODE_POS_FOOTER = 3
	};

    struct ReportTree
    {
    	ReportGenerator::DepthContextType context;                           // tag name
        std::vector<ReportTree_node> header;
        std::vector<ReportTree_node> body;
        std::vector<ReportTree_node> footer;
    };

    enum
	{
		MINIXML_POS_NAME = 0, MINIXML_POS_HEADER = 1, MINIXML_POS_BODY = 2, MINIXML_POS_FOOTER = 3
	};
}

// We need to tell fusion about our ReportTree struct
// to make it a first-class fusion citizen
//[tutorial_xml1_adapt_structures
BOOST_FUSION_ADAPT_STRUCT(
    ReportParser::ReportTree,
    (ReportGenerator::DepthContextType, context)
    (std::vector<ReportParser::ReportTree_node>, header)
    (std::vector<ReportParser::ReportTree_node>, body)
    (std::vector<ReportParser::ReportTree_node>, footer)
)

#include "ParsedTreeVisitor.hpp"
#include "ReportTreeAnnotator.hpp"
#include "Mini_xml_printer.hpp"


namespace ReportParser
{


    ///////////////////////////////////////////////////////////////////////////
    //  Our mini XML grammar definition
    ///////////////////////////////////////////////////////////////////////////
    //[tutorial_xml1_grammar
    template <typename Iterator>
    struct ReportTree_grammar : qi::grammar<Iterator, ReportTree(), asciiType::space_type>
    {
    	const char* HEADER_TAG;
    	const char* BODY_TAG;
    	const char* FOOTER_TAG;
    	const char* END_TAG;

    	ContextManager ctxtMngr;

        ReportTree_grammar() : ReportTree_grammar::base_type(reportSyntax, "reportSyntax")
        , HEADER_TAG("##H")
		, BODY_TAG("##B")
		, FOOTER_TAG("##F")
		, END_TAG("##E")
        {
            using qi::lit;
            using qi::lexeme;
            using qi::eol;
            using qi::on_error;
            using qi::fail;
            using asciiType::char_;
            using asciiType::string;
            using namespace qi::labels;

            using phoenix::construct;
            using phoenix::val;
            using phoenix::at_c;
            using phoenix::push_back;
            using phoenix::bind;


            start_tag = string(HEADER_TAG) - eol;
            body_tag = string(BODY_TAG) - eol;
            footer_tag = string(FOOTER_TAG) - eol;
            end_tag = string(END_TAG) - eol;
			
            text %= lexeme[+(char_ - (string(HEADER_TAG) | string(BODY_TAG) | string(FOOTER_TAG) | string(END_TAG)))];

            node %= (reportSyntax | text);

            reportSyntax = start_tag  [at_c<MINIXML_POS_NAME>(_val) = boost::phoenix::bind(&ContextManager::incGetCtxt, &ctxtMngr)] // increment context
            		> *node           [push_back(at_c<MINIXML_POS_HEADER>(_val), _1)]
            		> -body_tag
            		> *node           [push_back(at_c<MINIXML_POS_BODY>(_val), _1)]
            		> -footer_tag
            		> *node           [push_back(at_c<MINIXML_POS_FOOTER>(_val), _1)]
            		> end_tag [phoenix::bind(&ContextManager::decDepth, &ctxtMngr)]; // decrement context

            reportSyntax.name("reportSyntax");

            node.name("node");
            text.name("text");
            start_tag.name("start_tag");
            body_tag.name("body_tag");
            footer_tag.name("body_tag");
            end_tag.name("end_tag");

            on_error<fail>
                        (
                        	reportSyntax
                          , std::cout
                                << val("Error! Expecting ")
                                << _4                               // what failed?
                                << val(" here: \"")
                                << construct<ReportGenerator::InternalStringType>(_3, _2)   // iterators to error-pos, end
                                << val("\"")
                                << std::endl
                        );
        }

        qi::rule<Iterator, ReportTree(), asciiType::space_type> reportSyntax;
        qi::rule<Iterator, ReportTree_node(), asciiType::space_type> node;
        qi::rule<Iterator, ReportGenerator::InternalStringType(), asciiType::space_type> text;
        qi::rule<Iterator> start_tag;
		qi::rule<Iterator> body_tag;
		qi::rule<Iterator> footer_tag;
		qi::rule<Iterator> end_tag;
	};
}

// =============================================================================================
// =============================================================================================
// =============================================================================================
// =============================================================================================

ReportGenerator::ReportGenerator()
: reportResult("")
{
	// TODO Auto-generated constructor stub

}

ReportGenerator::~ReportGenerator()
{
	// TODO Auto-generated destructor stub
}

void ReportGenerator::replaceVar(const StringType& label, const StringType& value)
{
	currentReplacer->addReplacement(label.ToStd(), DeQtf(value).ToStd());
}

//Array<QtfRichObject> qtfim;

//void RepGen::PlaceImage(String s_from, Image im_to, Size rep_place ){
void ReportGenerator::replaceImage(const StringType& label, const Upp::Image& inputImg, Upp::Size destSize )
{
	Upp::String s;
	if (!inputImg.IsEmpty() )
	{
		if (destSize.cy != 0)
		{
			if ( inputImg.GetWidth()*100/inputImg.GetHeight() > destSize.cx*100/destSize.cy )
			{
				s << AsQTF(CreatePNGObject(inputImg, destSize.cx,0));
			}
			else
			{
				s << AsQTF(CreatePNGObject(inputImg, 0, destSize.cy));
			}
		}
		else
		{
			s << AsQTF( CreatePNGObject(inputImg));
		}
		currentReplacer->addReplacement(label.ToStd(), s.ToStd());
//		replaceVar(label,s);
	}
	else
	{
		replaceImage(label, ReportGeneratorImg::EMPTY_IMG(), destSize);
	}
};

void ReportGenerator::replaceDrawing(const StringType& label, const Upp::Drawing& inputDrw, Upp::Size destSize )
{
	Upp::String s;
	if (!inputDrw.IsNullInstance() )
	{
		if (destSize.cy != 0)
		{
			if ( inputDrw.GetSize().cx*100/inputDrw.GetSize().cy > destSize.cx*100/destSize.cy )
			{
				s << AsQTF(CreateDrawingObject(inputDrw, destSize.cx,0));
			}
			else
			{
				s << AsQTF(CreateDrawingObject(inputDrw, 0, destSize.cy));
			}
		}
		else
		{
			s << AsQTF(CreateDrawingObject(inputDrw));
		}
		currentReplacer->addReplacement(label.ToStd(), s.ToStd());
//		replaceVar(label,s);
	}
	else
	{
		replaceImage(label, ReportGeneratorImg::EMPTY_IMG(), destSize);
	}
};

bool ReportGenerator::isSameContext( const DepthContextType& ctxt, unsigned int depth, unsigned int sec0, unsigned int sec1, unsigned int sec2, unsigned int sec3, unsigned int sec4, unsigned int sec5, unsigned int sec6, unsigned int sec7, unsigned int sec8)
{
	bool res = false;
	if (ctxt.size() == depth)
	{
		switch(depth)
		{
			case 1:
				if (sec0 == ctxt[0])
				res = true;
				break;
			case 2:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]))
				res = true;
				break;
			case 3:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]) && (sec2 == ctxt[2]))
				res = true;
				break;
			case 4:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]) && (sec2 == ctxt[2]) && (sec3 == ctxt[3]))
				res = true;
				break;
			case 5:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]) && (sec2 == ctxt[2]) && (sec3 == ctxt[3]) && (sec4 == ctxt[4]))
				res = true;
				break;
			case 6:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]) && (sec2 == ctxt[2]) && (sec3 == ctxt[3]) && (sec4 == ctxt[4]) && (sec5 == ctxt[5]))
				res = true;
				break;
			case 7:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]) && (sec2 == ctxt[2]) && (sec3 == ctxt[3]) && (sec4 == ctxt[4]) && (sec5 == ctxt[5]) && (sec6 == ctxt[6]))
				res = true;
				break;
			case 8:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]) && (sec2 == ctxt[2]) && (sec3 == ctxt[3]) && (sec4 == ctxt[4]) && (sec5 == ctxt[5]) && (sec6 == ctxt[6]) && (sec7 == ctxt[7]))
				res = true;
				break;
			case 9:
				if ((sec0 == ctxt[0]) && (sec1 == ctxt[1]) && (sec2 == ctxt[2]) && (sec3 == ctxt[3]) && (sec4 == ctxt[4]) && (sec5 == ctxt[5]) && (sec6 == ctxt[6]) && (sec7 == ctxt[7]) && (sec8 == ctxt[8]))
				res = true;
				break;
		}
	}
	return res;		
}


ReportGenerator::StringType ReportGenerator::getAnnotatedDoc(const StringType & Upptemplat)
{
	std::string templat = Upptemplat.operator const char*();
    typedef ReportParser::ReportTree_grammar<ReportGenerator::InternalStringType::const_iterator> ReportTree_grammar;
    ReportTree_grammar xml; // Our grammar
    ReportParser::ReportTree ast; // Our tree

    using asciiType::space;
    ReportGenerator::InternalStringType::const_iterator iter = templat.begin();
    ReportGenerator::InternalStringType::const_iterator end = templat.end();
    bool r = phrase_parse(iter, end, xml, space, ast);

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        ReportParser::Annotator::ReportTree_runner generator(*this);
        reportResult = "";
        generator(ast);
        return ReportGenerator::StringType(reportResult.c_str());
    }
    else
    {
        ReportGenerator::InternalStringType::const_iterator some = iter+30;
        ReportGenerator::InternalStringType context(iter, (some>end)?end:some);
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "stopped at: \": " << context << "...\"\n";
        std::cout << "-------------------------\n";
    	return templat;
    }
}



ReportGenerator::StringType ReportGenerator::generateReport(const StringType& upptemplat)
{
	std::string templat = upptemplat.operator const char*();
    typedef ReportParser::ReportTree_grammar<ReportGenerator::InternalStringType::const_iterator> ReportTree_grammar;
    ReportTree_grammar xml; // Our grammar
    ReportParser::ReportTree ast; // Our tree

    using asciiType::space;
    ReportGenerator::InternalStringType::const_iterator iter = templat.begin();
    ReportGenerator::InternalStringType::const_iterator end = templat.end();
    bool r = phrase_parse(iter, end, xml, space, ast);

    if (r && iter == end)
    {
//        LOG( "-------------------------");
//        LOG( "Parsing succeeded");
//        LOG( "-------------------------\n");
        ReportParser::Converter::ReportTree_runner generator(*this);
        reportResult = "";
        generator(ast);
        return ReportGenerator::StringType(reportResult.c_str());
    }
    else
    {
        ReportGenerator::InternalStringType::const_iterator some = iter+30;
        ReportGenerator::InternalStringType context(iter, (some>end)?end:some);
//        LOG( "-------------------------\n");
//        LOG( "Parsing failed\n");
//        LOG( "stopped at: \": " << context << "...\"\n");
//        LOG( "-------------------------\n");
    	return templat;
    }
}


ReportGenerator::StringType ReportGenerator::getDocStructure(const StringType & upptemplat)
{
	std::string templat = upptemplat.operator const char*();
    typedef ReportParser::ReportTree_grammar<ReportGenerator::InternalStringType::const_iterator> ReportTree_grammar;
    ReportTree_grammar xml; // Our grammar
    ReportParser::ReportTree ast; // Our tree

    using asciiType::space;
    ReportGenerator::InternalStringType::const_iterator iter = templat.begin();
    ReportGenerator::InternalStringType::const_iterator end = templat.end();
    bool r = phrase_parse(iter, end, xml, space, ast);

    if (r && iter == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        ReportParser::ReportTree_printer generator;
        reportResult = "";
        generator(ast);
        return ReportGenerator::StringType(reportResult.c_str());
    }
    else
    {
        ReportGenerator::InternalStringType::const_iterator some = iter+30;
        ReportGenerator::InternalStringType context(iter, (some>end)?end:some);
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "stopped at: \": " << context << "...\"\n";
        std::cout << "-------------------------\n";
    	return templat;
    }
}



