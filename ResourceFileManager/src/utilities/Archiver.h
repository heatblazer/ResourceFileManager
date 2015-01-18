#ifndef ARCHIVER_H
#define ARCHIVER_H

struct ZFile {
    const void* data;
    unsigned long long fsize;
};

struct ZFile readBufferFromArchive(const char* arname, const char* filename);

#endif // ARCHIVER_H
