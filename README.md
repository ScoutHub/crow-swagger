# Crow-swagger
Custom swagger implementation for c++ crow framework.

# Getting started
## How it work
```c++
/*
    @Doc
    @Route("/auth/login")
    @Name("Login")
    @Description("Login user to api")
    @Method(POST)
    @Header(Content-Type: application/json)
    @Body(string email)
    @Body(string password)
*/
CROW_ROUTE(app, "/auth/login").methods(crow::HTTPMethod::Post)([](const crow::request &req)
{
    // Login logic
});
```

Then, in main file, just put the path of route like this:
```c++
string files[] = {"./examples/AuthRoutes.hpp", "./examples/UserRoutes.hpp"};
```
And
```console
$ g++ parser.cpp -o parser && ./parser
```
<img width="1460" alt="Capture d’écran 2024-12-18 à 10 15 46" src="https://github.com/user-attachments/assets/e55772f6-a001-4e73-8756-900a92f81b9e" />

