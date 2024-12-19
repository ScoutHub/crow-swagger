#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <map>
#include "parser.hpp"

using namespace std;

int main(void)
{
    map<string, void (*)(Docs *docs, size_t doc_index, string *line_content)> array_functions{
        {"@Route", extract_route},
        {"@Method", extract_method},
        {"@Name", extract_name},
        {"@Description", extract_description},
        {"@Header", extract_header},
        {"@Body", extract_body},
    };

    Docs docs = {
        .size = 0};

    string files[] = {"examples/AuthRoutes.hpp", "examples/UserRoutes.hpp"};
    size_t files_count = (sizeof(files) / sizeof(*files));

    for (size_t i = 0; i < files_count; ++i)
    {
        ifstream file(files[i]);
        string line_content;
        while (getline(file, line_content))
        {
            if (line_content.find("@Doc") != string::npos)
            {
                size_t doc_index = docs.size;
                docs.routes = (Route *)realloc(docs.routes, ++docs.size * sizeof(Route));
                docs.routes[doc_index].headers_array.size = 0;
                docs.routes[doc_index].body_array.size = 0;

                while (getline(file, line_content))
                {
                    if (line_content.find("*/") != string::npos)
                        break;
                    for (map<string, void (*)(Docs *docs, size_t doc_index, string *line_content)>::iterator it = array_functions.begin(); it != array_functions.end(); ++it)
                    {
                        if (line_content.find(it->first) != string::npos)
                            it->second(&docs, doc_index, &line_content);
                    }
                }
            }
        }
        file.close();
    }

    const char *output_path = "index.html";
    construct_documentation(&docs, output_path);
    free(docs.routes);
    return 0;
}