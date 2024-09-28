#include <Geode/modify/MenuLayer.hpp>

#include "Manager.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
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

		return true;
	}

	void onStats(CCObject*) {
		Utils::showBearing();
	}
};