#ifndef __CODECMANAGER_HPP__
#define __CODECMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////"
#include "audioCodec.hpp"
#include "imageCodec.hpp"
#include "meshCodec.hpp"
////////////////////////////////////////////////////////////////////////////////
class CodecManager
{
public:
    CodecManager();
    ~CodecManager();

    void addAudioCodec(AudioCodec* codec);
    void removeAudioCodec(AudioCodec* codec);
    std::vector<AudioCodec*>& getAudioCodecs();
    const std::vector<AudioCodec*>& getAudioCodecs() const;

    void addImageCodec(ImageCodec* codec);
    void removeImageCodec(ImageCodec* codec);
    std::vector<ImageCodec*>& getImageCodecs();
    const std::vector<ImageCodec*>& getImageCodecs() const;

    void addMeshCodec(MeshCodec* codec);
    void removeMeshCodec(MeshCodec* codec);
    std::vector<MeshCodec*>& getMeshCodecs();
    const std::vector<MeshCodec*>& getMeshCodecs() const;

private:
    std::vector<AudioCodec*> m_audioCodecs;
    std::vector<ImageCodec*> m_imageCodecs;
    std::vector<MeshCodec*> m_meshCodecs;
};
////////////////////////////////////////////////////////////////////////////////
/// Global codecs access
void setGlobalCodecs(CodecManager& codecs);
CodecManager& codecs();
////////////////////////////////////////////////////////////////////////////////
#endif // __CODECMANAGER_HPP__
