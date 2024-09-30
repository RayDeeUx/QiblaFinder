#include <Geode/loader/SettingEvent.hpp>
#include "Settings.hpp"
#include "Utils.hpp"

using namespace geode::prelude;

$execute {
	Mod::get()->addCustomSetting<MySettingValue>("privacyPolicy", "none");
	Mod::get()->addCustomSetting<MySettingValue>("latLongDotNet", "none");
	listenForSettingChanges<double>("userLatitude", [](double userLatitude) {
		if (Utils::getBool("useAPI")) Utils::findBearingWebAPI(userLatitude, Utils::getDouble("userLongitude"));
		else Utils::findBearing();
	});
	listenForSettingChanges<double>("userLongitude", [](double userLongitude) {
		if (Utils::getBool("useAPI")) Utils::findBearingWebAPI(Utils::getDouble("userLatitude"), userLongitude);
		else Utils::findBearing();
	});
	listenForSettingChanges<bool>("useAPI", [](bool useAPI) {
		if (useAPI) Utils::findBearingWebAPI(Utils::getDouble("userLatitude"), Utils::getDouble("userLongitude"));
		else Utils::findBearing();
	});
}