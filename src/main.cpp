#include <iostream>
#include <fstream> // for std::ifstream
#include <cstddef> // for std::size_t
#include <string>

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

    constexpr std::streamsize bufLen{16L};
    char buffer[bufLen]{};

    // read the given file 16-byte at a time
    // and print them in a group of 16 bytes
    // on each line
    // keep the loop running until !(std::ifstream::fail())
    while (in)
    {
        // read bufLen byte(s) at a time
        in.read(buffer, bufLen);

        // ONLY print the first in.gcount()
        // chars
        for (auto i{0}; i < in.gcount(); ++i)
        {
            char byte{buffer[i]};

            // substitute un-printable chars
            // with '.' char
            if (byte <= 31 || byte >= 127)
                std::cout << '.';
            else
                std::cout << byte;
        }

        std::cout << '\n';
    }

#if 0
    // read the given file byte-by-byte
    // and print them in a group of 16 bytes
    // on each line
    // keep the loop running until !(std::ifstream::fail())

    while (in)
    {
        // using this integral representation of
        // a byte I can print it in different forms
        // like hex, oct, dec, and ascii
        int ch{in.get()};

        // if we have reached to the EOF
        // terminate the loop
        if (!in)
            break;

        unsigned char byte{static_cast<unsigned char>(ch)};

        constexpr std::size_t charPerLine{16UL};
        static std::size_t charPrintedCount{0};

        if (charPrintedCount < charPerLine)
        {
            if (byte <= 31 || byte >= 127)
                std::cout << '.';
            else
                std::cout << byte;
        }
        else
        {
            if (byte <= 31 || byte >= 127)
                std::cout << '\n'
                          << '.';
            else
                std::cout << '\n'
                          << byte;
            charPrintedCount = 0;
        }

        ++charPrintedCount;
    }

#endif

    // ifstream object (in) will automatically close the file
    // via its destructor.

    return 0;
}