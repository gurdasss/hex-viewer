#include <iostream>
#include <fstream> // for std::ifstream
#include <cstddef> // for std::size_t

int main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        std::cerr << "error: need a text file to read.\n";
        std::cerr << "hexviewer FILEPATH\n";
        return 1;
    }

    std::ifstream in{argv[1]};

    if (!in)
    {
        std::cerr << "Could'nt open the given file.\n";
        return 1;
    }

    char byte{};
    // read the given file byte-by-byte
    // and print them in a group of 16 bytes
    // on each line
    while (in.get(byte))
    {
        constexpr std::size_t charPerLine{16UL};
        static std::size_t charPrintedCount{0};

        if (charPrintedCount < charPerLine)
        {
            if (byte == '\n')
                std::cout << '.';
            else
                std::cout << byte;
        }
        else
        {
            if (byte == '\n')
                std::cout << '\n'
                          << '.';
            else
                std::cout << '\n'
                          << byte;
            charPrintedCount = 0;
        }

        ++charPrintedCount;
    }

    std::cout << '\n';

    // ifstream object (in) will automatically close the file
    // via its destructor.

    return 0;
}