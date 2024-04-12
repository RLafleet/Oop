#pragma once

#include <iostream>
#include <string>
#include <map>

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params);