#ifndef __SHADER_OPENGL4_HPP__
#define __SHADER_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/shader.hpp"
#include "opengltools.hpp"
////////////////////////////////////////////////////////////////////////////////
class ShaderGL4 : public Shader
{
public:
    static ShaderPtr create(const std::string& name, Type t);
    ShaderGL4(const std::string& name, Type t);
    virtual ~ShaderGL4() override;

    virtual bool compile() override;

private:
    class ShaderTypeMapping
    {
    public:
        ShaderTypeMapping();
        uint32_t get(Type t);
    private:
        uint32_t m_mapping[6];
    };

    ShaderTypeMapping m_shaderTypeMapping;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADER_OPENGL4_HPP__
