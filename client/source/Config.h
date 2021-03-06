#ifndef CONFIG_H_
#define CONFIG_H_

#include <map>
#include <string>
#include <sstream>
#include <initializer_list>

namespace revel
{

class Config
{
	static std::map<std::string, std::string> s_ConfigMap;

private:
	static std::map<std::string, std::string> init()
 {
  std::map<std::string, std::string> configmap;

  configmap["graphics_api"] = "OpenGL";
  configmap["screen_width"] = "1280";
  configmap["screen_height"] = "720";

  return configmap;
 }

public:
	template <typename T> static
	T
	get(const std::string& name)
	{
		T result;
		std::stringstream ss;
		ss << s_ConfigMap[name];
		ss >> result;

		return result;
	}

	template <typename T> static
	void
	set(const std::string& name, T value)
	{
		std::stringstream ss;
		ss << value;

		s_ConfigMap[name] = ss.str();
	}
};



} /* namespace revel */

#endif /* CONFIG_H_ */
