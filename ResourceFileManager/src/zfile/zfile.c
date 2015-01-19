#include "zfile.h"
#include "miniz.c"
#include <stdio.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

int zfile_aux_strlen(const char* data) {
    int i = 0;
    while (data[i++] != '\0');

    /*discard the null terminator*/
    return i - 1;
}

///
/// \brief zfile_aux_print
/// \param message
/// \param file
///
/// For logging only not to display debug messages
///
void zfile_aux_print(const char* message, const char* file) {
    if (zfile_aux_strlen(file) <= 0) {
        fprintf(stdout, "%s\n", message);
    }
    else {
        FILE *fp = fopen(file, "w");
        fprintf(fp, "%s\n", message);

        fclose(fp);
    }
}

int aux_isDir(const char* file) {
    return ((file[zfile_aux_strlen(file)-1] == '/') || (file[zfile_aux_strlen(file)-1] == '\\'));
}

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

    int i  = 0;
    for (; i < (int) mz_zip_reader_get_num_files(&zip_archive); ++i) {

        mz_bool statusInFile = mz_zip_reader_file_stat(&zip_archive, i, &fstat);

        if ( aux_isDir(fstat.m_filename) ){
            zfile_aux_print("File is a dir", "");
        }
        else if (!statusInFile) {
            mz_zip_reader_end(&zip_archive);

            return zfile;
        }
        else if (strcmp(filename, fstat.m_filename) == 0) {
                printf("File found: %s\n", fstat.m_filename);

                zfile.data = mz_zip_reader_extract_file_to_heap(
                            &zip_archive,
                            filename,
                            (size_t*)&fstat.m_uncomp_size,
                            0);
                zfile.fsize = fstat.m_uncomp_size;

                if (!zfile.data) {
                    fprintf(stderr, "Error reading %s filename\n", fstat.m_filename);
                }
                else {
                    return zfile;
                }
        }
    }

    mz_zip_reader_end(&zip_archive);

    return zfile;
}

