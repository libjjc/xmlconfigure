#include <ConfigureVariant.h>

namespace xc{

    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================

    configure_variant_buffer::configure_variant_buffer() :_capacity(8){
        _buf = new char[_capacity];
        memset(_buf, 0, _capacity);
        _wpos = 0;
        _rpos = 0;
        _size = 0;
    }

    configure_variant_buffer::configure_variant_buffer(const configure_variant_buffer& cvb){
        _buf = new char[cvb._size];
        memset(_buf, 0, _capacity);
        memcpy(_buf, cvb._buf, cvb._size);
        _wpos = cvb._wpos;
        _rpos = cvb._rpos;
        _size = cvb._size;
        _capacity = cvb._capacity;
    }

    configure_variant_buffer& configure_variant_buffer::operator=(const configure_variant_buffer& cvb){
        clear();
        if (_capacity != cvb._capacity){
            delete[]_buf;
            _capacity = cvb._capacity;
            _buf = new char[_capacity];
        }
        memset(_buf, 0, _capacity);
        memcpy(_buf, cvb._buf, cvb._size);
        _wpos = cvb._wpos;
        _rpos = cvb._rpos;
        _size = cvb._size;
        return *this;
    }

    configure_variant_buffer::configure_variant_buffer(const char* addr, xcsize size){
        _wpos = 0;
        _rpos = 0;
        _size = size;
        _capacity = xcsize(log2(size)) + 1;
        _buf = new char[_capacity];
        memset(_buf, 0, _capacity);
        memcpy(_buf, addr, size);
    }

    configure_variant_buffer::~configure_variant_buffer(){
        delete[]_buf;
        _buf = NULL;
    }

    xcsize configure_variant_buffer::size()const{
        return _size;
    }

    xcsize configure_variant_buffer::append_data(const char* data, xcsize size){
        xcsize newcapacity = _capacity;
        while (newcapacity < _size + size){
            newcapacity *= 2;
        }
        if (_capacity == newcapacity){
            memcpy(_buf + _size, data, size);
        }
        else{
            _capacity = newcapacity;
            char* newbuf = new char[_capacity];
            memset(newbuf, 0, _capacity);
            memcpy(newbuf, _buf, _size);
            memcpy(newbuf + _size, data, size);
            delete[]_buf;
            _buf = newbuf;
        }
        _size += size;
        _wpos = _size;
        return _wpos;
    }

    xcsize configure_variant_buffer::append_char(char c, xcsize size){
        xcsize newcapacity = _capacity;
        while (newcapacity < _size + size){
            newcapacity *= 2;
        }
        char* buf = new char[size];
        memset(buf, c, size);
        if (_capacity == newcapacity){
            memcpy(_buf + _size, buf, size);
        }
        else{
            _capacity = newcapacity;
            char* newbuf = new char[_capacity];
            memset(newbuf, 0, _capacity);
            memcpy(newbuf, _buf, _size);
            memcpy(newbuf + _size, buf, size);
            delete[]_buf;
            _buf = newbuf;
        }
        delete[]buf;
        buf = NULL;
        _size += size;
        _wpos = _size;
        return _wpos;
    }

    xcsize configure_variant_buffer::wseek(xcsize pos){
        return _wpos = pos;
    }

    xcsize configure_variant_buffer::rseek(xcsize pos){
        return _rpos = pos;
    }

    xcsize configure_variant_buffer::write(const char* data, xcsize size){
        xcsize newcapacity = _capacity;
        while (newcapacity < _wpos + size){
            newcapacity *= 2;
        }
        if (_capacity == newcapacity){
            memcpy(_buf + _wpos, data, size);
        }
        else{
            _capacity = newcapacity;
            char* buf = new char[_capacity];
            memset(buf, 0, _capacity);
            memcpy(buf, _buf, _wpos);
            memcpy(buf + _wpos, data, size);
            delete[]_buf;
            _buf = buf;
            buf = NULL;
        }
        _size = (_wpos + size)>_size ? (_wpos + size) : _size;
        _wpos = _wpos + size;
        return _wpos;
    }

    xcsize configure_variant_buffer::write(xcsize pos, const char* data, xcsize size){
        wseek(pos);
        return write(data, size);
    }

