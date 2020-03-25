//
// Created by 孙策 on 2020/2/23.
//

#ifndef ENGINE_CTEXTURE_HPP
#define ENGINE_CTEXTURE_HPP

#include <string>
namespace GameClient{
    class CTexture {
    public:
        CTexture(const std::string& filename);
        ~CTexture();

        // 获取纹理OpenGl纹理id
        unsigned int get_id() const;

        // 获取纹理宽度
        int get_width() const {
            return width;
        }
        // 获取纹理高度
        int get_height() const {
            return height;
        }
    private:
        unsigned int id;
        int height,width;
    };
}




#endif //ENGINE_CTEXTURE_HPP
