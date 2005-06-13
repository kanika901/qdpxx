// $Id: qdp_scalarsite_bagel_qdp_blas_g5.h,v 1.2 2005-06-13 13:48:30 bjoo Exp $

/*! @file
 * @brief Generic Scalarsite  optimization hooks
 * 
 * 
 */


#ifndef QDP_SCALARSITE_GENERIC_BLAS_G5_H
#define QDP_SCALARSITE_GENERIC_BLAS_G5_H

#include "bagel_qdp.h"

using namespace QDP;

QDP_BEGIN_NAMESPACE(QDP);

// Types needed for the expression templates. 
// TVec has outer Ns template so it ought to work for staggered as well
typedef PSpinVector<PColorVector<RComplex<REAL>, 3>, Ns> TVec;
typedef PScalar<PScalar<RScalar<REAL> > >  TScal;

// #define DEBUG_BLAS_G6
// TVec is the LatticeFermion from qdp_dwdefs.h with the OLattice<> stripped
// from around it

// TScalar is the usual Real, with the OScalar<> stripped from it
//
// THis is simply to make the code more readable, and reduces < < s and > >s
// in the template arguments

// d += Scalar*ChiralProjPlus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpAddAssign& op, 
	      const QDPExpr<BinaryNode<OpMultiply, 
	                     Reference< QDPType< TScal, OScalar < TScal > > >,
	                     UnaryNode< FnChiralProjectPlus, Reference< QDPType<TVec,OLattice<TVec> > > >
>, 
	                     OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y += a*P{+}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().right().child());
  const OScalar< TScal >& a = static_cast<const OScalar< TScal > &> (rhs.expression().left());

  
  REAL ar = a.elem().elem().elem().elem();
  REAL* aptr = &ar;
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxpay_chp(yptr, aptr,yptr, xptr, n_4vec);
  
}

// d += Scalar*ChiralProjMinus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpAddAssign& op, 
	      const QDPExpr<BinaryNode<OpMultiply, 
	                     Reference< QDPType< TScal, OScalar < TScal > > >,
	                     UnaryNode< FnChiralProjectMinus, Reference< QDPType<TVec,OLattice<TVec> > > >
>, 
	                     OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y += a*P{-}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().right().child());
  const OScalar< TScal >& a = static_cast<const OScalar< TScal > &> (rhs.expression().left());

  
  REAL ar = a.elem().elem().elem().elem();
  REAL* aptr = &ar;
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxpay_chm(yptr, aptr,yptr, xptr, n_4vec);
  
}


// d -= Scalar*ChiralProjPlus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpSubtractAssign& op, 
	      const QDPExpr<BinaryNode<OpMultiply, 
	                     Reference< QDPType< TScal, OScalar < TScal > > >,
	                     UnaryNode< FnChiralProjectPlus, Reference< QDPType<TVec,OLattice<TVec> > > >
>, 
	                     OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y -= a*P{+}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().right().child());
  const OScalar< TScal >& a = static_cast<const OScalar< TScal > &> (rhs.expression().left());

  
  REAL ar = a.elem().elem().elem().elem();
  REAL* aptr = &ar;
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxmay_chp(yptr, aptr,yptr, xptr, n_4vec);
}

// d -= Scalar*ChiralProjMinus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpSubtractAssign& op, 
	      const QDPExpr<BinaryNode<OpMultiply, 
	                     Reference< QDPType< TScal, OScalar < TScal > > >,
	                     UnaryNode< FnChiralProjectMinus, Reference< QDPType<TVec,OLattice<TVec> > > >
>, 
	                     OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y -= a*P{-}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().right().child());
  const OScalar< TScal >& a = static_cast<const OScalar< TScal > &> (rhs.expression().left());

  
  REAL ar = a.elem().elem().elem().elem();
  REAL* aptr = &ar;
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxmay_chm(yptr, aptr,yptr, xptr, n_4vec);
  
}


// d += ChiralProjPlus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpAddAssign& op, 
	      const QDPExpr<
	                    UnaryNode< FnChiralProjectPlus, Reference< QDPType<TVec,OLattice<TVec> > > >, 
	                    OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y += P{+}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().child());

  
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vadd_chp(yptr, yptr, xptr, n_4vec);
  
}


