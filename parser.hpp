#ifndef _PARSER_H
#define _PARSER_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Body
{
    string *params;
    size_t size;
};

struct Headers
{
    string *params;
    size_t size;
};

struct Route
{
    string path;
    string method;
    string name;
    string description;
    Headers headers_array;
    Body body_array;
};

struct Docs
{
    Route *routes;
    size_t size;
};

void construct_documentation(Docs *docs, const char *output_path)
{
    string html_string =
        "<!DOCTYPE html>"
        "<html lang=\"fr\">"
        "<head>"
        "<meta charset=\"UTF-8\" />"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />"
        "<title>Documentation</title>"
        "<script src=\"https://cdn.tailwindcss.com\"></script>"
        "</head>"
        "<body class=\"min-h-screen w-full flex flex-col justify-between\">"
        "<header class=\"p-8 text-center bg-blue-400 text-white\">"
        "<h1 class=\"text-5xl font-medium\">Documentation</h1>"
        "</header>"
        "<main class=\"w-full h-full flex flex-col gap-4 p-4 grow\">";

    for (size_t i = 0; i < docs->size; ++i)
    {
        html_string +=
            "<div>"
            "   <div class='p-4 bg-white shadow-md rounded-md hover:bg-gray-100 transition' data-toggle='content-" +
            to_string(i) + "' >"
                           "      <div class='flex justify-between items-center'>"
                           "         <div class='flex flex-col gap-2'>"
                           "            <h2 class='text-lg font-semibold'>" +
            docs->routes[i].name + "</h2>"
                                   "            <p class='text-sm text-gray-600'>" +
            docs->routes[i].path + "</p>"
                                   "         </div>"
                                   "         <span class='text-gray-600'>+</span>"
                                   "      </div>"
                                   "   </div>"
                                   "   <div class='mt-2 text-sm text-gray-600 p-4 w-full h-full hidden' id='content-" +
            to_string(i) + "' >"
                           "      <p>" +
            docs->routes[i].description + "</p>"
                                          "      <p class='mt-1'><strong>Path: </strong>" +
            docs->routes[i].path + "</p>";

        if (docs->routes[i].headers_array.size != 0)
        {
            html_string +=
                "      <p class='mt-2'>Headers </p>"
                "      <code class='text-white bg-blue-400 w-full flex p-3 rounded-md mt-2'>{<br>";

            for (size_t j = 0; j < docs->routes[i].headers_array.size; ++j)
            {
                html_string += "&emsp;&emsp;" + docs->routes[i].headers_array.params[j];
                if (j == docs->routes[i].headers_array.size - 1)
                    html_string += "<br>";
                else
                    html_string += ",<br>";
            }
            html_string +=
                "      }</code>";
        }
        if (docs->routes[i].body_array.size != 0)
        {
            html_string +=
                "      <p class='mt-2'>Body </p>"
                "      <code class='text-white bg-blue-400 w-full flex p-3 rounded-md mt-2'>{<br>";

            for (size_t j = 0; j < docs->routes[i].body_array.size; ++j)
            {
                html_string += "&emsp;&emsp;" + docs->routes[i].body_array.params[j];
                if (j == docs->routes[i].body_array.size - 1)
                    html_string += "<br>";
                else
                    html_string += ",<br>";
            }
            html_string +=
                "      }</code>";
        }

        html_string +=
            "   </div>"
            "</div>";
    }

    html_string +=
        "<script>document.addEventListener('DOMContentLoaded',function(){const toggles=document.querySelectorAll('[data-toggle]');toggles.forEach((toggle)=>{toggle.addEventListener('click',function(){const targetId=toggle.getAttribute('data-toggle');const targetDiv=document.getElementById(targetId);if(targetDiv){targetDiv.classList.toggle('hidden');}});});});</script>"
        "</main>"
        "<footer class=\"p-8 text-center bg-blue-400 text-white\">"
        "<p>Copyright © Thémis</p>"
        "</footer>"
        "</body>"
        "</html>";

    ofstream doc_file(output_path);
    doc_file << html_string;

    doc_file.close();
}

static string extract_content(string *line_content, char first_char, char last_char)
{
    size_t first_quote = line_content->find(first_char);
    size_t second_quote = line_content->find(last_char, first_quote + 1);

    string result = line_content->substr(first_quote + 1, second_quote - first_quote - 1);
    return result;
}

void extract_route(Docs *docs, size_t doc_index, string *line_content)
{
    docs->routes[doc_index].path = extract_content(line_content, '"', '"');
}

void extract_method(Docs *docs, size_t doc_index, string *line_content)
{
    docs->routes[doc_index].method = extract_content(line_content, '(', ')');
}

void extract_body(Docs *docs, size_t doc_index, string *line_content)
{
    docs->routes[doc_index].body_array.params = (string *)realloc(docs->routes[doc_index].body_array.params, sizeof(string) * ++docs->routes[doc_index].body_array.size);
    docs->routes[doc_index].body_array.params[docs->routes[doc_index].body_array.size - 1] = extract_content(line_content, '(', ')');
}

void extract_header(Docs *docs, size_t doc_index, string *line_content)
{
    docs->routes[doc_index].headers_array.params = (string *)realloc(docs->routes[doc_index].headers_array.params, sizeof(string) * ++docs->routes[doc_index].headers_array.size);
    docs->routes[doc_index].headers_array.params[docs->routes[doc_index].headers_array.size - 1] = extract_content(line_content, '(', ')');
}

void extract_name(Docs *docs, size_t doc_index, string *line_content)
{
    docs->routes[doc_index].name = extract_content(line_content, '"', '"');
}

void extract_description(Docs *docs, size_t doc_index, string *line_content)
{
    docs->routes[doc_index].description = extract_content(line_content, '"', '"');
}

void debug(Docs *docs)
{
    for (size_t i = 0; i < docs->size; ++i)
    {
        cout << "========================\n";
        cout << "Path: " << docs->routes[i].path << "\n";
        cout << "Name: " << docs->routes[i].name << "\n";
        cout << "Description: " << docs->routes[i].description << "\n";
        cout << "Method: " << docs->routes[i].method << "\n";
        if (docs->routes[i].headers_array.size != 0)
        {
            for (size_t j = 0; j < docs->routes[i].headers_array.size; ++j)
            {
                cout << "Header: " << docs->routes[i].headers_array.params[j] << "\n";
            }
        }
        if (docs->routes[i].body_array.size != 0)
        {
            for (size_t j = 0; j < docs->routes[i].body_array.size; ++j)
            {
                cout << "Body: " << docs->routes[i].body_array.params[j] << "\n";
            }
        }
    }
}

#endif