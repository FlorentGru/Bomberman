/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** GraphicalElements.cpp
*/

#include <iostream>
#include "GraphicalElements.hpp"

GraphicalElements::GraphicalElements(const irr::core::vector3df &position, const irr::core::vector3df &rotation, irr::f32 scale, bool collide) :
                                    _mesh(nullptr),
                                    _node(nullptr),
                                    _scale(scale),
                                    _position(position),
                                    _rotation(rotation),
                                    _collide(collide),
                                    _selector(nullptr),
                                    _wordl(nullptr)
{}

const irr::core::vector3df &GraphicalElements::getRotation() const
{
    return _rotation;
}

void GraphicalElements::setRotation(const irr::core::vector3df &rotation)
{
    _rotation = rotation;
    if (_node)
        _node->setRotation(rotation);
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

void GraphicalElements::setMesh(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, std::vector<std::string> texture, std::string &meshPath)
{
    this->_mesh = smgr->getMesh(meshPath.data());
    _node = smgr->addAnimatedMeshSceneNode(this->_mesh);
    if (_node) {
        _node->setScale(irr::core::vector3df(1,1,1));
        _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _node->setMD2Animation(irr::scene::EMAT_STAND);
        for (irr::u16 i = 0; i < texture.size(); i++)
            _node->setMaterialTexture(i, driver->getTexture(texture[i].data()));
        _node->setPosition(irr::core::vector3df(_position.X, _position.Y, 0));
        _node->setRotation(_rotation);
        addColision(smgr);
    }
}

void GraphicalElements::setMesh(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, meshType_t type, std::string &texture)
{
    if (type == CUBE) {
        this->_mesh = smgr->getMesh("./assets/meshs/cube.obj");
        _node = smgr->addAnimatedMeshSceneNode(this->_mesh);
        if (_node) {
            _node->setScale(irr::core::vector3df(1,1,1));
            _node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            _node->setMD2Animation(irr::scene::EMAT_STAND);
            _node->setMaterialTexture(0, driver->getTexture(texture.data()));
            _node->setPosition(irr::core::vector3df(_position.X, _position.Y, 0));
            _node->setRotation(_rotation);
            addColision(smgr);
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
    //TODO chage scale into a vector3f
    _scale = scale;
    // _node->setScale(scale);
}

const irr::core::vector3df& GraphicalElements::getPosition()
{
    if (_node)
        return (_node->getPosition());
    return (_position);
}

void GraphicalElements::setPosition(irr::core::vector3df& position)
{
    _position = position;
    if (_node)
        _node->setPosition(position);
}

void GraphicalElements::addColision(irr::scene::ISceneManager* smgr)
{
    irr::core::vector3df sizeColision;

    if (!_node || !smgr || !_allSelectors) {
        return;
    }
    createSelectorWorld(smgr);
    _selector = smgr->createTriangleSelector(_node);
    _node->setTriangleSelector(_selector);
    _allSelectors->addTriangleSelector(_selector);
    
    irr::scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
			_wordl, _node, irr::core::vector3df(8,8,8),
			irr::core::vector3df(0, 0, 0), irr::core::vector3df(0,0,0));
	_node->addAnimator(anim);
	anim->drop();  // And 
}

bool GraphicalElements::createSelectorWorld(irr::scene::ISceneManager* smgr)
{
    irr::u32 size = 0;

    if (smgr == nullptr || _allSelectors == nullptr)
        return (false);
    _wordl = smgr->createMetaTriangleSelector();
    if (_wordl == nullptr)
        return (false);
    size = _allSelectors->getSelectorCount();
    for (irr::u32 i = 0; i < size; i++) {
        _wordl->addTriangleSelector(_allSelectors->getSelector(i));
    }
    return (true);
}

//TODO to improve the colisions
/*
    Les colisions ne doivent pas avoir le triangle selector de l'object lui meme
    Lorsqu'on crée un nouvel object, il faudrait "update" les colisions des autres
    gameObject qui possèdent de quoi faire une colision
    -> utilité du bool CanCollide qui optimise l'update


    de plus la position des cubes de cléments ne sont pas a la bonne position

    -> probleme venant du mesh en lui meme qui a une origine à l'exterieure de son cube
*/