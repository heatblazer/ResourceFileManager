#include "Archiver.h"
#include "miniz.c"
#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

struct ZFile loadFromZFile(const char* zfilepath, const char* filename) {
    struct ZFile zfile = {0, 0};
    mz_zip_archive zip_archive;
    mz_bool status;

    memset(&zip_archive, 0, sizeof(zip_archive));
    status = mz_zip_reader_init_file(&zip_archive, zfilepath, 0);
    if (!status) {
        printf("Zip read failed!\n");
        return zfile;
    }

    mz_zip_archive_file_stat fstat;

    int i;
    for (i = 0; i < (int) mz_zip_reader_get_num_files(&zip_archive); i++ ) {
        if (!mz_zip_reader_file_stat(&zip_archive, i, &fstat)) {
            printf("Reading filestat failed\n");
            mz_zip_reader_end(&zip_archive);

            return zfile;
        }
        else if (strcmp(filename, fstat.m_filename) == 0) {
            printf("FOUND MY FILE %s\n", filename);
            zfile.data = mz_zip_reader_extract_file_to_heap(
                        &zip_archive,
                        filename,
                        (size_t*)&fstat.m_uncomp_size,
                        0);
            zfile.fsize = fstat.m_uncomp_size;
            if (!zfile.data) {
                printf("Error reading %s\n", filename);
            } else {
                return zfile;
            }
        }
    }

    mz_zip_reader_end(&zip_archive);

    return zfile;
}

