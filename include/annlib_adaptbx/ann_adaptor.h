#ifndef ANNLIB_ANN_AD_H
#define ANNLIB_ANN_AD_H
#include <scitbx/array_family/flex_types.h>
#include <scitbx/array_family/shared.h>
#include <ANN/ANN.h>

namespace af = scitbx::af;

namespace annlib_adaptbx {

class AnnAdaptor {
 private:
  ANNkd_tree* kdTree;
  int dimension;
  int k;//number of near neighbors
  double eps;//error bound
  af::ref<ANNcoord> persist_data;
  af::shared<ANNcoord*> persist_ptr;

 public:
  af::flex_int nn;//nearest neighbors
  af::flex_double distances;//nearest distances

 public:
  AnnAdaptor(af::ref<ANNcoord>const&,int);//coordinates & space dimension
  ~AnnAdaptor();
  void query(af::ref<ANNcoord>);//query coordinates
};

}

#endif// ANNLIB_ANN_AD_H
