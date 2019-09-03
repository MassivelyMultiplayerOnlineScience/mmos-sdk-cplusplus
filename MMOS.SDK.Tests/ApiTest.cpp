#include "stdafx.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include <iostream>
#include <cpprest/http_client.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MMOS {
	namespace SDK {
		namespace TEST {
			TEST_CLASS(ApiTest)
			{
			public:

				TEST_METHOD(TestInfo)
				{
					MMOS::SDK::TEST::Config Config;
					MMOS::SDK::Api api = MMOS::SDK::Api::Api(Config.ApiConfig);

					web::json::value response = api.Info();

					Assert::AreEqual(Config.to_wstring("mmos-api-2"), response.at(U("body")).at(U("name")).as_string());
					Assert::AreEqual(true, response.at(U("body")).at(U("stats")).at(U("uptime")).as_integer() > 1);
					Assert::AreEqual(Config.to_wstring("depo"), response.at(U("body")).at(U("stats")).at(U("nodeEnv")).as_string());
				}

			};
		}
	}
}