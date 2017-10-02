// ---------------------------------------------------------------------------

#ifndef AddStringH
#define AddStringH

#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
namespace add_string {

	vector <string> split(const std::string& str, const string& delim);

	template<typename Stream>
	size_t findWord(Stream& in, const string& word) {
		string lineToWrite;
		while (in >> lineToWrite) {
			if (lineToWrite.find(word) != string::npos) {
				return in.tellg() - lineToWrite.size();
			}
		}

		if (in.fail() && !in.eof()) {
			throw(string("������ ���������� �����"));
		}

		return string::npos;
	}

	template<typename Stream>
	size_t findLine(Stream& in, const string& line) {
		string lineToWrite;
		while (getline(in, lineToWrite)) {
			if (lineToWrite.find(line) != string::npos) {
				return in.tellg() - lineToWrite.size();
			}
		}

		if (in.fail() && !in.eof()) {
			throw(string("������ ���������� �����"));
		}

		return string::npos;
	}

}
// ---------------------------------------------------------------------------
#endif