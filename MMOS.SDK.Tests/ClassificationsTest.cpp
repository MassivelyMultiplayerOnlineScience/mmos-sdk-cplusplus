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
				TEST_CLASS(ClassificationsTest) {
				public:

					TEST_METHOD(TestClassificationCreate) {
						MMOS::SDK::TEST::Config Config;
						MMOS::SDK::Api api = MMOS::SDK::Api::Api(Config.ApiConfig);

						std::string playerCode = Config.Player + "classification";
						web::json::value bodyTask;

						web::json::value projects;
						projects[0] = web::json::value(utility::conversions::to_utf16string(Config.Project));
						bodyTask[U("projects")] = projects;

						web::json::value playerObj;
						playerObj[U("accountCode")] = web::json::value(utility::conversions::to_utf16string(Config.PlayerAccountCode));
						bodyTask[U("player")] = playerObj;

						web::json::value responseTask = api.V2->players->CreateTask(playerCode, bodyTask);

						web::json::value taskId = responseTask.at(U("body")).at(U("task")).at(U("id"));

						web::json::value body;
						body[U("player")] = web::json::value(utility::conversions::to_utf16string(playerCode));
						body[U("playergroup")] = web::json::value(utility::conversions::to_utf16string(Config.PlayerGroup));

						web::json::value task;
						task[U("id")] = taskId;
						task[U("result")] = Config.Result;
		
						body[U("task")] = task;
						body[U("circumstances")] = Config.circumstances;

						web::json::value response = api.V2->classifications->Create(body);

						Assert::AreEqual(Config.to_wstring(Config.Game), response.at(U("body")).at(U("game")).as_string());
						Assert::AreEqual(Config.to_wstring(Config.Project), response.at(U("body")).at(U("task")).at(U("project")).as_string());
						Assert::AreEqual(Config.to_wstring(playerCode), response.at(U("body")).at(U("player")).at(U("code")).as_string());
					}
				};
			}
		}
	}
}