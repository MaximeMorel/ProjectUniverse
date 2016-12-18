#ifndef __AUDIOCODEC_HPP__
#define __AUDIOCODEC_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "core/library.hpp"
#include "core/codecs/codec.hpp"
////////////////////////////////////////////////////////////////////////////////
class AudioCodec : public Codec
{
public:
    AudioCodec(Engine& engine);
    ~AudioCodec() override;

    /*virtual bool load(SoundPtr sound);
    virtual bool load(Sound* sound);
    virtual bool save(SoundPtr sound, const std::string& filePath);
    virtual bool save(Sound* sound, const std::string& filePath);*/
};
////////////////////////////////////////////////////////////////////////////////
#endif // __AUDIOCODEC_HPP__
