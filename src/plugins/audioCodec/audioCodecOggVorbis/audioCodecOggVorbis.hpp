#ifndef __AUDIOCODECOGGVORBIS_HPP__
#define __AUDIOCODECOGGVORBIS_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/plugin/iplugin.hpp"
#include "core/library.hpp"
#include "core/codecs/audioCodec.hpp"
#include <vorbis/vorbisfile.h>
#include <vector>
////////////////////////////////////////////////////////////////////////////////
extern "C" const PluginInfo* getPluginInfo();
////////////////////////////////////////////////////////////////////////////////
extern "C" Library* getLibInstance(Engine* engine);
////////////////////////////////////////////////////////////////////////////////
extern "C" void closeLibInstance();
////////////////////////////////////////////////////////////////////////////////
class PluginAudioCodecOggVorbis : public AudioCodec
{
public:
    PluginAudioCodecOggVorbis(Engine& engine);
    ~PluginAudioCodecOggVorbis();
};
////////////////////////////////////////////////////////////////////////////////
class AudioBufferOggVorbis : public AudioBuffer
{
public:
    AudioBufferOggVorbis(const std::string& fileName)
        : AudioBuffer(4096)
    {
        int ret = ov_fopen(fileName.c_str(), &m_vorbisFile);
        if (ret == 0)
        {

        }
        else if (ret == OV_EREAD)
        {

        }
        else if (ret == OV_ENOTVORBIS)
        {

        }
        else if (ret == OV_EVERSION)
        {

        }
        else if (ret == OV_EBADHEADER)
        {

        }
        else if (ret == OV_EFAULT)
        {

        }
    }

    ~AudioBufferOggVorbis()
    {
        int ret = ov_clear(&m_vorbisFile);
        if (ret != 0)
        {

        }
    }

    bool decode()
    {
        char* buffer = reinterpret_cast<char*>(&m_buffer.front());
        long ret = ov_read(&m_vorbisFile, buffer, getSize(), 0, 2, 1, nullptr);
        if (ret > 0)
        {
            return true;
        }
        else if (ret == 0) // EOF
        {

        }
        else if (ret == OV_HOLE)
        {

        }
        else if (ret == OV_EBADLINK)
        {

        }
        else if (ret == OV_EINVAL)
        {

        }
        return false;
    }

private:
    OggVorbis_File m_vorbisFile;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AUDIOCODECOGGVORBIS_HPP__
