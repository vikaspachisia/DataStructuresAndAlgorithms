#pragma once
#include "..\program_base.h"

class AlgorithmBase : public ProgramBase {
	virtual string ProgramName() = 0 override;
	virtual void RunInternal() = 0 override;
};