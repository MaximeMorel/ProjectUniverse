#ifndef __SHADERPROGRAM_OPENGL4_HPP__
#define __SHADERPROGRAM_OPENGL4_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/render/shaderProgram.hpp"
#include "shader.hpp"
#include <string>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgramGL4 : public ShaderProgram
{
public:
    ShaderProgramGL4(const std::string& name, const std::string& fileName);
    static ShaderProgramPtr create(const std::string& name, const std::string& fileName);

    virtual ~ShaderProgramGL4() override;

    virtual void bind() override;
    virtual void unbind() override;

    virtual void addShader(ShaderPtr shader) override;

    virtual bool link() override;

    virtual void setUniform1f(uint32_t id, float v) override;
    virtual void setUniform1f(const char* str, float v) override;
    virtual void setUniform1i(uint32_t id, int32_t v) override;
    virtual void setUniform1i(const char* str, int32_t v) override;

    void reload() override;

protected:
    virtual void printOn(Logger& o) const override;

private:
    bool checkLinkError();

private:
    uint32_t    m_mtimeCache;        ///< last cache file modification time

private:
    using super = ShaderProgram;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_OPENGL4_HPP__
