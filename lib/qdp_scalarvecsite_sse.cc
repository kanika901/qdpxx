// $Id: qdp_scalarvecsite_sse.cc,v 1.1 2003-09-02 21:44:58 edwards Exp $

/*! @file
 * @brief Intel SSE optimizations
 * 
 * SSE optimizations of basic operations
 */


#include "qdp.h"

// These SSE asm instructions are only supported under GCC/G++
#if defined(__GNUC__)

QDP_BEGIN_NAMESPACE(QDP);

// Specialization to optimize the case   
//    LatticeColorMatrix[OrderedSubset] = LatticeColorMatrix * LatticeColorMatrix
template<>
void evaluate(OLattice<PScalar<PColorMatrix<RComplexFloat, 3> > >& d, 
	      const OpAssign& op, 
	      const QDPExpr<BinaryNode<OpMultiply, 
	      Reference<QDPType<PScalar<PColorMatrix<RComplexFloat, 3> >, 
	      OLattice<PScalar<PColorMatrix<RComplexFloat, 3> > > > >, 
	      Reference<QDPType<PScalar<PColorMatrix<RComplexFloat, 3> >, 
	      OLattice<PScalar<PColorMatrix<RComplexFloat, 3> > > > > >,
	      OLattice<PScalar<PColorMatrix<RComplexFloat, 3> > > >& rhs,
	      const OrderedSubset& s)
{
//  cout << "call single site QDP_M_eq_M_times_M" << endl;

  const LatticeColorMatrix& l = static_cast<const LatticeColorMatrix&>(rhs.expression().left());
  const LatticeColorMatrix& r = static_cast<const LatticeColorMatrix&>(rhs.expression().right());

  const int istart = s.start() >> INNER_LOG;
  const int iend   = s.end()   >> INNER_LOG;

  for(int i=istart; i <= iend; ++i) 
  {
    float *dd = (float*)&(d.elem(i).elem());
    float *ll = (float*)&(l.elem(i).elem());
    float *rr = (float*)&(r.elem(i).elem());

    _inline_ssevec_mult_su3_nn(dd,ll,rr,0);
    _inline_ssevec_mult_su3_nn(dd,ll,rr,1);
    _inline_ssevec_mult_su3_nn(dd,ll,rr,2);
  }
}

QDP_END_NAMESPACE();

#endif  // defined(__GNUC__)
