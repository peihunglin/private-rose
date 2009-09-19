#include <rose.h>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <interp_core.h>

using namespace std;
using namespace Interp;

int main(int argc, char **argv)
   {
     try
        {
          vector<string> argvList(argv, argv+argc);
          Interpretation interp;
          interp.parseCommandLine(argvList);

          SgProject *prj = frontend(argvList);
          SgSourceFile *file = isSgSourceFile((*prj)[0]);
          ROSE_ASSERT(file != NULL);
          SgGlobal *global = file->get_globalScope();
          SgFunctionSymbol *testSym = global->lookup_function_symbol("test");

          StackFrameP head(new StackFrame(&interp, testSym));
          ValueP rv = head->interpFunction(vector<ValueP>(1, ValueP(new IntValue(1, PTemp, head))));
          cout << "Returned " << (rv.get() ? rv->show() : "<<nothing>>") << endl;
        }
     catch (InterpError &ie)
        {
          cerr << "Interpreter error occurred: " << ie.err << endl;
          ie.dumpCallStack(cerr);
          return 1;
        }
     return 0;
   }