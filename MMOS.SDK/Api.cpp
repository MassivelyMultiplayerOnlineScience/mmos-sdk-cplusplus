#include "Api.h"

#include <iostream>
#include <sstream>
#include <algorithm>

using namespace web::http::client;
using namespace web::http;

namespace MMOS {
	namespace SDK{
		web::json::value Api::Info() {
			std::string path = "/";
			std::string method = "GET";
			std::vector<int> expectedStatusCodes{ 200 };
			
			return Call(path, method, web::json::value::null(), expectedStatusCodes);
		};
		web::json::value Api::Call(std::string path, std::string method, web::json::value body, std::vector<int> expectedStatusCodes){

			std::string data;
			if (!body.is_null()) {
				utility::stringstream_t stream;
				body.serialize(stream);
				data = utility::conversions::utf16_to_utf8(stream.str());
			}
			std::map<std::string, std::string> headers = Authentication->prepareHeaders(Config.Key, Config.Secret, method, path, data);
			
			http_request req;
			req.set_request_uri(utility::conversions::utf8_to_utf16(path));

			for (auto const & h : headers) {
				req.headers().add(utility::conversions::to_utf16string(h.first), utility::conversions::to_utf16string(h.second));
			}
			
			web::json::value response;

			if (method == "GET") {
				req.set_method(methods::GET);
			} else if (method == "POST") {
				req.headers().add(L"Content-Type", L"application/json");
				req.set_method(methods::POST);
				req.set_body(data);
				std::cout << "Request body: " << data << std::endl;
			}

			response = HandleResponse(client->request(req), expectedStatusCodes);
			
			return response;
		};

		std::string Api::GetGame() {
			return Game;
		};

		web::json::value Api::HandleResponse(pplx::task<web::http::http_response> response, std::vector<int> expectedStatusCodes) {

			response.wait();
			web::http::http_response result = response.get();
			
			int statusCode = result.status_code();
			web::json::value responseJson;
			responseJson[U("statusCode")] = web::json::value(statusCode);
			responseJson[U("body")] = result.extract_json().get();

			if (expectedStatusCodes.empty() || std::find(expectedStatusCodes.begin(), expectedStatusCodes.end(), statusCode) != expectedStatusCodes.end()) {
				return responseJson;
			} else {
				utility::stringstream_t stream;
				responseJson.serialize(stream);
				throw stream.str();
			}

		};

		Api::ApiV2::ApiV2(Api* api) {
			players = new V2::Players(api);
			classifications = new V2::Classifications(api);
			authentication = new V2::Authentication();
		};

		Api::ApiV2::~ApiV2() {
			delete classifications;
			delete players;
			delete authentication;
			classifications = NULL;
			players = NULL;
			authentication = NULL;
		};
		Api::Api(ApiConfig config) : Config(config), Game(config.Game) {
			std::string url = config.Protocol + "://" + config.Host + ":" + config.Port;
			client = new http_client(utility::conversions::utf8_to_utf16(url));
			switch (Config.Version) {
			case ApiVersion::V2:
				V2 = new ApiV2(this);
				Authentication = V2->authentication;
				break;
			}
		};
		Api::~Api() {
			delete client;
			delete V2;
			client = NULL;
			V2 = NULL;
			Authentication = NULL;
		};

	}
}