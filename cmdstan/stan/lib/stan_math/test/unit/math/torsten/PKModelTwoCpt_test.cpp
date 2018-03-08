#include <gtest/gtest.h>
#include <stan/math/rev/mat.hpp>  // FIX ME - include should be more specific
#include <test/unit/math/prim/mat/fun/expect_matrix_eq.hpp>
#include <test/unit/math/torsten/util_PKModelTwoCpt.hpp>
#include <vector>

using std::vector;
using Eigen::Matrix;
using Eigen::Dynamic;

TEST(Torsten, PKModelTwoCpt_MultipleDoses) {

	vector<vector<double> > pMatrix(1);
	pMatrix[0].resize(5);
	pMatrix[0][0] = 5;  // CL
	pMatrix[0][1] = 8;  // Q
	pMatrix[0][2] = 20;  // Vc
	pMatrix[0][3] = 70;  // Vp
	pMatrix[0][4] = 1.2;  // ka

  vector<vector<double> > biovar(1);
  biovar[0].resize(3);
  biovar[0][0] = 1;  // F1
  biovar[0][1] = 1;  // F2
  biovar[0][2] = 1;  // F3

  vector<vector<double> > tlag(1);
  tlag[0].resize(3);
  tlag[0][0] = 0;  // tlag1
  tlag[0][1] = 0;  // tlag2
  tlag[0][2] = 0;  // tlag3

	vector<double> time(10);
	time[0] = 0.0;
	for(int i = 1; i < 9; i++) time[i] = time[i - 1] + 0.25;
	time[9] = 4.0;

	vector<double> amt(10, 0);
	amt[0] = 1000;

	vector<double> rate(10, 0);

	vector<int> cmt(10, 2);
	cmt[0] = 1;

	vector<int> evid(10, 0);
	evid[0] = 1;

	vector<double> ii(10, 0);
	ii[0] = 12;
	
	vector<int> addl(10, 0);
	addl[0] = 14;
	
	vector<int> ss(10, 0);

	Matrix<double, Dynamic, Dynamic> x;
	x = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                   pMatrix, biovar, tlag);

	Matrix<double, Dynamic, Dynamic> amounts(10, 3);
	amounts << 1000.0, 0.0, 0.0,
			   740.818221, 238.3713, 12.75775,
			   548.811636, 379.8439, 43.55827,
			   406.569660, 455.3096, 83.95657,
			   301.194212, 486.6965, 128.32332,
			   223.130160, 489.4507, 173.01118,
			   165.298888, 474.3491, 215.75441,
			   122.456428, 448.8192, 255.23842,
			   90.717953, 417.9001, 290.79297,
			   8.229747, 200.8720, 441.38985;

	expect_matrix_eq(amounts, x);

	// Test AutoDiff against FiniteDiff
  // test_PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
  //                  pMatrix, biovar, tlag, 1e-8, 1e-4);

}

