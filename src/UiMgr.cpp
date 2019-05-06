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
#include <GameMgr.h>

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

	// createGameplayLabels(); Moved to input mgr so a splash screen can be made
	createSplashScreen();

}

void UiMgr::Tick(float dt){
	mTrayMgr->refreshCursor();

	if(engine->gameMgr->gameStarted == 1)
		updateGameplayLabels();
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
    // Keeping this in case we need to do some selection thing

	/*Ogre::Vector3 pos;
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
    }*/

}


void UiMgr::createGameplayLabels(){
	mTrayMgr->destroyAllWidgets(); // Clear the UI


	// Health bar info. setProgress is a number from 0 - 1.
	healthBarL = mTrayMgr->createProgressBar(OgreBites::TL_TOPLEFT,"LeftHealth", "Health", 300, 200);
	healthBarL->setProgress(1);

	healthBarR = mTrayMgr->createProgressBar(OgreBites::TL_TOPRIGHT,"RightHealth", "Health", 300, 200);
	healthBarR->setProgress(1);


	// Resource info
	resourcesL = mTrayMgr->createLabel(OgreBites::TL_TOPLEFT, "LeftResources", "Resources: ", 250);
	resourcesR = mTrayMgr->createLabel(OgreBites::TL_TOPRIGHT, "RightResources", "Resources: ", 250);

	// Spawn info
	mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "LeftPenguinSpawn", "Penguin: Z - $10", 250);
	mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "RightPenguinSpawn", "Penguin: M - $10", 250);


	mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "LeftNinjaSpawn", "Ninja: X - $10", 250);
	mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "RightNinjaSpawn", "Ninja: N - $10", 250);

	mTrayMgr->createLabel(OgreBites::TL_BOTTOMLEFT, "LeftRobotSpawn", "Robot: C - $40", 250);
	mTrayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "RightRobotSpawn", "Robot: B - $40", 250);

}

void UiMgr::updateGameplayLabels(){
	healthBarR->setProgress( engine->entityMgr->player2->currentHealth / engine->entityMgr->player2->maxHealth );
	healthBarL->setProgress( engine->entityMgr->player1->currentHealth / engine->entityMgr->player1->maxHealth );
	resourcesR->setCaption("Resources: $" + std::to_string( ((int)engine->entityMgr->player2->currentResources)));
	resourcesL->setCaption("Resources: $" + std::to_string( ((int)engine->entityMgr->player1->currentResources)));
}

void UiMgr::createSplashScreen(){
	mTrayMgr->destroyAllWidgets(); // Clear the UI
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "StartButton", "Push P to start the game");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "GameDescription", "The game objective is to spawn units to attack enemy units and eventually the enemy's base.");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "Player1Description", "Player 1 uses keys: Z to spawn penguins, X to spawn ninjas, and C to spawn robots.");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "Player2Description", "Player 2 uses keys: M to spawn penguins, N to spawn ninjas, and B to spawn robots.");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "BalanceDescription", "The first entity spawned is the \"tank\" entity. It will absorb all the damage from the opposing units until dead.");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "PenguinBalanceDescription", "Penguins do double damage to robots and take double damage from Ninjas. They have 10 health and 1 attack.");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "NinjaBalanceDescription", "Ninjas do double damage to penguins. They have 10 health and 1 attack.");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "RobotBalanceDescription", "Robots take double damage from penguins. They have 40 health and 1 attack.");
}

void UiMgr::createGameOverUi(){
	mTrayMgr->destroyAllWidgets(); // Clear the UI
	std::string winningPlayerMessage = "";
	if(engine->entityMgr->player1->currentHealth < 0)
	{
		winningPlayerMessage = "Player 2 wins!";
	} else
	{
		winningPlayerMessage = "Player 1 wins!";
	}
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "PlayerWins", "Congratulations!");
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "PlayerThatWonMessage", winningPlayerMessage);
	mTrayMgr->createLabel(OgreBites::TL_CENTER, "RestartOption", "Press R to play again.");
}
