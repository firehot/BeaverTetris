#include "GameTutorialsAnimationController.h"
#include "GameElementsDataHelper.h"
#include "GameViewElementsKeys.h"
#include "GameFileExtensionMaker.h"
#include "GameDesignConstants.h"
#include "CocosNodesHelper.h"
#include "ServiceLocator.h"
#include "GameServicesKeys.h"
#include "GameViewElementsDataSource.h"
#include "KeysForEnumsDataSource.h"
#include "TetraminoExplosionFactory.h"
#include "GameAnimationActionsConstants.h"
#include "GameViewStyleHelper.h"

using namespace cocos2d;
using namespace std;

const float tutorialActionDuration = 0.3f;
const int tetramino1Tag = 1;
const int tetramino2Tag = 2;
const int tetramino3Tag = 3;
const int tetramino4Tag = 4;

GameTutorialsAnimationController::GameTutorialsAnimationController(void)
{
}


GameTutorialsAnimationController::~GameTutorialsAnimationController(void)
{
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerControllsTutorial()
{
	Node *detail = getDetailForControllsTutorial();

	FiniteTimeAction *detailAppearanceAnimation = getDetailAppearanceAnimation(detail);
	FiniteTimeAction *operationsOnDetailAnimation = getOperationsOnDetailAnimation(detail);

	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);

	FiniteTimeAction *setStartAngle = CallFunc::create([detail](){detail->setRotation(90);});
	FiniteTimeAction *actionWithRotateDetailAtStartEngle = TargetedAction::create(detail, setStartAngle);

	ActionInterval *sequence  = Sequence::create(detailAppearanceAnimation, operationsOnDetailAnimation, actionWithMoveDetailAtStartPositon, actionWithRotateDetailAtStartEngle, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

Node* GameTutorialsAnimationController::getDetailForControllsTutorial()
{
	Node *detailPad = Node::create();
	CocosNodesHelper::addChildNodeToParentNodeWithKey(detailPad, this, gameTutorialStartDetailKey);

	Vec2 tetraminoOffset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);

	string teraminoImageName = GameFileExtensionMaker::getGraphicWithExtension(redTetraminoKey);
	Sprite *tetramino1 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino1->setPosition(Vec2(0, 0));
	tetramino1->setTag(tetramino1Tag);
	Sprite *tetramino2 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino2->setPosition(Vec2(0, tetraminoOffset.y));
	tetramino2->setTag(tetramino2Tag);
	Sprite *tetramino3 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino3->setPosition(Vec2(0, -tetraminoOffset.y));
	tetramino3->setTag(tetramino3Tag);
	Sprite *tetramino4 = Sprite::createWithSpriteFrameName(teraminoImageName);
	tetramino4->setPosition(Vec2(tetraminoOffset.x, tetraminoOffset.y));
	tetramino4->setTag(tetramino4Tag);

	detailPad->addChild(tetramino1);
	detailPad->addChild(tetramino2);
	detailPad->addChild(tetramino3);
	detailPad->addChild(tetramino4);

	return detailPad;
}

FiniteTimeAction* GameTutorialsAnimationController::getDetailAppearanceAnimation(Node *aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameTutorialStartDetailKey);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(tutorialActionDuration, finalPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}

FiniteTimeAction* GameTutorialsAnimationController::getOperationsOnDetailAnimation(Node *aDetail)
{
	FiniteTimeAction *moveDetailRightAnimation = getMoveDetailRightAnimation(aDetail);
	FiniteTimeAction *moveDetailLeftAnimation = getMoveDetailLeftAnimation(aDetail);
	FiniteTimeAction *rotateDetailAnimation = getRotateDetailAnimation(aDetail);
	FiniteTimeAction *moveDetailDownAnimation = getMoveDetailDownAnimation(aDetail);
	FiniteTimeAction *sequence = Sequence::create(moveDetailRightAnimation, moveDetailLeftAnimation, rotateDetailAnimation, moveDetailDownAnimation, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getMoveDetailRightAnimation(Node *aDetail)
{
	Node *rightController = getControllerWithKey(gameTutorialMoveDetailRightControlKey);
	FiniteTimeAction *actionWithRightController = getActivateControllerAnimation(rightController);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	FiniteTimeAction *moveDetailRight = MoveBy::create(tutorialActionDuration, Vec2(offset.x, 0));
	FiniteTimeAction *actionWithRightDetailDirection = TargetedAction::create(aDetail, moveDetailRight);
	FiniteTimeAction *sequence = Sequence::create(actionWithRightController, actionWithRightDetailDirection, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getMoveDetailLeftAnimation(Node *aDetail)
{
	Node *leftController = getControllerWithKey(gameTutorialMoveDetailLeftControlKey);
	FiniteTimeAction *actionWithLeftController = getActivateControllerAnimation(leftController);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	FiniteTimeAction *moveDetailLeft = MoveBy::create(tutorialActionDuration, Vec2(-offset.x, 0));
	FiniteTimeAction *actionWithLeftDetailDirection = TargetedAction::create(aDetail, moveDetailLeft);
	FiniteTimeAction *sequence = Sequence::create(actionWithLeftController, actionWithLeftDetailDirection, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getRotateDetailAnimation(Node *aDetail)
{
	Node *upController = getControllerWithKey(gameTutorialRotateDetailControlKey);
	FiniteTimeAction *actionWithUpController = getActivateControllerAnimation(upController);
	FiniteTimeAction *rotateDetail = RotateTo::create(tutorialActionDuration, 180.0f);
	FiniteTimeAction *actionWithRotateDetail = TargetedAction::create(aDetail, rotateDetail);
	FiniteTimeAction *sequence = Sequence::create(actionWithUpController, actionWithRotateDetail, nullptr);
	return sequence;
}

FiniteTimeAction* GameTutorialsAnimationController::getMoveDetailDownAnimation(Node *aDetail)
{
	Node *downController = getControllerWithKey(gameTutorialAccelerateDetailControlKey);
	FiniteTimeAction *actionWithDownController = getActivateControllerAnimation(downController);
	Vec2 detailDownPosition = GameElementsDataHelper::getElementOffsetForKey(gameTutorialStartDetailKey);
	FiniteTimeAction *moveDetailDown = MoveTo::create(tutorialActionDuration, detailDownPosition);
	FiniteTimeAction *actionWithMoveDetailDown = TargetedAction::create(aDetail, moveDetailDown);
	FiniteTimeAction *delay = DelayTime::create(tutorialActionDuration);
	FiniteTimeAction *sequence = Sequence::create(actionWithDownController, actionWithMoveDetailDown, delay, nullptr);
	return sequence;
}

Node* GameTutorialsAnimationController::getControllerWithKey(string aKey)
{
	Sprite *controllerView = CocosNodesHelper::getSpriteWithKey(playerControlActiveImageKey);
	controllerView->setScale(2.0f);
	GameViewElementsDataSource *gameViewElementsDataSource = (GameViewElementsDataSource*)ServiceLocator::getServiceForKey(gameViewElementsDataSourceKey);
	Vec2 controllerPosition = gameViewElementsDataSource->getElementPositionForKey(aKey);
	controllerView->setPosition(controllerPosition);
	Vec2 controllRotation = gameViewElementsDataSource->getElementOffsetForKey(aKey);
	controllerView->setRotation(controllRotation.x);
	this->addChild(controllerView);
	return controllerView;
}

FiniteTimeAction* GameTutorialsAnimationController::getActivateControllerAnimation(Node *aController)
{
	float startScale = aController->getScale();
	FiniteTimeAction *activateControllerScaleDown = ScaleTo::create(tutorialActionDuration, startScale / 2);
	FiniteTimeAction *activateControllerScaleUp = ScaleTo::create(tutorialActionDuration, startScale);
	FiniteTimeAction *sequence = Sequence::create(activateControllerScaleDown, activateControllerScaleUp, nullptr);
	FiniteTimeAction *actionWithController = TargetedAction::create(aController, sequence);
	return actionWithController;
}





FiniteTimeAction* GameTutorialsAnimationController::getPlayerReduceLineTutorial()
{
	Node *detail = getDetailForControllsTutorial();
	FiniteTimeAction *detailFallenAnimation = getDetailFallenAnimation(detail);
	vector<Sprite*> tetraminosInBottom = getTetraminosInBottom();
	FiniteTimeAction *tetraminosExplosionAnimation = getTetraminosExplosionAnimationForCallback([this](){makeBottomExplosion();});
	vector<Node*> detailTetraminos = getBottomDetailTetraminos(detail);
	FiniteTimeAction *tetraminosDisappearanceAnimation = getTetraminosDisappearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);
	FiniteTimeAction *actionWithTetraminosAppearance = getTetraminosAppearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(detailFallenAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, delayTime, actionWithMoveDetailAtStartPositon, actionWithTetraminosAppearance, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getDetailFallenAnimation(Node *aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementOffsetForKey(gameTutorialStartDetailKey);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(0.6f, finalPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}

vector<Sprite*> GameTutorialsAnimationController::getTetraminosInBottom()
{
	int bottomElements[] = {1,2,0,1,2,2,2,1,3,1};
	vector<Sprite*> elements = getElementsFromArray(bottomElements);
	return elements;
}

vector<Sprite*> GameTutorialsAnimationController::getElementsFromArray(int *aSourceMassive)
{
	vector<Sprite*> tetraminoElementsLine;
	for (int xIndex = 0; xIndex < tetrisBlocksWidth; xIndex++)
	{
		int tetraminoTag = aSourceMassive[xIndex];
		Sprite *tetraminoView = getTetraminoViewForType(tetraminoTag);
		Vec2 tetraminoPosition = getTetraminoPositionForIndexXY(xIndex, 1);
		tetraminoView->setPosition(tetraminoPosition);
		this->addChild(tetraminoView);
		tetraminoElementsLine.push_back(tetraminoView);
	}
	return tetraminoElementsLine;
}

Sprite* GameTutorialsAnimationController::getTetraminoViewForType(int aType)
{
	Sprite *tetraminoView;
	if (aType > 0)
	{
		TetraminoType type = (TetraminoType)aType;
		KeysForEnumsDataSource *keysForEnumsDataSource = (KeysForEnumsDataSource*)ServiceLocator::getServiceForKey(keysForEnumsDataSourceKey);
		string typeName = keysForEnumsDataSource->getKeyForTetraminoType(type);
		string teraminoImageName = GameFileExtensionMaker::getGraphicWithExtension(typeName);
		tetraminoView = Sprite::createWithSpriteFrameName(teraminoImageName);
	}
	else
	{
		tetraminoView = Sprite::create();
	}
	return tetraminoView;
}

Vec2 GameTutorialsAnimationController::getTetraminoPositionForIndexXY(int xIndex, int yIndex)
{
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	Vec2 position = Vec2(offset.x * xIndex, offset.y * yIndex);
	return position;
}

FiniteTimeAction* GameTutorialsAnimationController::getTetraminosExplosionAnimationForCallback(function<void()> aCallback)
{
	FiniteTimeAction *tetraminosLineExplosionAnimation = CallFunc::create(aCallback);
	FiniteTimeAction *delay = DelayTime::create(tetraminosExplosionDuration);
	FiniteTimeAction *sequence = Sequence::create(tetraminosLineExplosionAnimation, delay, NULL);
	FiniteTimeAction *blowUpAnimation = TargetedAction::create(this, sequence);
	return blowUpAnimation;
}

void GameTutorialsAnimationController::makeBottomExplosion()
{
	for (int explosionIndex = 0; explosionIndex < tetrisBlocksWidth; explosionIndex++)
	{
		setExplosionForIndexXY(explosionIndex, 1);
	}
}

void GameTutorialsAnimationController::setExplosionForIndexXY(int xIndex, int yIndex)
{
	ParticleSystem *explosion = getExplosion();
	Vec2 explosionPosition = getTetraminoPositionForIndexXY(xIndex, yIndex);
	explosion->setPosition(explosionPosition);
	this->addChild(explosion);
}

ParticleSystem* GameTutorialsAnimationController::getExplosion()
{
	ParticleSystem *explosion = ParticleExplosion::create();
	explosion->setAutoRemoveOnFinish(true);
	TetraminoExplosionFactory::setExplosionColors(explosion);
	TetraminoExplosionFactory::setExplosionParticles(explosion);
	return explosion;
}

vector<Node*> GameTutorialsAnimationController::getBottomDetailTetraminos(Node* aDetail)
{
	vector<Node*> detailTetraminos;
	Node* bottomTetramino = aDetail->getChildByTag(tetramino3Tag);
	detailTetraminos.push_back(bottomTetramino);
	return detailTetraminos;
}

FiniteTimeAction* GameTutorialsAnimationController::getTetraminosDisappearanceAnimation(vector<Sprite*> aTetraminos, vector<Node*> aDetailTetraminos)
{
	function<FiniteTimeAction*()> action = [](){return Hide::create();};
	FiniteTimeAction *animationHideTetraminos = getAnimationWithTetraminosAndDetailAndAction(aTetraminos, aDetailTetraminos, action);
	return animationHideTetraminos;
}

FiniteTimeAction* GameTutorialsAnimationController::getTetraminosAppearanceAnimation(vector<Sprite*> aTetraminos, vector<Node*> aDetailTetraminos)
{
	function<FiniteTimeAction*()> action = [](){return Show::create();};
	FiniteTimeAction *animationShowTetraminos = getAnimationWithTetraminosAndDetailAndAction(aTetraminos, aDetailTetraminos, action);
	return animationShowTetraminos;
}

FiniteTimeAction* GameTutorialsAnimationController::getAnimationWithTetraminosAndDetailAndAction(vector<Sprite*> aTetraminos, vector<Node*> aDetailTetraminos, function<FiniteTimeAction*()> action)
{
	Vector<FiniteTimeAction*> actions;
	vector<Sprite*>::iterator tetraminosIterator;
	for (tetraminosIterator = aTetraminos.begin(); tetraminosIterator != aTetraminos.end(); tetraminosIterator++)
	{
		Sprite *tetraminoView = *tetraminosIterator;
		FiniteTimeAction *animationWithTetramino = TargetedAction::create(tetraminoView, action());
		actions.pushBack(animationWithTetramino);
	}
	FiniteTimeAction *bottomTetraminosSequence = Sequence::create(actions);
	FiniteTimeAction *animationWithTetraminosInDetail = getAnimationWithTetraminosInDetail(aDetailTetraminos, action);
	FiniteTimeAction *sequence = Sequence::create(bottomTetraminosSequence, animationWithTetraminosInDetail, nullptr);
	FiniteTimeAction *animationWithTetraminos = TargetedAction::create(this, sequence);
	return animationWithTetraminos;
}

FiniteTimeAction* GameTutorialsAnimationController::getAnimationWithTetraminosInDetail(vector<Node*> aDetailTetraminos, function<FiniteTimeAction*()> action)
{
	Vector<FiniteTimeAction*> actions;
	vector<Node*>::iterator tetraminosIterator;
	for (tetraminosIterator = aDetailTetraminos.begin(); tetraminosIterator != aDetailTetraminos.end(); tetraminosIterator++)
	{
		Node *tetraminoView = *tetraminosIterator;
		FiniteTimeAction *animationWithTetramino = TargetedAction::create(tetraminoView, action());
		actions.pushBack(animationWithTetramino);
	}
	FiniteTimeAction *tetraminosInDetailSequence = Sequence::create(actions);
	FiniteTimeAction *animationWithTetraminos = TargetedAction::create(this, tetraminosInDetailSequence);
	return animationWithTetraminos;
}


FiniteTimeAction* GameTutorialsAnimationController::getPlayerReduceHorizontalCombinationTutorial()
{
	Node *detail = getDetailForControllsTutorial();
	FiniteTimeAction *detailFallenAnimation = getDetailFallenAnimation(detail);
	vector<Sprite*> tetraminosInBottom = getTetraminosHorizontalLineCombination();
	FiniteTimeAction *tetraminosExplosionAnimation = getTetraminosExplosionAnimationForCallback([this](){getHorizontalLineCombinationExplosion();});
	vector<Node*> detailTetraminos = getBottomDetailTetraminos(detail);
	FiniteTimeAction *tetraminosDisappearanceAnimation = getTetraminosDisappearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);
	FiniteTimeAction *actionWithTetraminosAppearance = getTetraminosAppearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(detailFallenAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, delayTime, actionWithMoveDetailAtStartPositon, actionWithTetraminosAppearance, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

vector<Sprite*> GameTutorialsAnimationController::getTetraminosHorizontalLineCombination()
{
	int bottomElements[] = {0,0,0,1,1,1,0,0,0,0};
	vector<Sprite*> elements = getElementsFromArray(bottomElements);
	return elements;
}

void GameTutorialsAnimationController::getHorizontalLineCombinationExplosion()
{
	for (int explosionIndex = 2; explosionIndex < 6; explosionIndex++)
	{
		setExplosionForIndexXY(explosionIndex, 1);
	}
}

FiniteTimeAction* GameTutorialsAnimationController::getPlayerReduceVerticalCombinationTutorial()
{
	Node *detail = getDetailForControllsTutorial();
	FiniteTimeAction *detailFallenAnimation = getDetailFallenToOneBlockAnimation(detail);
	vector<Sprite*> tetraminosInBottom = getTetraminosVerticallLineCombination();
	FiniteTimeAction *tetraminosExplosionAnimation = getTetraminosExplosionAnimationForCallback([this](){getVericalLineCombinationExplosion();});
	vector<Node*> detailTetraminos = getVerticalDetailTetraminos(detail);
	FiniteTimeAction *tetraminosDisappearanceAnimation = getTetraminosDisappearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *actionWithMoveDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);
	FiniteTimeAction *actionWithTetraminosAppearance = getTetraminosAppearanceAnimation(tetraminosInBottom, detailTetraminos);
	FiniteTimeAction *delayTime = DelayTime::create(0.4f);

	ActionInterval *sequence  = Sequence::create(detailFallenAnimation, tetraminosExplosionAnimation, tetraminosDisappearanceAnimation, delayTime, actionWithMoveDetailAtStartPositon, actionWithTetraminosAppearance, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getDetailFallenToOneBlockAnimation(Node *aDetail)
{
	Vec2 finalPosition = GameElementsDataHelper::getElementOffsetForKey(gameTutorialStartDetailKey);
	Vec2 offset = GameElementsDataHelper::getElementOffsetForKey(mainGameBoardControllerKey);
	Vec2 detailPosition = Vec2(finalPosition.x, finalPosition.y + offset.y);
	FiniteTimeAction *moveDetailOnScreen = MoveTo::create(0.6f,  detailPosition);
	FiniteTimeAction *actionWithDetailAppearance = TargetedAction::create(aDetail, moveDetailOnScreen);
	return actionWithDetailAppearance;
}

vector<Sprite*> GameTutorialsAnimationController::getTetraminosVerticallLineCombination()
{
	int bottomElements[] = {0,0,1,1,1,0,0,0,0,0};
	vector<Sprite*> elements = getElementsFromArray(bottomElements);
	vector<Sprite*> tetraminoInBottom;
	tetraminoInBottom.push_back(elements[2]);
	return tetraminoInBottom;
}

void GameTutorialsAnimationController::getVericalLineCombinationExplosion()
{
	for (int explosionIndex = 0; explosionIndex < 5; explosionIndex++)
	{
		setExplosionForIndexXY(2, explosionIndex);
	}
}

vector<Node*> GameTutorialsAnimationController::getVerticalDetailTetraminos(Node *aDetail)
{
	vector<Node*> detailTetraminos;
	Node* verticalTetramino1 = aDetail->getChildByTag(tetramino3Tag);
	detailTetraminos.push_back(verticalTetramino1);
	Node* verticalTetramino2 = aDetail->getChildByTag(tetramino2Tag);
	detailTetraminos.push_back(verticalTetramino2);
	Node* verticalTetramino3 = aDetail->getChildByTag(tetramino1Tag);
	detailTetraminos.push_back(verticalTetramino3);
	return detailTetraminos;
}



FiniteTimeAction* GameTutorialsAnimationController::getPlayerUseSpellTutorial()
{
	Node *detail = getDetailForControllsTutorial();

	FiniteTimeAction *detailAppearanceAnimation = getDetailAppearanceAnimation(detail);

	FiniteTimeAction *useSpellKeyAnimation = getUseSpellKeyAnimation();

	FiniteTimeAction *explosionAnimation = getTetraminosExplosionAnimationForCallback([this](){getSpellExplosion();});

	FiniteTimeAction *detailHideAnimation = Hide::create();
	FiniteTimeAction *hideDetail = TargetedAction::create(detail, detailHideAnimation);

	FiniteTimeAction *setStartPosition = Place::create(detail->getPosition());
	FiniteTimeAction *placeDetailAtStartPositon = TargetedAction::create(detail, setStartPosition);

	FiniteTimeAction *detailShowAnimation = Show::create();
	FiniteTimeAction *showDetail = TargetedAction::create(detail, detailShowAnimation);

	ActionInterval *sequence  = Sequence::create(detailAppearanceAnimation, useSpellKeyAnimation, explosionAnimation, hideDetail, placeDetailAtStartPositon, showDetail, nullptr);
	FiniteTimeAction *repeat = RepeatForever::create(sequence);
	return repeat;
}

FiniteTimeAction* GameTutorialsAnimationController::getUseSpellKeyAnimation()
{
	Label *spellButtonLabel = GameViewStyleHelper::getStandardLabelWithFontSize(46);
	spellButtonLabel->setColor(Color3B(41, 104, 110));
	spellButtonLabel->setString(string("1"));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(spellButtonLabel, this, gameTutorialUseSpellControlKey);
	FiniteTimeAction *actionWithUpController = getActivateControllerAnimation(spellButtonLabel);

	ParticleSystem *rocket = ParticleMeteor::create();
	rocket->setGravity(Vec2(200,200));
	CocosNodesHelper::addChildNodeToParentNodeWithKey(rocket, this, gameTutorialUseSpellRocketKey);
	Vec2 rocketFinalPosition = GameElementsDataHelper::getElementFinalActionPositionForKey(gameTutorialUseSpellRocketKey);
	FiniteTimeAction *moveRocket = MoveTo::create(0.3f, rocketFinalPosition);
	FiniteTimeAction *setStartRocketPosition = Place::create(rocket->getPosition());
	FiniteTimeAction *rocketSequence = Sequence::create(moveRocket, setStartRocketPosition, nullptr);
	FiniteTimeAction *animationWithRocket = TargetedAction::create(rocket, rocketSequence);

	FiniteTimeAction *sequence = Sequence::create(actionWithUpController, animationWithRocket, nullptr);
	return sequence;
}

void GameTutorialsAnimationController::getSpellExplosion()
{
	for (int explosionIndex = 16; explosionIndex < 19; explosionIndex++)
	{
		setExplosionForIndexXY(2, explosionIndex);
	}
	setExplosionForIndexXY(3, 18);
}