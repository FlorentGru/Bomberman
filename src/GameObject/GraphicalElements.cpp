/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** GraphicalElements.cpp
*/

#include <GraphicalElements.hpp>

GraphicalElements::GraphicalElements(const irr::core::vector3df &position, const irr::core::vector3df &rotation, irr::f32 scale, bool collide) :
                                    _scale(scale),
                                    _position(position),
                                    _rotation(rotation),
                                    _collide(collide)
{}

const irr::core::vector3df &GraphicalElements::getRotation() const
{
    return _rotation;
}

void GraphicalElements::setRotation(const irr::core::vector3df &rotation)
{
    // TODO - set on the mesh the rotation
    _rotation = rotation;
}

bool GraphicalElements::isCollide() const
{
    return _collide;
}

void GraphicalElements::setCollide(bool canCollide)
{
    _collide = canCollide;
}

const irr::scene::IAnimatedMesh* GraphicalElements::getMesh() const
{
    return (_mesh);
}

void GraphicalElements::setMesh(irr::scene::ISceneManager* smgr, std::string &meshPath, std::string texture)
{
    (void)smgr;
    (void)meshPath;
    (void)texture;
    // TODO - implement GraphicalElements::setMesh
    throw "Not yet implemented";
}

void GraphicalElements::setMesh(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, meshType_t type, std::string &texture)
{
    if (type == CUBE) {
        this->_mesh = smgr->getMesh("./assets/meshs/cube.obj");
        irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(this->_mesh);
        if (node) {
            node->setScale(irr::core::vector3df(1,1,1));
            node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            node->setMD2Animation(irr::scene::EMAT_STAND);
            node->setMaterialTexture(0, driver->getTexture(texture.data()));
            node->setPosition(irr::core::vector3df(_position.X, _position.Y, 0));
        }
    }
}

const std::string &GraphicalElements::getMeshPath() const
{
    return (_meshPath);
}

void GraphicalElements::setMeshPath(const std::string &meshPath)
{
    _meshPath = meshPath;
    // TODO - implement GraphicalElements::setMesh
    throw "Not yet implemented";
}

irr::f32 GraphicalElements::getScale()
{
    return (_scale);
}

void GraphicalElements::setScale(irr::f32 scale)
{
    _scale = scale;
    // TODO  set scale on the mesh
    throw "Not yet implemented";
}

const irr::core::vector3df& GraphicalElements::getPosition()
{
    return (_position);
}

void GraphicalElements::setPosition(irr::core::vector3df& position)
{
    _position = position;
    // TODO - implement GraphicalElements::setPosition
}