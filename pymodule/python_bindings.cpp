
// #include <pybind11/pybind11.h>
// #include <pybind11/stl.h>
#include </Library/Python/3.7m/include/pybind11/pybind11.h>
#include </Library/Python/3.7m/include/pybind11/stl.h>
#include "../src/VBBinaryLensingLibrary.h"
#include "../src/TripleLensingLibrary.h"
#include <string>

namespace py = pybind11;


TripleLensing TRIL;
// // Declaration of an instance to VBBinaryLensing class.
// VBBinaryLensing VBBL;

PYBIND11_MODULE(TripleLensing, m) {
    py::options options;
    options.disable_function_signatures();
    py::class_<TripleLensing>(m, "TripleLensing")
    .def(py::init())

    .def_readwrite("secnum", &TripleLensing::secnum,
                   "divide source boundary into how many parts.")
    .def_readwrite("basenum", &TripleLensing::basenum,
                   "how many points in each part.")
    .def_readwrite("nphi", &TripleLensing::nphi,
                   "how many points to start.")
    .def_readwrite("quaderr_Tol", &TripleLensing::quaderr_Tol,
                   "Tolerance of quadrupole test.")
    .def_readwrite("muPS", &TripleLensing::muPS,
                   "Tolerance of quadrupole test.")
    .def_readwrite("relerr_mag", &TripleLensing::relerr_mag,
                   "Tolerance of quadrupole test.")
    .def_readwrite("relerr_mag", &TripleLensing::RelTolLimb,
                   "Tolerance of quadrupole test.")
    .def_readwrite("relerr_mag", &TripleLensing::AbsTolLimb,
                   "Tolerance of quadrupole test.")

    // .def("TripleMag",
    // [](TripleLensing & self, std::vector<double> mlens, std::vector<double> zlens, double xsCenter, double ysCenter, double rs) {
    //     double mu;
    //     mu = self.tripleFS2python(mlens.data(), zlens.data(), xsCenter, ysCenter, rs);
    //     return mu;
    // },
    // R"mydelimiter(
    //         outputCriticalTriple_list
    //         )mydelimiter")

    // .def("reset",
    // [](TripleLensing & self, std::vector<double> mlens, std::vector<double> zlens) {
    //     self.reset2(mlens.data(), zlens.data());
    // },
    // R"mydelimiter(
    //         outputCriticalTriple_list
    //         )mydelimiter")

    .def("solv_lens_equation",
         [](TripleLensing & self, std::vector<double> mlens, std::vector<double> zlens,
            double xs, double ys, int nlens )
    {
        std::vector<double> zrxy( (nlens * nlens + 1) * 2 );
        self.solv_lens_equation(zrxy.data(), mlens.data(), zlens.data(), xs, ys, nlens
                               );
        return zrxy;
    },
    R"mydelimiter(
            solv_lens_equation
            )mydelimiter")

    .def("outputCriticalTriple_list",
         [](TripleLensing & self, std::vector<double> mlens, std::vector<double> zlens, int nlens, int NPS )
    {
        std::vector<double> allxys(NPS * 40);
        // std::vector<double> allxys(NPS*4+2);
        self.outputCriticalTriple_list(allxys.data(), mlens.data(), zlens.data(), nlens, NPS);
        return allxys;
    },
    R"mydelimiter(
            outputCriticalTriple_list
            )mydelimiter")

    // double mlens[], double Zlens[], double xsCenters[], double ysCenters[], double rs, int secnum, int basenum, double quaderr_Tol,double mags[], int Np
    .def("TriLightCurve",
         [](TripleLensing & self, std::vector<double> mlens,std::vector<double> Zlens,
            std::vector<double> y1s, std::vector<double> y2s, double rs, int secnum, int basenum, double quaderr_Tol,double relerr_mag)
    {
        std::vector<double> mags(y1s.size());
        self.tripleFS2py(mlens.data(),Zlens.data(),
                           y1s.data(), y2s.data(), rs, secnum, basenum, quaderr_Tol, relerr_mag, mags.data(), y1s.size());
        return mags;
    },
    R"mydelimiter(
            Static triple lens light curve for a given set of parameters.
            Uses the TripleMag function.

            Parameters
            ----------)mydelimiter")

    .def("TriLightCurveLimb",
         [](TripleLensing & self, std::vector<double> mlens,std::vector<double> Zlens,
            std::vector<double> y1s, std::vector<double> y2s, double rs, int secnum, int basenum, double quaderr_Tol,double relerr_mag,double RelTolLimb, double AbsTolLimb, double limba1)
    {
        std::vector<double> mags(y1s.size());
        self.tripleFSLimb2py(mlens.data(),Zlens.data(),
                           y1s.data(), y2s.data(), rs, secnum, basenum, quaderr_Tol, relerr_mag, mags.data(), y1s.size(), limba1, RelTolLimb, AbsTolLimb);
        return mags;
    },
    R"mydelimiter(
            Static triple lens light curve for a given set of parameters.
            Uses the TripleMag function.

            Parameters
            ----------)mydelimiter")

    ;

}