    xcsize configure_variant_buffer::insert(const char* data, xcsize size){
        xcsize newcapacity = _capacity;
        while (newcapacity < _size + size){
            newcapacity *= 2;
        }
        if (newcapacity == _capacity){
            memcpy(_buf + _wpos + size, _buf + _wpos, _size - _wpos);
            memcpy(_buf + _wpos, data, size);
        }
        else{
            _capacity = newcapacity;
            char* buf = new char[_capacity];
            memset(buf, 0, _capacity);
            memcpy(buf, _buf, _wpos);
            memcpy(buf + _wpos, data, size);
            memcpy(buf + _wpos + size, _buf + _wpos, _size - _wpos);
            delete[]_buf;
            _buf = buf;
            buf = NULL;
        }
        _size += size;
        _wpos += size;
        return _wpos;
    }

    xcsize configure_variant_buffer::insert(xcsize pos, const char* data, xcsize size){
        wseek(pos);
        return insert(data, size);
    }

    xcsize configure_variant_buffer::wpos()const{
        return _wpos;
    }

    xcsize configure_variant_buffer::rpos()const{
        return _rpos;
    }

    xcsize configure_variant_buffer::read(char* data, xcsize length, xcsize* size){
        xcsize real_size = (_rpos + length) > _size ? (_size - _rpos) : length;
        memcpy(data, _buf + _rpos, real_size);
        if (NULL != size){
            *size = real_size;
        }
        return _rpos += real_size;
    }

    xcsize configure_variant_buffer::read(xcsize pos, char* data, xcsize length, xcsize* size){
        rseek(pos);
        return read(data, length, size);
    }

    bool configure_variant_buffer::isempty()const{
        return _size == 0;
    }

    void configure_variant_buffer::shrink(){
        if (_capacity > _size){
            char* buf = new char[_size];
            memset(buf, 0, _size);
            memcpy(buf, _buf, _size);
            _capacity = _size;
            delete[]_buf;
            _buf = buf;
            buf = NULL;
        }
    }

    void configure_variant_buffer::clear(){
        delete[]_buf;
        _capacity = 8;
        _buf = new char[_capacity];
        memset(_buf, 0, _capacity);
        _size = 0;
        _wpos = 0;
        _rpos = 0;
    }

    char* configure_variant_buffer::data(xcsize* size)const{
        if (NULL != size){
            *size = _size;
        }
        return &_buf[0];
    }

    void configure_variant_buffer::reset(){
        _wpos = _rpos = 0;
    }

    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================

    configure_variant_stream::configure_variant_stream(){
        _buffer = NULL;
    }

    configure_variant_stream::configure_variant_stream(configure_variant_buffer* cvb){
        _buffer = cvb;
    }

    configure_variant_stream::configure_variant_stream(const configure_variant_stream& cvs){
        _buffer = cvs._buffer;
    }

    configure_variant_stream::~configure_variant_stream(){
        _buffer = NULL;
    }

    void configure_variant_stream::attach_buffer(configure_variant_buffer* cvb){
        _buffer = cvb;
    }

