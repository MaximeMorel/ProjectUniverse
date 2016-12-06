#ifndef __SHADER_HPP__
#define __SHADER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
////////////////////////////////////////////////////////////////////////////////
class Shader;
using ShaderPtr = std::shared_ptr<Shader>;
////////////////////////////////////////////////////////////////////////////////
class Shader : public Resource
{
public:
    enum Type
    {
        VERTEX_SHADER = 0,
        TESS_CONTROL_SHADER,
        TESS_EVALUATION_SHADER,
        GEOMETRY_SHADER,
        FRAGMENT_SHADER,
        COMPUTE_SHADER
    };

    static ShaderPtr create(const std::string& name, Type t);

    virtual ~Shader() override;

    /// Get internal shader handle id
    uint32_t getShaderId() const;

    /// Compile the shader
    virtual bool compile();

    /// Returns the compilation status of the shader
    bool isCompiled() const;

protected:
    Shader(const std::string& name, Type t);

protected:
    uint32_t m_shaderId;    ///< shader program handle id
    bool m_isCompiled;      ///< is compiled flag
    bool m_compileError;    ///< errors occurred during compilation flag
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADER_HPP__
