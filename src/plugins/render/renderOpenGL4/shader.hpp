#ifndef __SHADER_OPENGL4_HPP__
#define __SHADER_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/shader.hpp"
#include "opengltools.hpp"
////////////////////////////////////////////////////////////////////////////////
class ShaderGL4 : public Shader
{
protected:
    ShaderGL4(const std::string& name, const std::string& fileName, Type t);

public:
    static ShaderPtr create(const std::string& name, const std::string& fileName, Type t);
    static ShaderPtr createFromSource(const std::string& name, Type t, const std::string& src);
    virtual ~ShaderGL4() override;

    virtual bool compile() override;

protected:
    virtual void printOn(Logger& o) const override;

private:
    class ShaderTypeMapping
    {
    public:
        ShaderTypeMapping();
        uint32_t get(Type t);
    private:
        uint32_t m_mapping[6];
    };

private:
    // move that somewhere else (using memory for every shader...) or use static ?
    static ShaderTypeMapping m_shaderTypeMapping;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADER_OPENGL4_HPP__