    configure_variant_stream& configure_variant_stream::operator<<(int value){
        typedef union _int_convertor{
            int value;
            char data[sizeof(int)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(int));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(unsigned int value){
        typedef union _int_convertor{
            unsigned int value;
            char data[sizeof(unsigned int)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(unsigned int));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(float value){
        typedef union _int_convertor{
            float value;
            char data[sizeof(float)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(float));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(double value){
        typedef union _int_convertor{
            double value;
            char data[sizeof(double)];
        }int_convertor;
        int_convertor ci;
        ci.value = value;
        _buffer->append_data(&ci.data[0], sizeof(double));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(bool value){
        char c = value ? '\1' : '\0';
        _buffer->append_data(&c, sizeof(bool));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(const char* value){
        _buffer->append_data(value, strlen(value));
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator<<(const std::string& value){
        _buffer->append_data(value.data(), value.length());
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(int& value){
        char data[sizeof(int)];
        _buffer->read(data, sizeof(int));
        typedef union _int_convertor{
            char data[sizeof(int)];
            int value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(int));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(unsigned int& value){
        char data[sizeof(unsigned int)];
        _buffer->read(data, sizeof(unsigned int));
        typedef union _int_convertor{
            char data[sizeof(unsigned int)];
            unsigned int value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(unsigned int));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(float& value){
        char data[sizeof(float)];
        _buffer->read(data, sizeof(float));
        typedef union _int_convertor{
            char data[sizeof(float)];
            float value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(float));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(double& value){
        char data[sizeof(double)];
        _buffer->read(data, sizeof(double));
        typedef union _int_convertor{
            char data[sizeof(double)];
            double value;
        }int_convertor;
        int_convertor ci;
        memcpy(&ci.data[0], &data[0], sizeof(double));
        value = ci.value;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(bool& value){
        char c;
        _buffer->read(&c, 1);
        value = c == '\0' ? false : true;
        return *this;
    }

    configure_variant_stream& configure_variant_stream::operator>>(std::string& value){
        xcsize length = _buffer->size() - _buffer->rpos();
        char* data = new char[length];
        _buffer->read(data, length);
        value.assign(data, length);
        delete[]data;
        data = NULL;
        return *this;
    }

    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================
    //=========================================================================


    configure_variant::configure_variant(){
        _type = TYPE_UNKNOWN;
    }

    configure_variant::configure_variant(const configure_variant& cv){
        _buffer = cv._buffer;
        _type = cv._type;
    }

    configure_variant& configure_variant::operator=(const configure_variant& cv){
        _buffer = cv._buffer;
        _type = cv._type;
        return *this;
    }

    configure_variant::configure_variant(int value){
        _type = TYPE_INT;
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(unsigned int value){
        _type = TYPE_UINT;
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(bool value){
        _type = TYPE_BOOL;
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(double value){
        _type = TYPE_DOUBLE;
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(float value){
        _type = TYPE_FLOAT;
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(const char* value){
        _type = TYPE_STRING;
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::configure_variant(const std::string& value){
        _type = TYPE_STRING;
        configure_variant_stream(&_buffer) << value;
    }

    configure_variant::~configure_variant(){

    }

    configure_variant& configure_variant::operator=(int value){
        _buffer.clear();
        _type = TYPE_INT;
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(unsigned int value){
        _buffer.clear();
        _type = TYPE_UINT;
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(float value){
        _buffer.clear();
        _type = TYPE_FLOAT;
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(double value){
        _buffer.clear();
        _type = TYPE_DOUBLE;
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(bool value){
        _buffer.clear();
        _type = TYPE_BOOL;
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(const char* value){
        _buffer.clear();
        _type = TYPE_STRING;
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant& configure_variant::operator=(const std::string& value){
        _buffer.clear();
        _type = TYPE_STRING;
        configure_variant_stream(&_buffer) << value;
        return *this;
    }

    configure_variant::operator bool(){
        bool result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator int(){
        int result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator unsigned int(){
        unsigned int result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator float(){
        float result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator double(){
        double result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::operator std::string(){
        std::string result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    configure_variant::VAR_TYPE configure_variant::type()const{
        return _type;
    }

    bool  configure_variant::to_bool(){
        bool result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    int configure_variant::to_int(){
        int result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    unsigned int configure_variant::to_uint(){
        unsigned int result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    float configure_variant::to_float(){
        float result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }

    double configure_variant::to_double(){
        double result;
        _buffer.rseek(0);
        configure_variant_stream(&_buffer) >> result;
        return result;
    }



    std::string configure_variant::to_string(){
        std::stringstream result;
        switch (_type)
        {
        case xc::configure_variant::TYPE_INT:
            result << value<int>();
            break;
        case xc::configure_variant::TYPE_UINT:
            result << value<unsigned int>();
            break;
        case xc::configure_variant::TYPE_BOOL:
            result << value<bool>();
            break;
        case xc::configure_variant::TYPE_DOUBLE:
            result << value<double>();
            break;
        case xc::configure_variant::TYPE_FLOAT:
            result << value<float>();
            break;
        case xc::configure_variant::TYPE_STRING:
            result << value<std::string>();
            break;
        case xc::configure_variant::TYPE_UNKNOWN:
            break;
        default:
            break;
        }
        return result.str();
    }

    int configure_variant::cast_int(){
        int result;
        switch (_type)
        {
        case xc::configure_variant::TYPE_INT:
            result = to_int();
            break;
        case xc::configure_variant::TYPE_UINT:
            result = static_cast<int>(to_uint());
            break;
        case xc::configure_variant::TYPE_BOOL:
            result = to_bool() ? 1 : 0;
            break;
        case xc::configure_variant::TYPE_DOUBLE:
            result = static_cast<int>(to_double());
            break;
        case xc::configure_variant::TYPE_FLOAT:
            result = static_cast<int>(to_float());
            break;
        case xc::configure_variant::TYPE_STRING:
            std::stringstream(to_string().data()) >> result;
            break;
        case xc::configure_variant::TYPE_UNKNOWN:
            result = 0;
            break;
        default:
            break;
        }
        return result;
    }

    unsigned int configure_variant::cast_uint(){
        unsigned int result;
        switch (_type)
        {
        case xc::configure_variant::TYPE_INT:
            result = to_uint();
            break;
        case xc::configure_variant::TYPE_UINT:
            result = to_uint();
            break;
        case xc::configure_variant::TYPE_BOOL:
            result = to_bool() ? 1 : 0;
            break;
        case xc::configure_variant::TYPE_DOUBLE:
            result = static_cast<unsigned int>(to_double());
            break;
        case xc::configure_variant::TYPE_FLOAT:
            result = static_cast<unsigned int>(to_float());
            break;
        case xc::configure_variant::TYPE_STRING:
            std::stringstream(to_string().data()) >> result;
            break;
        case xc::configure_variant::TYPE_UNKNOWN:
            result = 0;
            break;
        default:
            break;
        }
        return result;

    }

    bool configure_variant::cast_bool(){
        bool result = false;
        switch (_type)
        {
        case xc::configure_variant::TYPE_INT:
            result = to_int() ? true : false;
            break;
        case xc::configure_variant::TYPE_UINT:
            result = to_uint() ? true : false;
            break;
        case xc::configure_variant::TYPE_BOOL:
            result = to_bool();
            break;
        case xc::configure_variant::TYPE_DOUBLE:
            result = (to_double() > -DBL_EPSILON && to_double() < DBL_EPSILON) ? false : true;
            break;
        case xc::configure_variant::TYPE_FLOAT:
            result = (to_float() > -FLT_EPSILON && to_float() < FLT_EPSILON) ? false : true;
            break;
        case xc::configure_variant::TYPE_STRING:{

            std::string value = to_string();
            std::transform(value.begin(), value.end(), value.begin(), tolower);
            if (value == "true" || value == "yes" || value == "1"){
                result = true;
            }
            else if (value == "false" || value == "no" || value == "0"){
                result = false;
            }
            else{
                result = value == "" ? false : true;
            }
        }   break;
        case xc::configure_variant::TYPE_UNKNOWN:
            break;
        default:
            break;
        }
        return result;
    }

    double configure_variant::cast_double(){
        double result = 0.0;
        switch (_type)
        {
        case xc::configure_variant::TYPE_INT:
            result = static_cast<double>(to_int());
            break;
        case xc::configure_variant::TYPE_UINT:
            result = static_cast<double>(to_uint());
            break;
        case xc::configure_variant::TYPE_BOOL:
            result = to_bool() ? 1.0 : 0.0;
            break;
        case xc::configure_variant::TYPE_DOUBLE:
            result = to_double();
            break;
        case xc::configure_variant::TYPE_FLOAT:
            result = static_cast<double>(to_float());
            break;
        case xc::configure_variant::TYPE_STRING:
            std::stringstream(to_string().data()) >> result;
            break;
        case xc::configure_variant::TYPE_UNKNOWN:
            break;
        default:
            break;
        }
        return result;
    }

    float configure_variant::cast_float(){
        float result;
        switch (_type)
        {
        case xc::configure_variant::TYPE_INT:
            result = static_cast<float>(to_float());
            break;
        case xc::configure_variant::TYPE_UINT:
            result = static_cast<float>(to_float());
            break;
        case xc::configure_variant::TYPE_BOOL:
            result = to_bool() ? 1.f : 0.f;
            break;
        case xc::configure_variant::TYPE_DOUBLE:
            result = static_cast<float>(to_double());
            break;
        case xc::configure_variant::TYPE_FLOAT:
            result = to_float();
            break;
        case xc::configure_variant::TYPE_STRING:
            std::stringstream(to_string().data()) >> result;
            break;
        case xc::configure_variant::TYPE_UNKNOWN:
            break;
        default:
            break;
        }
        return result;
    }

    std::string configure_variant::cast_string(){
        std::string result;
        switch (_type)
        {
        case xc::configure_variant::TYPE_INT:
            std::stringstream(result) << to_int();
            break;
        case xc::configure_variant::TYPE_UINT:
            std::stringstream(result) << to_uint();
            break;
        case xc::configure_variant::TYPE_BOOL:
            std::stringstream(result) << to_bool();
            break;
        case xc::configure_variant::TYPE_DOUBLE:
            std::stringstream(result) << to_double();
            break;
        case xc::configure_variant::TYPE_FLOAT:
            std::stringstream(result) << to_float();
            break;
        case xc::configure_variant::TYPE_STRING:
            result = to_string();
            break;
        case xc::configure_variant::TYPE_UNKNOWN:
            break;
        default:
            break;
        }
        return result;
    }
}