#ifndef ANDROIDGLINVESTIGATIONS_MODEL_H
#define ANDROIDGLINVESTIGATIONS_MODEL_H

#include <vector>
#include "TextureAsset.h"

union Vector3 {
    struct {
        float x, y, z;
    };
    float idx[3];
};

union Vector2 {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
    float idx[2];
};

struct Vertex {
    constexpr Vertex(const Vector3 &inPosition, const Vector2 &inUV) : position(inPosition),
                                                                       uv(inUV) {}

    Vector3 position;
    Vector2 uv;
};

typedef uint16_t Index;

class Model {
public:
    inline Model(
            std::vector<Vertex> vertices,
            std::vector<Index> indices,
            std::shared_ptr<TextureAsset> spTexture)
            : vertices_(std::move(vertices)),
              indices_(std::move(indices)),
              spTexture_(std::move(spTexture)) {}

    inline const Vertex *getVertexData() const {
        return vertices_.data();
    }

    inline const size_t getIndexCount() const {
        return indices_.size();
    }

    inline const Index *getIndexData() const {
        return indices_.data();
    }

    inline const TextureAsset &getTexture() const {
        return *spTexture_;
    }

    inline void setPosition(float x, float y) {
        std::vector<Vertex> vertices = {
                // 第1引数のVector3は画面における座標を指定するための引数 第2引数のVector2は画像のどこからどこまでを読み込む、みたいな意味の引数
                Vertex(Vector3{(float)(0.2 + x), (float)(0.2 + y), 0}, Vector2{0, 0}), // 0
                Vertex(Vector3{(float)(-0.2 + x), (float)(0.2 + y), 0}, Vector2{1, 0}), // 1
                Vertex(Vector3{(float)(-0.2 + x), (float)(-0.2 + y), 0}, Vector2{1, 1}), // 2
                Vertex(Vector3{(float)(0.2 + x), (float)(-0.2 + y), 0}, Vector2{0, 1}) // 3
        };
        vertices_ = vertices;

        positionX = x;
        positionY = y;
    }


    [[nodiscard]] inline float getX() const {
        return positionX;
    }

    [[nodiscard]] inline float getY() const {
        return positionY;
    }

private:
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    std::shared_ptr<TextureAsset> spTexture_;
    float positionX;
    float positionY;
    float width;
    float height;
};

#endif //ANDROIDGLINVESTIGATIONS_MODEL_H