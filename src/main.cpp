#include <iostream>
#include <fstream> // for std::ifstream
#include <string>  // for std::getline, std::string
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

    constexpr std::size_t charPerLine{16UL};

    // Value-initializes all elements to zero ('/0')
    char buffer[charPerLine]{};

    while (in.getline(buffer, charPerLine))
    {
        std::cout << in.gcount() << ' ';
        std::cout << buffer << '\n';
        // std::cout << "PEEK: " << static_cast<int>(buffer[15UL]);
    }

    std::cout << in.fail() << '\n';

    // ifstream object (in) will automatically close the file
    // via its destructor.

    return 0;
}