// d += ChiralProjMinus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpAddAssign& op, 
	      const QDPExpr<
	                    UnaryNode< FnChiralProjectMinus, Reference< QDPType<TVec,OLattice<TVec> > > >, 
	                    OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y += P{-}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().child());

  
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vadd_chm(yptr, yptr, xptr, n_4vec);
  
}


// d -= ChiralProjPlus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpSubtractAssign& op, 
	      const QDPExpr<
	                    UnaryNode< FnChiralProjectPlus, Reference< QDPType<TVec,OLattice<TVec> > > >, 
	                    OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y -= P{+}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().child());

  
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vsub_chp(yptr, yptr, xptr, n_4vec);
  
}


// d += ChiralProjMinus(Vec);
template<>
inline
void evaluate(OLattice< TVec >& d, 
	      const OpSubtractAssign& op, 
	      const QDPExpr<
	                    UnaryNode< FnChiralProjectMinus, Reference< QDPType<TVec,OLattice<TVec> > > >, 
	                    OLattice< TVec > > &rhs,
	      const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "y -= P{-}x" << endl;
#endif

  const OLattice< TVec >& x = static_cast<const OLattice< TVec > &>(rhs.expression().child());

  
  REAL* xptr = (REAL *)&(x.elem(s.start()).elem(0).elem(0).real());
  REAL* yptr = (REAL *)&(d.elem(s.start()).elem(0).elem(0).real());
  
  
  int n_4vec = (s.end()-s.start()+1);
  qdp_vsub_chm(yptr, yptr, xptr, n_4vec);
  
}

// d = x + a P_{+} y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpAdd,
	                  Reference< QDPType< TVec, OLattice< TVec > > >,
	                  BinaryNode<OpMultiply, 
	                             Reference< QDPType< TScal, OScalar< TScal > > >,
	                  UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice<TVec> > > >
                                    > 
                          >,
	                  OLattice< TVec > 
               > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = x + a*P{+} y" << endl;
#endif


  // Peel the stuff out of the expression

  // y is the left side of rhs
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&> (rhs.expression().left());

  // ax is the right side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,    
    UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().right());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode.right().child());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());

  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxpay_chp(zptr, aptr, xptr, yptr, n_4vec);

}

// d = x + a P_{-} y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpAdd,
	                  Reference< QDPType< TVec, OLattice< TVec > > >,
	                  BinaryNode<OpMultiply, 
	                             Reference< QDPType< TScal, OScalar< TScal > > >,
	                  UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice<TVec> > > >
                                    > 
                          >,
	                  OLattice< TVec > 
               > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = x + a*P{-} y" << endl;
#endif


  // Peel the stuff out of the expression

  // y is the left side of rhs
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&> (rhs.expression().left());

  // ax is the right side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,    
    UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().right());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode.right().child());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());

  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxpay_chm(zptr, aptr, xptr, yptr, n_4vec);

}

// d = x - a P_{+} y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpSubtract,
	                  Reference< QDPType< TVec, OLattice< TVec > > >,
	                  BinaryNode<OpMultiply, 
	                             Reference< QDPType< TScal, OScalar< TScal > > >,
	                  UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice<TVec> > > >
                                    > 
                          >,
	                  OLattice< TVec > 
               > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = x - a*P{+} y" << endl;
#endif


  // Peel the stuff out of the expression

  // y is the left side of rhs
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&> (rhs.expression().left());

  // ax is the right side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,    
    UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().right());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode.right().child());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());

  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxmay_chp(zptr, aptr, xptr, yptr, n_4vec);

}

// d = x - a P_{-} y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpSubtract,
	                  Reference< QDPType< TVec, OLattice< TVec > > >,
	                  BinaryNode<OpMultiply, 
	                             Reference< QDPType< TScal, OScalar< TScal > > >,
	                  UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice<TVec> > > >
                                    > 
                          >,
	                  OLattice< TVec > 
               > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = x - a*P{-} y" << endl;
#endif


  // Peel the stuff out of the expression

  // y is the left side of rhs
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&> (rhs.expression().left());

  // ax is the right side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,    
    UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().right());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode.right().child());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());

  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxmay_chm(zptr, aptr, xptr, yptr, n_4vec);

}

// d = ax + P+ y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	         BinaryNode<OpAdd,
	           BinaryNode<OpMultiply, 
	              Reference< QDPType< TScal, OScalar< TScal > > >,
	              Reference< QDPType< TVec, OLattice< TVec  > > > 
                   >,
	           UnaryNode<FnChiralProjectPlus, Reference< QDPType<TVec, OLattice<TVec> > > >
                 >,
	        OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x + P{+} y" << endl;
