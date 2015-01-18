#ifndef ARCHIVER_H
#define ARCHIVER_H
/* use Archiver.[NAME OF FOO] */

#define MinizAR _getArkive() /* simulate a C namespace */

struct ZFILE {
    const void* data;
    unsigned int  fsize;
};

typedef struct ZFILE (*_readToBuffFromArch)(const char*, const char*);

typedef void(*_dummy)(void);
struct Arkive {
	_readToBuffFromArch readBufferFromArchive;
	_dummy  dummy; //plain test
};

struct Arkive _getArkive();
#endif //Archiver
