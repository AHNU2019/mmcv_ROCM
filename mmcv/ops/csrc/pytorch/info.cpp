// modified from
// https://github.com/facebookresearch/detectron2/blob/master/detectron2/layers/csrc/vision.cpp
#include "pytorch_cpp_helper.hpp"

#ifdef MMCV_WITH_CUDA

#ifdef __NVCC__
#include <cuda_runtime_api.h>
int get_cudart_version() { return CUDART_VERSION; }
#endif

#ifdef __HIP_PLATFORM_HCC__
#include <hip/hip_version.h>
int get_hiprt_version() { return HIP_VERSION; }
#endif

#endif

std::string get_compiling_cuda_version() {
#ifdef MMCV_WITH_CUDA
  std::ostringstream oss;
  // copied from
  // https://github.com/pytorch/pytorch/blob/master/aten/src/ATen/cuda/detail/CUDAHooks.cpp#L231
  auto printCudaStyleVersion = [&](int v) {
    oss << (v / 1000) << "." << (v / 10 % 100);
    if (v % 10 != 0) {
      oss << "." << (v % 10);
    }
  };
#ifdef __NVCC__
  printCudaStyleVersion(get_cudart_version());
#endif

#ifdef __HIP_PLATFORM_HCC__
  printCudaStyleVersion(get_hiprt_version());
#endif

  return oss.str();
#else
  return std::string("not available");
#endif
}

// similar to
// https://github.com/pytorch/pytorch/blob/master/aten/src/ATen/Version.cpp
std::string get_compiler_version() {
  std::ostringstream ss;
#if defined(__GNUC__)
#ifndef __clang__
  { ss << "GCC " << __GNUC__ << "." << __GNUC_MINOR__; }
#endif
#endif

#if defined(__clang_major__)
  {
    ss << "clang " << __clang_major__ << "." << __clang_minor__ << "."
       << __clang_patchlevel__;
  }
#endif

#if defined(_MSC_VER)
  { ss << "MSVC " << _MSC_FULL_VER; }
#endif
  return ss.str();
}
