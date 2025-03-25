#include "Colors.h"

void Colors::reset() const
{
    cout << "\033[0m";
}

void Colors::red() const
{
    cout << "\033[1;31m";
}

void Colors::green() const
{
    cout << "\033[1;32m";
}

void Colors::yellow() const
{
    cout << "\033[1;33m";
}

void Colors::blue() const
{
    cout << "\033[1;34m";
}