TEST(Torsten, PKModelTwoCpt_MultipleDoses_overload) {
  
  vector<vector<double> > pMatrix(1);
  pMatrix[0].resize(5);
  pMatrix[0][0] = 5;  // CL
  pMatrix[0][1] = 8;  // Q
  pMatrix[0][2] = 20;  // Vc
  pMatrix[0][3] = 70;  // Vp
  pMatrix[0][4] = 1.2;  // ka
  
  vector<vector<double> > biovar(1);
  biovar[0].resize(3);
  biovar[0][0] = 1;  // F1
  biovar[0][1] = 1;  // F2
  biovar[0][2] = 1;  // F3
  
  vector<vector<double> > tlag(1);
  tlag[0].resize(3);
  tlag[0][0] = 0;  // tlag1
  tlag[0][1] = 0;  // tlag2
  tlag[0][2] = 0;  // tlag3
  
  vector<double> time(10);
  time[0] = 0.0;
  for(int i = 1; i < 9; i++) time[i] = time[i - 1] + 0.25;
  time[9] = 4.0;
  
  vector<double> amt(10, 0);
  amt[0] = 1000;
  
  vector<double> rate(10, 0);
  
  vector<int> cmt(10, 2);
  cmt[0] = 1;
  
  vector<int> evid(10, 0);
  evid[0] = 1;
  
  vector<double> ii(10, 0);
  ii[0] = 12;
  
  vector<int> addl(10, 0);
  addl[0] = 14;
  
  vector<int> ss(10, 0);

  Matrix<double, Dynamic, Dynamic> x_122, x_112, x_111, x_121, x_212,
    x_211, x_221;
  x_122 = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                        pMatrix[0], biovar, tlag);
  x_112 = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                        pMatrix[0], biovar[0], tlag);
  x_111 = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                        pMatrix[0], biovar[0], tlag[0]);
  x_121 = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                        pMatrix[0], biovar, tlag[0]);
  x_212 = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                        pMatrix, biovar[0], tlag);
  x_211 = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                        pMatrix, biovar[0], tlag[0]);
  x_221 = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                        pMatrix, biovar, tlag[0]);

  Matrix<double, Dynamic, Dynamic> amounts(10, 3);
  amounts << 1000.0, 0.0, 0.0,
             740.818221, 238.3713, 12.75775,
             548.811636, 379.8439, 43.55827,
             406.569660, 455.3096, 83.95657,
             301.194212, 486.6965, 128.32332,
             223.130160, 489.4507, 173.01118,
             165.298888, 474.3491, 215.75441,
             122.456428, 448.8192, 255.23842,
             90.717953, 417.9001, 290.79297,
             8.229747, 200.8720, 441.38985;

  expect_matrix_eq(amounts, x_122);
  expect_matrix_eq(amounts, x_112);
  expect_matrix_eq(amounts, x_111);
  expect_matrix_eq(amounts, x_121);
  expect_matrix_eq(amounts, x_212);
  expect_matrix_eq(amounts, x_211);
  expect_matrix_eq(amounts, x_221);

  // CHECK - do I need an AD test for every function signature ?
}

