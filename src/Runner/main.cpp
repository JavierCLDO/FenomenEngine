#include "MainEngine/FenomenEngine.h"

int main() {

	fenomen::FenomenEngine fe;

	if(fe.Init(fenomen::FenomenEngine::Prioritize::feDefault) < 0)
		return -1;

	fe.Run();

	return 0;
}