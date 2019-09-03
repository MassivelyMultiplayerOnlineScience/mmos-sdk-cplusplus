#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <iostream>
#include <cpprest/http_client.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MMOS {
	namespace SDK {
		namespace TEST {
			namespace V2 {
				TEST_CLASS(PlayerTest) {
				public:

					TEST_METHOD(TestGet) {
						MMOS::SDK::TEST::Config Config;
						MMOS::SDK::Api api = MMOS::SDK::Api::Api(Config.ApiConfig);

						web::json::value response = api.V2->players->Get(Config.Player, "");

						Assert::AreEqual(Config.to_wstring(Config.Game), response.at(U("body")).at(U("game")).as_string());
						Assert::AreEqual(Config.to_wstring(Config.Player), response.at(U("body")).at(U("player")).as_string());
					}

					TEST_METHOD(TestGetWithProject) {
						MMOS::SDK::TEST::Config Config;
						MMOS::SDK::Api api = MMOS::SDK::Api::Api(Config.ApiConfig);

						web::json::value response = api.V2->players->Get(Config.Player, Config.Project);

						Assert::AreEqual(Config.to_wstring(Config.Game), response.at(U("body")).at(U("game")).as_string());
						Assert::AreEqual(Config.to_wstring(Config.Player), response.at(U("body")).at(U("player")).as_string());
					}

					TEST_METHOD(TestCreateTask) {
						MMOS::SDK::TEST::Config Config;
						MMOS::SDK::Api api = MMOS::SDK::Api::Api(Config.ApiConfig);

						web::json::value body;

						web::json::value projects;
						projects[0] = web::json::value(utility::conversions::to_utf16string(Config.Project));
						body[U("projects")] = projects;
						
						web::json::value playerObj;
						playerObj[U("accountCode")] = web::json::value(utility::conversions::to_utf16string(Config.PlayerAccountCode));
						body[U("player")] = playerObj;

						web::json::value response = api.V2->players->CreateTask(Config.Player, body);

						Assert::AreEqual(Config.to_wstring(Config.Game), response.at(U("body")).at(U("game")).as_string());
						Assert::AreEqual(Config.to_wstring(Config.Project), response.at(U("body")).at(U("task")).at(U("project")).as_string());
						Assert::AreEqual(Config.to_wstring(Config.Player), response.at(U("body")).at(U("player")).at(U("code")).as_string());
					}
				};
			}
		}
	}
}