#endif


  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&> (rhs.expression().right().child());

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().left());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode.right());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxpy_chp(zptr, aptr, xptr, yptr, n_4vec);
}

// d = ax + P- y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	         BinaryNode<OpAdd,
	           BinaryNode<OpMultiply, 
	              Reference< QDPType< TScal, OScalar< TScal > > >,
	              Reference< QDPType< TVec, OLattice< TVec  > > > 
                   >,
	           UnaryNode<FnChiralProjectMinus, Reference< QDPType<TVec, OLattice<TVec> > > >
                 >,
	        OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x + P{-} y" << endl;
#endif


  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&> (rhs.expression().right().child());

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().left());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode.right());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxpy_chm(zptr, aptr, xptr, yptr, n_4vec);
}


// d = ax - P+ y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	         BinaryNode<OpSubtract,
	           BinaryNode<OpMultiply, 
	              Reference< QDPType< TScal, OScalar< TScal > > >,
	              Reference< QDPType< TVec, OLattice< TVec  > > > 
                   >,
	           UnaryNode<FnChiralProjectPlus, Reference< QDPType<TVec, OLattice<TVec> > > >
                 >,
	        OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x + P{+} y" << endl;
#endif


  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&> (rhs.expression().right().child());

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().left());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode.right());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxmy_chp(zptr, aptr, xptr, yptr, n_4vec);
}

// d = ax - P- y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	         BinaryNode<OpSubtract,
	           BinaryNode<OpMultiply, 
	              Reference< QDPType< TScal, OScalar< TScal > > >,
	              Reference< QDPType< TVec, OLattice< TVec  > > > 
                   >,
	           UnaryNode<FnChiralProjectMinus, Reference< QDPType<TVec, OLattice<TVec> > > >
                 >,
	        OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{
#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x + P{-} y" << endl;
#endif


  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&> (rhs.expression().right().child());

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN;

  // get the binary node
  const BN &mulNode = static_cast<const BN&> (rhs.expression().left());

  // get a and x out of the bynary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode.right());
  // Set pointers 
  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxmy_chm(zptr, aptr, xptr, yptr, n_4vec);
}

// Vec = Scal * P_{+} Vec
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpMultiply,
	       Reference< QDPType< TScal, OScalar< TScal > > >,
	       UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice< TVec > > > >
               >,
	       OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  cout << "BJ: v = a*P{+}v " << endl;
#endif

  const OLattice< TVec > &x = static_cast<const OLattice< TVec >&>(rhs.expression().right().child());
  const OScalar< TScal > &a = static_cast<const OScalar< TScal >&>(rhs.expression().left());

  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = &ar;  
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *zptr =  &(d.elem(s.start()).elem(0).elem(0).real());
  int n_4vec = (s.end()-s.start()+1);

  qdp_vscal_chp(zptr, aptr, xptr, n_4vec);
}

// Vec = Scal * P_{-} Vec
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpMultiply,
	       Reference< QDPType< TScal, OScalar< TScal > > >,
	       UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice< TVec > > > >
               >,
	       OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  cout << "BJ: v = a*P{-}v " << endl;
#endif

  const OLattice< TVec > &x = static_cast<const OLattice< TVec >&>(rhs.expression().right().child());
  const OScalar< TScal > &a = static_cast<const OScalar< TScal >&>(rhs.expression().left());

  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = &ar;  
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *zptr =  &(d.elem(s.start()).elem(0).elem(0).real());
  int n_4vec = (s.end()-s.start()+1);

  qdp_vscal_chm(zptr, aptr, xptr, n_4vec);
}

// z = ax + bP+ y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpAdd,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         Reference< QDPType< TVec, OLattice< TVec > > > >,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice< TVec > > > >
                > 
               >,
	       OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x + b*P+y" << endl;
