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
	MeasurementParameter(const std::string &datasize_str, const std::string &number_str, const std::string &inputfile_str);
	~MeasurementParameter();
	int datasize;
	int number;
	std::ifstream inputfile;
	std::string inputfile_name;
};


MeasurementParameter::MeasurementParameter(const std::string &datasize_str, const std::string &number_str, const std::string &inputfile_str)
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

	inputfile.open(inputfile_str, std::ios::in | std::ios::binary);
	if (!inputfile.is_open())
	{
		std::cerr << "can not open " << inputfile_str << std::endl;
		throw;
	}
	inputfile_name = inputfile_str;
}

MeasurementParameter::~MeasurementParameter()
{
	inputfile.close();
}

int main(int argc, char** argv)
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
			std::string inputfile_str(path+param[2]);

			mplist.push_back(new MeasurementParameter(datasize_str, number_str, inputfile_str));
		}
	}

	std::ofstream resultfile(argv[2]);
	if (!resultfile.is_open())
	{
		std::cerr << "can not open " << argv[2] << std::endl;
	}

	for (auto& mp : mplist)
	{
		std::cout << "start datasize:" << mp->datasize << " number:" << mp->number << " inputfile:" << mp->inputfile_name << std::endl;
		char* data = new char[mp->datasize];

		auto start = std::chrono::high_resolution_clock::now().time_since_epoch();
		for (int i = 0; i < mp->number; i++)
		{
			if (!mp->inputfile.eof())
			{
				mp->inputfile.read(data, mp->datasize);
			}
			else
			{
				std::cerr << "read error:" << mp->inputfile_name << std::endl;
				return 1;
			}
		}
		auto end = std::chrono::high_resolution_clock::now().time_since_epoch();

		std::chrono::duration<double> diff = end - start;

		resultfile << mp->datasize << "\t" << mp->number << "\t" << diff.count() << std::endl;

		delete[] data;
		delete mp;

		std::cout << "------------------------------------" << std::endl;
	}

	resultfile.close();

	return 0;
}