#ifndef XML_CONFIGURE_EXPORT_HH
#define XML_CONFIGURE_EXPORT_HH

#if defined(_MSC_VER) && defined(XC_DISABLE_MSVC_WARNINGS)
#pragma warning( disable : 4244 )
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#pragma warning( disable : 4512 )
#pragma warning( disable : 4267 )
#pragma warning( disable : 4702 )
#pragma warning( disable : 4511 )
#endif

#if defined(_MSC_VER) || defined(__CYGWIN__) || defined(__MINGW32__) || defined( __BCPLUSPLUS__)  || defined( __MWERKS__)
#  if defined( XC_LIBRARY_STATIC )
#    define XCAPI
#  elif defined( XC_LIBRARY )
#    define XCAPI   __declspec(dllexport)
#  else
#    define XCAPI   __declspec(dllimport)
#  endif
#else
#  define XCAPI
#endif

#ifdef _MSC_VER
# if (_MSC_VER >= 1300)
#  define __STL_MEMBER_TEMPLATES
# endif
#endif


#ifndef NULL
#ifdef  __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

namespace xc{
    typedef unsigned int xcsize;
}

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#endif//XML_CONFIGURE_EXPORT_HH