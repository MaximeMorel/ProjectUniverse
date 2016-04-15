////////////////////////////////////////////////////////////////////////////////
#include "protector.hpp"
#include <cppunit/Exception.h>
#include <cppunit/extensions/TypeInfoHelper.h>
////////////////////////////////////////////////////////////////////////////////
bool DefaultProtector::protect(const CppUnit::Functor &functor, const CppUnit::ProtectorContext &context)
{
    try
    {
        return functor();
    }
    catch (const CppUnit::Exception &failure)
    {
        reportFailure(context, failure);
    }
    catch (const std::exception &e)
    {
        std::string shortDescription( "uncaught exception of type " );
    #if CPPUNIT_USE_TYPEINFO_NAME
        shortDescription += CppUnit::TypeInfoHelper::getClassName(typeid(e));
    #else
        shortDescription += "std::exception (or derived).";
    #endif
        CppUnit::Message message(shortDescription, e.what());
        reportError(context, message );
    }
    catch ( ... )
    {
        reportError(context, CppUnit::Message("uncaught exception of unknown type"));
    }

    return false;
}
////////////////////////////////////////////////////////////////////////////////
