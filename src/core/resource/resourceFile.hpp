#ifndef __RESOURCEFILE_HPP__
#define __RESOURCEFILE_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "resource.hpp"
////////////////////////////////////////////////////////////////////////////////
class ResourceFile;
using ResourceFilePtr = std::shared_ptr<ResourceFile>;
////////////////////////////////////////////////////////////////////////////////
/// \brief Resource base class
////////////////////////////////////////////////////////////////////////////////
class ResourceFile : public Resource
{
protected:
    ResourceFile(const std::string& name, const std::string& fileName);

public:
    virtual ~ResourceFile() override;

    ////////////////////////////////////////////////////////////////////////////
    /// \brief Get resource file name
    /// \return std::string containing resource file name
    ////////////////////////////////////////////////////////////////////////////
    const std::string& getFileName() const;

protected:
    virtual void printOn(Logger& o) const override;

    void updateMtime();

private:
    std::string m_fileName;     ///< resource filename

protected:
    uint32_t    m_mtime;        ///< last file modification time

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;

private:
    using super = Resource;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __RESOURCEFILE_HPP__
