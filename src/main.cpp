/*
** EPITECH PROJECT, 2018
** test_irrlisht
** File description:
** main.cpp
*/

#include <boost/multi_array.hpp>
#include <irrlicht/irrlicht.h>

using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:
    // This is the one method that we have to implement
    virtual bool OnEvent(const SEvent& event)
    {
        // Remember whether each key is down or up
        if (event.EventType == irr::EET_KEY_INPUT_EVENT)
            KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

        return false;
    }

    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const
    {
        return KeyIsDown[keyCode];
    }
    
    MyEventReceiver()
    {
        for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
            KeyIsDown[i] = false;
    }

private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

int main(void)
{
    MyEventReceiver receiver;
    boost::multi_array<double, 3> array_type(boost::extents[3][4][2]);

    //open a window
    IrrlichtDevice *device = createDevice(video::EDT_SOFTWARE, core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);
    if (!device)
        return 1;

    //name of the window i think
    device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");

    //easier to use
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    //print text
    guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!", core::rect<s32>(10,10,260,22), true);

    //mesh
    scene::IAnimatedMesh* mesh = smgr->getMesh("./assets/tris.md2");
    if (!mesh)
    {
        device->drop();
        return 1;
    }
    scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

    if (node)
    {
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setMD2Animation(scene::EMAT_PAIN_B);
        node->setMaterialTexture( 0, driver->getTexture("./assets/storm.pcx") );
    }
    smgr->addCameraSceneNode(0, core::vector3df(0,30,-40), core::vector3df(0,5,0));
    irr::scene::ICameraSceneNode *camera = smgr->getActiveCamera();

    u32 then = device->getTimer()->getTime();
    
    core::vector3df nodePosition;
    const f32 MOVEMENT_SPEED = 20.f;
    while(device->run()) {
        const u32 now = device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
        then = now;

        driver->beginScene(true, true, video::SColor(255,100,101,140));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();

        if (node)
            nodePosition = camera->getPosition();

        //input
        if(receiver.IsKeyDown(irr::KEY_KEY_Z))
            nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_S))
            nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;

        if(receiver.IsKeyDown(irr::KEY_KEY_Q))
            nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
        else if(receiver.IsKeyDown(irr::KEY_KEY_D))
            nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;

        if (camera) {
            camera->setPosition(nodePosition);
        }
    }
    device->drop();
    return (0);
}