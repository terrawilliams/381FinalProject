/*
 * UiMgr.cpp
 *
 *  Created on: Apr 12, 2017
 *      Author: chad
 */

#include <UiMgr.h>
#include <Engine.h>
#include <GfxMgr.h>
#include <InputMgr.h>
#include <EntityMgr.h>
#include <Types381.h>

UiMgr::UiMgr(Engine* eng): Mgr(eng){
	// Initialize the OverlaySystem (changed for Ogre 1.9)
	    mOverlaySystem = new Ogre::OverlaySystem();
	    engine->gfxMgr->mSceneMgr->addRenderQueueListener(mOverlaySystem);

	    //Ogre::WindowEventUtilities::addWindowEventListener(engine->gfxMgr->ogreRenderWindow, this);
}

UiMgr::~UiMgr(){ // before gfxMgr destructor

}

void UiMgr::Init(){
	//init sdktrays

    mInputContext.mKeyboard = engine->inputMgr->mKeyboard;
    mInputContext.mMouse = engine->inputMgr->mMouse;
    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", engine->gfxMgr->mWindow, mInputContext, this);
    //mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //mTrayMgr->hideCursor();
}

void UiMgr::Stop(){

}

void UiMgr::LoadLevel(){
	//mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "MyButton", "Spawn Boat!");
	//mTrayMgr->createButton(OgreBites::TL_TOPLEFT, "SelectButton", "Select Next");


	/*Ogre::StringVector options;
	options.push_back("Select Unit");
	options.push_back("Spawn Penguin");
	options.push_back("Spawn Not Penguin");
	options.push_back("Spawn Not a Penguin");
	mTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "MyMenu", "Menu", 300, 4,options);*/

	//mTrayMgr->showBackdrop("ECSLENT/UI");
//
//	mLabel = mTrayMgr->createLabel(OgreBites::TL_LEFT,"MyLabel","Label!",250);
//
//	infoLabel = mTrayMgr->createLabel(OgreBites::TL_RIGHT, "infoLabel", "No Unit Selected", 250);


	healthBarL = mTrayMgr->createProgressBar(OgreBites::TL_TOPLEFT,"LeftHealth", "Health", 300, 200);
	healthBarL->setProgress(1);

	healthBarR = mTrayMgr->createProgressBar(OgreBites::TL_TOPRIGHT,"RightHealth", "Health", 300, 200);
	healthBarR->setProgress(1);


	resourcesL = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "LeftResources", "Resources: ", 250);
	resourcesR = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "RightResources", "Resources: ", 250);
	infoPenguinSpawnL  = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "LeftPenguinSpawn", "Penguin: Z - $10", 250);
	infoPenguinSpawnR = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "RightPenguinSpawn", "Penguin: M - $10", 250);
	infoRobotSpawnL = mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "LeftRobotSpawn", "Robot: X - $40", 250);
	infoRobotSpawnR = mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "RightRobotSpawn", "Robot: N - $40", 250);

}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();

	/*switch(engine->entityMgr->selectedEntity->entityType)
	{
		case DDG51Type:
			infoLabel->setCaption("Type: DDG51");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case CarrierType:
			infoLabel->setCaption("Type: Carrier");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case SpeedBoatType:
			infoLabel->setCaption("Type: SpeedBoat");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case FrigateType:
			infoLabel->setCaption("Type: Frigate");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case AlienType:
			infoLabel->setCaption("Type: Alien");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		case BansheeType:
			infoLabel->setCaption("Type: Banshee");
			infoLabel2->setCaption("Heading: " + std::to_string(engine->entityMgr->selectedEntity->heading));
			infoLabel3->setCaption("Speed: " + std::to_string(engine->entityMgr->selectedEntity->speed));
			break;
		default:
			infoLabel->setCaption("No Unit Selected");
			infoLabel2->setCaption("No Unit Selected");
			infoLabel3->setCaption("No Unit Selected");
			break;

	}*/
	healthBarR->setProgress( engine->entityMgr->player2->currentHealth / engine->entityMgr->player2->maxHealth );
	healthBarL->setProgress( engine->entityMgr->player1->currentHealth / engine->entityMgr->player1->maxHealth );
	resourcesR->setCaption("Resources: $" + std::to_string( ((int)engine->entityMgr->player2->currentResources)));
	resourcesL->setCaption("Resources: $" + std::to_string( ((int)engine->entityMgr->player1->currentResources)));
}

void UiMgr::windowResized(Ogre::RenderWindow* rw){
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = engine->inputMgr->mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

void UiMgr::windowClosed(Ogre::RenderWindow* rw){

}

bool UiMgr::keyPressed(const OIS::KeyEvent &arg) {
	return true;
}
bool UiMgr::keyReleased(const OIS::KeyEvent &arg){
	return true;
}
bool UiMgr::mouseMoved(const OIS::MouseEvent &arg){
    if (mTrayMgr->injectMouseMove(arg)) return true;
	return false;
}
bool UiMgr::mousePressed(const OIS::MouseEvent &me, OIS::MouseButtonID mid) {
	std::cout << "mouse clicked" << std::endl;
	if (mTrayMgr->injectMouseDown(me, mid)) return true;
	return false;
}
bool UiMgr::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id){
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    /* normal mouse processing here... */
	return false;
}

void UiMgr::buttonHit(OgreBites::Button *b){
    if(b->getName()=="MyButton")
    {
        std::cout <<"Boat Spawned!" << std::endl;
        Ogre::Vector3 pos;
        pos.x = 0;
        pos.y = 0;
        pos.z = -100;
        engine->entityMgr->CreatePlayer1UnitOfType(SpeedBoatType);
    }
    else if(b->getName()=="SelectButton")
        {
            std::cout <<"Selection Changed!" << std::endl;
            engine->entityMgr->SelectNextEntity();
        }

}

void UiMgr::itemSelected(OgreBites::SelectMenu *m){
    Ogre::Vector3 pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 100;
    switch(m->getSelectionIndex()){
    case 1:
    	engine->entityMgr->CreatePlayer1UnitOfType(SpeedBoatType);
    	mLabel->setCaption("SpeedBoat has Arrived!");
    	break;
    case 2:
    	engine->entityMgr->CreatePlayer1UnitOfType(DDG51Type);
    	mLabel->setCaption("DDG51 has Arrived!");
    	break;
    case 3:
    	engine->entityMgr->CreatePlayer1UnitOfType(CarrierType);
    	mLabel->setCaption("Carrier has Arrived!");
    	break;
    default:
    	break;
    }

}
