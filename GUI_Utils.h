#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
using namespace std;


int GetGameDir(string path, vector<string> &dirpath);
bool CheckScript(string path);
int GetGameIcon(string path, vector<string>&list);