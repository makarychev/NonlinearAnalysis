#pragma once
#include "DataReader.h"

class DstDataReader : public DataReader
{
public:
	enum {
		NumbersInLine = 25
	};
	DstDataReader(std::string sPath);
	~DstDataReader();

	virtual std::list<int> LoadDst(boost::gregorian::date dateIn) override;
	virtual std::list<int> LoadDst(boost::gregorian::date dateFrom, boost::gregorian::date dateTo) override;

};
