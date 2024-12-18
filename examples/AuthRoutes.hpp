#ifndef _AUTH_ROUTES_H
#define _AUTH_ROUTES_H

#include <string>

#include "crow.h"

using namespace std;

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

/*
    @Doc
    @Route("/auth/register")
    @Name("Register")
    @Description("Register user to api")
    @Method(POST)
    @Header(Content-Type: application/json)
    @Body(string email)
    @Body(string username)
    @Body(string first_name)
    @Body(string last_name)
    @Body(string confirm_password)
*/
CROW_ROUTE(app, "/auth/register").methods(crow::HTTPMethod::Post)([](const crow::request &req)
{
    // Register logic
});

/*
    @Doc
    @Route("/auth/refresh/token")
    @Name("Get refresh token")
    @Description("Get new access and refresh token")
    @Method(GET)
    @Header(X-REFRESH-TOKEN: refresh_token)
*/
CROW_ROUTE(app, "/auth/refresh/token")([](const crow::request &req)
{
    // Generate token logic
});

#endif
