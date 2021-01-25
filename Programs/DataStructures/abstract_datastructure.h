#pragma once
#include "..\program_base.h"

class DataStructuresBase : public ProgramBase {
public:
	virtual string ProgramName() = 0 override;
	virtual void RunInternal() = 0 override;
};