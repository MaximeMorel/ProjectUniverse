////////////////////////////////////////////////////////////////////////////////
#include "shaderProgramGL.hpp"
#include "core/resource/resourceManager.hpp"
#include "core/log/logManager.hpp"
#include "core/tools/filetools.hpp"
#include "opengltools.hpp"
#include <GL/glew.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL::ShaderProgramGL(const std::string& name, const std::string& fileName)
    : super(name, fileName)
    , m_skipBinaryCache(false)
{
    m_shaderProgId = glCreateProgram();
}
////////////////////////////////////////////////////////////////////////////////
ShaderProgramGL::~ShaderProgramGL()
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
ShaderProgramPtr ShaderProgramGL::create(const std::string& name, const std::string& fileName)
{
    return std::make_shared<ShaderProgramGL>(name, fileName);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::bind()
{
    if (!m_isLinked && !m_linkError)
        link();

    glUseProgram(m_shaderProgId);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::unbind()
{
    glUseProgram(0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::addShader(ShaderPtr shader)
{
    /*glFlushErrors();
    glAttachShader(m_shaderProgId, shader->getShaderId());
    GLenum err = glGetError();
    if (err == GL_NO_ERROR)
        m_shaders.push_back(shader);
    else
        log().log() << "addShader fail: " << err << "\n";*/

    m_shaders.push_back(shader);
    if (shader->getShaderId() == 0)
    {
        m_attachDeferred.push_back(shader);
        log().log() << "addShader deferred: " << shader << "\n";
    }
    else
    {
        glAttachShader(m_shaderProgId, shader->getShaderId());
    }
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::removeShader(ShaderPtr shader)
{
    auto it = std::find(m_shaders.begin(), m_shaders.end(), shader);
    if (it != m_shaders.end())
    {
        m_shaders.erase(it);
        glDetachShader(m_shaderProgId, shader->getShaderId());
    }
    /*for (ShaderPtr shader :  m_shaders)
    {

    }*/
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderProgramGL::link()
{
    // this will try to link the shader program if not already done
    // binary cache will be tried first
    // if the binary cache cannot be loaded, it will be invalidated
    // and we will compile and link the normal way
    // shaders are not necessarily compiled when added to the program
    // so at that point, they will be compiled
    // then we try to link
    // if successful, save the binary cache

    if (m_isLinked)
        return true;

    if (m_linkError)
        return false;

    // try binary cache
    bool binaryCacheUsed = false;
    if (!m_skipBinaryCache)
    {
        std::string cacheFile = res().getUserSearchPath() + getFileName() + ".cache";
        std::ifstream file(cacheFile, std::ios::in | std::ios::binary);
        if (file)
        {
            // invalidate cache if shader program or shader files are newer
            struct stat st;
            int err = stat(cacheFile.c_str(), &st);
            if (err == 0 && st.st_mtime >= m_mtime)
            {
                bool cacheOutdated = false;
                for (ShaderPtr shader : m_shaders)
                {
                    if (shader->getMtime() > st.st_mtime)
                    {
                        cacheOutdated = true;
                        break;
                    }
                }

                if (!cacheOutdated)
                {
                    std::vector<uint8_t> binary((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                    GLsizei length = binary.size();
                    const uint8_t* s = reinterpret_cast<const uint8_t*>(&binary.front());
                    GLenum binaryFormat = *reinterpret_cast<GLenum*>(&binary.front());
                    const void* v = s + sizeof(binaryFormat);
                    glProgramBinary(m_shaderProgId, binaryFormat, v, length - sizeof(binaryFormat));
                    binaryCacheUsed = true;
                }
            }
        }
    }
    m_skipBinaryCache = false;

    if (!binaryCacheUsed)
    {
        // check shaders are compiled
        bool allCompiled = true;
        for (ShaderPtr shader : m_shaders)
        {
            bool compiled = shader->compile();
            if (!compiled)
                allCompiled = false;
        }

        for (ShaderPtr shader : m_attachDeferred)
        {
            glAttachShader(m_shaderProgId, shader->getShaderId());
        }
        m_attachDeferred.clear();

        if (!allCompiled)
            log().log() << *this << "some stages did not compile.\n";

        glLinkProgram(m_shaderProgId);
    }

    // check linking status
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

        // if binary cache is loaded but linking failed
        // invalidate the cache and relink
        if (binaryCacheUsed)
        {
            m_linkError = false;
            m_skipBinaryCache = true;
            link();
        }
    }
    else
    {
        m_isLinked = true;
        m_linkError = false;
        log().log() << *this << " link success.";
        if (binaryCacheUsed)
            log().log() << "(using binary cache)";
        log().log() << std::endl;

        // save binary in cache if successful
        if (!binaryCacheUsed)
        {
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
                    std::string binaryCachePath = res().getUserSearchPath() + getFileName() + ".cache";
                    std::ofstream file(binaryCachePath, std::ios::out | std::ios::binary);
                    if (!file)
                    {
                        // try to mkdir, then reopen the file
                        size_t pos = binaryCachePath.rfind('/');
                        if (pos != std::string::npos)
                        {
                            FileTools::mkdir(binaryCachePath.substr(0, pos));
                            file = std::ofstream(binaryCachePath, std::ios::out | std::ios::binary);
                        }
                    }
                    if (file)
                    {
                        const char* s = reinterpret_cast<const char*>(&binaryFormat);
                        file.write(s, sizeof(binaryFormat));
                        s = reinterpret_cast<const char*>(&binary.front());
                        file.write(s, binary.size());
                    }
                    else
                    {
                        log().log() << "Cannot write binary cache: " << binaryCachePath << "\n";
                    }
                }
            }
        }
    }

    return true;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniform1f(uint32_t id, float v0)
{
    glProgramUniform1f(m_shaderProgId, id, v0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniform1f(const char* str, float v0)
{
    GLint loc = glGetUniformLocation(m_shaderProgId, str);
    setUniform1f(loc, v0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniform2f(uint32_t id, float v0, float v1)
{
    glProgramUniform2f(m_shaderProgId, id, v0, v1);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniform2f(const char* str, float v0, float v1)
{
    GLint loc = glGetUniformLocation(m_shaderProgId, str);
    setUniform2f(loc, v0, v1);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniform1i(uint32_t id, int32_t v0)
{
    glProgramUniform1i(m_shaderProgId, id, v0);
    glUniform1i(id, v0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniform1i(const char* str, int32_t v0)
{
    GLint loc = glGetUniformLocation(m_shaderProgId, str);
    setUniform1i(loc, v0);
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniformMat4f(uint32_t id, const Mat4f& m)
{
    glProgramUniformMatrix4fv(m_shaderProgId, id, 1, GL_FALSE, m.getArray());
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::setUniformMat4f(const char* str, const Mat4f& m)
{
    GLint loc = glGetUniformLocation(m_shaderProgId, str);
    setUniformMat4f(loc, m);
}
////////////////////////////////////////////////////////////////////////////////
bool ShaderProgramGL::reload()
{
    bool shaderProgOutdated = ShaderProgram::reload();

    bool shadersOutDated = false;
    for (ShaderPtr shader : m_shaders)
    {
        if (shader->reload())
            shadersOutDated = true;
    }
    if (shaderProgOutdated || shadersOutDated)
    {
        log().log() << "Reload: " << *this << "\n";
        m_isLinked = false;
        m_linkError = false;
        link();
        return true;
    }
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void ShaderProgramGL::printOn(Logger& o) const
{
    o << "ShaderProgramGL " << m_shaderProgId << " " << getName();
}
////////////////////////////////////////////////////////////////////////////////
