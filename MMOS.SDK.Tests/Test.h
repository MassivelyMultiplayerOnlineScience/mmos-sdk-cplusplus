#pragma once
#include <string>
#include <cpprest/http_client.h>
#include "../MMOS.SDK/Api.h"

namespace MMOS {
	namespace SDK {
		namespace TEST {
			class Config {
			private:
				std::string Key;
				std::string Secret;

				std::string Protocol = "https";
				std::string Host = "api.depo.mmos.blue";
				std::string Port = "443";
				MMOS::SDK::Api::ApiVersion Version = MMOS::SDK::Api::ApiVersion::V2;

			public:
				std::string Game;
				MMOS::SDK::Api::ApiConfig ApiConfig;
				std::string Project = "unige-exoplanet";
				std::string Player = "testPlayer";
				std::string PlayerAccountCode = "testAccount";
				std::string PlayerGroup = "testPlayerGroup";
				web::json::value Result;
				web::json::value circumstances;
				Config() {
					Key = env("MMOS_SDK_TEST_API_KEY");
					Secret = env("MMOS_SDK_TEST_API_SECRET");
					Game = env("MMOS_SDK_TEST_GAME");

					circumstances[U("t")] = web::json::value(6000);
					Result = web::json::value::parse(U("{\"transits\": [{\"epoch\": 2454132.32909,\"period\": 4.29507,\"transitMarkers\": [54137.336412, 54141.631482, 54145.926552]}, {\"epoch\": 2454132.32909,\"period\": 4.29507,\"transitMarkers\": [54152.221622]}],\"stellarActivity\": [100]}"));

					ApiConfig = {
						Key,
						Secret,
						Game,
						Protocol,
						Host,
						Port,
						MMOS::SDK::Api::ApiVersion::V2
					};
				};

				const wchar_t* to_wchar(utf16string str) {
					return to_wchar(utility::conversions::utf16_to_utf8(str));
				}

				const std::wstring to_wstring(std::string str) {
					return utility::conversions::to_utf16string(str);
				}

				const wchar_t* to_wchar(std::string str) {
					std::wstring w = std::wstring(str.begin(), str.end());
					return w.c_str();
				}

				std::string env(const char *name){
					const char *ret = std::getenv(name);
					if (!ret) return std::string();
					return std::string(ret);
				}
			};
		}
	}
}