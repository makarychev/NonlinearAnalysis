#include "DstDataReader.h"
#include <gsl.h>
#include <list>
#include <vector>
#include <iterator>
#include <sstream>
#include <boost/lexical_cast.hpp>

using namespace std;

DstDataReader::DstDataReader(std::string sPath) : DataReader(sPath)
{
}

DstDataReader::~DstDataReader()
{
}

std::list<int> DstDataReader::LoadDst(boost::gregorian::date dateIn)
{
	using namespace boost::gregorian;
	date::ymd_type ymd = dateIn.year_month_day();
	std::list<int> row;
	string sYear(boost::lexical_cast<std::string>(dateIn.year()));
	string sMonth;
	string sFileSeparator("\\");
	char sFileName[10] = {0};
	
	if (dateIn.month() < 10)
		sMonth += "0";
	sMonth += boost::lexical_cast<std::string>(dateIn.month());
	string sFilePath(m_sPath + sFileSeparator + sYear + sFileSeparator + sYear + "-" + sMonth + ".txt");
	std::fstream m_file;
	
	m_file.open(sFilePath, std::ios::in);
	if (m_file.is_open())
	{
		std::string sLine;
		while (getline(m_file, sLine))
		{
			auto Split = [&row, sLine]() {
				if (sLine.empty() == false)
				{

					istringstream iss(sLine);
					std::vector<string> tokens;
					std::copy(istream_iterator<string>(iss),
						istream_iterator<string>(),
						back_inserter(tokens));
					if (tokens.size() == NumbersInLine)
					{
						for (auto token = begin(tokens) + 1; token != end(tokens); ++token)
						{
							row.push_back(stoi(*token));
						}
					}
					else
						throw std::exception("Bad count of numbers in line", RetCode::BadNumCountInLine);

				}
			};

			Split();
		}
	}
	else
		throw std::exception("File not opened", RetCode::FileNotOpened);

	m_file.close();
	
	return move(row);
}

std::list<int> DstDataReader::LoadDst(boost::gregorian::date dateFrom, boost::gregorian::date dateTo)
{
	using namespace boost::gregorian;
	std::list<int> listResult;

	if (dateFrom > dateTo)
		throw std::exception("", DataReader::RetCode::BadDate);

	for (year_iterator year_iter(dateFrom); year_iter != dateTo; ++year_iter)
	for (month_iterator month_iter(dateFrom); month_iter != dateTo; ++month_iter)
	{
		listResult = LoadDst(boost::gregorian::date(year_iter->year(), month_iter->month(), 1));
		//int i = 0;
		//i++;
	}
}


// *************
// example usage
// *************
int main()
{
	string sFilePath("C:\\Users\\Maksym\\Documents\\Visual Studio 2015\\Projects\\NonlinearAnalysis\\external_files\\data\\kyoto-dst\\kyoto-dst-hourly");

	gsl::owner<DataReader*> pDataReader = new DstDataReader(sFilePath);
	std::list<int> row = pDataReader->LoadDst(boost::gregorian::date(2015, 1, 1));

	delete pDataReader;
}