TEST(Torsten, PKModelTwoCpt_signature_test) {
  using stan::math::var;

  vector<vector<double> > pMatrix(1);
  pMatrix[0].resize(5);
  pMatrix[0][0] = 5;  // CL
  pMatrix[0][1] = 8;  // Q
  pMatrix[0][2] = 20;  // Vc
  pMatrix[0][3] = 70;  // Vp
  pMatrix[0][4] = 1.2;  // ka
  
  vector<vector<double> > biovar(1);
  biovar[0].resize(3);
  biovar[0][0] = 1;  // F1
  biovar[0][1] = 1;  // F2
  biovar[0][2] = 1;  // F3
  
  vector<vector<double> > tlag(1);
  tlag[0].resize(3);
  tlag[0][0] = 0;  // tlag1
  tlag[0][1] = 0;  // tlag2
  tlag[0][2] = 0;  // tlag3
  
  vector<vector<var> > pMatrix_v(1);
  pMatrix_v[0].resize(5);
  pMatrix_v[0][0] = 5;  // CL
  pMatrix_v[0][1] = 8;  // Q
  pMatrix_v[0][2] = 20;  // Vc
  pMatrix_v[0][3] = 70;  // Vp
  pMatrix_v[0][4] = 1.2;  // ka
  
  vector<vector<var> > biovar_v(1);
  biovar_v[0].resize(3);
  biovar_v[0][0] = 1;  // F1
  biovar_v[0][1] = 1;  // F2
  biovar_v[0][2] = 1;  // F3
  
  vector<vector<var> > tlag_v(1);
  tlag_v[0].resize(3);
  tlag_v[0][0] = 0;  // tlag 1
  tlag_v[0][1] = 0;  // tlag 2
  tlag_v[0][2] = 0;  // tlag 3
  
  vector<double> time(10);
  time[0] = 0.0;
  for(int i = 1; i < 9; i++) time[i] = time[i - 1] + 0.25;
  time[9] = 4.0;
  
  vector<double> amt(10, 0);
  amt[0] = 1000;
  
  vector<double> rate(10, 0);
  
  vector<int> cmt(10, 2);
  cmt[0] = 1;
  
  vector<int> evid(10, 0);
  evid[0] = 1;
  
  vector<double> ii(10, 0);
  ii[0] = 12;
  
  vector<int> addl(10, 0);
  addl[0] = 14;
  
  vector<int> ss(10, 0);
  
  Matrix<double, Dynamic, Dynamic> amounts(10, 3);
  amounts << 1000.0, 0.0, 0.0,
             740.818221, 238.3713, 12.75775,
             548.811636, 379.8439, 43.55827,
             406.569660, 455.3096, 83.95657,
             301.194212, 486.6965, 128.32332,
             223.130160, 489.4507, 173.01118,
             165.298888, 474.3491, 215.75441,
             122.456428, 448.8192, 255.23842,
             90.717953, 417.9001, 290.79297,
             8.229747, 200.8720, 441.38985;

  vector<Matrix<var, Dynamic, Dynamic> > x_122(7);
  x_122[0] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar, tlag);
  x_122[1] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v, tlag);
  x_122[2] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar, tlag_v);
  x_122[3] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v, tlag_v);
  x_122[4] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v, tlag);
  x_122[5] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v, tlag_v);
  x_122[6] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar, tlag_v);

  for (size_t i = 0; i < x_122.size(); i++)
    for (int j = 0; j < x_122[i].rows(); j++)
      for (int k = 0; k < x_122[i].cols(); k++)
        EXPECT_FLOAT_EQ(amounts(j, k), x_122[i](j, k).val());


  vector<Matrix<var, Dynamic, Dynamic> > x_112(7);
  x_112[0] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar[0], tlag);
  x_112[1] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v[0], tlag);
  x_112[2] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar[0], tlag_v);
  x_112[3] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v[0], tlag_v);
  x_112[4] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v[0], tlag);
  x_112[5] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v[0], tlag_v);
  x_112[6] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar[0], tlag_v);
  
  for (size_t i = 0; i < x_112.size(); i++)
    for (int j = 0; j < x_112[i].rows(); j++)
      for (int k = 0; k < x_112[i].cols(); k++)
        EXPECT_FLOAT_EQ(amounts(j, k), x_112[i](j, k).val());


  vector<Matrix<var, Dynamic, Dynamic> > x_121(7);
  x_121[0] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar, tlag[0]);
  x_121[1] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v, tlag[0]);
  x_121[2] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar, tlag_v[0]);
  x_121[3] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v, tlag_v[0]);
  x_121[4] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v, tlag[0]);
  x_121[5] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v, tlag_v[0]);
  x_121[6] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar, tlag_v[0]);
  
  for (size_t i = 0; i < x_121.size(); i++)
    for (int j = 0; j < x_121[i].rows(); j++)
      for (int k = 0; k < x_121[i].cols(); k++)
        EXPECT_FLOAT_EQ(amounts(j, k), x_121[i](j, k).val());

  
  vector<Matrix<var, Dynamic, Dynamic> > x_111(7);
  x_111[0] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar[0], tlag[0]);
  x_111[1] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v[0], tlag[0]);
  x_111[2] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar[0], tlag_v[0]);
  x_111[3] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v[0], biovar_v[0], tlag_v[0]);
  x_111[4] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v[0], tlag[0]);
  x_111[5] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar_v[0], tlag_v[0]);
  x_111[6] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix[0], biovar[0], tlag_v[0]);
  
  for (size_t i = 0; i < x_111.size(); i++)
    for (int j = 0; j < x_111[i].rows(); j++)
      for (int k = 0; k < x_111[i].cols(); k++)
        EXPECT_FLOAT_EQ(amounts(j, k), x_111[i](j, k).val());


  vector<Matrix<var, Dynamic, Dynamic> > x_212(7);
  x_212[0] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar[0], tlag);
  x_212[1] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar_v[0], tlag);
  x_212[2] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar[0], tlag_v);
  x_212[3] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar_v[0], tlag_v);
  x_212[4] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar_v[0], tlag);
  x_212[5] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar_v[0], tlag_v);
  x_212[6] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar[0], tlag_v);
  
  for (size_t i = 0; i < x_212.size(); i++)
    for (int j = 0; j < x_212[i].rows(); j++)
      for (int k = 0; k < x_212[i].cols(); k++)
        EXPECT_FLOAT_EQ(amounts(j, k), x_212[i](j, k).val());


  vector<Matrix<var, Dynamic, Dynamic> > x_211(7);
  x_211[0] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar[0], tlag[0]);
  x_211[1] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar_v[0], tlag[0]);
  x_211[2] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar[0], tlag_v[0]);
  x_211[3] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar_v[0], tlag_v[0]);
  x_211[4] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar_v[0], tlag[0]);
  x_211[5] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar_v[0], tlag_v[0]);
  x_211[6] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar[0], tlag_v[0]);
  
  for (size_t i = 0; i < x_211.size(); i++)
    for (int j = 0; j < x_211[i].rows(); j++)
      for (int k = 0; k < x_211[i].cols(); k++)
        EXPECT_FLOAT_EQ(amounts(j, k), x_211[i](j, k).val());


  vector<Matrix<var, Dynamic, Dynamic> > x_221(7);
  x_221[0] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar, tlag[0]);
  x_221[1] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar_v, tlag[0]);
  x_221[2] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar, tlag_v[0]);
  x_221[3] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix_v, biovar_v, tlag_v[0]);
  x_221[4] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar_v, tlag[0]);
  x_221[5] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar_v, tlag_v[0]);
  x_221[6] = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                           pMatrix, biovar, tlag_v[0]);
  
  for (size_t i = 0; i < x_221.size(); i++)
    for (int j = 0; j < x_221[i].rows(); j++)
      for (int k = 0; k < x_221[i].cols(); k++)
        EXPECT_FLOAT_EQ(amounts(j, k), x_221[i](j, k).val());  

  // CHECK - do I need an AD test for every function signature ?
}

