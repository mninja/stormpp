#include "archive.hh"

#include <iostream>

namespace storm {

Archive::Archive(const std::string& filename, bool create) throw(FileNotFound, InvalidArchive) : mpqHandle(0), open(false) {
	file.exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);
	try {
		file.open(filename.c_str());
	} catch (std::exception e) {
		throw FileNotFound(filename);
	}
	int nError = ERROR_SUCCESS;

	if(!SFileOpenArchive(filename.c_str(), 0, 0, &mpqHandle)) nError = GetLastError();
	if (nError != ERROR_SUCCESS) throw InvalidArchive(filename);
	
	open = true;
}

Archive::~Archive() {
	if (open) SFileCloseArchive(mpqHandle);
}

}
