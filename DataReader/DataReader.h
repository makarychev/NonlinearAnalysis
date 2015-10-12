#pragma once
#include <string>
#include <fstream>
#include <list>
#include "boost/date_time/gregorian/gregorian_types.hpp"

class DataReader
{
public:
	enum RetCode
	{
		Ok,
		UndefinedError,
		BadNumCountInLine,
		FileNotOpened,
		BadDate,
	};
	DataReader(std::string sPath) : m_sPath(sPath) {};
	~DataReader() {};

	virtual std::list<int> LoadDst(boost::gregorian::date dateIn) = 0;
	virtual std::list<int> LoadDst(boost::gregorian::date dateFrom, boost::gregorian::date dateTo) = 0;

protected:
	std::string m_sPath;

};