#ifndef __SHADER_HPP__
#define __SHADER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
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

    Shader(const std::string& name, Type t);
    virtual ~Shader() override;

    uint32_t getShaderId() const;

protected:
    uint32_t m_shaderId;
};
////////////////////////////////////////////////////////////////////////////////
using ShaderPtr = std::shared_ptr<Shader>;
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADER_HPP__
