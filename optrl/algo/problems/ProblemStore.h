#ifndef pargo_ProblemStore_h__guard
#define pargo_ProblemStore_h__guard

#include <string>
#include <map>

namespace pargo {

class Problem;

struct  ProblemStore  {

	ProblemStore(const std::string& name, Problem *);

	explicit ProblemStore(Problem *);
	
	static Problem& getProblemByName(const std::string& name);

	static std::map<std::string, Problem*> getAllProblems();

private:
	static std::map<std::string, Problem*>  problemMap;
};

}

#endif
