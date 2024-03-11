#pragma once

#include "IConfigParse.hpp"

class IReportError{
	virtual void reportError() const = 0;
};