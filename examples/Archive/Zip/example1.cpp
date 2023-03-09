// g++ main.cpp -o main -I../../../include -L../../../thirdparty/poco/build/lib  -lPocoZip -lPocoFoundation

#include "Archive/Zip/Compress.h"
#include "Filesystem/File.h"
#include "Filesystem/Path.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace SquidKit::Archive;
using namespace SquidKit;


int main(int argc, char **argv)
{
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] 
    << " filename.zip [files...]" << std::endl;
    return -1;
  }

  std::ofstream out(argv[1], std::ios::binary);
  Zip::Compress c(out, true);
  
  for (int i = 2; i < argc; i++)
  {
    Filesystem::File f(argv[i]);
    if (f.exists())
    {
      Filesystem::Path p(f.path());
      if (f.isDirectory())
      {
        std::cout << "Ignore directory " << f.path() << std::endl;
      }
      else if (f.isFile())
      {
        std::cout << "Add file " << f.path() << std::endl;
        c.addFile(p, p.getFileName());
      }
    }
  }
  c.close();
  out.close();

  return 0;
}
