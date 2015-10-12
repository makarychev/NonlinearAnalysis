#include "DataReaderFactory.h"
#include "DstDataReader.h"

gsl::owner<DataReader*> DataReaderFactory::GetDataReader(DataReaderFactory::Type type, std::string sPath) {
	switch (type)
	{
	case DataReaderFactory::None:
		return nullptr;
	case DataReaderFactory::Dst:
		return new DstDataReader(sPath);
	default:
		return nullptr;
	}
}