#include <iostream>
#include <stdio.h>
#include <fstream>
#include <set>

#include <experimental/filesystem>

#include <zlib.h>
#include <emscripten.h>

#include "inflate.h"
#include "untar.h"

const std::string source_filename{"example.tar.gz"};

int main() {

  // this call to copy down the tar.gz archive is blocking
  // you have to compile with -s ASYNCIFY=1 to use it
  // emscripten_async_wget doesn't require ASYNCIFY
  emscripten_wget(
    "http://127.0.0.1:8000/example.tar.gz",
    source_filename.c_str()
  );

  auto file = gzopen(source_filename.c_str(), "rb");
  auto temp = std::tmpfile();

  // unzip into temporary file
  inflate(file, temp);

  gzclose(file);
  std::rewind(temp);

  // untar into present working directory
  untar(temp, "temp");

  // deletes temporary file
  std::fclose(temp);

  // remove the original .tar.gz archive... we don't need it anymore!
  std::experimental::filesystem::remove(source_filename);

  // print results
  std::cout << "time to print results!" << std::endl;

  for (const auto & filename : std::set{
    "example/example_file.txt",
    "example/example_directory/another_file.txt"
  }) {

    std::cout << "filename: " << filename << std::endl;

    std::cout << "  size: " << std::experimental::filesystem::file_size(filename) << std::endl;

    std::cout << "  content: " << std::endl;

    std::ifstream file{filename};

    std::string line;
    while(getline(file, line)) std::cout << "    " << line << std::endl;

  }

  std::cout << "all done" << std::endl;


}
