////////////////////////////////////////////////////////////////////////////////
#include "fboGL.hpp"
#include "textureGL.hpp"
#include "core/resource/resourceManager.hpp"
#include <GL/glew.h>
////////////////////////////////////////////////////////////////////////////////
FBOGL::FBOGL(const std::string& name)
    : FBO(name)
    , m_fboId(0)
{
    glGenFramebuffers(1, &m_fboId);
}
////////////////////////////////////////////////////////////////////////////////
FBOGL::~FBOGL()
{
    glDeleteFramebuffers(1, &m_fboId);

    if (isEnginemanaged())
    {
        log().log() << __FUNCTION__ << ": " << *this << std::endl;
        res().delResource(this);
    }
}
////////////////////////////////////////////////////////////////////////////////
FBOPtr FBOGL::create(const std::string& name)
{
    return std::make_shared<FBOGL>(name);
}
////////////////////////////////////////////////////////////////////////////////
GLuint FBOGL::getFboId() const
{
    return m_fboId;
}
////////////////////////////////////////////////////////////////////////////////
void FBOGL::resize(uint32_t x, uint32_t y)
{
    FBO::resize(x, y);

    for (auto& tex : m_textures)
    {
        if (tex)
        {
            tex->resize(m_resolution);
        }
    }

    if (m_depthTexture)
    {
        m_depthTexture->resize(m_resolution);
    }
}
////////////////////////////////////////////////////////////////////////////////
void FBOGL::attach(TexturePtr tex, uint32_t attachement)
{
    if (m_textures.size() <= attachement)
    {
        m_textures.resize(attachement + 1);
    }

    m_textures[attachement] = tex;
    if (tex)
    {
        Vec3ui res3d = tex->getResolution();
        Vec2ui res2d(res3d.x, res3d.y);
        if (res2d != m_resolution)
        {
            tex->resize(m_resolution);
        }
        TextureGL* texGL = static_cast<TextureGL*>(tex.get());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachement, GL_TEXTURE_2D, texGL->getTextureId(), 0);
    }
}
////////////////////////////////////////////////////////////////////////////////
void FBOGL::attachDepth(TexturePtr tex)
{
    m_depthTexture = tex;
    if (m_depthTexture)
    {
        Vec3ui res3d = m_depthTexture->getResolution();
        Vec2ui res2d(res3d.x, res3d.y);
        if (res2d != m_resolution)
        {
            m_depthTexture->resize(m_resolution);
        }
        TextureGL* texGL = static_cast<TextureGL*>(m_depthTexture.get());
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, texGL->getTextureId(), 0);
    }
}
////////////////////////////////////////////////////////////////////////////////
void FBOGL::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fboId);
}
////////////////////////////////////////////////////////////////////////////////
void FBOGL::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
////////////////////////////////////////////////////////////////////////////////
void FBOGL::printOn(Logger& o) const
{
    o << "FBOGL " << m_fboId;
}
////////////////////////////////////////////////////////////////////////////////
