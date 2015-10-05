#include <string>

class Matlab
{
public:
	Matlab();
	~Matlab();

	static void ConvertToCpp(std::string sInputFileName, std::string sOutputFileName);
	static void RevertFromCpp(std::string sFileName);

private:

};