#include <Geode/modify/MenuLayer.hpp>

#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
	void addQiblaFinderButton(CCNode *node) {
		auto btn = CCMenuItemSpriteExtra::create(
			CircleButtonSprite::create(CCSprite::create("kaaba.png"_spr)),
			this,
			menu_selector(MyMenuLayer::onQiblaFinder)
		);
		btn->setID("qibla-finder-button"_spr);

		node->addChild(btn);
		node->updateLayout();
	}

	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}

		Utils::findBearingWebAPI(Utils::getDouble("userLatitude"), Utils::getDouble("userLongitude"));

		if (!Manager::getSharedInstance()->userAgentBareMinimumAcquired) {
			auto manager = Manager::getSharedInstance();
			auto loader = Loader::get();
			manager->gameVer = loader->getGameVersion();
			manager->loaderVer = loader->getVersion().toNonVString();
			manager->modVer = Mod::get()->getVersion().toNonVString();
			manager->platformName = GEODE_PLATFORM_NAME;
			manager->userAgentBareMinimumAcquired = true;
		}

		if (!Utils::modEnabled()) return true;

		auto bottomMenu = getChildByIDRecursive("bottom-menu");
		if (!bottomMenu) return true;

		addQiblaFinderButton(bottomMenu);

		return true;
	}

	void onQiblaFinder(CCObject*) {
		if (Utils::modEnabled()) Utils::showBearing();
	}
};