TEST(Torsten, PKModelTwoCpt_SS) {

  vector<vector<double> > pMatrix(1);
  pMatrix[0].resize(5);
  pMatrix[0][0] = 5;  // CL
  pMatrix[0][1] = 8;  // Q
  pMatrix[0][2] = 20;  // Vc
  pMatrix[0][3] = 70;  // Vp
  pMatrix[0][4] = 1.2;  // ka

  vector<vector<double> > biovar(1);
  biovar[0].resize(3);
  biovar[0][0] = 1;  // F1
  biovar[0][1] = 1;  // F2
  biovar[0][2] = 1;  // F3

  vector<vector<double> > tlag(1);
  tlag[0].resize(3);
  tlag[0][0] = 0;  // tlag1
  tlag[0][1] = 0;  // tlag2
  tlag[0][2] = 0;  // tlag3

	vector<double> time(10);
	time[0] = 0.0;
	time[1] = 0.0;
	for(int i = 2; i < 10; i++) time[i] = time[i - 1] + 5;

	vector<double> amt(10, 0);
	amt[0] = 1200;

	vector<double> rate(10, 0);

	vector<int> cmt(10, 2);
	cmt[0] = 1;

	vector<int> evid(10, 0);
	evid[0] = 1;

	vector<double> ii(10, 0);
	ii[0] = 12;

	vector<int> addl(10, 0);
	addl[0] = 10;

	vector<int> ss(10, 0);
	ss[0] = 1;

	Matrix<double, Dynamic, Dynamic> x;
	x = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                   pMatrix, biovar, tlag);

	Matrix<double, Dynamic, Dynamic> amounts(10, 3);
	amounts << 1.200001e+03, 224.5332, 1196.900,
	           1.200001e+03, 224.5332, 1196.900, 
	           2.974504e+00, 360.2587, 1533.000,
	           7.373059e-03, 244.3668, 1294.140,
	           3.278849e+01, 548.9136, 1534.479,
	           8.127453e-02, 270.3431, 1396.353,
	           3.614333e+02, 799.6771, 1304.769,
	           8.959035e-01, 316.6314, 1494.540,
	           2.220723e-03, 234.0179, 1244.718,
	           9.875702e+00, 432.4698, 1552.220;

	for(int i = 0; i < amounts.rows(); i++) {
		EXPECT_NEAR(amounts(i, 0), x(i, 0), std::max(amounts(i, 0), x(i, 0)) * 1e-6);
		EXPECT_NEAR(amounts(i, 1), x(i, 1), std::max(amounts(i, 1), x(i, 1)) * 1e-6);
	}

	// Test AutoDiff against FiniteDiff
  test_PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                    pMatrix, biovar, tlag, 1e-8, 2e-4);
}


