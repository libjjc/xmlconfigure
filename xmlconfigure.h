#ifndef XML_CONFIGURE_HH
#define XML_CONFIGURE_HH
#include <Export.h>
#include <ConfigureNode.h>
#include <tinyxml/tinyxml.h>

namespace xc{

    class XCAPI configure : public configure_node {

	public:
		typedef configure_node inherited;

    public:

        configure();

        configure(const std::string& name);

        configure(const configure& config);

        virtual ~configure();

    public:

		bool read(const char* file);

		bool read(const std::string& file);

		bool read(FILE* file);

		bool save(const char* file);

		bool save(const std::string& file);

		bool save(FILE* file);

	private:

		TiXmlDocument* _xml;

    };

    class configure_node_visitor : public TiXmlVisitor{

    public:

        configure_node_visitor(configure&);

        ~configure_node_visitor();

    public:

        typedef std::vector<configure_node*> configure_node_path;

    public:

        virtual bool VisitEnter(const TiXmlDocument& /*doc*/);

        virtual bool VisitExit(const TiXmlDocument& /*doc*/);

        virtual bool VisitEnter(const TiXmlElement& /*element*/, 
			const TiXmlAttribute* /*firstAttribute*/);

        virtual bool VisitExit(const TiXmlElement& /*element*/);

        virtual bool Visit(const TiXmlDeclaration& /*declaration*/);

        virtual bool Visit(const TiXmlText& /*text*/);

        virtual bool Visit(const TiXmlComment& /*comment*/);

        virtual bool Visit(const TiXmlUnknown& /*unknown*/);

    protected:

        configure_node_path _path;

        configure& _configure;

    };

	class configure_node_serializer{
	public:
		configure_node_serializer();

		~configure_node_serializer();
	public:

		bool serialize(const configure_node* node, TiXmlDocument* doc);

		bool serialize(const configure_node* node, TiXmlElement* root);

		bool serialize_attribute(const configure_node* node, TiXmlElement* element);

	};
}
#endif//XML_CONFIGURE_HH