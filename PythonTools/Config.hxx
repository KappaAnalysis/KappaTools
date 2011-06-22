template<typename T>
void PythonConfig::put(const std::string &name, const T &obj)
{
	boost::python::object runtime = getattr(main_module, "runtime");
	if (runtime.ptr() == Py_None)
		exec("runtime = Runtime()", main_namespace);
	runtime = getattr(main_module, "runtime", true);
	try
	{
		setattr(runtime, name, put(obj));
	}
	catch(boost::python::error_already_set const &)
	{
		std::cout << "Error while setting '" << name << "'!" << std::endl;
		PyErr_Print();
		exit(1);
	}
}

template<typename T>
boost::python::object PythonConfig::put(const T &obj)
{
	return boost::python::object(obj);
}

template<typename T>
boost::python::object PythonConfig::put(const std::vector<T> &obj)
{
	boost::python::list result;
	for (typename std::vector<T>::const_iterator it = obj.begin(); it != obj.end(); ++it)
		result.append(put(*it));
	return result;
}

template<typename Tk, typename Tv>
boost::python::object PythonConfig::put(const std::map<Tk, Tv> &obj)
{
	boost::python::dict result;
	for (typename std::map<Tk, Tv>::const_iterator it = obj.begin(); it != obj.end(); ++it)
		result[put(it->first)] = put(it->second);
	return result;
}

template<typename T1, typename T2>
boost::python::object PythonConfig::put(const std::pair<T1, T2> &obj)
{
	return boost::python::make_tuple(put(obj.first), put(obj.second));
}

template<typename T>
T PythonConfig::get(const std::string &name)
{
	T output;
	boost::python::object obj = getattr(config, name);
	if (obj.ptr() != Py_None)
		if (get(obj, output))
			return output;
	std::cerr << "Error while accessing object '" << name << "'" << std::endl;
	exit(1);
	return output; // just to be nice to the compiler
}

template<typename T>
T PythonConfig::get(const std::string &name, const T &def)
{
	T output(def);
	boost::python::object obj = getattr(config, name);
	if (obj.ptr() != Py_None)
		if (get(obj, output))
			return output;
	return def;
}

template<typename T>
bool PythonConfig::get(const boost::python::object &obj, T &output)
{
	try
	{
		output = boost::python::extract<T>(obj);
		return true;
	}
	catch(boost::python::error_already_set const &)
	{
		PyErr_Print();
		PyErr_Clear();
	}
	return false;
}

template<typename T>
bool PythonConfig::get(const boost::python::object &obj, std::vector<T> &output)
{
	boost::python::list tmp;
	if (!get(obj, tmp))
		return false;
	for (int i = 0; i < len(tmp); ++i)
	{
		T item;
		if (!get(tmp[i], item))
			return false;
		output.push_back(item);
	}
	return true;
}

template<typename Tk, typename Tv>
bool PythonConfig::get(const boost::python::object &obj, std::map<Tk, Tv> &output)
{
	boost::python::dict tmp;
	if (!get(obj, tmp))
		return false;
	boost::python::list iterkeys(tmp.iterkeys());
	for (int i = 0; i < len(iterkeys); ++i)
	{
		Tk key = Tk();
		if (!get(iterkeys[i], key))
			return false;
		Tv value = Tv();
		if (!get(tmp[iterkeys[i]], value))
			return false;
		output[key] = value;
	}
	return true;
}

template<typename T1, typename T2>
bool PythonConfig::get(const boost::python::object &obj, std::pair<T1, T2> &output)
{
	boost::python::tuple tmp;
	if (!get(obj, tmp))
		return false;
	if (len(tmp) != 2)
		return false;
	if (!get(tmp[0], output.first))
		return false;
	if (!get(tmp[1], output.second))
		return false;
	return true;
}
