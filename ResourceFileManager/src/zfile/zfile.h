#ifndef ARCHIVER_H
#define ARCHIVER_H

struct ZFile {
    const void* data;
    unsigned long long fsize;
};

struct ZFile loadFromZFile(const char* zfilepath, const char* filename);

#endif // ARCHIVER_H
