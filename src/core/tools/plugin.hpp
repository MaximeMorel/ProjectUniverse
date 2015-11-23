#ifndef __PLUGIN_HPP__
#define __PLUGIN_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource.hpp"
////////////////////////////////////////////////////////////////////////////////
class Plugin : public Resource
{
public:
    /// Load library
    /// \param filename dynamic library path
    Plugin(const std::string& filename);
    virtual ~Plugin() override;

    /// Load a symbol form the dynamic library
    /// \param symbolname Symbol to load from the dynamic library
    /// \return nullptr if symbolname could not be loaded
    void* getSymbol(const std::string& symbolname);

private:
    void* m_handle;     ///< handle for the dynamic library
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CRUSADERNOMERCY_HPP__
