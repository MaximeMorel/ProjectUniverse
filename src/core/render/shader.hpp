#ifndef __SHADER_HPP__
#define __SHADER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
////////////////////////////////////////////////////////////////////////////////
class Shader;
using ShaderPtr = std::shared_ptr<Shader>;
////////////////////////////////////////////////////////////////////////////////
class Shader : public ResourceFile
{
public:
    enum Type : uint8_t
    {
        VERTEX_SHADER = 0,
        TESS_CONTROL_SHADER,
        TESS_EVALUATION_SHADER,
        GEOMETRY_SHADER,
        FRAGMENT_SHADER,
        COMPUTE_SHADER
    };

protected:
    Shader(const std::string& name, const std::string& fileName, Type t);

public:
    static ShaderPtr create(const std::string& name, const std::string& fileName);

    virtual ~Shader() override;

    /// Get the sub search path for this resource
    static const char* getSearchPath();

    /// Get internal shader handle id
    uint32_t getShaderId() const;

    /// Compile the shader
    virtual bool compile();

    /// Returns the compilation status of the shader
    bool isCompiled() const;

    static const char* getShaderTypeString(Shader::Type type);

protected:
    virtual void printOn(Logger& o) const override;

protected:
    uint32_t m_shaderId;    ///< shader program handle id
    Shader::Type m_type;    ///< shader type (vertex, fragment, geometry, ...)
    bool m_isCompiled;      ///< is compiled flag
    bool m_compileError;    ///< errors occurred during compilation flag

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;

private:
    using super = ResourceFile;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADER_HPP__
