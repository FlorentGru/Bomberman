/*
** EPITECH PROJECT, 2019
** Bomberman
** File description:
** GraphicalElements.hpp
*/

#ifndef GRAPHICALELEMENTS_HPP
#define GRAPHICALELEMENTS_HPP

#include <string>
#include <vector>

#ifdef _WIN64
    #include <irrlicht.h>
#else
    #include <irrlicht/irrlicht.h>
#endif

class GraphicalElements
{
private:
    irr::scene::IAnimatedMesh* _mesh;
    irr::scene::IAnimatedMeshSceneNode *_node;
    std::string _meshPath;
    irr::f32 _scale;
    irr::core::vector3df _position;
    irr::core::vector3df _rotation;
    bool _collide;
    irr::scene::ITriangleSelector *_selector;
    irr::scene::IMetaTriangleSelector *_wordl;

    bool createSelectorWorld(irr::scene::ISceneManager* smgr);

public:

    enum meshType_e {
        CUBE
    };
    typedef enum meshType_e meshType_t;

public:
    static irr::scene::IMetaTriangleSelector *_allSelectors;

    GraphicalElements(const irr::core::vector3df &position = irr::core::vector3df(0, 0, 0), const irr::core::vector3df &rotation = irr::core::vector3df(0, 0, 0), irr::f32 scale = 1, bool collide = true);

    const irr::core::vector3df &getRotation() const;
    void setRotation(const irr::core::vector3df &rotation);

    bool isCollide() const;
    void setCollide(bool canCollide);

    const irr::scene::IAnimatedMesh* getMesh() const;
    void setMesh(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, std::vector<std::string>, std::string &meshPath);
    void setMesh(irr::scene::ISceneManager* smgr, irr::video::IVideoDriver* driver, meshType_t type, std::string &texture);

    const std::string &getMeshPath() const;
    void setMeshPath(const std::string &meshPath);

    irr::f32 getScale();
    void setScale(irr::f32 _scale);

    const irr::core::vector3df& getPosition();
    void setPosition(irr::core::vector3df& _position);

    void addColision(irr::scene::ISceneManager* smgr);

};

#endif
