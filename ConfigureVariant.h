#ifndef XML_CONFIGURE_VARIANT_HH
#define XML_CONFIGURE_VARIANT_HH

#include <Export.h>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
namespace xc{

    /**
     *
     */
    class XCAPI configure_variant_buffer{

    public:
        /**
         *
         */
        configure_variant_buffer();

        /**
         *
         */
        configure_variant_buffer(const configure_variant_buffer& cvb);

        /**
         *
         */
        configure_variant_buffer& operator=(const configure_variant_buffer& cvb);

        /**
         *
         */
        configure_variant_buffer(const char* addr, xcsize size);

        ~configure_variant_buffer();

    public:

        /**
         *
         */
        xcsize size()const;

        /**
         *
         */
        xcsize append_data(const char* data, xcsize size);

        /**
         *
         */
        xcsize append_char(char c, xcsize size);

        /**
         *
         */
        xcsize wseek(xcsize pos);

        /**
         *
         */
        xcsize rseek(xcsize pos);

        /**
         *
         */
        xcsize write(const char* data, xcsize size);

        /**
         *
         */
        xcsize write(xcsize pos, const char* data, xcsize size);

        /**
         *
         */
        xcsize insert(const char* data, xcsize size);

        /**
         *
         */
        xcsize insert(xcsize pos, const char* data, xcsize size);

        /**
         *
         */
        xcsize wpos()const;

        /**
         *
         */
        xcsize rpos()const;

        /**
         *
         */
        xcsize read(char*data, xcsize length, xcsize* size = NULL);

        /**
         *
         */
        xcsize read(xcsize pos, char* data, xcsize length, xcsize* size = NULL);

        /**
         *
         */
        xcsize capacity()const;

        /**
         *
         */
        bool isempty()const;

        /**
         *
         */
        void shrink();

        /**
         *
         */
        void clear();

        /**
         *
         */
        char* data(xcsize* size = NULL)const;

        /**
         *
         */
        void reset();

        /**
         *
         */
    protected:

        /**
         *
         */
        xcsize _capacity;

        /**
         *
         */
        xcsize _wpos;

        /**
         *
         */
        xcsize _rpos;

        /**
         *
         */
        char* _buf;

        /**
         *
         */
        xcsize _size;


    };

    /**
     *
     */
    class XCAPI configure_variant_stream{

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant_stream();

        /**
         *
         */
        configure_variant_stream(configure_variant_buffer* cvb);

        /**
         *
         */
        configure_variant_stream(const configure_variant_stream& cvs);

        /**
         *
         */
        ~configure_variant_stream();
    public:
        /**
         *
         */

        void attach_buffer(configure_variant_buffer* cvb);
        /**
         *
         */

    public:
        /**
         *
         */

        configure_variant_stream& operator<<(int value);

        /**
         *
         */
        configure_variant_stream& operator<<(unsigned int value);

        /**
         *
         */
        configure_variant_stream& operator<<(float value);

        /**
         *
         */
        configure_variant_stream& operator<<(double value);

        /**
         *
         */
        configure_variant_stream& operator<<(bool value);

        /**
         *
         */
        configure_variant_stream& operator<<(const char* value);

        /**
         *
         */
        configure_variant_stream& operator<<(const std::string& value);

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant_stream& operator>>(int& value);

        /**
         *
         */
        configure_variant_stream& operator>>(unsigned int& value);

        /**
         *
         */
        configure_variant_stream& operator>>(float& value);

        /**
         *
         */
        configure_variant_stream& operator>>(double& value);

        /**
         *
         */
        configure_variant_stream& operator>>(bool& value);

        /**
         *
         */
        configure_variant_stream& operator>>(std::string& value);

        /**
         *
         */
    protected:

        /**
         *
         */
        configure_variant_buffer* _buffer;


    };

    /**
     *
     */
    class XCAPI configure_variant{

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant();

        /**
         *
         */
        configure_variant(const configure_variant& cv);

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant(int value);

        /**
         *
         */
        configure_variant(unsigned int value);

        /**
         *
         */
        configure_variant(bool value);

        /**
         *
         */
        configure_variant(double value);

        /**
         *
         */
        configure_variant(float value);

        /**
         *
         */
        configure_variant(const char* value);

        /**
         *
         */
        configure_variant(const std::string& value);

        /**
         *
         */
    public:

        /**
         *
         */
        ~configure_variant();

        /**
         *
         */
    public:

        /**
         *
         */
        enum VAR_TYPE{
            TYPE_INT,
            TYPE_UINT,
            TYPE_BOOL,
            TYPE_DOUBLE,
            TYPE_FLOAT,
            TYPE_STRING,
            TYPE_UNKNOWN
        };

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant& operator=(const configure_variant& cv);

        /**
         *
         */
    public:

        /**
         *
         */
        configure_variant& operator=(int value);

        /**
         *
         */
        configure_variant& operator=(unsigned int value);

        /**
         *
         */
        configure_variant& operator=(float value);

        /**
         *
         */
        configure_variant& operator=(double value);

        /**
         *
         */
        configure_variant& operator=(bool value);

        /**
         *
         */
        configure_variant& operator=(const char* value);


        /**
         *
         */
        configure_variant& operator=(const std::string& value);

        /**
         *
         */
        operator int();

        /**
         *
         */
        operator unsigned int();

        /**
         *
         */
        operator float();

        /**
         *
         */
        operator double();

        /**
         *
         */
        operator bool();

        /**
         *
         */
        operator std::string();

        /**
         *
         */
    public:

        /**
         *
         */
        VAR_TYPE type()const;

        /**
         *
         */
    public:

        /**
         *
         */
        template<typename T> inline T value(){
            T t;
            t = *this;
            return t;
        }


    public:

        /**
         *
         */
        int to_int();

        /**
         *
         */
        unsigned int to_uint();

        /**
         *
         */
        bool to_bool();

        /**
         *
         */
        double to_double();

        /**
         *
         */
        float to_float();

        /**
         *
         */
        std::string to_string();

        /**
         *
         */
    public:

        /**
         *
         */
        template<typename T> inline T cast(){
            T t;
            t = *this;
            return t;
        }
        
        /**
         *
         */
        template<> inline int cast<int>(){
            return cast_int();
        }
        
        /**
         *
         */
        template<> inline unsigned int cast<unsigned int>(){
            return cast_uint();
        }
        
        /**
         *
         */
        template<> inline bool cast<bool>(){
            return cast_bool();
        }

        /**
         *
         */
        template<> inline double cast<double>(){
            return cast_double();
        }
        
        /**
         *
         */
        template<> inline float cast<float>(){
            return cast_float();
        }
        
        /**
         *
         */
        template<> inline std::string cast<std::string>(){
            return cast_string();
        }

        /**
         *
         */
    public:

        /**
         *
         */
        int cast_int();

        /**
         *
         */
        unsigned int cast_uint();
        /**
         *
         */
        bool cast_bool();

        /**
         *
         */
        double cast_double();

        /**
         *
         */
        float cast_float( );

        /**
         *
         */
        std::string cast_string( );

    protected:

        configure_variant_buffer _buffer;

        VAR_TYPE    _type;

    };



}

#endif//XML_CONFIGURE_VARIANT_HH
