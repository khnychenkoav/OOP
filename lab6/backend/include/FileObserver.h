// backend/include/FileObserver.h

#ifndef FILEOBSERVER_H
#define FILEOBSERVER_H

#include "Observer.h"
#include <fstream>
#include <string>

class FileObserver : public Observer {
public:
    explicit FileObserver(const std::string& filename);
    ~FileObserver();
    void update(const std::string& message) override;

private:
    std::ofstream file;
};

#endif // FILEOBSERVER_H
