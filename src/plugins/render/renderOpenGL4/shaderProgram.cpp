////////////////////////////////////////////////////////////////////////////////
#include "shaderProgram.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include "opengltools.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::ShaderProgramGL4(const std::string& name, const std::string& fileName)
    : super(name, fileName)
{
    m_shaderProgId = glCreateProgram();

    /*GLenum binaryFormat = 0;
    std::ifstream file(getFileName() + ".cache", std::ios_base::binary);
    std::vector<uint8_t> binary((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    GLsizei length=binary.size();
    const void* s = reinterpret_cast<const void*>(&binary.front());
    binaryFormat = *reinterpret_cast<GLenum*>(&binary.front());
    glProgramBinary(m_shaderProgId, binaryFormat, s + sizeof(binaryFormat), length - sizeof(binaryFormat));*/
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL4::~ShaderProgramGL4()
{
    // attached shaders are automatically detached
    glDeleteProgram(m_shaderProgId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramPtr ShaderProgramGL4::create(const std::string& name, const std::string& fileName)
{
    // check binary shader cache
    return std::make_shared<ShaderProgramGL4>(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::bind()
{
    if (!m_isLinked && !m_linkError)
        link();

    glUseProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::unbind()
{
    glUseProgram(0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::addShader(ShaderPtr shader)
{
    glFlushErrors();
    glAttachShader(m_shaderProgId, shader->getShaderId());
    GLenum err = glGetError();
    if (err == GL_NO_ERROR)
        m_shaders.push_back(shader);
    else
        log().log() << "addShader fail: " << err << "\n";
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderProgramGL4::link()
{
    if (m_isLinked)
        return true;

    if (m_linkError)
        return false;

    // check shaders are compiled
    bool allCompiled = true;
    for (ShaderPtr shader : m_shaders)
    {
        bool compiled = shader->compile();
        if (!compiled)
            allCompiled = false;
    }

    if (!allCompiled)
        log().log() << *this << "some stages did not compile.\n";

    glLinkProgram(m_shaderProgId);

    GLint status = GL_FALSE;
    glGetProgramiv(m_shaderProgId, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        m_isLinked = false;
        log().log() << *this << " link failed.\n";
        GLsizei logLength = 0;
        glGetProgramiv(m_shaderProgId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength > 0)
        {
            m_linkError = true;
            GLsizei charsWritten = 0;
            std::string infoLog(logLength, 0);
            glGetProgramInfoLog(m_shaderProgId, logLength, &charsWritten, &infoLog.front());
            if (charsWritten < logLength)
                infoLog.resize(charsWritten);
            log().log() << "Shader program log: " << infoLog.substr(0, charsWritten) << "\n";
        }
    }
    else
    {
        m_isLinked = true;
        m_linkError = false;
        log().log() << *this << " link success." << std::endl;

        GLint binLength = 0;
        glGetProgramiv(m_shaderProgId, GL_PROGRAM_BINARY_LENGTH, &binLength);
        if (binLength > 0)
        {
            std::vector<uint8_t> binary(binLength);
            GLsizei lenWritten = 0;
            GLenum binaryFormat = 0;
            glGetProgramBinary(m_shaderProgId, binary.size(), &lenWritten, &binaryFormat, &binary.front());
            if (lenWritten > 0)
            {
                if (lenWritten < binLength)
                    binary.resize(lenWritten);
                log().log() << "Shader program " << m_shaderProgId << " binary: " << binary.size() << " bytes, format: " << binaryFormat << "\n";
                std::ofstream file(getFileName() + ".cache", std::ios_base::binary);
                const char* s = reinterpret_cast<const char*>(&binaryFormat);
                file.write(s, sizeof(binaryFormat));
                s = reinterpret_cast<const char*>(&binary.front());
                file.write(s, binary.size());
            }
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::setUniform1f(uint32_t id, float v)
{
    glProgramUniform1f(m_shaderProgId, id, v);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::setUniform1f(const char* str, float v)
{
    GLint loc = glGetUniformLocation(m_shaderProgId, str);
    setUniform1f(loc, v);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::setUniform1i(uint32_t id, int32_t v)
{
    glProgramUniform1i(m_shaderProgId, id, v);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::setUniform1i(const char* str, int32_t v)
{
    GLint loc = glGetUniformLocation(m_shaderProgId, str);
    setUniform1f(loc, v);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::reload()
{
    log().log() << "Reload: " << *this << "\n";
    updateMtime();
    m_isLinked = false;
    m_linkError = false;
    for (ShaderPtr shader : m_shaders)
    {
        shader->reload();
    }
    link();
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL4::printOn(Logger& o) const
{
    o << "ShaderProgramGL4 " << m_shaderProgId << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
