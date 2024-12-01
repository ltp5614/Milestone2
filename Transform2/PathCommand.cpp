#include "PathCommand.h"

PathCommand::PathCommand(char cmd, const std::vector<float>& params)
        : command(cmd), parameters(params) {}


char PathCommand::getCommand() const
{
  return command;
}

//
std::string PathCommand::toString() const
{
  std::ostringstream oss;
  oss << command << " ";
  for(int i = 0; i < parameters.size(); i++)
  {
    oss << parameters[i];
    if (i < parameters.size() - 1) oss << " ";
  }
  return oss.str();
}

const std::vector<float>& PathCommand::getParameters() const
{
  return parameters;
}