#endif

  // Peel the stuff out of the expression
  // y is the right side of rhs

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN1;

  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN2;

  // get the binary node
  const BN1 &mulNode1 = static_cast<const BN1&> (rhs.expression().left());
  const BN2 &mulNode2 = static_cast<const BN2&> (rhs.expression().right());

  // get a and x out of the binary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode1.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode1.right());
  
  // get b and y out of the binary node
  const OScalar< TScal >& b = static_cast<const OScalar< TScal >&>(mulNode2.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode2.right().child());

  
  // Set pointers 
  REAL *aptr = (REAL *)&(a.elem().elem().elem().elem());
  REAL *bptr = (REAL *)&(b.elem().elem().elem().elem());
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxpby_chp(zptr, aptr, xptr, bptr, yptr, n_4vec);
}

// z = ax + bP- y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpAdd,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         Reference< QDPType< TVec, OLattice< TVec > > > >,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice< TVec > > > >
                > 
               >,
	       OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x + b*P-y" << endl;
#endif

  // Peel the stuff out of the expression
  // y is the right side of rhs

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN1;

  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN2;

  // get the binary node
  const BN1 &mulNode1 = static_cast<const BN1&> (rhs.expression().left());
  const BN2 &mulNode2 = static_cast<const BN2&> (rhs.expression().right());

  // get a and x out of the binary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode1.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode1.right());
  
  // get b and y out of the binary node
  const OScalar< TScal >& b = static_cast<const OScalar< TScal >&>(mulNode2.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode2.right().child());

  
  // Set pointers 
  REAL *aptr = (REAL *)&(a.elem().elem().elem().elem());
  REAL *bptr = (REAL *)&(b.elem().elem().elem().elem());
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxpby_chm(zptr, aptr, xptr, bptr, yptr, n_4vec);
}

// z = ax - bP+ y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpSubtract,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         Reference< QDPType< TVec, OLattice< TVec > > > >,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice< TVec > > > >
                > 
               >,
	       OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x - b*P+y" << endl;
#endif

  // Peel the stuff out of the expression
  // y is the right side of rhs

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN1;

  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    UnaryNode< FnChiralProjectPlus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN2;

  // get the binary node
  const BN1 &mulNode1 = static_cast<const BN1&> (rhs.expression().left());
  const BN2 &mulNode2 = static_cast<const BN2&> (rhs.expression().right());

  // get a and x out of the binary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode1.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode1.right());
  
  // get b and y out of the binary node
  const OScalar< TScal >& b = static_cast<const OScalar< TScal >&>(mulNode2.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode2.right().child());

  
  // Set pointers 
  REAL *aptr = (REAL *)&(a.elem().elem().elem().elem());
  REAL *bptr = (REAL *)&(b.elem().elem().elem().elem());
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxmby_chp(zptr, aptr, xptr, bptr, yptr, n_4vec);
}

// z = ax - bP- y
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	       BinaryNode<OpSubtract,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         Reference< QDPType< TVec, OLattice< TVec > > > >,
	        BinaryNode<OpMultiply, 
	         Reference< QDPType< TScal, OScalar< TScal > > >,
	         UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice< TVec > > > >
                > 
               >,
	       OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x - b*P-y" << endl;
#endif

  // Peel the stuff out of the expression
  // y is the right side of rhs

  // ax is the left side of rhs and is in a binary node
  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    Reference< QDPType< TVec, OLattice< TVec > > > > BN1;

  typedef BinaryNode<OpMultiply, 
    Reference< QDPType< TScal, OScalar< TScal > > >,
    UnaryNode< FnChiralProjectMinus, Reference< QDPType< TVec, OLattice< TVec > > > > > BN2;

  // get the binary node
  const BN1 &mulNode1 = static_cast<const BN1&> (rhs.expression().left());
  const BN2 &mulNode2 = static_cast<const BN2&> (rhs.expression().right());

  // get a and x out of the binary node
  const OScalar< TScal >& a = static_cast<const OScalar< TScal >&>(mulNode1.left());
  const OLattice< TVec >& x = static_cast<const OLattice< TVec >&>(mulNode1.right());
  
  // get b and y out of the binary node
  const OScalar< TScal >& b = static_cast<const OScalar< TScal >&>(mulNode2.left());
  const OLattice< TVec >& y = static_cast<const OLattice< TVec >&>(mulNode2.right().child());

  
  // Set pointers 
  REAL *aptr = (REAL *)&(a.elem().elem().elem().elem());
  REAL *bptr = (REAL *)&(b.elem().elem().elem().elem());
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxmby_chm(zptr, aptr, xptr, bptr, yptr, n_4vec);
}

