// Copyright 2025 Pound Emulator Project. All rights reserved.

#include "Config.h"

#include <fmt/core.h>
#include <toml.hpp>

namespace Config {

static bool logAdvanced = false;

static std::string typeLog = "async";

bool isLogAdvanced() {
  return logAdvanced;
}

std::string logType() {
  return typeLog;
}

void Load(const std::filesystem::path& path) {
  // If the configuration file does not exist, create it and return
  std::error_code error;
  if (!std::filesystem::exists(path, error)) {
    Save(path);
    return;
  }

  toml::value data;

  try {
    data = toml::parse(path);
  } catch (std::exception& ex) {
    fmt::print("Got exception trying to load config file. Exception: {}\n", ex.what());
    return;
  }
  if (data.contains("General")) {
    const toml::value& general = data.at("General");

    logAdvanced = toml::find_or<bool>(general, "Advanced Log", false);
    typeLog = toml::find_or<std::string>(general, "Log Type", "async");
  }
}

void Save(const std::filesystem::path& path) {
  toml::ordered_value data;

  std::error_code error;
  if (std::filesystem::exists(path, error)) {
    try {
      data = toml::parse(path);
    } catch (const std::exception& ex) {
      fmt::print("Exception trying to parse config file. Exception: {}\n", ex.what());
      return;
    }
  } else {
    if (error) {
      fmt::print("Filesystem error: {}\n", error.message());
    }
    fmt::print("Saving new configuration file {}\n", path.string());
  }

  data["General"]["Advanced Log"] = logAdvanced;
  data["General"]["Log Type"] = typeLog;

  std::ofstream file(path, std::ios::binary);
  file << data;
  file.close();
}

} // namespace Config
