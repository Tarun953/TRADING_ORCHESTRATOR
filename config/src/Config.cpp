#include <config/Config.hpp>

namespace config
{
    Config::Config(const std::string &config_path)
    {
        config_ = toml::parse_file(config_path);
    }

    void Config::init(const std::string &config_path)
    {
        std::call_once(init_flag_, [&config_path]()
                       { instance_.reset(new Config(config_path)); });
    }

    Config &Config::get_instance()
    {
        if (!instance_)
            throw std::runtime_error("Config is not initialised yet. Run Config::init(filename) first\n");
        return *instance_;
    }

    std::string Config::getString(const std::string &section, const std::string &name, const std::string &default_value) const
    {
        return config_[section][name].value_or(default_value);
    }

    int Config::getInt(const std::string &section, const std::string &name, const int default_value) const
    {
        return config_[section][name].value_or(default_value);
    }

    bool Config::getBool(const std::string &section, const std::string &name, const bool default_value) const
    {
        return config_[section][name].value_or(default_value);
    }
}