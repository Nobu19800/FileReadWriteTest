#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <vector>
#include <string>

#include "FileReadWriteTestUtil.h"





class MeasurementParameter
{
public:
	MeasurementParameter(const std::string &datasize_str, const std::string &number_str, const std::string &outputfile_str);
	~MeasurementParameter();
	int datasize;
	int number;
	std::ofstream outputfile;
	std::string outputfile_name;
};

MeasurementParameter::MeasurementParameter(const std::string &datasize_str, const std::string &number_str, const std::string &outputfile_str)
{
	if (!stringTo(datasize, datasize_str.c_str()))
	{
		std::cerr << "Failed to convert " << datasize_str << std::endl;
		throw;
	}

	if (datasize <= 0)
	{
		std::cerr << "datasize <= 0" << std::endl;
		throw;
	}

	if (!stringTo(number, number_str.c_str()))
	{
		std::cerr << "Failed to convert " << number_str << std::endl;
		throw;
	}

	if (number <= 0)
	{
		std::cerr << "number <= 0" << std::endl;
		throw;
	}

	outputfile.open(outputfile_str);
	if (!outputfile.is_open())
	{
		std::cerr << "can not open " << outputfile_str << std::endl;
		throw;
	}

	outputfile_name = outputfile_str;
}



MeasurementParameter::~MeasurementParameter()
{
	outputfile.close();
}

int main (int argc, char** argv)
{
	if (argc < 3)
	{
		std::cerr << "please set the file name" << std::endl;
		return 1;
	}

	std::ifstream configfile(argv[1]);
	if (!configfile.is_open())
	{
		std::cerr << "can not open " << argv[1] << std::endl;
		return 1;
	}

	std::string path;

	if (argc > 3)
	{
		path = argv[3];
	}

	std::vector<MeasurementParameter*> mplist;
	std::string line;

	std::getline(configfile, line);
	while (std::getline(configfile, line)) {
		vstring param(split(line, "\t"));
		if (param.size() >= 3)
		{
			std::string datasize_str(param[0]);
			std::string number_str(param[1]);
			std::string outputfile_str(path+param[2]);

			mplist.push_back(new MeasurementParameter(datasize_str, number_str, outputfile_str));
		}
	}



	std::ofstream resultfile(argv[2]);
	if (!resultfile.is_open())
	{
		std::cerr << "can not open " << argv[2] << std::endl;
	}


	for (auto& mp : mplist)
	{
		std::cout << "start datasize:" << mp->datasize << " number:" << mp->number << " outputfile:" << mp->outputfile_name << std::endl;
		std::string data;
		data.resize(mp->datasize);

		auto start = std::chrono::high_resolution_clock::now().time_since_epoch();
		for (int i = 0; i < mp->number; i++)
		{
			mp->outputfile << data << std::endl;
		}
		auto end = std::chrono::high_resolution_clock::now().time_since_epoch();

		std::chrono::duration<double> diff = end - start;

		resultfile << mp->datasize << "\t" << mp->number << "\t" << diff.count() << std::endl;

		delete mp;

		std::cout << "------------------------------------" << std::endl;
	}

	
	resultfile.close();

  return 0;
}