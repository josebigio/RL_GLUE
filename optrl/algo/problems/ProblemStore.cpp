#include "ProblemStore.h"

#include <pargo/Problem.h>

#include <stdexcept>
#include <iostream>
using namespace std;

namespace pargo {

std::map<std::string, Problem*>  ProblemStore::problemMap;

ProblemStore::ProblemStore ( const std::string& name, Problem* p) {
	problemMap.insert(make_pair(name,p));
}

ProblemStore::ProblemStore ( Problem* p) {

	problemMap.insert(make_pair(p->getName(),p));
}

Problem& ProblemStore::getProblemByName ( const std::string& name ) {
	std::map<std::string, Problem*>::iterator problemIt = problemMap.find(name);

	if(problemIt != problemMap.end())
		return *(problemIt->second);

	throw invalid_argument("no problem with name " + name);
}

std::map<std::string, Problem*> ProblemStore::getAllProblems() {
	return problemMap;
}

}
