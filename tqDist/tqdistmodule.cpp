#include "TripletDistanceCalculator.h"
#include "QuartetDistanceCalculator.h"

#include <Python.h>
#include <vector>
#include "newick_parser.h"
#ifdef _WIN32
#include <windows.h>

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved) {
	return TRUE;
}
#endif

#ifdef _WIN32
	__declspec(dllexport)
#endif
    static PyObject *method_TripletDistance(PyObject *self,PyObject *args) {
        const char *nw1, *nw2; // two newick strings
        /* Parse arguments */
        if(!PyArg_ParseTuple(args, "ss", &nw1, &nw2)) {
            return NULL;
        }
        
        UnrootedTree *ut1 = NULL;
        UnrootedTree *ut2 = NULL;
        RootedTree *rt1 = NULL;
        RootedTree *rt2 = NULL;

        NewickParser parser;

        ut1 = parser.parseStr(nw1);
        ut2 = parser.parseStr(nw2);
        rt1 = ut1->convertToRootedTree(NULL);
        rt2 = ut2->convertToRootedTree(rt1->factory);

        TripletDistanceCalculator tripletCalc;
        double dist = tripletCalc.calculateTripletDistance(rt1, rt2);
        double n = tripletCalc.get_n();
        double total = tripletCalc.get_totalNoTriplets();
        double resolved = tripletCalc.get_resolvedTriplets();
        double resolved_norm = resolved/total;
        double unresolved = tripletCalc.get_unresolvedTriplets();
        double unresolved_norm = unresolved/total;
        double dist_norm = dist/total;         
       
        PyObject* py_n = PyFloat_FromDouble(n);
        PyObject* py_total = PyFloat_FromDouble(total);
        PyObject* py_resolved = PyFloat_FromDouble(resolved);
        PyObject* py_resolved_norm = PyFloat_FromDouble(resolved_norm);
        PyObject* py_unresolved = PyFloat_FromDouble(unresolved);
        PyObject* py_unresolved_norm = PyFloat_FromDouble(unresolved_norm);
        PyObject* py_dist = PyFloat_FromDouble(dist);
        PyObject* py_dist_norm = PyFloat_FromDouble(dist_norm);
        
        PyObject* result = PyTuple_Pack(8,py_n,py_total,py_dist,py_dist_norm,py_resolved,py_resolved_norm,py_unresolved,py_unresolved_norm);

        if (ut1 != NULL) delete ut1;
        if (ut2 != NULL) delete ut2;
        if (rt1 != NULL) delete rt1->factory;
        if (rt2 != NULL) delete rt2->factory;
        
        return result;    
    }
    
#ifdef _WIN32
	__declspec(dllexport)
#endif
    static PyObject *method_QuartetDistance(PyObject *self,PyObject *args) {
        const char *nw1, *nw2;
        /* Parse arguments */
        if(!PyArg_ParseTuple(args, "ss", &nw1, &nw2)) {
            return NULL;
        }
        
        UnrootedTree *ut1 = NULL;
        UnrootedTree *ut2 = NULL;
        
        NewickParser parser;

        ut1 = parser.parseStr(nw1);
        ut2 = parser.parseStr(nw2); 
        
        QuartetDistanceCalculator quartetCalc;
        //double total = quartetCalc.get_totalNoQuartets();
        //PyObject* result = PyFloat_FromDouble(dquart/total);
        //PyObject* result = PyTuple_Pack(2,PyFloat_FromDouble(dquart),PyFloat_FromDouble(total));
        double dquart = quartetCalc.calculateQuartetDistance(ut1, ut2);
        double totalNoQuartets = quartetCalc.get_totalNoQuartets();

        double resolvedQuartetsAgree = quartetCalc.get_resolvedQuartetsAgree();
        double resolvedQuartetsAgreeDiag = quartetCalc.get_resolvedQuartetsAgreeDiag();
        double resolvedQuartetsAgreeUpper = quartetCalc.get_resolvedQuartetsAgreeUpper();
        double resAgree = resolvedQuartetsAgree + resolvedQuartetsAgreeDiag + resolvedQuartetsAgreeUpper;
        double unresolvedAgree = quartetCalc.get_unresolvedQuartets();

        PyObject* py_n = PyFloat_FromDouble(quartetCalc.get_n());
        PyObject* py_totalNoQuartets = PyFloat_FromDouble(quartetCalc.get_totalNoQuartets());
        PyObject* py_dist = PyFloat_FromDouble(dquart);
        PyObject* py_dist_norm = PyFloat_FromDouble(double(dquart) / double(totalNoQuartets));
        PyObject* py_resAgree = PyFloat_FromDouble(resAgree);
        PyObject* py_resAgree_norm = PyFloat_FromDouble(double(resAgree) / double(totalNoQuartets));
        PyObject* py_unresolvedAgree = PyFloat_FromDouble(unresolvedAgree);
        PyObject* py_unresolvedAgree_norm = PyFloat_FromDouble(double(unresolvedAgree) / double(totalNoQuartets));

        PyObject* result = PyTuple_Pack(8,py_n,py_totalNoQuartets,py_dist,py_dist_norm,py_resAgree,py_resAgree_norm,py_unresolvedAgree,py_unresolvedAgree_norm);
                
        return result;    
    }
    
static PyMethodDef TQMethods[] = {
    {"triplet_distance", method_TripletDistance, METH_VARARGS, "Compute normalized triplet distance"},
    {"quartet_distance", method_QuartetDistance, METH_VARARGS, "Compute normalized quartet distance"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef tqdistmodule = {
    PyModuleDef_HEAD_INIT,
    "tqdist",
    "Python interface for the tqdist C library",
    -1,
    TQMethods
};


PyMODINIT_FUNC PyInit_tqdist(void) {
    return PyModule_Create(&tqdistmodule);
}
