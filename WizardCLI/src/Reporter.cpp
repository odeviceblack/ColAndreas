#include <Reporter.hpp>
#include <iostream>
#include <cstdarg>
#include <cstdio>

void ConsoleReporter::addMessage(const char* msg) {
	std::cout << msg << std::endl;
}

void ConsoleReporter::addFormattedMessage(const char* format, ...) {
	char buffer[1024];
	va_list args;
	va_start(args, format);
	vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	std::cout << buffer << std::endl;
}

void ConsoleReporter::setProgress(int progress) {
	currentProgress = progress;
	std::cout << "Progress: " << currentProgress << "%" << std::endl;
}

void ConsoleReporter::reportProgress(int progress, const char* msg) {
	currentProgress += progress;
	if(currentProgress > 100) currentProgress = 100;
	std::cout << "[" << currentProgress << "%] " << msg << std::endl;
}