//
// Created by SunCe on 2020/2/2.
//

#ifndef ENGINE_CDEMO_H
#define ENGINE_CDEMO_H
namespace GameClient {
    class CDemo {
    public:
        void init();
        void draw();
    private:
        unsigned VAO,EBO;
        unsigned ShaderProgram;
    };
}
#endif //ENGINE_CDEMO_H
