#pragma once

#include <string>
#include <cstdarg>

class Reporter {
public:
    virtual ~Reporter() {}
    virtual void addMessage(const char* msg) = 0;
    virtual void addFormattedMessage(const char* format, ...) = 0;
    virtual void setProgress(int progress) = 0;
    virtual void reportProgress(int progress, const char* msg) = 0;
};

class ConsoleReporter : public Reporter {
public:
    void addMessage(const char* msg) override;
    void addFormattedMessage(const char* format, ...) override;
    void setProgress(int progress) override;
    void reportProgress(int progress, const char* msg) override;

private:
    int currentProgress = 0;
};