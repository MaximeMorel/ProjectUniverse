#ifndef __CODECMANAGER_HPP__
#define __CODECMANAGER_HPP__
////////////////////////////////////////////////////////////////////////////////"
#include "imageCodec.hpp"
////////////////////////////////////////////////////////////////////////////////
class CodecManager
{
public:
    CodecManager();
    ~CodecManager();

    void addImageCodec(ImageCodec* codec);
    void removeImageCodec(ImageCodec* codec);
    std::vector<ImageCodec*> getCodecs();

private:
    std::vector<ImageCodec*> m_imageCodecs;
};
////////////////////////////////////////////////////////////////////////////////
#endif // __CODECMANAGER_HPP__
