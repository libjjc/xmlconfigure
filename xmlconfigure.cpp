#include <xmlconfigure.h>

namespace xc{

	configure::configure():inherited(){
        _xml = new TiXmlDocument();
	}

    configure::configure(const std::string& name) : inherited(name){
        _xml = new TiXmlDocument();
    }

	configure::configure(const configure& config):inherited(config){
        if (NULL != _xml){
            delete _xml;
        }
		_xml = new TiXmlDocument(*config._xml);
	}

	configure::~configure(){
        delete _xml;
	}

	bool configure::read(const char* file){
		if (false == _xml->LoadFile(file)){
			return false;
		}
		return _xml->Accept(&configure_node_visitor(*this));
	}

	bool configure::read(const std::string& file){
		if (false == _xml->LoadFile(file.c_str())){
			return false;
		}
		return _xml->Accept(&configure_node_visitor(*this));
	}

	bool configure::read(FILE* file){
		if (false == _xml->LoadFile(file)){
			return false;
		}
		return _xml->Accept(&configure_node_visitor(*this));
	}

    bool configure::save(const char* file){
        configure_node_serializer cns;
        if (false == cns.serialize(this, _xml)){
            return false;
        }
        return _xml->SaveFile(file);
    }

	bool configure::save(const std::string& file){
        configure_node_serializer cns;
        if (false == cns.serialize(this, _xml )){
            return false;
        }
		return _xml->SaveFile(file);
	}

	bool configure::save(FILE* file){
        configure_node_serializer cns;
        if (false == cns.serialize(this, _xml )){
            return false;
        }
		return _xml->SaveFile(file);
	}

    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    configure_node_visitor::configure_node_visitor(configure& config)
        :_configure(config){

    }

    configure_node_visitor::~configure_node_visitor(){

    }

    bool configure_node_visitor::VisitEnter(const TiXmlDocument& doc){
        assert(_path.empty());
        return true;
    }

    bool configure_node_visitor::VisitExit(const TiXmlDocument& doc){
        assert(_path.empty());
        return true;
    }

    bool configure_node_visitor::VisitEnter(const TiXmlElement& element, 
        const TiXmlAttribute* firstAttribute){
        configure_node* node = NULL;
        if (_path.empty()){
            node = &_configure;
			node->set_name(element.Value());
        }
        else{
            node = &(_path[_path.size()-1]->field<C>(element.Value()));
        }
		const TiXmlAttribute* attr = firstAttribute;
		while (attr){
			configure_variant& cv = node->attr<C>(attr->Name());
			cv = std::string(attr->Value());
			attr = attr->Next();
		}
		_path.push_back(node);
        return true;
    }

    bool configure_node_visitor::VisitExit(const TiXmlElement& element){
		_path.pop_back();
        return true;
    }

    bool configure_node_visitor::Visit(const TiXmlDeclaration& declaration){
        return true;
    }

    bool configure_node_visitor::Visit(const TiXmlText& text){
		(*_path.rend())->set_text(text.Value());
        return true;
    }

    bool configure_node_visitor::Visit(const TiXmlComment& comment){
        return true;
    }

    bool configure_node_visitor::Visit(const TiXmlUnknown& unknown){
        return true;
    }


	//============================================================================
	//============================================================================
	//============================================================================
	//============================================================================
	//============================================================================
	//============================================================================

	configure_node_serializer::configure_node_serializer(){

	}


	configure_node_serializer::~configure_node_serializer(){

	}

	bool configure_node_serializer::serialize(const configure_node* node, TiXmlDocument* doc){
		if (NULL == node || NULL == doc){
			return false;
		}
		doc->Clear();

		TiXmlElement* root = new TiXmlElement(node->name().c_str());
		
		if (false == serialize(node, root)){
			delete root;
			root = NULL;
			return false;
		}
		doc->LinkEndChild(root);
        return true;
	}

	bool configure_node_serializer::serialize(const configure_node* node,TiXmlElement* root){
		if (NULL == node || NULL == root){
			return false;
		}

        if (false == serialize_attribute(node, root)){
            return false;
        }

		for (std::size_t n = 0; n < node->children().size(); n++){
			configure_node cn = node->children()[n];
            TiXmlElement* element = new TiXmlElement(cn.name().c_str());
			if (false == serialize(&cn, element)){
                delete element;
				return false;
			}
            root->LinkEndChild(element);
		}
		return true;
	}

	bool configure_node_serializer::serialize_attribute(const configure_node* node,TiXmlElement* element){
		if (NULL == node || NULL == element){
			return false;
		}
		for (std::size_t n = 0; n < node->attributes().size(); n++){
			std::string name = node->attributes()[n].name;
			configure_variant var = node->attributes()[n].variant;
			switch (var.type()){
			case configure_variant::TYPE_INT:
				element->SetAttribute(name.c_str(), var.value<int>());
				break;
			case configure_variant::TYPE_UINT:
				element->SetAttribute(name.c_str(), var.value<unsigned int>());
				break;
			case configure_variant::TYPE_BOOL:
				element->SetAttribute(name.c_str(), var.value<bool>() ? "true" : "false");
				break;
			case configure_variant::TYPE_DOUBLE:
				element->SetDoubleAttribute(name.c_str(), var.value<double>());
				break;
			case configure_variant::TYPE_FLOAT:
				element->SetDoubleAttribute(name.c_str(), var.value<float>());
				break;
			case configure_variant::TYPE_STRING:
				element->SetAttribute(name.c_str(), var.value<std::string>().c_str());
                break;
			case configure_variant::TYPE_UNKNOWN:
				return false;
			default:
				break;
			}
		}
		return true;
	}
}




















