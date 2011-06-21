#include "Config.h"

PythonConfig::PythonConfig()
{
	InitPython();
	exec("config = Config()", main_namespace);
	config = getattr(main_module, "config", true);
}

PythonConfig::PythonConfig(const std::string &filename)
{
	InitPython();
	loadConfig(filename);
}

void PythonConfig::loadConfig(const std::string &filename)
{
	try
	{
		exec_file(boost::python::str(filename), main_namespace);
	}
	catch(boost::python::error_already_set const &)
	{
		std::cerr << "Error while parsing config file: " << filename << std::endl;
		PyErr_Print();
		exit(1);
	}
	config = getattr(main_module, "config", true);
}

std::vector<std::string> PythonConfig::dir(const std::string &name, const bool hide)
{
	boost::python::dict locals;
	locals["__introspection"] = getattr(config, name);
	boost::python::list tmp(eval("dir(__introspection)", main_namespace, locals));
	std::vector<std::string> result;
	for (int i = 0; i < len(tmp); ++i)
	{
		std::string item = boost::python::extract<std::string>(tmp[i]);
		if ((!startswith(item, "__")) || (!hide))
			result.push_back(item);
	}
	return result;
}

boost::python::object PythonConfig::getattr(const boost::python::object &obj, const std::string &name)
{
	if (in('.', name))
	{
		std::vector<std::string> tmp = split(name, ".", 1);
		return getattr(getattr(obj, tmp[0]), tmp[1]);
	}
	else
	{
		try
		{
			if (name == "")
				return obj;
			return obj.attr(boost::python::str(name));
		}
		catch(boost::python::error_already_set const &)
		{
			PyErr_Clear();
			return boost::python::object();
		}
	}
}

boost::python::object PythonConfig::getattr(const boost::python::object &obj, const std::string &name, const bool abortOnNull)
{
	boost::python::object result = getattr(obj, name);
	if ((result.ptr() == Py_None) && abortOnNull)
	{
		std::cerr << "Error while accessing object '" << name << "'" << std::endl;
		exit(1);
	}
	return result;
}

void PythonConfig::InitPython()
{
	Py_Initialize();
	main_module = boost::python::import("__main__");
	main_namespace = main_module.attr("__dict__");
	exec("Config = type('Config', (), {})", main_namespace);
	exec("Runtime = type('Runtime', (), {})", main_namespace);
}
