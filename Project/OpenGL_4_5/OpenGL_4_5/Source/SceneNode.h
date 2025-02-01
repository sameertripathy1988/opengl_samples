#pragma once
#include <vector>
#include <memory>
#include "glm\glm\glm.hpp"
#include "MeshRenderer.h"

class SceneNode
{
public:
    SceneNode();
    ~SceneNode();

    void setMeshRenderer(const std::shared_ptr<MeshRenderer>& meshRenderer);
    void addChild(const std::shared_ptr<SceneNode>& child);
    void setTransformation(const glm::mat4& transformation);

    void render(const glm::mat4& parentTransform = glm::mat4(1.0f));

private:
    std::shared_ptr<MeshRenderer> meshRenderer;
    std::vector<std::shared_ptr<SceneNode>> children;
    glm::mat4 transformation;
};