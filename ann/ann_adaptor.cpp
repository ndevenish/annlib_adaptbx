#include<iostream>
#include <scitbx/error.h>
#include <annlib_adaptbx/ann_adaptor.h>

namespace af = scitbx::af;

using namespace annlib_adaptbx;

AnnAdaptor::AnnAdaptor(
  af::ref<ANNcoord>const& data,int dimension):
  dimension(dimension),
  k(1),
  eps(0.0),
  kdTree(NULL){
  SCITBX_ASSERT (data.size()%dimension == 0);
  af::ref<ANNcoord>::iterator yyy = data.begin();  //double*
  af::shared<ANNcoord*> xxx(data.size()/dimension);
  for (int i=0; i<data.size()/dimension; ++i,yyy+=dimension){
    xxx[i]=yyy;
  }
  persist_data = data;
  persist_ptr = xxx;
  ANNpointArray dataPts = xxx.begin(); //double**

  kdTree = new ANNkd_tree(                   // build search structure
                       dataPts,              // the data points
                       data.size()/dimension,// number of points
                       dimension);
  //not known if the annlib requires the data to be persistent
  // but initial tests led to the implementation of persist_data and persist_ptr
}

AnnAdaptor::~AnnAdaptor(){
  delete kdTree;
  annClose();//because of this, it is not possible to have two instances
             //so not thread safe!!
}

void AnnAdaptor::query(af::ref<ANNcoord> data){
  SCITBX_ASSERT (data.size()%dimension == 0);
  af::ref<ANNcoord>::iterator queryPt = data.begin();
  nn = af::flex_int(data.size()*k);
  distances = af::flex_double(data.size()*k);
  af::shared<ANNidx>::iterator nnIdx = nn.begin();
  af::shared<ANNdist>::iterator dists = distances.begin();
  for (;queryPt!=data.end();queryPt+=dimension,nnIdx+=k,dists+=k){
    kdTree->annkSearch(// search
      queryPt,
      k,
      nnIdx,// nearest neighbors (returned)
      dists,// distance (returned)
      eps);
  }
}