// Vec = Scal * GammaConst<Ns,Ns-1>* Vec
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	          BinaryNode<OpMultiply,
	          Reference< QDPType< TScal, OScalar< TScal > > >,
	            BinaryNode< 
	                OpGammaConstMultiply,
 	                GammaConst<Ns,Ns*Ns-1>,
	                Reference< QDPType< TVec, OLattice< TVec > > >
                    >	        
                  >,
	          OLattice< TVec > 
               > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*(GammaConst<Ns,Ns*Ns-1>()*x)" << endl;
#endif


   typedef BinaryNode< 
            OpGammaConstMultiply,
            GammaConst<Ns,Ns*Ns-1>,
	    Reference< QDPType< TVec, OLattice< TVec > > >
    > BN1;
        
  const OScalar< TScal > &a = static_cast<const OScalar< TScal >&>(rhs.expression().left());
  const BN1 &node = static_cast<const BN1&>(rhs.expression().right());
  
  const OLattice< TVec > &x = static_cast<const OLattice< TVec >&>(node.right());

  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = &ar;  
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *zptr =  &(d.elem(s.start()).elem(0).elem(0).real());
  int n_4vec = (s.end()-s.start()+1);

  qdp_vscal_g5(zptr, aptr, xptr, n_4vec);
 
}


// Vec = Vec - a*Gamma5*Vec
//
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	         BinaryNode<OpSubtract,
	           Reference< QDPType< TVec, OLattice< TVec > > >, 
 	           BinaryNode<OpMultiply,
	             Reference< QDPType< TScal, OScalar< TScal > > >,
	             BinaryNode< 
	                OpGammaConstMultiply,
 	                GammaConst<Ns,Ns*Ns-1>,
	                Reference< QDPType< TVec, OLattice< TVec > > >
                     >	        
                   >
                 >,
	        OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = x - a GammaConst<Ns,Ns*Ns-1>()*y" << endl;
#endif
  const OLattice<TVec>& x = static_cast<const OLattice<TVec>&>(rhs.expression().left());

  typedef BinaryNode<OpMultiply,
	             Reference< QDPType< TScal, OScalar< TScal > > >,
	             BinaryNode< 
	                OpGammaConstMultiply,
 	                GammaConst<Ns,Ns*Ns-1>,
	                Reference< QDPType< TVec, OLattice< TVec > > >
                     >	        
    > MN;
  const MN& mul_node = static_cast<const MN&>(rhs.expression().right());

  const OScalar<TScal>& a = static_cast<const OScalar<TScal>& >(mul_node.left());

  typedef BinaryNode< 
    OpGammaConstMultiply,
    GammaConst<Ns,Ns*Ns-1>,
    Reference< QDPType< TVec, OLattice< TVec > > >
    > GN;

  const GN& gamma_node = static_cast<const GN&>(mul_node.right());
  const OLattice<TVec>& y = static_cast<const OLattice<TVec>&>(gamma_node.right());

  REAL ar =  a.elem().elem().elem().elem();
  REAL *aptr = (REAL *)&ar;
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vxmag5y(zptr, aptr, xptr, yptr, n_4vec);

}


// Vec = a*Vec + b*Gamma5*Vec
//
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	         BinaryNode<OpAdd,
	           BinaryNode<OpMultiply,
	             Reference< QDPType<TScal, OScalar< TScal > > >,  
	             Reference< QDPType<TVec, OLattice< TVec > > >
	           >, 
 	           BinaryNode<OpMultiply,
	             Reference< QDPType< TScal, OScalar< TScal > > >,
	             BinaryNode< 
	                OpGammaConstMultiply,
 	                GammaConst<Ns,Ns*Ns-1>,
	                Reference< QDPType< TVec, OLattice< TVec > > >
                     >	        
                   >
                 >,
	         OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = a*x + b*GammaConst<Ns,Ns*Ns-1>()*y" << endl;
