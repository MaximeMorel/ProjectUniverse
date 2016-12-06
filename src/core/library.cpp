////////////////////////////////////////////////////////////////////////////////
#include "library.hpp"
#include "core/log/logManager.hpp"
////////////////////////////////////////////////////////////////////////////////
Library::Library(Engine& engine)
    : m_engine(engine)
{

}
////////////////////////////////////////////////////////////////////////////////
Library::~Library()
{
    log().log() << __FUNCTION__ << std::endl;
    // clear resources allocated by this library
}
////////////////////////////////////////////////////////////////////////////////
Engine& Library::getEngine()
{
    return m_engine;
}
////////////////////////////////////////////////////////////////////////////////
LogManager& Library::log()
{
    return m_engine.log();
}
////////////////////////////////////////////////////////////////////////////////
