#pragma once

#include <string>
#include <iostream>

std::string ReadInputHtmlStr();
std::string DecodeHtmlStr(const std::string& strToDecode);
void OutputHtmlStr(const std::string& str);