#endif

  typedef BinaryNode<OpMultiply,
            Reference< QDPType<TScal, OScalar< TScal > > >,  
            Reference< QDPType<TVec, OLattice< TVec > > >
    > MN1;

  typedef BinaryNode<OpMultiply,
            Reference< QDPType< TScal, OScalar< TScal > > >,
	      BinaryNode< 
                OpGammaConstMultiply,
 	        GammaConst<Ns,Ns*Ns-1>,
	        Reference< QDPType< TVec, OLattice< TVec > > >
            >	        
    > MN2;

  typedef BinaryNode< 
            OpGammaConstMultiply,
            GammaConst<Ns,Ns*Ns-1>,
            Reference< QDPType< TVec, OLattice< TVec > > >
    > GN;

  const MN1& mulNode1 = static_cast< const MN1& >(rhs.expression().left());
  const MN2& mulNode2 = static_cast< const MN2& >(rhs.expression().right());
  const GN& gammaNode = static_cast< const GN& >(mulNode2.right());

  const OScalar<TScal>& a = static_cast<const OScalar<TScal>&>(mulNode1.left());
  const OLattice<TVec>& x = static_cast<const OLattice<TVec>&>(mulNode1.right());

  const OScalar<TScal>& b = static_cast<const OScalar<TScal>&>(mulNode2.left());
  const OLattice<TVec>& y = static_cast<const OLattice<TVec>&>(gammaNode.right());


  REAL *aptr = (REAL *)&(a.elem().elem().elem().elem());
  REAL *bptr = (REAL *)&(b.elem().elem().elem().elem());
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vaxpbg5y(zptr, aptr, xptr, bptr, yptr, n_4vec);
  
}

// Vec = Gamma_5 *( a*Vec - b*Vec )
//
template<>
inline
void evaluate( OLattice< TVec > &d,
	       const OpAssign &op,
	       const QDPExpr< 
	         BinaryNode<OpGammaConstMultiply,
	                    GammaConst<Ns,Ns*Ns-1>, 
	                    BinaryNode<OpSubtract,
	                      BinaryNode<OpMultiply,
	                        Reference< QDPType<TScal, OScalar< TScal > > >,  
	                        Reference< QDPType<TVec, OLattice< TVec > > >
	                      >, 
 	                      BinaryNode<OpMultiply,
	                        Reference< QDPType< TScal, OScalar< TScal > > >,
	                        Reference< QDPType< TVec, OLattice< TVec > > >
                              >	        
                            >
                 >,
	         OLattice< TVec > > &rhs,
	       const OrderedSubset& s)
{

#ifdef DEBUG_BLAS_G5
  QDPIO::cout << "z = GammaConst<Ns,Ns*Ns-1>()*(ax - by)" << endl;
#endif

  typedef BinaryNode<OpSubtract,
	             BinaryNode<OpMultiply,
	               Reference< QDPType<TScal, OScalar< TScal > > >,  
	               Reference< QDPType<TVec, OLattice< TVec > > >
	             >, 
 	             BinaryNode<OpMultiply,
	               Reference< QDPType< TScal, OScalar< TScal > > >,
	               Reference< QDPType< TVec, OLattice< TVec > > >
                     >	        
    > AXMBY;

  const AXMBY& axmby_node = static_cast<const AXMBY&>(rhs.expression().right());


  typedef BinaryNode<OpMultiply,
            Reference< QDPType<TScal, OScalar< TScal > > >,  
            Reference< QDPType<TVec, OLattice< TVec > > >
    > MN;

  const MN& mulNode1 = static_cast<const MN& >( axmby_node.left());
  const MN& mulNode2 = static_cast<const MN& >( axmby_node.right());

  const OScalar<TScal>& a = static_cast<const OScalar<TScal>&>(mulNode1.left());
  const OLattice<TVec>& x = static_cast<const OLattice<TVec>&>(mulNode1.right());

  const OScalar<TScal>& b = static_cast<const OScalar<TScal>&>(mulNode2.left());
  const OLattice<TVec>& y = static_cast<const OLattice<TVec>&>(mulNode2.right());


  REAL *aptr = (REAL *)&(a.elem().elem().elem().elem());
  REAL *bptr = (REAL *)&(b.elem().elem().elem().elem());
  REAL *xptr = (REAL *) &(x.elem(s.start()).elem(0).elem(0).real());
  REAL *yptr = (REAL *) &(y.elem(s.start()).elem(0).elem(0).real());
  REAL* zptr =  &(d.elem(s.start()).elem(0).elem(0).real());


  // Get the no of 3vecs. s.start() and s.end() are inclusive so add +1
  int n_4vec = (s.end()-s.start()+1);
  qdp_vg5axmby(zptr, aptr, xptr, bptr, yptr, n_4vec);
  
}

QDP_END_NAMESPACE();

#endif  // guard
 
