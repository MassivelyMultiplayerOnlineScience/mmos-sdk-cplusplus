#include "Classifications.h"
#include "../Api.h"

namespace MMOS {
	namespace SDK {
		namespace V2 {
			Classifications::Classifications(Api* api) : api(api) {
			}
			Classifications::~Classifications() {
				api = NULL;
			}
			web::json::value Classifications::Create(web::json::value body) {
				std::string path = "/classifications";
				std::string method = "POST";
				std::vector<int> expectedStatusCodes{ 201 };

				body[U("game")] = web::json::value::string(utility::conversions::utf8_to_utf16(api->GetGame()));

				return api->Call(path, method, body, expectedStatusCodes);
			}
		}
	}
}