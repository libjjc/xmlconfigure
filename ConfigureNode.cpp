#include <ConfigureNode.h>

namespace xc{

    const char G[] = "G";

    const char C[] = "C";

    const char GOC[] = "GOC";

    const char policy_apply_on_node[] = "policy_apply_on_node";

    const char policy_apply_on_attr[] = "policy_apply_on_attr";


    configure_node::configure_node(){
        _name = "";
        _text = "";
    }

    configure_node::configure_node(const std::string& name,const std::string& text){
        _name = name;
        _text = text;
    }

    configure_node::configure_node(const configure_node& node){
        _name = node._name;
        _text = node._text;
        _children.assign(node._children.begin(), node._children.end());
        _field.assign(node._field.begin(), node._field.end());
    }

    configure_node& configure_node::operator=(const configure_node& node){
        _name = node._name;
        _text = node._text;
        _children.assign(node._children.begin(), node._children.end());
        _field.assign(node._field.begin(), node._field.end());
        return *this;
    }

    configure_node::~configure_node(){

    }

    const std::string& configure_node::text()const{
        return _text;
    }

    void configure_node::set_text(const std::string& name){
        _text = name;
    }

    const std::string& configure_node::name()const{
        return _name;
    }

    void configure_node::set_name(const std::string& name){
        _name = name;
    }

	configure_variant& configure_node::operator[](const char* attr_name){
		return *get_attr(attr_name);
	}

	/**
	 *
	 */
	configure_variant& configure_node::operator[](const std::string& attr_name){
		return *get_attr(attr_name);
	}

	configure_variant& configure_node::operator[](unsigned int index){
		return _field[index].variant;
	}

	configure_node& configure_node::operator()(const char* field_name){
		std::string str_field(field_name);
		std::size_t s_index = 0;
		std::size_t e_index = 0;
		configure_node* node = this;
		while (std::string::npos != (e_index = str_field.find_first_of('.', s_index))){
			node = node->get_node(str_field.substr(s_index, e_index - s_index));
			s_index = e_index+1;
		}
		node = node->get_node(str_field.substr(s_index, str_field.size() - s_index));
		return *node;
	}

	configure_node& configure_node::operator()(const std::string& field_name){
		std::size_t s_index = 0;
		std::size_t e_index = 0;
		configure_node* node = this;
		while (field_name.size() != (e_index = field_name.find_first_of('.', s_index))){
			node = node->get_node(field_name.substr(s_index, e_index - s_index));
			s_index = e_index+1;
		}
		node = node->get_node(field_name.substr(s_index, field_name.size() - s_index));
		return *node;
	}

	configure_node& configure_node::operator()(const char* field_name, unsigned int index){
		unsigned int found = 0;
		for (unsigned int n = 0; n < _children.size(); n++){
			if (_children[n].name() == field_name ){
				if (found == index){
					return _children[n];
				}
				found++;
			}
		}
		return *(configure_node*)(NULL);
	}

	configure_node& configure_node::operator()(const std::string& field_name, unsigned int index){
		unsigned int found = 0;
		for (unsigned int n = 0; n < _children.size(); n++){
			if (_children[n].name() == field_name ){
				if (found == index){
					return _children[n];
				}
				found++;
			}
		}
		return *(configure_node*)(NULL);
	}

	configure_node& configure_node::operator()(unsigned int index){
		return _children[index];
	}

    configure_node_list configure_node::fields(const char* identity){
        configure_node_list cnl;
        configure_node_list::iterator itr = _children.begin();
        for (; itr != _children.end(); itr++){
            if (itr->name() == identity){
                cnl.push_back(*itr);
            }
        }
        return cnl;
    }

    configure_node* configure_node::get_node(const std::string& name){
        for (std::size_t n = 0; n < _children.size(); n++){
            if (_children[n].name() == name){
                return &_children[n];
            }
        }
       
        return NULL;
    }

    configure_node* configure_node::create_node(const std::string& name){
        _children.push_back(configure_node(name));
        return &(_children[_children.size() - 1]);
    }

    configure_node* configure_node::get_or_create_node(const std::string& name){
        configure_node* node = get_node(name);
        if (NULL == node){
            node = create_node(name);
        }
        return node;
    }

    configure_variant* configure_node::get_attr(const std::string& name){
		for (std::size_t n = 0; n < _field.size(); n++){
			if (_field[n].name == name){
				return &_field[n].variant;
			}
		}
        
        return NULL;
    }

    configure_variant* configure_node::create_attr(const std::string& name){
		for (std::size_t n = 0; n < _field.size(); n++){
			if (_field[n].name == name){
				_field[n].variant = configure_variant();
				return &_field[n].variant;
			}
		}
        configure_attr_node can;
        can.name = name;
        can.variant = configure_variant();
		_field.push_back(can);
		return &_field[_field.size() - 1].variant;
    }

    configure_variant* configure_node::get_or_create_attr(const std::string& name){
        configure_variant* attr = get_attr(name);
        if (NULL == attr){
            attr = create_attr(name);
        }
        return attr;
    }

	const configure_node_list& configure_node::children()const{
		return _children;
	}

	const configure_attr_list& configure_node::attributes()const{
		return _field;
	}


}