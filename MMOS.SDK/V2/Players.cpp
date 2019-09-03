#include "Players.h"
#include "../Api.h"

namespace MMOS {
	namespace SDK {
		namespace V2 {
			Players::Players(Api* api) : api(api) {
			};
			Players::~Players() {
				api = NULL;
			}
			web::json::value Players::Get(std::string playerCode, std::string project) {
				std::string path = "/games/" + api->GetGame() + "/players/" + playerCode;
				
				std::string method = "GET";
				std::vector<int> expectedStatusCodes{ 200, 404 };

				if (!project.empty()) {
					path += "?project=" + project;
				}

				return api->Call(path, method, web::json::value::null(), expectedStatusCodes);
				
			};
			web::json::value Players::CreateTask(std::string playerCode, web::json::value body) {
				std::string path = "/games/" + api->GetGame() + "/players/" + playerCode + "/tasks";

				std::string method = "POST";
				std::vector<int> expectedStatusCodes{ 201 };

				return api->Call(path, method, body, expectedStatusCodes);
			};
		}
	}
}