#ifndef CONFIG_CONFIG_HPP
#define CONFIG_CONFIG_HPP

#include <config/toml.hpp>
#include <string>
#include <memory>
#include <stdexcept>
#include <mutex>
#include <iostream>

namespace config
{
    class Config
    {
    private:
        toml::table config_;
        inline static std::unique_ptr<Config> instance_ = nullptr;
        inline static std::once_flag init_flag_{};

        explicit Config(const std::string &config_path);

    public:
        Config() = delete;
        Config(Config &) = delete;
        Config(Config &&) = delete;
        Config &operator=(Config &) = delete;
        Config &operator=(Config &&) = delete;

        static void init(const std::string &config_path);

        static Config &get_instance();

        std::string getString(const std::string &section, const std::string &name, const std::string &default_value = "") const;

        int getInt(const std::string &section, const std::string &name, const int default_value = 0) const;

        bool getBool(const std::string &section, const std::string &name, const bool default_value = false) const;

        ~Config() = default;
    };
}

#endif