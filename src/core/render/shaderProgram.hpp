#ifndef __SHADERPROGRAM_HPP__
#define __SHADERPROGRAM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resource.hpp"
#include "shader.hpp"
#include <string>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgram;
using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;
////////////////////////////////////////////////////////////////////////////////
class ShaderProgram : public Resource
{
public:
    ShaderProgram(const std::string& name,
                  std::initializer_list<ShaderPtr> shaders = std::initializer_list<ShaderPtr>());
    virtual ~ShaderProgram() override;

    static ShaderProgramPtr create(const std::string& name,
                                   std::initializer_list<ShaderPtr> shaders = std::initializer_list<ShaderPtr>());

    /// Get internal shader program handle id
    uint32_t getProgId() const;

    /// Bind / activate the shader program
    virtual void bind() const;

    /// Unbind / deactivate the shader program
    virtual void unbind() const;

    /// Add a shader to the shader program
    virtual void addShader(ShaderPtr shader);

    /// Link the program. Will try to compile attached shaders if not done already
    virtual bool link();

protected:
    virtual void printOn(Logger& o) const override;

protected:
    uint32_t m_shaderProgId;            ///< shader program handle id
    bool m_isLinked;                    ///< is linked flag
    bool m_linkError;                   ///< errors occurred during linkage flag
    std::vector<ShaderPtr> m_shaders;   ///< attached shaders
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_HPP__
