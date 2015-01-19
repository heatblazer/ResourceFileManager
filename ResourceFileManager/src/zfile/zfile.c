#include "zfile.h"
#include "miniz.c"
#include <stdio.h>

/* in case we no longer need miniz.c custom functions
 * to avoid including <string.h>
 * */

int aux_isDir(const char*) ;
int aux_strlen(const char*);

int aux_isDir(const char* file) {
    return (file[aux_strlen(file)-1] == '/' || file[aux_strlen(file)-1] == '\\');
}

int aux_strlen(const char* data) {
    int i=0;
    while ( data[i++] != '\0');
    return i-1; /*discard the null terminator*/
}

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

struct ZFile loadFromZFile(const char* zfilepath, const char* filename) {
    struct ZFile zfile = {0,0};
    mz_zip_archive zip_archive;
    mz_bool status;
    memset(&zip_archive, 0, sizeof(zip_archive));
    status = mz_zip_reader_init_file(&zip_archive, zfilepath, 0);
    if ( !status ) {
        printf("Zip read failed!\n");
        return zfile;
    }
    int i;
    mz_zip_archive_file_stat fstat;
    for (i=0; i < (int) mz_zip_reader_get_num_files(&zip_archive); i++ ) {

        mz_bool statusInFile = mz_zip_reader_file_stat(&zip_archive, i, &fstat);

        if ( aux_isDir(fstat.m_filename) ){
            fprintf(stdout, "FILE IS A DIR\n");
            /* perform recursive call or discard the message */

        } else if ( !statusInFile ) {
            fprintf(stderr, "Reading filestat failed\n");
            mz_zip_reader_end(&zip_archive);
            return zfile;
        } else {
            if ( strcmp(filename, fstat.m_filename) == 0) {
                printf("FOUND MY FILE %s\n", filename);
                zfile.data = mz_zip_reader_extract_file_to_heap(
                            &zip_archive, filename, (uint)&fstat.m_uncomp_size, 0);
                zfile.fsize = fstat.m_uncomp_size;
                if ( !zfile.data ) {
                    fprintf(stderr, "Error reading %s\n", filename);
                } else {
                    return zfile;
                }
            }
        }
    }
    mz_zip_reader_end(&zip_archive);
    return zfile;
}






