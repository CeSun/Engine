//
// Created by 孙策 on 2020/2/23.
//

#ifndef ENGINE_CTEXTURE_HPP
#define ENGINE_CTEXTURE_HPP

namespace GameClient{
    class CTexture {
    public:
        CTexture(const char* filename);
        ~CTexture();
        unsigned int getTextureId() const;
    private:
        unsigned int id;
        int height,width;
    };
}




#endif //ENGINE_CTEXTURE_HPP
