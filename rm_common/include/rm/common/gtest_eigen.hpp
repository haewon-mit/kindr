/*
 * gtest_eigen.hpp
 *
 *  Created on: Nov 20, 2013
 *      Author: gech
 */

#ifndef GTEST_EIGEN_HPP_
#define GTEST_EIGEN_HPP_

#include <gtest/gtest.h>
#include <rm/common/source_file_pos.hpp>
#include <rm/common/assert_macros_eigen.hpp>
#include <Eigen/Core>

namespace rm { namespace eigen {


//    template<int N>
//    Eigen::Matrix<double,N,N> randomCovariance()
//    {
//      Eigen::Matrix<double,N,N> U;
//      U.setRandom();
//      return U.transpose() * U + 5.0 * Eigen::Matrix<double,N,N>::Identity();
//    }
//
//
//    inline Eigen::MatrixXd randomCovarianceXd(int N)
//    {
//        Eigen::MatrixXd U(N,N);
//        U.setRandom();
//        return U.transpose() * U + 5.0 * Eigen::MatrixXd::Identity(N,N);
//    }



    template<typename M1, typename M2>
    void assertEqual(const M1 & A, const M2 & B, rm::source_file_pos const & sfp, std::string const & message = "")
    {
        ASSERT_EQ((size_t)A.rows(),(size_t)B.rows()) << message << "\nMatrix A:\n" << A << "\nand matrix B\n" << B << "\nare not the same\n" << sfp.toString();
      ASSERT_EQ((size_t)A.cols(),(size_t)B.cols()) << message << "\nMatrix A:\n" << A << "\nand matrix B\n" << B << "\nare not the same\n" << sfp.toString();

      for(int r = 0; r < A.rows(); r++)
    {
      for(int c = 0; c < A.cols(); c++)
      {
        ASSERT_EQ(A(r,c),B(r,c)) << message << "\nEquality comparison failed at (" << r << "," << c << ")\n" << sfp.toString()
                                       << "\nMatrix A:\n" << A << "\nand matrix B\n" << B;
      }
    }
    }


    template<typename M1, typename M2, typename T>
    void assertNear(const M1 & A, const M2 & B, T tolerance, rm::source_file_pos const & sfp, std::string const & message = "")
    {
      // Note: If these assertions fail, they only abort this subroutine.
      // see: http://code.google.com/p/googletest/wiki/AdvancedGuide#Using_Assertions_in_Sub-routines
      // \todo better handling of this
        ASSERT_EQ((size_t)A.rows(),(size_t)B.rows()) << message << "\nMatrix A:\n" << A << "\nand matrix B\n" << B << "\nare not the same\n" << sfp.toString();
      ASSERT_EQ((size_t)A.cols(),(size_t)B.cols()) << message << "\nMatrix A:\n" << A << "\nand matrix B\n" << B << "\nare not the same\n" << sfp.toString();

      for(int r = 0; r < A.rows(); r++)
    {
      for(int c = 0; c < A.cols(); c++)
      {
        ASSERT_NEAR(A(r,c),B(r,c),tolerance) << message << "\nTolerance comparison failed at (" << r << "," << c << ")\n" << sfp.toString()
                           << "\nMatrix A:\n" << A << "\nand matrix B\n" << B;
      }
    }
    }

    template<typename M1, typename M2, typename T>
    void expectNear(const M1 & A, const M2 & B, T tolerance, rm::source_file_pos const & sfp, std::string const & message = "")
    {
      EXPECT_EQ((size_t)A.rows(),(size_t)B.rows()) << message << "\nMatrix A:\n" << A << "\nand matrix B\n" << B << "\nare not the same\n" << sfp.toString();
      EXPECT_EQ((size_t)A.cols(),(size_t)B.cols()) << message << "\nMatrix A:\n" << A << "\nand matrix B\n" << B << "\nare not the same\n" << sfp.toString();

      for(int r = 0; r < A.rows(); r++)
        {
          for(int c = 0; c < A.cols(); c++)
            {
              EXPECT_NEAR(A(r,c),B(r,c),tolerance) << message << "\nTolerance comparison failed at (" << r << "," << c << ")\n" << sfp.toString()
                           << "\nMatrix A:\n" << A << "\nand matrix B\n" << B;
            }
        }
    }


    template<typename M1>
    void assertFinite(const M1 & A, rm::source_file_pos const & sfp, std::string const & message = "")
    {
      for(int r = 0; r < A.rows(); r++)
    {
      for(int c = 0; c < A.cols(); c++)
      {
        ASSERT_TRUE(std::isfinite(A(r,c))) << sfp.toString() << std::endl << "Check for finite values failed at A(" << r << "," << c << "). Matrix A:" << std::endl << A << std::endl;
      }
    }
    }


#define ASSERT_DOUBLE_MX_EQ(A, B, PERCENT_TOLERANCE, MSG)       \
    ASSERT_EQ((size_t)(A).rows(), (size_t)(B).rows())  << MSG << "\nMatrix " << #A << ":\n" << A << "\nand matrix " << #B << "\n" << B << "\nare not the same size"; \
    ASSERT_EQ((size_t)(A).cols(), (size_t)(B).cols())  << MSG << "\nMatrix " << #A << ":\n" << A << "\nand matrix " << #B << "\n" << B << "\nare not the same size"; \
    for(int r = 0; r < (A).rows(); r++)                 \
      {                                 \
    for(int c = 0; c < (A).cols(); c++)               \
      {                               \
      double percentError = 0.0;                  \
      ASSERT_TRUE(rm::eigen::compareRelative( (A)(r,c), (B)(r,c), PERCENT_TOLERANCE, &percentError)) \
        << MSG << "\nComparing:\n"                \
        << #A << "(" << r << "," << c << ") = " << (A)(r,c) << std::endl \
        << #B << "(" << r << "," << c << ") = " << (B)(r,c) << std::endl \
        << "Error was " << percentError << "% > " << PERCENT_TOLERANCE << "%\n" \
        << "\nMatrix " << #A << ":\n" << A << "\nand matrix " << #B << "\n" << B; \
      }                               \
      }





  }} // namespace rm::eigen



#endif /* GTEST_EIGEN_HPP_ */