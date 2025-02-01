#include "SceneNode.h"

SceneNode::SceneNode()
    : transformation(glm::mat4(1.0f))
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::setMeshRenderer(const std::shared_ptr<MeshRenderer>& meshRenderer_)
{
    meshRenderer = meshRenderer_;
}

void SceneNode::addChild(const std::shared_ptr<SceneNode>& child)
{
    children.push_back(child);
}

void SceneNode::setTransformation(const glm::mat4& transformation_)
{
    transformation = transformation_;
}

void SceneNode::render(const glm::mat4& parentTransform)
{
    glm::mat4 globalTransform = parentTransform * transformation;

    if (meshRenderer)
    {
        meshRenderer->getMaterial()->bind();
        meshRenderer->getMaterial()->linkMatrixToShader("M", &globalTransform[0][0]);
        meshRenderer->render();
        meshRenderer->getMaterial()->unbind();
    }

    for (const auto& child : children)
    {
        child->render(globalTransform);
    }
}