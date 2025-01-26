

namespace ReportParser
{
    ///////////////////////////////////////////////////////////////////////////
    //  Print out the mini xml tree
    ///////////////////////////////////////////////////////////////////////////
    int const tabsize = 4;

    void tab(int indent)
    {
        for (int i = 0; i < indent; ++i)
            std::cout << ' ';
    }

    struct ReportTree_printer
    {
        ReportTree_printer(int indent = 0)
          : indent(indent)
        {
        }

        void operator()(ReportTree const& xml) const;

        int indent;
    };

    struct ReportTree_node_printer : boost::static_visitor<>
    {
        ReportTree_node_printer(int indent, const ReportGenerator::DepthContextType& _ctxt )
          : indent(indent)
          , ctxt(_ctxt)
        {
        }

        // go to next node
        void operator()( ReportTree const& xml) const
        {
            ReportTree_printer(indent+tabsize)(xml);
        }

        // print text
        void operator()(std::string const& text) const
        {
            tab(indent+tabsize);
            std::cout << ctxt << "  text: \"" << text << '"' << std::endl;
        }

        int indent;
        const ReportGenerator::DepthContextType& ctxt;
    };

    void ReportTree_printer::operator()(ReportTree const& xml) const
    {
        tab(indent);
        std::cout << '{' << std::endl;
        tab(indent);
//        std::cout << "HEADER: ";
        BOOST_FOREACH(ReportTree_node const& node, xml.header)
        {
            boost::apply_visitor(ReportTree_node_printer(indent,xml.context) , node);
        }

        tab(indent);
//        std::cout << "BODY: ";
        BOOST_FOREACH(ReportTree_node const& node, xml.body)
        {
            boost::apply_visitor(ReportTree_node_printer(indent,xml.context), node);
        }

        tab(indent);
//        std::cout << "FOOTER: ";
        BOOST_FOREACH(ReportTree_node const& node, xml.footer)
        {
            boost::apply_visitor(ReportTree_node_printer(indent,xml.context), node);
        }

        tab(indent);
        std::cout << '}' << std::endl;
    }
};
