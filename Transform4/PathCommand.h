#ifndef PATHCOMMAND_H
#define PATHCOMMAND_H


#include "SVGElements.h"


class PathCommand
{
  private:
    char command;
    std::vector<float> parameters;
  public:
    PathCommand(char cmd, const std::vector<float>& params);
    char getCommand() const;
    const std::vector<float>& getParameters() const;
    std::string toString() const;
};

#endif

