#ifndef __SHADERPROGRAM_HPP__
#define __SHADERPROGRAM_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/resource/resourceFile.hpp"
#include "shader.hpp"
#include "core/math/mat3.hpp"
#include "core/math/mat4.hpp"
#include "core/math/vec2.hpp"
#include "core/math/vec3.hpp"
#include "core/math/vec4.hpp"
#include "core/engine_export.h"
#include <string>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
class ShaderProgram;
using ShaderProgramPtr = std::shared_ptr<ShaderProgram>;
////////////////////////////////////////////////////////////////////////////////
class ENGINE_EXPORT ShaderProgram : public ResourceFile
{
protected:
    ShaderProgram(const std::string& name, const std::string& fileName);

public:
    static ShaderProgramPtr create(const std::string& name, const std::string& fileName);

    virtual ~ShaderProgram() override;

    /// Get the sub search path for this resource
    static const char* getSearchPath();

    /// Get internal shader program handle id
    uint32_t getProgId() const;

    /// Bind / activate the shader program
    virtual void bind();

    /// Unbind / deactivate the shader program
    virtual void unbind();

    /// Add a shader to the shader program
    virtual void addShader(ShaderPtr shader);

    /// Remove a shader to the shader program
    virtual void removeShader(ShaderPtr shader);

    /// Link the program. Will try to compile attached shaders if not done already
    virtual bool link();

    virtual void setUniform1f(uint32_t id, float v0);
    virtual void setUniform1f(const char* str, float v0);

    virtual void setUniform2f(uint32_t id, float v0, float v1);
    virtual void setUniform2f(const char* str, float v0, float v1);

    virtual void setUniform1i(uint32_t id, int32_t v0);
    virtual void setUniform1i(const char* str, int32_t v0);

    virtual void setUniformMat4f(uint32_t id, const Mat4f& m);
    virtual void setUniformMat4f(const char* str, const Mat4f& m);

    virtual bool reload() override;

protected:
    virtual void printOn(Logger& o) const override;

protected:
    uint32_t m_shaderProgId;            ///< shader program handle id
    bool m_isLinked;                    ///< is linked flag
    bool m_linkError;                   ///< errors occurred during linkage flag
    std::vector<ShaderPtr> m_shaders;   ///< attached shaders

public:
    virtual ResourceType& dyntype() override { return type; }
    virtual const ResourceType& dyntype() const override { return type; }
    static ResourceType type;

private:
    using super = ResourceFile;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __SHADERPROGRAM_HPP__