TEST(Torsten, PKModelTwoCpt_SS_rate) {
	
	vector<vector<double> > pMatrix(1);
  pMatrix[0].resize(5);
  pMatrix[0][0] = 5;  // CL
  pMatrix[0][1] = 8;  // Q
  pMatrix[0][2] = 20;  // Vc
  pMatrix[0][3] = 70;  // Vp
  pMatrix[0][4] = 1.2;  // ka
  
  vector<vector<double> > biovar(1);
  biovar[0].resize(3);
  biovar[0][0] = 1;  // F1
  biovar[0][1] = 1;  // F2
  biovar[0][2] = 1;  // F3
  
  vector<vector<double> > tlag(1);
  tlag[0].resize(3);
  tlag[0][0] = 0;  // tlag1
  tlag[0][1] = 0;  // tlag2
  tlag[0][2] = 0;  // tlag3

	vector<double> time(10);
	time[0] = 0.0;
	time[1] = 0.0;
	for(int i = 2; i < 10; i++) time[i] = time[i - 1] + 5;

	vector<double> amt(10, 0);
	amt[0] = 1200;

	vector<double> rate(10, 0);
	rate[0] = 150;

	vector<int> cmt(10, 2);
	cmt[0] = 1;

	vector<int> evid(10, 0);
	evid[0] = 1;

	vector<double> ii(10, 0);
	ii[0] = 12;

	vector<int> addl(10, 0);
	addl[0] = 10;

	vector<int> ss(10, 0);
	ss[0] = 1;

	Matrix<double, Dynamic, Dynamic> x;
	x = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                   pMatrix, biovar, tlag);

	Matrix<double, Dynamic, Dynamic> amounts(10, 3);
	amounts << 1.028649, 286.5656, 1391.610,
	           1.028649, 286.5656, 1391.610,
	           124.692706, 452.4021, 1377.667,
	           11.338982, 367.1773, 1461.416,
	           121.612641, 410.2024, 1340.203,
	           124.991604, 477.3286, 1452.499,
	           87.660547, 315.1768, 1352.746,
	           124.907445, 463.2236, 1402.095,
	           3.415236, 318.7214, 1432.451,
	           123.979747, 436.1057, 1355.890;

	for(int i = 0; i < amounts.rows(); i++) {
		EXPECT_NEAR(amounts(i, 0), x(i, 0), std::max(amounts(i, 0), x(i, 0)) * 1e-6);
		EXPECT_NEAR(amounts(i, 1), x(i, 1), std::max(amounts(i, 1), x(i, 1)) * 1e-6);
	}

	// Test AutoDiff against FiniteDiff
    test_PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                      pMatrix, biovar, tlag, 1e-8, 2e-4);
}

