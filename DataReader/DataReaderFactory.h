#pragma once

#include "DataReader.h"
#include <gsl.h>

class DataReaderFactory
{
public:
	enum Type
	{
		None,
		Dst
	};
	DataReaderFactory() {}
	~DataReaderFactory() {}

	static gsl::owner<DataReader*> GetDataReader(DataReaderFactory::Type type, std::string sPath);
};