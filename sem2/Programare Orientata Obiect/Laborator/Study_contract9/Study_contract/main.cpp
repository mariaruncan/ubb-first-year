#include "ui.h"
#include "service.h"
#include "file_repo.h"
#include "validator.h"
#include "repolab.h"
#include "tests.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main() {

	test_all();
	{
		FileRepo repo{"subjects.txt"};
		Validator valid;
		Contract contr{ repo };
		Service srv{ repo, valid, contr };
		UI cons{ srv };
		cons.run();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
