#ifndef STAN_MATH_PRIM_MAT_FUN_DOGLEG_HPP
#define STAN_MATH_PRIM_MAT_FUN_DOGLEG_HPP

#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <unsupported/Eigen/NonLinearOptimization>

namespace stan {
  namespace math {

    template <typename _Scalar, int NX = Eigen::Dynamic,
      int NY = Eigen::Dynamic>
    struct NLOFunctor {
      typedef _Scalar Scalar;
      enum {
        InputsAtCompileTime = NX,
        ValuesAtCompileTime = NY
      };

      typedef Eigen::Matrix<Scalar, InputsAtCompileTime, 1> InputType;
      typedef Eigen::Matrix<Scalar, ValuesAtCompileTime, 1> ValueType;
      typedef Eigen::Matrix<Scalar, ValuesAtCompileTime, InputsAtCompileTime>
        JacobianType;

      const int m_inputs, m_values;

      NLOFunctor() : m_inputs(InputsAtCompileTime),
        m_values(ValuesAtCompileTime) {}
      NLOFunctor(int inputs, int values) : m_inputs(inputs), m_values(values) {}

      int inputs() const { return m_inputs; }
      int values() const { return m_values; }
    };

    template <typename F1, typename F2>
    struct hybrj_functor : NLOFunctor<double> {
    private:
      F1 f1;
      F2 f2;

    public:
      hybrj_functor(const F1& f1_param, const F2& f2_param) {
        f1 = f1_param;
        f2 = f2_param;
      }


      int operator()(const Eigen::VectorXd &x, Eigen::VectorXd &fvec) {
        fvec = f1(x);
        return 0;
      }
      int df(const Eigen::VectorXd &x, Eigen::MatrixXd &fjac) {
        fjac = f2(x);
        return 0;
      }
    };

    /**
     * Returns the solution to the specified system of
     * algebraic system given an initial guess and the
     * gradient of the system with respect to the unknowns
     * for which we are trying to solve.
     *
     * @tparam F1 type of equation of algebraic system
     * @tparam F2 type of equation of gradient of algebraic system
     * @param x Vector of starting values
     * @param f1 Functor that evaluates the system of equations
     * @param f2 Functor that evaluates the Jacobian matrix
     * @return Vector that solves the system of equations
     */
    template <typename F1, typename F2>
    inline
    Eigen::VectorXd
    dogleg(const Eigen::VectorXd& x, const F1 f1, const F2 f2) {
      stan::math::hybrj_functor<F1, F2> functor(f1, f2);
      Eigen::HybridNonLinearSolver<hybrj_functor<F1, F2> > solver(functor);
      Eigen::VectorXd theta = x;
      solver.solve(theta);
      return theta;
    }

  }
}
#endif
