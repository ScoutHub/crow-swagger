#ifndef _USER_ROUTES_H
#define _USER_ROUTES_H

#include "crow.h"

using namespace std;

/*
    @Doc
    @Route("/api/users/list")
    @Name("Users list")
    @Description("Get registered users list")
    @Method(GET)
    @Header(Authorization: Bearer token)
*/
CROW_ROUTE(app, "/api/users/list").CROW_MIDDLEWARES(app)([]()
{
    // Get user list logic
});
/*
    @Doc
    @Route("/api/users")
    @Name("User information")
    @Description("Get logged user information")
    @Method(GET)
    @Header(Authorization: Bearer token)
*/
CROW_ROUTE(app, "/api/users").CROW_MIDDLEWARES(app)([](const crow::request &req)
{
    // Get user logic
});
/*
    @Doc
    @Route("/api/users")
    @Name("User update")
    @Description("Update user information")
    @Method(PUT)
    @Header(Authorization: Bearer token)
    @Header(Content-Type: application/json)
    @Body(string last_name)
    @Body(string first_name)
    @Body(string email)
    @Body(string username)
*/
CROW_ROUTE(app, "/api/users").CROW_MIDDLEWARES(app).methods(crow::HTTPMethod::Put)([](const crow::request &req)
{
    // Update user logic
});

#endif
