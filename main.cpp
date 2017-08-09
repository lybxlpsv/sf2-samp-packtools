#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int bsearch(char* filename,char* search_term)
{
    int itfound;
    size_t search_term_size = strlen(search_term);

    std::ifstream file(filename, std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);
        std::string file_content;
        file_content.reserve(file_size);
        char buffer[16384];
        std::streamsize chars_read;

        while (file.read(buffer, sizeof buffer), chars_read = file.gcount())
            file_content.append(buffer, chars_read);

        if (file.eof())
        {
            for (std::string::size_type offset = 0, found_at;
                 file_size > offset &&
                 (found_at = file_content.find(search_term, offset)) !=
                                                            std::string::npos;
                 offset = found_at + search_term_size)
                 {
                   //std::cout << found_at << std::endl;
                   itfound = found_at;
                 }

        }
        file.close();
        return itfound;

    }
}

int bconv (char* filename, char* filewav, char* sf2output, int a, int b)
{
    std::ifstream file(filename, std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        char buffer1[a];
        char buffer2[file_size-b];


        std::streamsize chars_read;
        file.read(buffer1, sizeof buffer1);

        FILE* pFile = fopen( sf2output, "wb" );
        buffer1[10] = 'b';
        fwrite(buffer1,1,sizeof(buffer1),pFile);

        FILE* wavefile = fopen ( filewav , "rb" );
        long lSize;
        char * buffer;
        size_t result;
        fseek (wavefile , 0 , SEEK_END);
        lSize = ftell (wavefile) - 40;
        rewind (wavefile);
        fseek(wavefile,40,SEEK_SET);
        buffer = (char*) malloc (sizeof(char)*lSize);

        result = fread (buffer,1,lSize,wavefile);
        std::cout << result << std::endl;
        fwrite(buffer,1,lSize,pFile);

        file.seekg(b, std::ios::beg);
        file.read(buffer2, sizeof buffer2);
        fwrite(buffer2,1,sizeof(buffer2),pFile); fclose(pFile);
    }
    return 0;
}

int splitsamp(int a, int b, char* filename, char* wavout)
{
        FILE* pFile = fopen( wavout, "wb" );
        FILE* wavefile = fopen ( filename , "rb" );
        long lSize;
        char * buffer;
        size_t result;
        fseek (wavefile , 0 , SEEK_END);
        lSize = ftell (wavefile);
        lSize = lSize - a - (lSize - b);
        rewind (wavefile);
        fseek(wavefile,a,SEEK_SET);
        buffer = (char*) malloc (sizeof(char)*lSize);

        result = fread (buffer,1,lSize,wavefile);
        std::cout << result << std::endl;
        fwrite(buffer,1,lSize,pFile);
        fclose(pFile);

    return 0;
}

int joinsamp(int a, int b, char* filename, char* fileogg, char* sfogg)
{
    std::ifstream file(filename, std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        size_t file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        char buffer1[a];
        char buffer2[file_size-b];


        std::streamsize chars_read;
        file.read(buffer1, sizeof buffer1);

        FILE* pFile = fopen( sfogg, "wb" );
        fwrite(buffer1,1,sizeof(buffer1),pFile);

        FILE* wavefile = fopen ( fileogg , "rb" );
        long lSize;
        char * buffer;
        size_t result;
        fseek (wavefile , 0 , SEEK_END);
        lSize = ftell (wavefile);
        rewind (wavefile);
        fseek(wavefile,0,SEEK_SET);
        buffer = (char*) malloc (sizeof(char)*lSize);

        result = fread (buffer,1,lSize,wavefile);
        std::cout << result << std::endl;
        fwrite(buffer,1,lSize,pFile);

        file.seekg(b, std::ios::beg);
        file.read(buffer2, sizeof buffer2);
        fwrite(buffer2,1,sizeof(buffer2),pFile); fclose(pFile);
    }
    return 0;
}


int main(int argc, char *argv[])
{
    if(argv[1] == std::string("d")) {
    printf("DECODE");
    const char* filename = argv[2];
    const char* search_term = "smpl";
    const char* search_term2 = "LIST";

    int a = bsearch(argv[2],"smpl") + 4;
    int b = bsearch(argv[2],"LIST");
    bconv(argv[2],argv[3],argv[4],a,b);
    }

    if(argv[1] == std::string("s")) {
    printf("SPLITSAMP");
    const char* filename = argv[2];
    const char* search_term = "smpl";
    const char* search_term2 = "LIST";

    int a = bsearch(argv[2],"smpl") + 4;
    int b = bsearch(argv[2],"LIST");
    splitsamp(a,b,argv[2],argv[3]);
    }

    if(argv[1] == std::string("e")) {
    printf("JOIN");
    const char* filename = argv[2];
    const char* search_term = "smpl";
    const char* search_term2 = "LIST";

    int a = bsearch(argv[2],"smpl") + 4;
    int b = bsearch(argv[2],"LIST");
    joinsamp(a,b,argv[2],argv[3],argv[4]);
    }

    return 0;
}


