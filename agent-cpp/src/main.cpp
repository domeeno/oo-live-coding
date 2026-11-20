#include <iostream>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
  std::string input = "";

  std::cin >> input;

  json payload = {
      {"model", "google/gemma-4-e2b"},
      {"input", input},
  };

  auto post = cpr::Post(cpr::Url{"http://localhost:1234/api/v1/chat"},
                        cpr::Header{{"Content-Type", "application/json"}},
                        cpr::Body{payload.dump()});

  json result = json::parse(post.text);

  std::cout << result << "\n";

  for (const auto &item : result["output"]) {
    if (item.value("type", "") == "message") {
      std::cout << item["content"].get<std::string>() << '\n';
    }
  }
}
