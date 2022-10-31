#include <Python.h>
#include <assert.h>
#include "numpy/arrayobject.h"
#include "MBD_distance_2d.h"
#include <iostream>
using namespace std;


static PyObject *
topology_error_3D_wrapper(PyObject *self, PyObject *args)
{
    PyObject *I=NULL, *Seed=NULL;
    PyArrayObject *arr_I=NULL, *arr_Seed=NULL;
    
    if (!PyArg_ParseTuple(args, "OO", &I, &Seed)) return NULL;
    
    arr_I = (PyArrayObject*)PyArray_FROM_OTF(I, NPY_INT, NPY_IN_ARRAY);
    if (arr_I == NULL) return NULL;
    
    arr_Seed = (PyArrayObject*)PyArray_FROM_OTF(Seed, NPY_UINT8, NPY_IN_ARRAY);
    if (arr_Seed == NULL) return NULL;
    
    
    int nd = PyArray_NDIM(arr_I);   //number of dimensions
    npy_intp * shape = PyArray_DIMS(arr_I);  // npy_intp array of length nd showing length in each dim.
    npy_intp * shape_seed = PyArray_DIMS(arr_Seed);
    // cout<<"input shape ";
    // for(int i=0; i<nd; i++)
    // {
    //     cout<<shape[i]<<" ";
    //     if(i < 2 && shape[i]!=shape_seed[i])
    //     {
    //         cout<<"input shape does not match"<<endl;
    //         return NULL;
    //     }
    // }
    // cout<<std::endl;
    // int channel = 1;
    // if(nd == 3){
    //     channel = shape[2];
    // }

    npy_intp output_shape[3];
    output_shape[0] = shape[0];
    output_shape[1] = shape[1];
    output_shape[2] = shape[2];

    PyArrayObject * saddle = (PyArrayObject*)  PyArray_SimpleNew(3, output_shape, NPY_INT);


    topology_error_3D((const int *)arr_I->data, (const unsigned char *)arr_Seed->data, 
           (int *) saddle->data,  shape[0], shape[1], shape[2]);
    
    Py_DECREF(arr_I);
    Py_DECREF(arr_Seed);
    //Py_INCREF(distance);
    return PyArray_Return(saddle);
}



static PyMethodDef Methods[] = {
    {"topology_error_3D",  topology_error_3D_wrapper, METH_VARARGS, "computing segment point"},

};