TEST(Torsten, PKModelTwoCpt_MultipleDoses_timePara) {

  int nEvent = 11;
	vector<vector<double> > pMatrix(nEvent);
	for (int i = 0; i < nEvent; i++) {
	  pMatrix[i].resize(5);
	  if (i < 6) pMatrix[i][0] = 5; // CL
	  else pMatrix[i][0] = 50;  // CL is piece-wise constant
	  pMatrix[i][1] = 8;  // Q
	  pMatrix[i][2] = 20;  // Vc
	  pMatrix[i][3] = 70;  // Vp
	  pMatrix[i][4] = 1.2;  // ka
	}
	
	vector<vector<double> > biovar(1);
	biovar[0].resize(3);
	biovar[0][0] = 1;  // F1
	biovar[0][1] = 1;  // F2
	biovar[0][2] = 1;  // F3
	
	vector<vector<double> > tlag(1);
	tlag[0].resize(3);
	tlag[0][0] = 0;  // tlag1
	tlag[0][1] = 0;  // tlag2
	tlag[0][2] = 0;  // tlag3

	vector<double> time(nEvent);
	time[0] = 0.0;
	for(int i = 1; i < nEvent; i++) time[i] = time[i - 1] + 2.5;

	vector<double> amt(nEvent, 0);
	amt[0] = 1000;

	vector<double> rate(nEvent, 0);

	vector<int> cmt(nEvent, 2);
	cmt[0] = 1;

	vector<int> evid(nEvent, 0);
	evid[0] = 1;

	vector<double> ii(nEvent, 0);
	ii[0] = 12;

	vector<int> addl(nEvent, 0);
	addl[0] = 1;

	vector<int> ss(nEvent, 0);

	Matrix<double, Dynamic, Dynamic> x;
	x = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                   pMatrix, biovar, tlag);

	Matrix<double, Dynamic, Dynamic> amounts(nEvent, 3);
	amounts << 1.000000e+03,   0.000000,   0.0000,
			   4.978707e+01, 352.089056, 349.4148,
			   2.478752e+00, 146.871246, 458.3010,
			   1.234098e-01,  93.537648, 442.6420,
			   6.144212e-03,  77.732083, 405.7800,
			   5.488119e+02, 449.105589, 412.0337,
			   2.732374e+01,  36.675537, 430.0023,
			   1.360369e+00,  14.886990, 341.6754,
			   6.772877e-02,  10.966107, 267.7033,
			   3.372017e-03,   8.549649, 209.5604,
			   1.678828e-04,   6.690631, 164.0364;

	expect_matrix_eq(amounts, x);

	// Test AutoDiff against FiniteDiff
  test_PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                    pMatrix, biovar, tlag, 1e-8, 1e-4);
}

TEST(Torsten, PKModelTwoCptModel_Rate) {
  using std::vector;

  vector<vector<double> > pMatrix(1);
  pMatrix[0].resize(5);
  pMatrix[0][0] = 5;  // CL
  pMatrix[0][1] = 8;  // Q
  pMatrix[0][2] = 35;  // Vc
  pMatrix[0][3] = 105;  // Vp
  pMatrix[0][4] = 1.2;  // ka
  
  vector<vector<double> > biovar(1);
  biovar[0].resize(3);
  biovar[0][0] = 1;  // F1
  biovar[0][1] = 1;  // F2
  biovar[0][2] = 1;  // F3
  
  vector<vector<double> > tlag(1);
  tlag[0].resize(3);
  tlag[0][0] = 0;  // tlag1
  tlag[0][1] = 0;  // tlag2
  tlag[0][2] = 0;  // tlag3

  vector<double> time(10);
  time[0] = 0;
  for(int i = 1; i < 9; i++) time[i] = time[i - 1] + 0.25;
  time[9] = 4.0;

  vector<double> amt(10, 0);
  amt[0] = 1200;

  vector<double> rate(10, 0);
  rate[0] = 1200;

  vector<int> cmt(10, 2);
  cmt[0] = 1;

  vector<int> evid(10, 0);
  evid[0] = 1;

  vector<double> ii(10, 0);
  ii[0] = 12;

  vector<int> addl(10, 0);
  addl[0] = 14;

  vector<int> ss(10, 0);

  Matrix<double, Dynamic, Dynamic> x;
  x = torsten::PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                    pMatrix, biovar, tlag);

  Matrix<double, Dynamic, Dynamic> amounts(10, 3);
  amounts << 0.00000,   0.00000,   0.0000000,
             259.18178,  39.55748,   0.7743944,
             451.18836, 139.65573,   5.6130073,
             593.43034, 278.43884,  17.2109885,
             698.80579, 440.32663,  37.1629388,
             517.68806, 574.76950,  65.5141658,
             383.51275, 653.13596,  99.2568509,
             284.11323, 692.06145, 135.6122367,
             210.47626, 703.65965, 172.6607082,
             19.09398, 486.11014, 406.6342765;

  expect_matrix_eq(amounts, x);

  // Test AutoDiff against FiniteDiff
  test_PKModelTwoCpt(time, amt, rate, ii, evid, cmt, addl, ss,
                     pMatrix, biovar, tlag, 1e-8, 5e-4);
}
