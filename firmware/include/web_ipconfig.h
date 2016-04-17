#pragma once

#include <SmingCore/SmingCore.h>

bool check_auth(HttpRequest &request, HttpResponse &response);

void onFile(HttpRequest &request, HttpResponse &response);

void onSettings(HttpRequest &request, HttpResponse &response);
void onIpConfig(HttpRequest &request, HttpResponse &response);

void onAjaxNetworkList(HttpRequest &request, HttpResponse &response);

void onAjaxConnect(HttpRequest &request, HttpResponse &response);

void networkScanCompleted(bool succeeded, BssList list);
